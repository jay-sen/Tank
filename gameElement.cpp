#include "gameElement.h"
#include "tank.h"
/*-----------------------------------------------------------------*/
MapBlock *GameMap::map[REALROW][REALCOLUMN]{};
GameMap::GameMap()
{
    int row, column;
    for (row = 0; row < REALROW; ++row) {
        for (column = 0; column < REALCOLUMN; ++column) {
            GameMap::map[row][column] = new MapBlock(row, column, Block::SPACE);
        }
    }
}

GameMap::~GameMap()
{
    reset();
}

void GameMap::paint(QPainter &painter)
{
    int row, column;
    for (row = 0; row < REALROW; ++row) {
        for (column = 0; column < REALCOLUMN; ++column) {
            if (GameMap::map[row][column])
                GameMap::map[row][column]->paint(painter);
        }
    }
}

void GameMap::setMap1()
{
    int map1[REALROW][REALCOLUMN] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                                     {4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 4},
                                     {4, 0, 4, 0, 0, 4, 0, 0, 0, 0, 3, 4, 0, 0, 4, 0, 4},
                                     {4, 0, 4, 3, 0, 0, 4, 0, 0, 0, 4, 3, 0, 0, 4, 0, 4},
                                     {4, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 2, 0, 4},
                                     {4, 0, 0, 1, 2, 0, 0, 3, 3, 3, 0, 0, 2, 1, 0, 0, 4},
                                     {4, 0, 0, 1, 2, 0, 0, 3, 1, 3, 0, 0, 2, 1, 0, 0, 4},
                                     {4, 0, 0, 1, 2, 0, 0, 3, 3, 3, 0, 0, 2, 1, 0, 0, 4},
                                     {4, 0, 0, 2, 0, 0, 0, 0, 3, 0, 3, 0, 0, 2, 2, 0, 4},
                                     {4, 0, 4, 0, 0, 3, 4, 0, 0, 0, 4, 0, 0, 3, 4, 0, 4},
                                     {4, 0, 4, 0, 0, 4, 3, 0, 0, 0, 0, 4, 0, 0, 4, 0, 4},
                                     {4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 4},
                                     {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};
    ;
    int row, column;
    for (row = 0; row < REALROW; ++row) {
        for (column = 0; column < REALCOLUMN; ++column) {
            GameMap::map[row][column]->setType((Block) map1[row][column]);
        }
    }
}

void GameMap::reset()
{
    int row, column;
    for (row = 0; row < REALROW; ++row) {
        for (column = 0; column < REALCOLUMN; ++column) {
            if (GameMap::map[row][column])
                delete GameMap::map[row][column];
        }
    }
}

/*----------------------------------------------------------------------------------*/

QVector<Enemy *> GameTank::enemy{};
QVector<Player *> GameTank::player{};
GameTank::GameTank()
{
    
}

void GameTank::setLevel1()
{
    Tank_No3 *enemy1 = new Tank_No3();
    enemy1->setInstruction(1);
    enemy1->setPos(QPoint(15 * BLOCKWIDTH, 1 * BLOCKHEIGHT));
    enemy.push_back(enemy1);
    Tank_No3 *enemy2 = new Tank_No3();
    enemy2->setInstruction(1);
    enemy2->setPos(QPoint(15 * BLOCKWIDTH, 3 * BLOCKHEIGHT));
    enemy.push_back(enemy2);
    Tank_No3 *enemy3 = new Tank_No3();
    enemy3->setInstruction(1);
    enemy3->setPos(QPoint(15 * BLOCKWIDTH, 9 * BLOCKHEIGHT));
    enemy.push_back(enemy3);
    Tank_No4 *enemy4 = new Tank_No4();
    enemy4->setInstruction(1);
    enemy4->setPos(QPoint(15 * BLOCKWIDTH, 11 * BLOCKHEIGHT));
    enemy.push_back(enemy4);
}

void GameTank::reset()
{
    qDeleteAll(enemy);
    enemy.clear();
    qDeleteAll(player);
    player.clear();
}

GameTank::~GameTank()
{
    reset();
}

void GameTank::paint(QPainter &painter)
{
    for (Enemy *tank : qAsConst(enemy)) {
        tank->paint(painter);
        if (tank->bullet.isMoving()) {
            tank->bullet.paint(painter);
        }
    }
    for (int i = 1; i < player.size(); ++i) {
        player[i]->paint(painter);
        if (player[i]->bullet.isMoving()) {
            player[i]->bullet.paint(painter);
        }
    }
}

void GameTank::update()
{
    checkTanks();
    for (Enemy *tank : qAsConst(enemy)) {
        tank->update();
    }
    for (int i = 1; i < player.size(); ++i) {
        player[i]->update();
    }
}

void GameTank::checkTanks()
{
    for (auto it = enemy.begin(); it != enemy.end();) {
        if (!(*it)->alive()) {
            delete *it;
            it = enemy.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = player.begin(); it != player.end();) {
        if (!(*it)->alive()) {
            delete *it;
            it = player.erase(it);
        } else {
            ++it;
        }
    }
}

int GameTank::enemyNum()
{
    return enemy.size();
}

int GameTank::playerNum()
{
    return player.size();
}

void GameTank::initSiglePlayer()
{
    Tank_No1 *help = new Tank_No1();
    help->setPos(QPoint(0, 0));
    player.push_back(help);

    player.push_back(new Tank_No1());
}

void GameTank::initMultiPlayer()
{
    Tank_No1 *help = new Tank_No1();
    help->setPos(QPoint(0, 0));
    player.push_back(help);

    player.push_back(new Tank_No1());
    player.push_back(new Tank_No2());
}

void GameTank::keyPressed(QKeyEvent *event)
{
    int size = player.size();
    if (size == 1) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_W:
        player[1]->moving = true;
        player[1]->direction = Direction::UP;
        break;
    case Qt::Key_S:
        player[1]->moving = true;
        player[1]->direction = Direction::DOWN;
        break;
    case Qt::Key_A:
        player[1]->moving = true;
        player[1]->direction = Direction::LEFT;
        break;
    case Qt::Key_D:
        player[1]->moving = true;
        player[1]->direction = Direction::RIGHT;
        break;
    case Qt::Key_J:
        player[1]->fire();
        break;
    case Qt::Key_Up:
        player[size - 1]->moving = true;
        player[size - 1]->direction = Direction::UP;
        break;
    case Qt::Key_Down:
        player[size - 1]->moving = true;
        player[size - 1]->direction = Direction::DOWN;
        break;
    case Qt::Key_Left:
        player[size - 1]->moving = true;
        player[size - 1]->direction = Direction::LEFT;
        break;
    case Qt::Key_Right:
        player[size - 1]->moving = true;
        player[size - 1]->direction = Direction::RIGHT;
        break;
    case Qt::Key_0:
        player[size - 1]->fire();
        break;
    }
}

void GameTank::KeyReleased(QKeyEvent *event)
{
    int size = player.size();
    if (size == 1) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_W:
        player[1]->moving = false;
        break;
    case Qt::Key_S:
        player[1]->moving = false;
        break;
    case Qt::Key_A:
        player[1]->moving = false;
        break;
    case Qt::Key_D:
        player[1]->moving = false;
        break;
    case Qt::Key_J:
        break;
    case Qt::Key_Up:
        player[size - 1]->moving = false;
        break;
    case Qt::Key_Down:
        player[size - 1]->moving = false;
        break;
    case Qt::Key_Left:
        player[size - 1]->moving = false;
        break;
    case Qt::Key_Right:
        player[size - 1]->moving = false;
        break;
    case Qt::Key_0:
        break;
    }
}
/*-----------------------------------------------------------------------------------------------*/
QVector<Effect *> GameEffect::effect{};
GameEffect::GameEffect() {}

GameEffect::~GameEffect()
{
    reset();
}

void GameEffect::paint(QPainter &painter)
{
    checkEffect();
    for (Effect *eff : qAsConst(effect)) {
        eff->paint(painter);
    }
}

void GameEffect::checkEffect()
{
    for (auto it = effect.begin(); it != effect.end();) {
        if ((*it)->finished()) {
            delete *it;
            it = effect.erase(it);
        } else {
            ++it;
        }
    }
}

void GameEffect::reset()
{
    qDeleteAll(effect);
    effect.clear();
}
