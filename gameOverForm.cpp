#include "gameOverForm.h"
#include "ui_gameoverform.h"

GameOverForm::GameOverForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOverForm)
{
    ui->setupUi(this);
    connect(ui->btn_back, &QPushButton::clicked, this, &GameOverForm::back);
    connect(ui->btn_back, &QPushButton::clicked, this, [=] { this->slideIn(); });

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    propertyAnimation = new QPropertyAnimation(this, "geometry");
    propertyAnimation->setEasingCurve(QEasingCurve::InOutExpo);
    propertyAnimation->setDuration(1000);
}

GameOverForm::~GameOverForm()
{
    delete ui;
}

void GameOverForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /* set the round border */
    QPen pen(QColor(255, 200, 0, 80));
    pen.setWidth(1);
    painter.setPen(pen);
    QBrush brush(QColor(255, 255, 255, 200));
    painter.setBrush(brush);
    QRect rect = this->rect();
    rect.setWidth((rect.width() - 1));
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 10, 10);

    // game over
    QFont font(painter.font().family(), 25);
    pen.setColor(QColor(255, 100, 0));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(50, 150, "GAME OVER");
}

void GameOverForm::mousePressEvent(QMouseEvent *event)
{
    //鼠标相对于桌面左上角，鼠标全局位置
    QPoint mousePos = event->globalPos();
    //窗口左上角相对于桌面位置，窗口位置
    QPoint winPos = this->geometry().topLeft();
    //定值不变
    this->delta = mousePos - winPos;
    drag = true;
}

void GameOverForm::mouseMoveEvent(QMouseEvent *event)
{
    if (drag) {
        QPoint mousePos = event->globalPos();
        QPoint winPos = mousePos - this->delta;
        this->move(winPos);
    }
}

void GameOverForm::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (drag) {
        drag = false;
    }
}

void GameOverForm::slideIn()
{
    propertyAnimation->setStartValue(QRect(this->pos().x(), 0, this->width(), this->height()));
    propertyAnimation->setEndValue(
        QRect(this->pos().x(), -this->height(), this->width(), this->height()));
    propertyAnimation->start();
}

void GameOverForm::slideOut()
{
    propertyAnimation->setStartValue(
        QRect(this->pos().x(), -this->height(), this->width(), this->height()));
    propertyAnimation->setEndValue(QRect(this->pos().x(), 0, this->width(), this->height()));
    propertyAnimation->start();
}
