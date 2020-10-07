#include "playergamestate.h"
#include <QJsonArray>
#include <QVariantMap>

// Default constructor
PlayerGameState::PlayerGameState() {}

// Constructor with all attributes
PlayerGameState::PlayerGameState(GamePhase phase, const Bid* currentBid, const Bid* contractBid,
                                 qint8 gameNumber, qint8 dealNumber, qint8 trickNumber,
                                 QVector<CardSet> tricks, PlayerPosition playerTurn,
                                 PlayerPosition handToPlay, PlayerPosition dealer,
                                 PlayerPosition declarer, bool teamVulnerable[2], Score score,
                                 GameEvent gameEvent, QMap<PlayerPosition, QString> playerPositions,
                                 CardSet playerHand, CardSet dummyHand)
{
    this->phase = phase;
    if(currentBid == nullptr)
        this->currentBid = nullptr;
    else
        this->currentBid = new Bid(*currentBid);
    if(contractBid == nullptr)
        this->contractBid = nullptr;
    else
        this->contractBid = new Bid(*contractBid);
    this->gameNumber = gameNumber;
    this->dealNumber =dealNumber;
    this->trickNumber = trickNumber;
    this->tricks = tricks;
    this->playerTurn = playerTurn;
    this->handToPlay = handToPlay;
    this->dealer = dealer;
    this->declarer = declarer;
    this->teamVulnerable[N_S] = teamVulnerable[N_S];
    this->teamVulnerable[E_W] = teamVulnerable[E_W];
    this->score = score;
    this->gameEvent = gameEvent;
    this->playerPositions = playerPositions;
    this->playerHand = playerHand;
    this->dummyHand = dummyHand;
}

// Constructor with parent class GameState referenceand PlayerGameState class attributes
PlayerGameState::PlayerGameState(const GameState &gameState, GameEvent gameEvent,
                                 QMap<PlayerPosition, QString> playerPositions,
                                 CardSet playerHand, CardSet dummyHand)
{
    phase = gameState.getPhase();
    if(gameState.getCurrentBid() == nullptr)
        currentBid = nullptr;
    else
        currentBid = new Bid(*gameState.getCurrentBid());
    if(gameState.getContractBid() == nullptr)
        contractBid = nullptr;
    else
        contractBid = new Bid(*gameState.getContractBid());
    gameNumber = gameState.getGameNumber();
    dealNumber = gameState.getDealNumber();
    trickNumber = gameState.getTrickNumber();
    tricks = gameState.getTricks();
    playerTurn = gameState.getPlayerTurn();
    handToPlay = gameState.getHandToPlay();
    dealer = gameState.getDealer();
    declarer = gameState.getDeclarer();
    teamVulnerable[N_S] = gameState.getTeamVulnerable(N_S);
    teamVulnerable[E_W] = gameState.getTeamVulnerable(E_W);
    score = gameState.getScore();
    this->gameEvent = gameEvent;
    this->playerPositions = playerPositions;
    this->playerHand = playerHand;
    this->dummyHand = dummyHand;
}

// Getter for the latest game event occurence
GameEvent PlayerGameState::getEvent()
{
    return gameEvent;
}

// Getter for the cards in the player's hand
CardSet PlayerGameState::getPlayerHand()
{
    return playerHand;
}

// Getter for the cards in the dummy's hand
CardSet PlayerGameState::getDummyHand()
{
    return dummyHand;
}

// Getter for the name of the player in the position specified by the position argument
QString PlayerGameState::getPlayerName(PlayerPosition position)
{
    return playerPositions.value(position);
}

// Initialize player game state attributes from JSON object
void PlayerGameState::read(const QJsonObject &json)
{
    // Read GameState non-list non-object attributes from JSON object
    phase = GamePhase(json["phase"].toInt());
    gameNumber = json["gameNumber"].toInt();
    dealNumber = json["dealNumber"].toInt();
    trickNumber = json["trickNumber"].toInt();
    playerTurn = PlayerPosition(json["playerTurn"].toInt());
    handToPlay = PlayerPosition(json["handToPlay"].toInt());
    dealer = PlayerPosition(json["dealer"].toInt());
    declarer = PlayerPosition(json["declarer"].toInt());

    // Read GameState non-list non-object attributes from JSON object
    if(json["currentBid"].isNull()){
        currentBid = nullptr;
    }
    else{
        if(currentBid == nullptr)
            currentBid = new Bid();
        currentBid->read(json["currentBid"].toObject());
    }
    if(json["contractBid"].isNull()){
        contractBid = nullptr;
    }
    else{
        if(contractBid == nullptr)
            contractBid = new Bid();
        contractBid->read(json["contractBid"].toObject());
    }
    score.read(json["score"].toObject());

    // Read PlayerGameState non-list non-object attributes from JSON object
    gameEvent = GameEvent(json["gameEvent"].toInt());

    // Read PlayerGameState non-list object attributes from JSON object
    playerHand.read(json["playerHand"].toObject());
    dummyHand.read(json["dummyHand"].toObject());


    // Read GameState tricks vector from JSON object
    QJsonArray jsonTricks = json["tricks"].toArray();
    tricks.clear();
    tricks.reserve(jsonTricks.size());
    for (qint8 index = 0; index < jsonTricks.size(); ++ index) {
        QJsonObject jsonTrick = jsonTricks[index].toObject();
        CardSet trick;
        trick.read(jsonTrick);
        tricks.append(trick);
    }

    // Read GameState team vunerable array from JSON object
    QJsonArray jsonTeamVulnerableArray = json["teamVulnerable"].toArray();
    for (qint8 index = 0; index < jsonTeamVulnerableArray.size(); ++ index) {
        bool teamVulnerableElement = jsonTeamVulnerableArray[index].toBool();
        teamVulnerable[index] = teamVulnerableElement;
    }

    // Read PlayerGameState player positions map from JSON object
    playerPositions.clear();
    QJsonArray playerPositionKeys = json["playerPositionKeys"].toArray();
    QJsonArray playerPositionValues = json["playerPositionValues"].toArray();
    for(qint8 index = 0; index < playerPositionKeys.size(); ++index){
        PlayerPosition key = PlayerPosition(playerPositionKeys[index].toInt());
        QString value = playerPositionValues[index].toString();
        playerPositions.insert(key, value);
    }
}

// Add PlayerGameState instance attributes to the JSON object argument
void PlayerGameState::write(QJsonObject &json) const
{
    // Add GameState non-list non-object attributes to JSON object
    json["phase"] = phase;
    json["gameNumber"] = gameNumber;
    json["dealNumber"] = dealNumber;
    json["trickNumber"] = trickNumber;
    json["playerTurn"] = playerTurn;
    json["handToPlay"] = handToPlay;
    json["dealer"] = dealer;
    json["declarer"] = declarer;

    // Add GameState non-list object attributes to JSON object
    if(currentBid == nullptr){
        json["currentBid"] = QJsonValue(QJsonValue::Type::Null);
    }
    else{
        QJsonObject jsonCurrentBid;
        currentBid->write(jsonCurrentBid);
        json["currentBid"] = jsonCurrentBid;
    }
    if(contractBid == nullptr){
        json["contractBid"] = QJsonValue(QJsonValue::Type::Null);
    }
    else{
        QJsonObject jsonContractBid;
        contractBid->write(jsonContractBid);
        json["contractBid"] = jsonContractBid;
    }
    QJsonObject jsonScore;
    score.write(jsonScore);
    json["score"] = jsonScore;

    // Add PlayerGameState non-list non-object attributes to JSON object
    json["gameEvent"] = gameEvent;

    // Add PlayerGameState non-list object attributes to JSON object
    QJsonObject jsonPlayerHand;
    playerHand.write(jsonPlayerHand);
    json["playerHand"] = jsonPlayerHand;
    QJsonObject jsonDummyHand;
    dummyHand.write(jsonDummyHand);
    json["dummyHand"] = jsonDummyHand;


    // Add GameState tricks vector to JSON object
    QJsonArray jsonTricks;
    for (const CardSet &trick: tricks) {
        QJsonObject jsonTrick;;
        trick.write(jsonTrick);
        jsonTricks.append(jsonTrick);
    }
    json["tricks"] = jsonTricks;

    // Add GameState team vunerable array to JSON object
    QJsonArray jsonTeamVulnerableArray;
    for (const bool &teamVulnerableElement: teamVulnerable)
        jsonTeamVulnerableArray.append(teamVulnerableElement);
    json["teamVulnerable"] = jsonTeamVulnerableArray;

    // Add PlayerGameState player positions map to JSON object
    QMapIterator<PlayerPosition, QString> iter(playerPositions);
    QJsonArray playerPositionKeys;
    QJsonArray playerPositionValues;
    while (iter.hasNext()) {
        iter.next();
        playerPositionKeys.append(iter.key());
        playerPositionValues.append(iter.value());
    }
    json["playerPositionKeys"] = playerPositionKeys;
    json["playerPositionValues"] = playerPositionValues;
}
