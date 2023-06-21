
#include "effect.h"

Effect::Effect()
{
    this->frame = 1;
}

Effect::~Effect() {}

/*-----------------------------------------------------------------------------------------------*/
ExplodeEffect::ExplodeEffect() {}

ExplodeEffect::ExplodeEffect(QPoint pos)
{
    this->pos = pos;
}

void ExplodeEffect::paint(QPainter &painter)
{
    this->setPixmap();
    painter.drawPixmap(this->pos.x() - pixmap.width() / 2,
                       this->pos.y() - pixmap.height() / 2,
                       pixmap);
    ++this->frame;
}

void ExplodeEffect::setPixmap()
{
    QString path = QString::asprintf(":/effect/effect/explosion%d.png", this->frame / 5 + 1);
    this->pixmap.load(path);
}

bool ExplodeEffect::finished()
{
    return this->frame == 25;
}

/*-----------------------------------------------------------------------------------------------*/

FireEffect::FireEffect() {}

FireEffect::FireEffect(QPoint pos, Direction direction, QSize size)
{
    this->pos = pos;
    this->direction = direction;
    this->size = size;
    QString path = QString::asprintf(":/effect/effect/shotRed%d.png", (int) this->direction + 1);
    this->pixmap.load(path);
    switch (this->direction) {
    case Direction::UP:
        this->pos = this->pos
                    + QPoint(this->size.width() / 2 - this->pixmap.width() / 2,
                             -this->pixmap.height())
                    + QPoint(-2, -2);
        break;
    case Direction::DOWN:
        this->pos = this->pos
                    + QPoint(this->size.width() / 2 - this->pixmap.width() / 2, this->size.height())
                    + QPoint(-2, 2);
        break;
    case Direction::LEFT:
        this->pos = this->pos
                    + QPoint(-this->pixmap.width(),
                             this->size.height() / 2 - this->pixmap.height() / 2)
                    + QPoint(-2, 0);
        break;
    case Direction::RIGHT:
        this->pos = this->pos
                    + QPoint(this->size.width(), this->size.height() / 2 - this->pixmap.height() / 2)
                    + QPoint(2, 0);
        break;
    }
}

void FireEffect::paint(QPainter &painter)
{
    painter.drawPixmap(this->pos.x(), this->pos.y(), pixmap);
    ++this->frame;
}

void FireEffect::setPixmap() {}

bool FireEffect::finished()
{
    return this->frame == 10;
}

