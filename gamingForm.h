#ifndef GAMINGFORM_H
#define GAMINGFORM_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "gameLevel.h"
#include "base.h"

namespace Ui {
class GamingForm;
}

class GamingForm : public QWidget
{
    Q_OBJECT
public:
    explicit GamingForm(QWidget *parent = nullptr);
    ~GamingForm();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void setGameMode(GameMode mode);
    void setGameRestart();

public slots:
    void timeOut();

signals:
    void gameOver(bool);

private:
    Ui::GamingForm *ui;
    QTimer *timer;
    GameLevel *level;
    bool finished;
};

#endif // GAMINGFORM_H
