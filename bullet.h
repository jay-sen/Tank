
#ifndef BULLET_H
#define BULLET_H

#include "base.h"
#include "effect.h"
#include "mapBlock.h"

class Bullet : public Base
{
public:
    Bullet();
    ~Bullet();
    void paint(QPainter &painter);
    QRect getSphere();
    void move();
    bool crush();
    void explode();
    void setBullet(QPoint pos, Direction direction);
    void setSpeed(int speed) { this->speed = speed; }
    void setMove(bool move) { move ? this->moving = true : this->moving = false; }
    bool isMoving() { return this->moving; }

private:
    bool moving = false;
};

#endif // BULLET_H
