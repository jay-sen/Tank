
#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

#include <QKeyEvent>
#include <QQueue>

#include "base.h"

class TankBase;
class Player;
class Enemy;
class Effect;
class MapBlock;

class GameMap
{
public:
    GameMap();
    ~GameMap();

    void paint(QPainter &painter);
    void setMap1();
    static void reset();

    static MapBlock *map[REALROW][REALCOLUMN];
};

class GameTank
{
public:
    GameTank();
    ~GameTank();
    void paint(QPainter &painter);
    void update();

    void checkTanks();

    void keyPressed(QKeyEvent *event);
    void KeyReleased(QKeyEvent *event);

    int enemyNum();
    int playerNum();

    void initSiglePlayer();
    void initMultiPlayer();
    void setLevel1();
    static void reset();

    static QVector<Enemy *> enemy;
    static QVector<Player *> player;
};

class GameEffect
{
public:
    GameEffect();
    ~GameEffect();
    void paint(QPainter &painter);
    void checkEffect();

    static void reset();
    static QVector<Effect *> effect;
};

#endif // GAMEELEMENT_H
