
#ifndef TANK_H
#define TANK_H

#include <QKeyEvent>
#include <QVector>

#include "base.h"
#include "bullet.h"

//class GameTank;

class TankBase : public Base
{
public:
    TankBase();
    virtual ~TankBase() = 0;
    virtual void paint(QPainter &painter) = 0;
    virtual bool isAttacked() = 0;
    virtual void update() = 0;

    QRect getSphere();
    void move();
    void fire();
    bool crush();
    bool alive() { return this->hitPoints > 0; }
    void setBulletSpeed(int speed) { this->bullet.setSpeed(speed); }

    bool moving; // 通过点击按键开始移动，释放按键停止
    Bullet bullet;
    int hitPoints;
};

class Enemy : public TankBase
{
public:
    Enemy() = default;
    virtual ~Enemy() = 0;
    void paint(QPainter &painter) { Q_UNUSED(painter); }
    void update();
    bool isAttacked();

    void instruction1(); // 为敌方坦克移动和射击预定义的指令
    void instruction2();
    void setInstruction(int mode);

    void (Enemy::*instruct)(void);
};

class Player : public TankBase
{
public:
    Player() = default;
    virtual ~Player() = 0;
    void paint(QPainter &painter) { Q_UNUSED(painter); }
    void update();
    bool isAttacked();
};

class Tank_No1 : public Player
{
public:
    Tank_No1();
    void paint(QPainter &painter) override;
};

class Tank_No2 : public Player
{
public:
    Tank_No2();
    void paint(QPainter &painter) override;
};

class Tank_No3 : public Enemy
{
public:
    Tank_No3();
    void paint(QPainter &painter) override;
};

class Tank_No4 : public Enemy
{
public:
    Tank_No4();
    void paint(QPainter &painter) override;
};

#endif // TANK_H
