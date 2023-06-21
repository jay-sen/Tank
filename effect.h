
#ifndef EFFECT_H
#define EFFECT_H

#include <QPainter>
#include <QPixmap>
#include "base.h"

class Effect
{
public:
    Effect();
    virtual ~Effect() = 0;
    virtual void paint(QPainter &painter) = 0;
    virtual void setPixmap() = 0;
    virtual bool finished() = 0;

    QPixmap pixmap;
    int frame;  // “帧”
    QPoint pos; // 爆炸中心
};

class ExplodeEffect : public Effect
{
public:
    ExplodeEffect();
    ExplodeEffect(QPoint pos);
    void paint(QPainter &painter);
    void setPixmap();
    bool finished();
};

class FireEffect : public Effect
{
public:
    FireEffect();
    FireEffect(QPoint pos, Direction direction, QSize size);
    void paint(QPainter &painter);
    void setPixmap();
    bool finished();

private:
    Direction direction;
    QSize size; // 坦克大小，位置
};

#endif // EFFECT_H
