#include "playergamestate.h"
#include <QJsonArray>
#include <QVariantMap>

PlayerGameState::PlayerGameState() {}

GameEvent PlayerGameState::getEvent()
{
    return gameEvent;
}

CardSet PlayerGameState::getPlayerHand()
{
    return playerHand;
}

CardSet PlayerGameState::getDummyHand()
{
    return dummyHand;
}

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
    currentBid.read(json["currentBid"].toObject());
    contractBid.read(json["contractBid"].toObject());
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
    QJsonObject jsonCurrentBid;
    currentBid.write(jsonCurrentBid);
    json["currentBid"] = jsonCurrentBid;
    QJsonObject jsonContractBid;
    contractBid.write(jsonContractBid);
    json["contractBid"] = jsonContractBid;
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
    json["teamVulnerable"];

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
