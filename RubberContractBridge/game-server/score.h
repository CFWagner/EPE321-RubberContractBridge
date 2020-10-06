#ifndef SCORE_H
#define SCORE_H

#include <QJsonObject>



class Score
{
public:
    Score();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // SCORE_H
