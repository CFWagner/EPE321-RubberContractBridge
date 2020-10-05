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
    // Read GameState non-list attributes from JSON object
    phase = GamePhase(json["phase"].toInt());
    currentBid.read(json["currentBid"].toObject());
    contractBid.read(json["contractBid"].toObject());
    gameNumber = json["gameNumber"].toInt();
    dealNumber = json["dealNumber"].toInt();
    trickNumber = json["trickNumber"].toInt();
    playerTurn = PlayerPosition(json["playerTurn"].toInt());
    handToPlay = PlayerPosition(json["handToPlay"].toInt());
    dealer = PlayerPosition(json["dealer"].toInt());
    declarer = PlayerPosition(json["declarer"].toInt());
    score.read(json);

    // Read PlayerGameState non-list attributes from JSON object
    gameEvent = GameEvent(json["gameEvent"].toInt());
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

    // Read GameState team vunerable vector from JSON object
    QJsonArray jsonTeamVulnerableArray = json["tricks"].toArray();
    for (qint8 index = 0; index < jsonTeamVulnerableArray.size(); ++ index) {
        bool teamVulnerableElement = jsonTeamVulnerableArray[index].toBool();
        teamVulnerable[index] = teamVulnerableElement;

    }

    // Read PlayerGameState player positions map from JSON object
    playerPositions.clear();
    QJsonArray playerPositionKeys;
    QJsonArray playerPositionValues;
    for(qint8 index = 0; index < playerPositionKeys.size(); ++index){
        PlayerPosition key = PlayerPosition(playerPositionKeys[index].toInt());
        QString value = playerPositionValues[index].toString();
        playerPositions.insert(key, value);
    }
}

// Add PlayerGameState instance attributes to the JSON object argument
void PlayerGameState::write(QJsonObject &json) const
{
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
