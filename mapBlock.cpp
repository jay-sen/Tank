
#include "mapBlock.h"

MapBlock::MapBlock(int row, int column, Block type)
{
    this->pos = QPoint(column * BLOCKWIDTH, row * BLOCKHEIGHT);
    this->type = type;
}

void MapBlock::paint(QPainter &painter)
{
    QPixmap block;

    switch (this->type) {
    case Block::SPACE:
        block = QPixmap(":/block/background/sand.png");
        break;
    case Block::BRICK:
        block = QPixmap(":/block/background/crateWood.png");
        break;
    case Block::METAL:
        block = QPixmap(":/block/background/crateMetal.png");
        break;
    case Block::WATER:
        block = QPixmap(":/block/background/water.png");
        break;
    case Block::TREE:
        block = QPixmap(":/block/background/tree.png");
        break;
    }

    painter.drawPixmap(this->pos, block);
}

QRect MapBlock::getSphere()
{
    return QRect(this->pos, QSize(64, 64));
}
