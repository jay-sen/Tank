#include "tank.h"
#include <QSound>
#include "gameElement.h"

/*----------------------------------------------------------------------------------*/

TankBase::TankBase()
{
    this->moving = false;
}

QRect TankBase::getSphere()
{
    return QRect(this->pos, this->size);
}

TankBase::~TankBase()
{

}

void TankBase::move()
{
    if (!this->moving)
        return;
    if (this->crush())
        return;
    switch (this->direction) {
    case Direction::UP:

        this->pos += QPoint(0, -speed);
        break;
    case Direction::DOWN:

        this->pos += QPoint(0, speed);
        break;
    case Direction::LEFT:

        this->pos += QPoint(-speed, 0);
        break;
    case Direction::RIGHT:

        this->pos += QPoint(speed, 0);
        break;
    }
}

void TankBase::fire()
{
    if (this->bullet.isMoving()) {
        return;
    }

    switch (this->direction) {
    case Direction::UP:
        this->bullet.setBullet(this->pos
                                   + QPoint((this->size.width() - BULLETWIDTH) / 2, -BULLETHEIGHT),
                               this->direction);
        break;
    case Direction::DOWN:
        this->bullet.setBullet(this->pos
                                   + QPoint((this->size.width() - BULLETWIDTH) / 2,
                                            this->size.height()),
                               this->direction);
        break;
    case Direction::LEFT:
        this->bullet.setBullet(this->pos
                                   + QPoint(-BULLETWIDTH, (this->size.height() - BULLETHEIGHT) / 2),
                               this->direction);
        break;
    case Direction::RIGHT:
        this->bullet.setBullet(this->pos
                                   + QPoint(this->size.width(),
                                            (this->size.height() - BULLETHEIGHT) / 2),
                               this->direction);
        break;
    }
    GameEffect::effect.push_back(new FireEffect(this->pos, this->direction, this->size));
    this->bullet.setMove(true);
    QSound::play(":/sound/explode.wav");
    //this->sound->play();
}

bool TankBase::crush()
{
    int step = this->speed;
    int column = this->pos.x() / BLOCKWIDTH;
    int row = this->pos.y() / BLOCKHEIGHT;
    int x = this->pos.x() % BLOCKWIDTH;
    int y = this->pos.y() % BLOCKHEIGHT;
    switch (this->direction) {
    case Direction::UP:

        if ((GameMap::map[row - 1][column]->getType() > 0
             || GameMap::map[row - 1][column + (x + this->size.width()) / BLOCKWIDTH]->getType() > 0)
            && y - step <= 0) {
            return true;
        }
        break;
    case Direction::DOWN:

        row = row + (y + this->size.height()) / BLOCKHEIGHT;
        y = (y + this->size.height()) % BLOCKHEIGHT;
        if ((GameMap::map[row + 1][column]->getType() > 0
             || GameMap::map[row + 1][column + (x + this->size.width()) / BLOCKWIDTH]->getType() > 0)
            && y + step >= BLOCKHEIGHT) {
            return true;
        }
        break;
    case Direction::LEFT:

        if ((GameMap::map[row][column - 1]->getType() > 0
             || GameMap::map[row + (y + this->size.height()) / BLOCKHEIGHT][column - 1]->getType()
                    > 0)
            && x - step <= 0) {
            return true;
        }
        break;
    case Direction::RIGHT:

        column = column + (x + this->size.width()) / BLOCKWIDTH;
        x = (x + this->size.width()) % BLOCKWIDTH;
        if ((GameMap::map[row][column + 1]->getType() > 0
             || GameMap::map[row + (y + this->size.height()) / BLOCKHEIGHT][column + 1]->getType()
                    > 0)
            && x + step >= BLOCKWIDTH) {
            return true;
        }
        break;
    }
    return false;
}

/*----------------------------------------------------------------------------------*/

Enemy::~Enemy() {}

void Enemy::update()
{
    (this->*instruct)();
    this->move();
    this->bullet.move();
    this->isAttacked();
}

bool Enemy::isAttacked()
{
    this->sphere = this->getSphere();
    int player_num = GameTank::player.size();
    for (int i = 1; i < player_num; ++i) {
        if (this->sphere.intersects(GameTank::player[i]->bullet.getSphere())) {
            GameTank::player[i]->bullet.explode();
            --this->hitPoints;
            return true;
        }
    }
    return false;
}

void Enemy::instruction1()
{
    int num = GameTank::player.size();
    for (int i = 1; i < num; ++i) {
        QSize size = GameTank::player[i]->size;
        int deltaX = this->pos.x() - GameTank::player[i]->pos.x();
        int deltaY = this->pos.y() - GameTank::player[i]->pos.y();
        switch (this->direction) {
        case Direction::UP:
            if ((deltaX < size.width()) && (deltaX > -size.width()) && (deltaY > 0)) {
                this->fire();
            }
            break;
        case Direction::DOWN:
            if ((deltaX < size.width()) && (deltaX > -size.width()) && (deltaY < 0)) {
                this->fire();
            }
            break;
        case Direction::LEFT:
            if ((deltaY < size.height()) && (deltaY > -size.height()) && (deltaX > 0)) {
                this->fire();
            }
            break;
        case Direction::RIGHT:
            if ((deltaY < size.height()) && (deltaY > -size.height()) && (deltaX < 0)) {
                this->fire();
            }
            break;
        }
    }

    if (!this->moving) {
        this->direction = (Direction) (rand() % 4);
        moving = true;
    }

    static int turn = (rand() % 100 + 200);
    static int fire = (rand() % 100 + 400);
    if (this->crush()) {
        this->direction = (Direction) (((int) this->direction + rand() % 3 + 1) % 4);
    }
    if (turn == 0) {
        this->direction = (Direction) (((int) this->direction + rand() % 3 + 1) % 4);
        turn = (rand() % 100 + 200);
    }
    if (fire == 0) {
        this->fire();
        fire = (rand() % 100 + 400);
    }
    --turn;
    --fire;
}

void Enemy::instruction2() {}

void Enemy::setInstruction(int mode)
{
    switch (mode) {
    case 1:
        this->instruct = &Enemy::instruction1;
        break;
    case 2:
        this->instruct = &Enemy::instruction2;
        break;
    }
}

/*----------------------------------------------------------------------------------*/

Player::~Player() {}

void Player::update()
{
    this->move();
    this->bullet.move();
    this->isAttacked();
}

bool Player::isAttacked()
{
    this->sphere = this->getSphere();
    int enemy_num = GameTank::enemy.size();
    for (int i = 0; i < enemy_num; ++i) {
        if (this->sphere.intersects(GameTank::enemy[i]->bullet.getSphere())) {
            GameTank::enemy[i]->bullet.explode();
            --this->hitPoints;
            return true;
        }
    }
    return false;
}
/*----------------------------------------------------------------------------------*/
Tank_No1::Tank_No1()
{
    this->speed = 3;
    this->size = QSize(44, 44);
    this->pos = QPoint(1 * BLOCKWIDTH, 5 * BLOCKHEIGHT);
    this->direction = Direction::RIGHT;
    this->hitPoints = 2;
}

void Tank_No1::paint(QPainter &painter)
{
    QPixmap tank;

    switch (this->direction) {
    case Direction::UP:
        tank = QPixmap(":/tanks/tank/1.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::DOWN:
        tank = QPixmap(":/tanks/tank/2.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::LEFT:
        tank = QPixmap(":/tanks/tank/3.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::RIGHT:
        tank = QPixmap(":/tanks/tank/4.png");

        painter.drawPixmap(this->pos, tank);
        break;
    }
}

/*----------------------------------------------------------------------------------*/
Tank_No2::Tank_No2()
{
    this->speed = 3;
    this->size = QSize(44, 44);
    this->pos = QPoint(1 * BLOCKWIDTH, 7 * BLOCKHEIGHT);
    this->direction = Direction::RIGHT;
    this->hitPoints = 2;
}

void Tank_No2::paint(QPainter &painter)
{
    QPixmap tank;

    switch (this->direction) {
    case Direction::UP:
        tank = QPixmap(":/tanks/tank/5.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::DOWN:
        tank = QPixmap(":/tanks/tank/6.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::LEFT:
        tank = QPixmap(":/tanks/tank/7.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::RIGHT:
        tank = QPixmap(":/tanks/tank/8.png");

        painter.drawPixmap(this->pos, tank);
        break;
    }
}

/*----------------------------------------------------------------------------------*/
Tank_No3::Tank_No3()
{
    this->speed = 2;
    this->size = QSize(44, 44);
    this->pos = QPoint(15 * BLOCKWIDTH, 7 * BLOCKHEIGHT);
    this->direction = Direction::LEFT;
    this->setBulletSpeed(5);
    this->hitPoints = 2;
}

void Tank_No3::paint(QPainter &painter)
{
    QPixmap tank;

    switch (this->direction) {
    case Direction::UP:
        tank = QPixmap(":/tanks/tank/9.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::DOWN:
        tank = QPixmap(":/tanks/tank/10.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::LEFT:
        tank = QPixmap(":/tanks/tank/11.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::RIGHT:
        tank = QPixmap(":/tanks/tank/12.png");

        painter.drawPixmap(this->pos, tank);
        break;
    }
}

/*----------------------------------------------------------------------------------*/
Tank_No4::Tank_No4()
{
    this->speed = 1;
    this->size = QSize(45, 45);
    this->pos = QPoint(15 * BLOCKWIDTH, 5 * BLOCKHEIGHT);
    this->direction = Direction::LEFT;
    this->setBulletSpeed(5);
    this->hitPoints = 3;
}

void Tank_No4::paint(QPainter &painter)
{
    QPixmap tank;

    switch (this->direction) {
    case Direction::UP:
        tank = QPixmap(":/tanks/tank/13.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::DOWN:
        tank = QPixmap(":/tanks/tank/14.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::LEFT:
        tank = QPixmap(":/tanks/tank/15.png");

        painter.drawPixmap(this->pos, tank);
        break;
    case Direction::RIGHT:
        tank = QPixmap(":/tanks/tank/16.png");

        painter.drawPixmap(this->pos, tank);
        break;
    }
}
