#include "ai.h"
#include <math.h>
//the generate card function will be archaic, might use it in the future to improve selection but for demo only consider dummy hand and my hand
//Further my AI is greedy so will only look in current position best move np heuristics nor probability (yet????)
//Why errors on switches still??????


AI::AI(QObject *parent)
{
}
AI::~AI()
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
    //for now no slots or signals since no integration
}
void AI::notifyMoveTurn()
{
//assuming this tells AI to make a move suggestion
    initialMainSet();
    Card maker;
    maker=guessMove();
    //for now no slots or signals since no integration
}
void AI::updateGameState(PlayerGameState gameState)
{
    currentState=gameState;
}
void AI::notifyBidRejected(QString reason)
{
    //assuming rejects so redo bid move?

}
void AI::notifyMoveRejected(QString reason)
{
    //assuming rejects so redo move?
    //shouldn't ever happen if does spot
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
        for (int holder = ACE; holder!= KING; holder++)
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
       Card dummy = Card(foo,KING);
       deck.addCard(dummy);
    }

    deck.orderHand();
}
void AI::generatebidlist()
{
    //does as the name implies. During initial main set prunes selection based upon what was played previously
    //this is used to try and find possible bids to be pulled from
    for (int i=1 ; i<7 ; i++)
    {
        for ( int fooInt = CLUBS ; fooInt != NONE; fooInt++ )
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
    currentbid = *currentState.getCurrentBid();
    for (int i=0;i<bidlist.size();i++)
    {
        if ((bidlist[i].getTricksAbove()<=currentbid.getTricksAbove()) && (bidlist[i].getTrumpSuit()<= currentbid.getTrumpSuit() ))
        {
            bidlist.erase(bidlist.begin()+i);
        }
    }
}
//removes impozsible cards from pool
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
            for (int i = 0; i < handAmount-1; i++)
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
        Card trickCard;
        qint8 handAmount;
        // if card count goes from 1,2,3,4 gets the recent card played
        trickCard = currentTricks.getCard(currentTricks.getCardCount()-1);
        handAmount = myhand.getCardCount();
        //check if trump or NT
        if (trump==4)
        {
            //then it is no trump so any card higher than last played is valid for me and dummy
            for (int i = 0; i < handAmount-1; i++)
            {
                if (trickCard <myhand.getCard(i))
                {
                    canPlay.addCard(myhand.getCard(i));
                }
                if (trickCard <dummyhand.getCard(i))
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
            for (int i = 0; i < handAmount-1; i++)
            {
                if (trickCard.getSuit() == myhand.getCard(i).getSuit())
                {
                    canPlay.addCard(myhand.getCard(i));
                }
                if (trickCard.getSuit() == dummyhand.getCard(i).getSuit())
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
    cardPlayed=suggestion;
   return suggestion;

}
Bid AI::guessBid()
{
    Bid idea;
    Bid suggestion;
    initialBidSet();
    generatebidlist();
    removebids();
    //gets the total points for each high card in a suit. 10=1,J=2,Q=3 ... A=5
    int clubsCount=0;
    int diamondsCount=0;
    int heartsCount=0;
    int spadesCount=0;
    //obtains value for every suit
    for (int i=0; i<myhand.getCardCount()-1;i++)
    {
        //gets total for every suit
        if (myhand.getCard(i).getSuit()==0)
        {
            if (myhand.getCard(i).getRank()==1)
            {
                //if ace add 14 since ace is worth more
                clubsCount+=14;
            }
            else
            {
               clubsCount+= myhand.getCard(i).getRank();
            }
        }
        else if (myhand.getCard(i).getSuit()==1)
        {
            if (myhand.getCard(i).getRank()==1)
            {
                //if ace add 14 since ace is worth more
                diamondsCount+=14;
            }
            else
            {
               diamondsCount+= myhand.getCard(i).getRank();
            }
        }
        else if (myhand.getCard(i).getSuit()==2)
        {
            if (myhand.getCard(i).getRank()==1)
            {
                //if ace add 14 since ace is worth more
                heartsCount+=14;
            }
            else
            {
               heartsCount+= myhand.getCard(i).getRank();
            }
        }
        else if (myhand.getCard(i).getSuit()==3)
        {
            if (myhand.getCard(i).getRank()==1)
            {
                //if ace add 14 since ace is worth more
                spadesCount+=14;
            }
            else
            {
               spadesCount+= myhand.getCard(i).getRank();
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
            idea = Bid(position,BID);
            suggestion = Bid(position,NONE,currentbid.getTricksAbove()+1);
        }
        //gg m8 nothing works
        else
        {
           idea = Bid(position,PASS);
        }
    }
    return idea;
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
