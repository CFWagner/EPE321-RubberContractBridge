#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QWidget>
#include "game-server/score.h"
#include "game-server/playergamestate.h"

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
};

#endif // SCOREWINDOW_H
