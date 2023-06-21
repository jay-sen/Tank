#include "modeChooseForm.h"
#include <QGraphicsDropShadowEffect>
#include "ui_modeChooseForm.h"

ModeChooseForm::ModeChooseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeChooseForm)
{
    ui->setupUi(this);
    connect(ui->btn_mode1, &QPushButton::clicked, this, &ModeChooseForm::siglePlayerMode);
    connect(ui->btn_mode2, &QPushButton::clicked, this, &ModeChooseForm::multiPlayerMode);

    pixmap.load(":/button/button/mode.png");

    /*
    QString qss
        = "QPushButton{"
          "background-color:rgb(253, 253, 253);border:1px solid "
          "rgb(100,100,100);border-radius:4px;font: 12pt \"Corbel\""
          "}"
          "QPushButton:hover{"
          "color:rgb(255,185,0);background-color:rgb(255,255,255);border-color:rgb(255,185,0)"
          "}";
    ui->btn_mode1->setStyleSheet(qss);
    ui->btn_mode2->setStyleSheet(qss);

    QGraphicsDropShadowEffect *shadow1 = new QGraphicsDropShadowEffect(this);
    shadow1->setOffset(0, 0);
    shadow1->setColor(QColor(100, 100, 100, 100));
    shadow1->setBlurRadius(10);
    ui->btn_mode1->setGraphicsEffect(shadow1);
    QGraphicsDropShadowEffect *shadow2 = new QGraphicsDropShadowEffect(this);
    shadow2->setOffset(0, 0);
    shadow2->setColor(QColor(100, 100, 100, 100));
    shadow2->setBlurRadius(10);
    ui->btn_mode2->setGraphicsEffect(shadow2);
*/
}

ModeChooseForm::~ModeChooseForm()
{
    delete ui;
}

void ModeChooseForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(240, 300, QPixmap(":/tanks/tank/tank_blue.png"));
    painter.drawPixmap(650, 300, QPixmap(":/tanks/tank/tank_blue.png"));
    painter.drawPixmap(850, 300, QPixmap(":/tanks/tank/tank_green.png"));
    painter.drawPixmap(350, 100, pixmap);
}
