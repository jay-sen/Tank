#include "gamingForm.h"

#include "ui_gamingform.h"

GamingForm::GamingForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamingForm)
{
    ui->setupUi(this);
    this->setFixedSize(1088, 832);

    level = new GameLevel();
    timer = new QTimer(this);
    timer->start(FRESHTIME);
    connect(timer, &QTimer::timeout, this, &GamingForm::timeOut);

    finished = false;
    ui->btn_pause->setIcon(QIcon(":/button/button/pause.ico"));
    ui->btn_pause->setIconSize(QSize(40, 40));
    connect(ui->btn_pause, &QPushButton::clicked, this, [=] {
        static int flag = 0;
        if (flag == 0) {
            this->timer->stop();
            ui->btn_pause->setIcon(QIcon(":/button/button/play.ico"));
            flag = 1;
        } else {
            this->timer->start(FRESHTIME);
            ui->btn_pause->setIcon(QIcon(":/button/button/pause.ico"));
            flag = 0;
        }
    });
}

GamingForm::~GamingForm()
{
    delete timer;
    delete level;
    delete ui;
}

void GamingForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    level->paint(painter);
}

void GamingForm::keyPressEvent(QKeyEvent *event)
{
    level->receiveKeyPressEvent(event);
}

void GamingForm::keyReleaseEvent(QKeyEvent *event)
{
    level->receiveKeyReleaseEvent(event);
}

void GamingForm::setGameMode(GameMode mode)
{
    level->setGameMode(mode);
}

void GamingForm::setGameRestart() {}
void GamingForm::timeOut()
{
    if (!finished) {
        if (level->missionFailed()) {
            emit gameOver(false);
            finished = true;
        }
        if (level->missionSuccessful()) {
            emit gameOver(true);
            finished = true;
        }
    }
    level->update();
    this->update();
}
