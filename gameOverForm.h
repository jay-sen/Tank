#ifndef GAMEOVERFORM_H
#define GAMEOVERFORM_H

#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QWidget>

namespace Ui {
class GameOverForm;
}

class GameOverForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameOverForm(QWidget *parent = nullptr);
    ~GameOverForm();
    // 实现窗口圆角化以及GameOver的绘制
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 实现窗口滑动效果
    void slideIn();
    void slideOut();

signals:
    void back();

private:
    Ui::GameOverForm *ui;
    QPropertyAnimation *propertyAnimation = nullptr;

    QPoint delta;
    bool drag = false;
};

#endif // GAMEOVERFORM_H
