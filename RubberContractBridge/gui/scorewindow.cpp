#include "scorewindow.h"
#include "ui_scorewindow.h"

ScoreWindow::ScoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/guiResources/background/background2.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(640,480);
    this->setWindowTitle ("Server Logger");
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::showScore(PlayerGameState gameState)
{
    this->show();
}


void ScoreWindow::on_button_exit_clicked()
{
    this->hide();
}
