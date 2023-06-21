
#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QPainter>

/*---------------------方向-------------------------------*/
enum class Direction { UP, DOWN, LEFT, RIGHT };
/*--------------------地图块------------------------------*/
enum class Block { SPACE, WATER, TREE, BRICK, METAL };
/*---------------------模式-------------------------------*/
enum class GameMode { SIGLEPLAYER, MULTIPLAYER };

/* ********************************************************\
 * 地图的设计
 * 地图由许多块组成，每个块像素为 64*64
 * 地图由空白块和地图块 MapBlock 组成，一共 15 * 11 个块 （除了四周的铁块）
 * 地图大小为 width = 15*64 = 960，height = 11*64 = 704
 * Row 1~11，Column 1~15
\* ********************************************************/
// 地图块
const int BLOCKWIDTH = 64;
const int BLOCKHEIGHT = 64;
// 地图，这里的行列就是地图块的所在行所在列，不是从 0 开始，坦克和子弹可以行动的范围
const int MAPROW = 11;
const int MAPCOLUMN = 15;
const int MAPWIDTH = 960;  // 64*15
const int MAPHEIGHT = 704; // 64*11
// 实际绘制的地图，包括四个墙壁
const int REALROW = MAPROW + 2;
const int REALCOLUMN = MAPCOLUMN + 2;
// 子弹
const int BULLETWIDTH = 14;
const int BULLETHEIGHT = 14;

// 刷新时间 ms
const int FRESHTIME = 10;

/*-----------------------------------------------------------*/

/***********************************************************\
 * Base 类
 * 由坦克、炮弹、地图块继承
 * 包含位置信息、方向等
 * 使用统一的接口 paint()来绘制
\***********************************************************/

class Base : public QObject
{
    Q_OBJECT
public:
    explicit Base(QObject *parent = nullptr);
    virtual ~Base() = 0;
    /*--------------------method------------------------*/
    virtual void paint(QPainter &painter) = 0; // 绘制图片
    virtual QRect getSphere() = 0;
    virtual void move() = 0;
    void setPos(QPoint pos) { this->pos = pos; }

    /*---------------------data-------------------------*/
    QPoint pos;          // 物体位置，图片的左上角
    Direction direction; // 坦克、子弹方向
    int speed;           // 坦克、子弹速度
    QRect sphere;        // 物体矩形范围，碰撞检测使用
    QSize size;          // 物体宽高
};

#endif // BASE_H
