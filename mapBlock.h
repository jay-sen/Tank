
#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "base.h"

class MapBlock : public Base
{
public:
    MapBlock() = default;
    MapBlock(int row, int column, Block type);
    ~MapBlock() = default;
    virtual void paint(QPainter &painter);
    virtual QRect getSphere();
    virtual void move(){};
    void setType(Block type) { this->type = type; }
    int getType() { return (int) this->type; }

private:
    Block type;
};

#endif // MAPBLOCK_H
