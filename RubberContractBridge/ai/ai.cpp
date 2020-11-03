#include "ai.h"

//TLDR add edge statement to check if ai is very first round opening
//the generate card function will be archaic, might use it in the future to improve selection but for demo only consider dummy hand and my hand
//Further my AI is greedy so will only look in current position best move np heuristics nor probability (yet????)
//Why errors on switches still??????
using namespace std;

AI::AI(QObject *parent)
{
}
void AI::message(QString source, QString message)
{
//meep
}
void AI::notifyBidTurn()
{
//assuming this tells AI to make a bid suggestion
    initialBidSet();
    Bid made;
    made = guessBid();
    emit bidSelected(made);
}
void AI::notifyMoveTurn()
{
//assuming this tells AI to make a move suggestion
    initialMainSet();
    Card maker;
    maker=guessMove();
    cardRecovered = maker;
    emit moveSelected(maker);
}
void AI::updateGameState(PlayerGameState gameState)
{
    currentState=gameState;
}
void AI::notifyBidRejected(QString reason)
{
    //assuming rejects so redo bid move
    //quite hard to recover this state
    //thus pick random number between 0 and 10 in the list of bid if possible
    //pop the last bid from bid list
    generatebidlist();
    removebids();
    //if I fail when I call a pass then I dunno what to do
    //Is that possible?
    if (bidMade.getCall()!=PASS)
    {
        for (int i = 0 ;i<bidlist.length();i++)
        {
            if (bidMade==bidlist.value(i))
            {
                bidlist.remove(i);
            }
        }
    }
    int seed = time(0);
    int number;
    if (bidlist.length()<=10 && bidlist.length() > 0)
    {
        number = random(seed) % bidlist.length();
    }
    else
    {
        number = random(seed) % 10;
    }
    Bid made;
    made = bidlist.value(number);
    bidRecovered = made;
    emit bidSelected(made);
}
void AI::notifyMoveRejected(QString reason)
{
    //assuming rejects so redo move?
    //shouldn't ever happen if does spot
    //When move is made that move is saved, initial hand is generated from gamestate thus that should still stay the same after
    //this function is called. All that needs doing is removing card that caused the error from the hand and making
    // a new suggested move

    // TEMP FIX 1 START: Trying to play from own hand when player needs to play from dummy hand
    // Check if the player needs to play and play a random card from the dummy's hand
    if(currentState.getHandToPlay() == currentState.getDummy()){
        emit moveSelected(currentState.getDummyHand().getCard(rand() % currentState.getDummyHand().getCardCount()));
        return;
    }
    // TEMP FIX 1 END

    // TEMP FIX 2 START: AI can get into infinite loop of playing the wrong cards over and over
    // Play randomly from hand (won't get stuck in loop as with AI)
    emit moveSelected(currentState.getPlayerHand().getCard(rand() % currentState.getPlayerHand().getCardCount()));
    return;
    // TEMP FIX 2 END

        generateDeckOptions();
        generateAvailableCards();
    for (int i=0;i<canPlay.getCardCount();i++)
    {
        if (canPlay.getCard(i)==cardPlayed)
        {
            canPlay.removeCard(i);
        }
    }
    int size = canPlay.getCardCount();
    int seed = time(0);
    int number = random(seed)%size;
    cardRecovered = canPlay.getCard(number);
    emit moveSelected(cardRecovered);
}
void AI::gameTerminated(QString reason)
{
    //assume game ends so AI destructor

}
void AI::generatedeck()
{
    //does as the name implies. During initial main set prunes selection based upon what was played previously
    //this is used to try and find possible responses from opponent
    deck=CardSet();
    for ( int fooInt = CLUBS ; fooInt != NONE; fooInt++ )
    {
        for (int holder = TWO; holder!= ACE; holder++)
        {
            CardSuit foo = static_cast<CardSuit>(fooInt);
            CardRank fool = static_cast<CardRank>(holder);
            Card dummy = Card(foo,fool);
            deck.addCard(dummy);


        }
    }
    for ( int fooInt = CLUBS ; fooInt != NONE; fooInt++ )
    {
       CardSuit foo = static_cast<CardSuit>(fooInt);
       Card dummy = Card(foo,ACE);
       deck.addCard(dummy);
    }

    deck.orderHand();
}
void AI::generatebidlist()
{
    //Remember to always reset the bidlist upon new generation
    //does as the name implies. During initial main set prunes selection based upon what was played previously
    //this is used to try and find possible bids to be pulled from
    bidlist.clear();
    for (int i=1 ; i<=7 ; i++)
    {
        for ( int fooInt = CLUBS ; fooInt < NONE; fooInt++ )
        {
            CardSuit foo = static_cast<CardSuit>(fooInt);
            Bid dummy = Bid(currentState.getPlayerTurn(),foo,i);
            bidlist.append(dummy);
        }
        Bid dummy = Bid(currentState.getPlayerTurn(),NONE,i);
        bidlist.append(dummy);
    }
}
//removes invalid bids from pool
void AI::removebids()
{
    if(currentState.getCurrentBid() != nullptr){
        currentbid = *currentState.getCurrentBid();
        label:
        for (int i=0;i<bidlist.size();i++)
        {
            if ((currentbid.getTricksAbove()*10+currentbid.getTrumpSuit())>=(bidlist.value(i).getTricksAbove()*10+bidlist.value(i).getTrumpSuit()))
            {
                bidlist.remove(i);
                goto label;
            }
        }
    }
}
//removes impossible cards from pool
void AI::removecards(CardSet handy)
{
    for (int i = 0;i< handy.getCardCount();i++)
    {
        for (int j = 0;j<deck.getCardCount();j++)
        {
            if (handy.getCard(i)==deck.getCard(j))
            {
                deck.removeCard(j);
            }
        }
    }
}

//Generates all possible cards that might be part of opponents hand that can be played
void AI::generateDeckOptions()
{
    generatedeck();
    removecards(myhand);
    if (dummyhand.getCardCount()!=0)
    {
        removecards(dummyhand);
    }
    if (currentState.getTricks().length()!=0)
    {
        for (int i=0;i<currentState.getTricks().length();i++)
        {
            if (currentState.getTricks()[i].getCardCount()!=0)
                removecards(currentState.getTricks()[i]);
        }
    }
    //first check if trump cards are still in circulation
    int amount = 0;
    if (trump!=NONE)
    {
        for (int i = 0;i<deck.getCardCount();i++)
        {
            if (deck.getCard(i).getSuit()!=trump)
            {
                amount++;
            }
        }
    }
    //remove all non trump suits if trump exists
    // also only if a trump is in circulation do we care about this
    if ((trump!=NONE) && (amount!=deck.getCardCount()))
    {
        for (int i = 0;i<deck.getCardCount();i++)
        {
            if (deck.getCard(i).getSuit()!=trump)
            {
                deck.removeCard(i);
            }
        }
    }
}
//initialize the needed variables to play a card
void AI::initialMainSet()
{
    myhand = currentState.getPlayerHand();
    dummyhand = currentState.getDummyHand();
    //assuming the contract bid is all bids that made the contract
    contract = *currentState.getContractBid();
    //get most recent tricks assuming tricks is array of max 4 size arrays of played tricks
    currentTricks = currentState.getTricks().back();
    trump = contract.getTrumpSuit();
    dummypos = currentState.getDummy();
}
void AI::initialBidSet()
{
    if(currentState.getCurrentBid() != nullptr)
        currentbid= *currentState.getCurrentBid();
}
//generates available legal cards that can be selected from the hand
void AI::generateAvailableCards()
{
    //first check if you are playing first round
    if (currentTricks.getCardCount()==0)
    {
        //this is the first card that will be played
        dummyPlay = CardSet();
        canPlay = CardSet();
        Card trickCard;
        qint8 handAmount;
        // if card count goes from 1,2,3,4 gets the recent card played
        handAmount = myhand.getCardCount();
        //check if trump or NT
        if (trump==4)
        {
            //then it is no trump so any card is valid
            dummyPlay=dummyhand;
            canPlay=myhand;
        }
        else
        {
            //a trump is assigned select cards that are trump for player and dummy
            for (int i = 0; i <= handAmount-1; i++)
            {
                if (trump == myhand.getCard(i).getSuit())
                {
                    canPlay.addCard(myhand.getCard(i));
                }
                if (trump == dummyhand.getCard(i).getSuit())
                {
                    dummyPlay.addCard(dummyhand.getCard(i));
                }
            }
            //If can't play trump don't waist cards
            if (canPlay.getCardCount()==0)
            {
                dummyPlay=dummyhand;
                canPlay=myhand;
            }
        }
    }// end if for first move
    else
    {
     //playing after someone
        dummyPlay = CardSet();
        canPlay = CardSet();
        const Card* trickCard;
        qint8 handAmount;
        // if card count goes from 1,2,3,4 gets the recent card played
        trickCard = currentState.getLastCardPlayed();
        handAmount = myhand.getCardCount();
        //check if trump or NT
        if (trump==4)
        {
            //then it is no trump so any card higher than last played is valid for me and dummy
            for (int i = 0; i <= handAmount-1; i++)
            {
                if (*trickCard <myhand.getCard(i))
                {
                    canPlay.addCard(myhand.getCard(i));
                }
                if (*trickCard <dummyhand.getCard(i))
                {
                    dummyPlay.addCard(dummyhand.getCard(i));
                }
            }
            // if none higher were found treat just like every card found
            if (canPlay.getCardCount()==0)
            {
                canPlay=myhand;
            }
            if (dummyPlay.getCardCount()==0)
            {
                 dummyPlay=dummyhand;
            }
        }
        else
        {
            //a trump is assigned select cards that are trump for player and dummy
            for (int i = 0; i <= handAmount-1; i++)
            {
                if ((*trickCard).getSuit() == myhand.getCard(i).getSuit())
                {
                    canPlay.addCard(myhand.getCard(i));
                }
                if ((*trickCard).getSuit() == dummyhand.getCard(i).getSuit())
                {
                    dummyPlay.addCard(dummyhand.getCard(i));
                }

            }

            //If can't play trump don't waist cards
            if (canPlay.getCardCount()==0)
            {

                canPlay=myhand;
            }
            if (dummyPlay.getCardCount()==0)
            {
                 dummyPlay=dummyhand;
            }
        }
        delete trickCard;
    }// end of else for later moves
    //I do trust I needn't check for edge cases where the tricks are full yet I'm called?
}
Card AI::guessMove()
{
    //do intial data processing before card selection
    initialMainSet();
    generateAvailableCards();
    removecards(myhand);
    canPlay.orderHand();
    dummyPlay.orderHand();
    Card suggestion;

    // TEMP FIX START: Trying to play from own hand when player needs to play from dummy hand
    // Check if the player needs to play and play a random card from the dummy's hand
    if(currentState.getHandToPlay() == currentState.getDummy())
        return dummyhand.getCard(rand() % dummyhand.getCardCount());
    // TEMP FIX END

    if ((myhand.getCard(0)==canPlay.getCard(0)) && ((myhand.getCard(myhand.getCardCount()-1)==canPlay.getCard(canPlay.getCardCount()-1))) && (myhand.getCardCount()==canPlay.getCardCount()))
    {
        // this means NT or nothing wins

        if (contract.getTrumpSuit()==NONE)
        {
            //NT
            switch (currentTricks.getCardCount()) {

             case 0:
             {
                     //means I lead
                     if (canPlay.getCard(canPlay.getCardCount()-1)<dummyPlay.getCard(dummyPlay.getCardCount()-1))
                     {
                         //dummy high card so want dummy to win
                         suggestion=canPlay.getCard(0);

                     }
                     else
                     {
                         //I will win and let dummy toss lowest
                         suggestion=canPlay.getCard(canPlay.getCardCount()-1);

                     }
             }
             case 1:
             {
                 //I am first defender no idea what is dummy yet try starve out cards? leave for second defender to win?
                 suggestion=canPlay.getCard(0);

             }
             case 2:
             {
                 //means I lead
                 if (canPlay.getCard(canPlay.getCardCount()-1)<currentTricks.getCard(0))
                 {

                     //My first player played a high card high card so toss lowest
                     suggestion=canPlay.getCard(0);

                 }
                 else
                 {
                     //I will win since left to me
                     suggestion=canPlay.getCard(canPlay.getCardCount()-1);

                 }

             }
             case 3:
             {
                 currentTricks.orderHand();
                 if (canPlay.getCard(canPlay.getCardCount()-1)<currentTricks.getCard(currentTricks.getCardCount()-1))
                 {
                     //can beat this round
                     suggestion=canPlay.getCard(canPlay.getCardCount());
                 }
                 else
                 {
                     //useless gg
                     suggestion=canPlay.getCard(0);
                 }

               }
              default:
            {
                // keep compiler happy
                suggestion=canPlay.getCard(0);

            }

             }
        }
        else
        {
            //nothing works toss out worst card
            suggestion=canPlay.getCard(0);
        }
    }
    else
    {
        //I have trump cards
        switch (currentTricks.getCardCount()) {

         case 0:
         {
                 //means I lead
                 if (canPlay.getCard(canPlay.getCardCount()-1)<dummyPlay.getCard(dummyPlay.getCardCount()-1))
                 {
                     //dummy high card so want dummy to win
                     suggestion=canPlay.getCard(0);

                 }
                 else
                 {
                     if (dummyPlay.getCardCount()==0)
                     {
                         //can't see dummy yet play lowest hope dummy can do it
                         suggestion = canPlay.getCard(0);
                     }
                     else
                     {//I will win and let dummy toss lowest
                     suggestion=canPlay.getCard(canPlay.getCardCount()-1);}

                 }
         }
         case 1:
         {
             //I am first defender check if dummy is visible
            if (dummyPlay.getCardCount()==0)
            {
                //I can't see dummy so try to play low and see what happens
                suggestion=canPlay.getCard(0);
            }
            else
            {
                //I can see the dummy if the dummy has a high card toss low
                if (canPlay.getCard(canPlay.getCardCount()-1)<dummyPlay.getCard(dummyPlay.getCardCount()-1))
                {
                    suggestion=canPlay.getCard(0);

                }
                else
                {
                    //I have a high card not sure what my friend has. RNG will help at and so pick highest
                    suggestion = canPlay.getCard(canPlay.getCardCount()-1);
                }
            }


         }
         case 2:
         {
             //means I lead
             if (canPlay.getCard(canPlay.getCardCount()-1)<currentTricks.getCard(0))
             {

                 //My first player played a high card so toss lowest
                 suggestion=canPlay.getCard(0);

             }
             else
             {
                 //I will win since left to me
                 suggestion=canPlay.getCard(canPlay.getCardCount()-1);

             }

         }
         case 3:
         {
             int count=0;
             currentTricks.orderHand();
             if (canPlay.getCard(canPlay.getCardCount()-1)<currentTricks.getCard(currentTricks.getCardCount()-1))
             {
                 //can beat this round
                 suggestion=canPlay.getCard(canPlay.getCardCount());
             }
             else
             {
                 //useless gg
                 suggestion=canPlay.getCard(0);
             }

           }
        default:
        {
        //keep compiler happy again
            suggestion=canPlay.getCard(0);
        }

         }

    }
    generateDeckOptions();
    //Check how many higher cards are in circulation than currently selected
    int total = 0;
    for (int i = 0;i<deck.getCardCount();i++)
    {
        if (suggestion<deck.getCard(i))
        {
            total++;
        }
    }
    if (total>0)
    {
        //there are higher cards
        //first find position of the card
        int position = 0;
        for (int i=0;i<canPlay.getCardCount();i++)
        {
            if (canPlay.getCard(i)==suggestion)
            {
                position=i;
            }
        }
        if (position==canPlay.getCardCount()-1)
        {
            //playing best card, maybe not good idea so in interval [0,position)
            //generate a number and play that 20% of the time
            bool flag = false;
            int seed = time(0);
            flag = random(seed) % 100 < 20;
            if (flag)
            {
                int seeder = time(0);
                int newpos=random(seeder) % 100*position;
                newpos = newpos/100;
                suggestion = canPlay.getCard(newpos);
                cardPlayed=suggestion;
               return suggestion;
            }
            else
            {
                cardPlayed=suggestion;
               return suggestion;
            }
        }
        else
        {
            //Do the same for the top just a smaller chance of occuring
            bool flag = false;
            int seed = time(0);
            flag = random(seed) % 100 < 10;
            if (flag)
            {
                int newpos=random(time(0)) % 100*position;
                newpos = newpos/100;
                suggestion = canPlay.getCard(newpos);
                cardPlayed=suggestion;
               return suggestion;
            }
            else
            {
                cardPlayed=suggestion;
               return suggestion;
            }

        }

    }
    else
    {
        //playing highest card
        cardPlayed=suggestion;
       return suggestion;
    }


}
Bid AI::guessBid()
{
    Bid idea = Bid();
    Bid suggestion = Bid();
    initialBidSet();
    generatebidlist();
    removebids();
    //gets the total points for each high card in a suit. 10=1,J=2,Q=3 ... A=5
    int clubsCount=0;
    int diamondsCount=0;
    int heartsCount=0;
    int spadesCount=0;
    //obtains value for every suit
    for (int i=0; i<=myhand.getCardCount()-1;i++)
    {
        //gets total for every suit
        if (myhand.getCard(i).getSuit()==CLUBS)
        {
            if (myhand.getCard(i).getRank()==ACE)
            {
                //if ace add 14 since ace is worth more
                clubsCount+=14;
            }
            else
            {
                if (myhand.getCard(i).getRank()>=TEN)
                {
                   clubsCount+= myhand.getCard(i).getRank();
                }

            }
        }
        else if (myhand.getCard(i).getSuit()==DIAMONDS)
        {
            if (myhand.getCard(i).getRank()==ACE)
            {
                //if ace add 14 since ace is worth more
                diamondsCount+=14;
            }
            else
            {
                if (myhand.getCard(i).getRank()>=TEN)
                {
                    diamondsCount+= myhand.getCard(i).getRank();
                }

            }
        }
        else if (myhand.getCard(i).getSuit()==HEARTS)
        {
            if (myhand.getCard(i).getRank()==ACE)
            {
                //if ace add 14 since ace is worth more
                heartsCount+=14;
            }
            else
            {
                if (myhand.getCard(i).getRank()>=TEN)
                {
                  heartsCount+= myhand.getCard(i).getRank();
                }

            }
        }
        else if (myhand.getCard(i).getSuit()==SPADES)
        {
            if (myhand.getCard(i).getRank()==ACE)
            {
                //if ace add 14 since ace is worth more
                spadesCount+=14;
            }
            else
            {
                if (myhand.getCard(i).getRank()>=TEN)
                {
                   spadesCount+= myhand.getCard(i).getRank();
                }

            }
        }

    }
    //The bot's plan is to mostly play with suit with most high cards. if the tricks are higher than roundup(count/12) then pass
    //the bot will never double since making a bot do that results in an insane algorithm
    //for NT shouldn't be higher than total of two highes ceiling minus 1
    // first obtain highest suit and second highest
    int highest=0;
    int second = 0;
    CardSuit highsuit = CLUBS;
    CardSuit secondsuit = CLUBS;
    if (clubsCount>second)
    {
       if (clubsCount>highest)
       {
           highest=clubsCount;
           highsuit=CLUBS;
       }
       else
       {
           second=clubsCount;
           secondsuit=CLUBS;
       }
    }
    if (diamondsCount>second)
    {
       if (diamondsCount>highest)
       {
           highest=diamondsCount;
           highsuit=DIAMONDS;
       }
       else
       {
           second=diamondsCount;
           secondsuit=DIAMONDS;
       }
    }
    if (heartsCount>second)
    {
       if (heartsCount>highest)
       {
           highest=heartsCount;
           highsuit=HEARTS;
       }
       else
       {
           second=heartsCount;
           secondsuit=HEARTS;
       }
    }
    if (spadesCount>second)
    {
       if (spadesCount>highest)
       {
           highest=spadesCount;
           highsuit=SPADES;
       }
       else
       {
           second=spadesCount;
           secondsuit=SPADES;
       }
    }
    if (currentState.getContractBid()==nullptr)
    {
        //no bid yet throw highest out

        idea=Bid(position,BID);
        suggestion=Bid(position,highsuit,1);
    }
    else
    {
        if (highsuit>=currentbid.getTrumpSuit())
        {
            //if my best hand is the suit or better suit then use that if higher
            if (ceil(highest)>(currentbid.getTricksAbove()*10))
            {
                idea = Bid(position,BID);
                suggestion = Bid(position,highsuit,currentbid.getTricksAbove()+1);
            }
            //this means my best suit can't compete compute second+high and NT if higher tricks might win?????
            else if (ceil(highest+second)>(currentbid.getTricksAbove()*20))
            {
                idea = Bid(position,BID);
                suggestion = Bid(position,NONE,currentbid.getTricksAbove()+1);
            }
        }
        // this means my best suit isn't better than current bid check if second is better
        else if (secondsuit>=currentbid.getTrumpSuit())
        {
            //suboptimal but play with what you have maybe rng likes you
            if (ceil(second)>(currentbid.getTricksAbove()*10))
            {
                idea = Bid(position,BID);
                suggestion = Bid(position,secondsuit,currentbid.getTricksAbove()+1);
            }
            else
            {
                //so neither hand is more or better than suit in play give up???
                idea = Bid(position,PASS);
            }
        }
        //this means nothing works bud maybe try for a super NT play? calculate this but with penalties
        else if (ceil(diamondsCount+heartsCount+spadesCount)>(currentbid.getTricksAbove()*30))
        {
            suggestion = Bid(position,NONE,currentbid.getTricksAbove()+1);
            idea = Bid(position,BID);

        }
        //gg m8 nothing works
        else
        {
           idea = Bid(position,PASS);
        }
    }
    if (suggestion.getTricksAbove()>0)
    {
        //here the random number generator will be used to see if the AI will double or not
        int total = highest+second;
        //first just check if this isn't stupid
        if (total>60)
        {
            bool bIsDouble = false;
            //creates a unique seed based upon the highest and lowest values
            int seed = highest << 16 | second;
            //if the number generated is below 32 then call double
            bIsDouble = random(seed) % 256 < 32;
            if (bIsDouble)
            {
                suggestion.setCall(DOUBLE_BID);
            }

        }
        bidMade = suggestion;
        return suggestion;
    }
    else
    {
        bidMade = suggestion;
        return idea;
    }

}


CardSet AI::getHand()
{
    return myhand;
}

void AI::setCurrentBid(Bid bidding)
{
    currentbid = bidding;
}

void AI::setContractBid(Bid contracter)
{
    contract=contracter;
}


Bid AI::getBidContract()
{
    return contract;
}

Bid AI::getBidCurrent()
{
    return currentbid;
}

CardSet AI::getDeck()
{
    return deck;
}

//To add some flair to the ai, uses the lehmer 32 random number generator to make it possible that the AI
// might make a "mistake"
uint32_t AI::random(uint32_t nSeed)
{
    nSeed += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)nSeed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;

}
