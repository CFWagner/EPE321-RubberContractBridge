#ifndef SCORE_H
#define SCORE_H

#include <QJsonObject>

// Contains the various components of the team scores throughout the game
class Score
{
public:
    Score();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const Score& score) const;
};

#endif // SCORE_H
