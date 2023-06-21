
#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QDateTime>
#include <QHeaderView>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtFontDatabaseSupport/QtFontDatabaseSupport>

#include "gameOverForm.h"
#include "gamingForm.h"
#include "menuForm.h"
#include "modeChooseForm.h"
#include "recordForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameForm; }
QT_END_NAMESPACE

class GameForm : public QMainWindow

{
    Q_OBJECT

public:
    GameForm(QWidget *parent = nullptr);
    ~GameForm();

    // 实现自定义的圆角窗口
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 数据库的使用
    void connectDataBase();
    void addRecord(bool res);
    void clearRecord();

private:
    Ui::GameForm *ui;
    QSqlDatabase db;       // 数据库连接
    QSqlQueryModel *model; // 显示数据库表的内容

    GamingForm *gaming = nullptr; // 游戏界面
    MenuForm *menu;               // 游戏菜单界面
    ModeChooseForm *modeChoose;   // 游戏单人双人选择界面
    GameOverForm *over;           // 游戏结束滑窗
    RecordForm *record;           // 游戏历史记录界面

    // 去掉标题栏后实现窗口拖动
    QPoint delta;
    bool drag = false;
    bool sizeFlag = true; // window max or normal ?
};

#endif // GAMEFORM_H
