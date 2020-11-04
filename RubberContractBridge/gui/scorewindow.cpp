#include "scorewindow.h"
#include "ui_scorewindow.h"

ScoreWindow::ScoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/guiResources/background/background3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(640,480);
    this->setWindowTitle ("Server Logger");
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));
    setWindowIcon(QIcon(":/resources/guiResources/cards/ace_diamonds.png"));
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::showScore(PlayerGameState gameState)
{
    ui->left->clear();
    for(int i = 0; i < gameState.getScore().getContractPoints(E_W).size();i++)
    {
        qDebug() <<"2";
        ui->left->appendPlainText("Game "+QString::number(i) + ":");
    }
    ui->left->appendPlainText(backScoreL);
    ui->left->appendPlainText(overTrickL);
    ui->left->appendPlainText(undertricks);
    ui->left->appendPlainText(honorsL);
    ui->left->appendPlainText(slamBonusesL);
    ui->left->appendPlainText(doubleBonusesL);
    ui->left->appendPlainText(redoubleBonusesL);
    ui->left->appendPlainText(rubberBonusesL);
    ui->left->appendPlainText(getTotalScoreL);

    ui->NS->clear();
    for(int i = 0; i < gameState.getScore().getContractPoints(N_S).size();i++)
    {
        qDebug() <<"1";
        ui->NS->appendPlainText(QString::number(gameState.getScore().getContractPoints(N_S).value(i)));
    }
    ui->NS->appendPlainText(QString::number(gameState.getScore().getBackScore(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getOvertricks(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getUndertricks(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getHonors(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getSlamBonuses(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getDoubleBonuses(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getReDoubleBonuses(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getRubberBonuses(N_S)));
    ui->NS->appendPlainText(QString::number(gameState.getScore().getTotalScore(N_S)));

    ui->EW->clear();
    for(int i = 0; i < gameState.getScore().getContractPoints(E_W).size();i++)
    {
        qDebug() <<"3";
        ui->EW->appendPlainText(QString::number(gameState.getScore().getContractPoints(E_W).value(i)));
    }
    ui->EW->appendPlainText(QString::number(gameState.getScore().getBackScore(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getOvertricks(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getUndertricks(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getHonors(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getSlamBonuses(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getDoubleBonuses(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getReDoubleBonuses(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getRubberBonuses(E_W)));
    ui->EW->appendPlainText(QString::number(gameState.getScore().getTotalScore(E_W)));
    this->show();
}


void ScoreWindow::on_button_exit_clicked()
{
    this->hide();
}
