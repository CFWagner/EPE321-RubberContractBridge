#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QWidget>
#include "game-server/score.h"
#include "game-server/playergamestate.h"
#include "enumerations/team.h"
namespace Ui {
class ScoreWindow;
}

class ScoreWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreWindow(QWidget *parent = nullptr);
    ~ScoreWindow();
    void updateScore();
public slots:
    void showScore(PlayerGameState gameState);

private slots:
    void on_button_exit_clicked();

private:
    Ui::ScoreWindow *ui;
    QString backScoreL = "Back score: ";
    QString overTrickL = "Overtricks: ";
    QString undertricks = "Undertricks: ";
    QString honorsL = "Honors: ";
    QString slamBonusesL = "Slam bonuses: ";
    QString doubleBonusesL = "Double bonuses: ";
    QString redoubleBonusesL = "Redouble bonuses: ";
    QString rubberBonusesL = "Rubber bonuses: ";
    QString getTotalScoreL = "Total score: ";
};

#endif // SCOREWINDOW_H
