
#include "bullet.h"
#include "gameElement.h"

Bullet::Bullet()
{
    this->speed = 8;
    this->size = QSize(14, 14);
}

Bullet::~Bullet() {}

void Bullet::paint(QPainter &painter)
{
    QPixmap bullet;
    switch (this->direction) {
    case Direction::UP:
        bullet = QPixmap(":/bullet/bullet/1.png");
        painter.drawPixmap(this->pos, bullet);

        break;
    case Direction::DOWN:
        bullet = QPixmap(":/bullet/bullet/2.png");
        painter.drawPixmap(this->pos, bullet);

        break;
    case Direction::LEFT:
        bullet = QPixmap(":/bullet/bullet/3.png");
        painter.drawPixmap(this->pos, bullet);

        break;
    case Direction::RIGHT:
        bullet = QPixmap(":/bullet/bullet/4.png");
        painter.drawPixmap(this->pos, bullet);

        break;
    }
}

QRect Bullet::getSphere()
{
    return QRect(this->pos, QSize(14, 14));
}

void Bullet::move()
{
    if (!this->moving)
        return;
    if (this->crush()) {
        this->explode();
    }
    switch (this->direction) {
    case Direction::UP:
        this->pos += QPoint(0, -this->speed);
        break;
    case Direction::DOWN:      
        this->pos += QPoint(0, this->speed);
        break;
    case Direction::LEFT:
        this->pos += QPoint(-this->speed, 0);
        break;
    case Direction::RIGHT:        
        this->pos += QPoint(this->speed, 0);
        break;
    }
}

bool Bullet::crush()
{   
    int column = this->pos.x() / BLOCKWIDTH;
    int row = this->pos.y() / BLOCKHEIGHT;

    if (GameMap::map[row][column]->getType() > 1) {
        if (GameMap::map[row][column]->getType() == 2 || GameMap::map[row][column]->getType() == 3) {
            GameMap::map[row][column]->setType(Block::SPACE);
        }
        return true;
    }

    return false;
}

void Bullet::explode()
{
    GameEffect::effect.push_back(
        new ExplodeEffect(this->pos + QPoint(this->size.width() / 2, this->size.height() / 2)));
    this->moving = false;
    this->pos = QPoint(0, 0);
}

void Bullet::setBullet(QPoint pos, Direction direction)
{
    this->pos = pos;
    this->direction = direction;
}
