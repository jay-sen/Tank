
#include "base.h"
#include "gameform.h"
#include "ui_gameform.h"

GameForm::GameForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameForm)
{
    ui->setupUi(this);
    this->connectDataBase();

    // 加入游戏菜单界面
    menu = new MenuForm(this);
    ui->display->addWidget(menu);
    ui->display->setCurrentWidget(menu);
    // 加入游戏单人双人选择界面
    modeChoose = new ModeChooseForm(this);
    ui->display->addWidget(modeChoose);
    // 游戏结束通知滑窗
    over = new GameOverForm(this);
    over->setGeometry((this->width() - over->width()) / 2,
                      -over->height(),
                      over->width(),
                      over->height());
    connect(over, &GameOverForm::back, this, [=] {
        ui->display->setCurrentWidget(menu);
        ui->display->removeWidget(gaming);
        delete gaming;
        gaming = nullptr;
    });
    // 加入游戏记录界面
    record = new RecordForm(this);
    ui->display->addWidget(record);
    connect(record, &RecordForm::clear, this, [=] {
        this->clearRecord();
        model->setQuery("SELECT * FROM record"); // 查询数据库
        model->removeColumn(0);
        record->view->setModel(model);
    });
    // menu界面按钮信号槽连接
    connect(menu, &MenuForm::startGame, this, [=] { ui->display->setCurrentWidget(modeChoose); });
    connect(menu, &MenuForm::recordQuery, this, [=] {
        ui->display->setCurrentWidget(record);
        model->setQuery("SELECT * FROM record"); // 查询数据库
        model->removeColumn(0);
        record->view->setModel(model);
        record->view->horizontalHeader()->resizeSection(0, 550);      
    });
    // 模式选择界面信号槽连接
    connect(modeChoose, &ModeChooseForm::siglePlayerMode, this, [=] {
        gaming = new GamingForm(this); // 选择了模式后再初始化游戏界面
        gaming->setGameMode(GameMode::SIGLEPLAYER);
        ui->display->addWidget(gaming);
        ui->display->setCurrentWidget(gaming);
        gaming->setFocus();
        // 游戏界面与游戏结束界面通信
        connect(gaming, &GamingForm::gameOver, this, [=](bool res) {
            this->addRecord(res);
            over->slideOut();
        });
    });
    connect(modeChoose, &ModeChooseForm::multiPlayerMode, this, [=] {
        gaming = new GamingForm(this); // 选择了模式后再初始化游戏界面
        gaming->setGameMode(GameMode::MULTIPLAYER);
        ui->display->addWidget(gaming);
        ui->display->setCurrentWidget(gaming);
        gaming->setFocus();
        // 游戏界面与游戏结束界面通信
        connect(gaming, &GamingForm::gameOver, this, [=](bool res) {
            this->addRecord(res);
            over->slideOut();
        });
    });
    // 从任意界面返回菜单界面的家按钮
    ui->btn_home->setIcon(QIcon(":/button/button/back.ico"));
    ui->btn_home->setIconSize(QSize(20, 20));
    connect(ui->btn_home, &QPushButton::clicked, this, [=] {
        ui->display->setCurrentWidget(menu);
        if (gaming) {
            ui->display->removeWidget(gaming);
            delete gaming;
            gaming = nullptr;
        }
    });

    // 加载外部字体
    int fontID = QFontDatabase::addApplicationFont("://font/kenvector_future.ttf");
    QString kenvector = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont font(kenvector, 14);
    QApplication::setFont(font);

    // 主窗口去除标题栏
    // 使用自定义的关闭、最小化、最大化按钮
    // 主窗口圆角化，在 paintEvent 事件函数中绘制圆角
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    connect(ui->btn_close, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->btn_min, &QPushButton::clicked, this, &QWidget::showMinimized);
    // 不使用窗口最大化
    //    connect(ui->btn_adjust, &QPushButton::clicked, this, [=]() {
    //        if (sizeFlag) {
    //            this->showMaximized();
    //            sizeFlag = false;
    //        } else {
    //            this->showNormal();
    //            sizeFlag = true;
    //        }
    //    });

    ui->titleBar->setStyleSheet("background-color:rgb(240, 240, "
                                "240);border-top-left-radius:10px;border-top-right-radius:10px");
}

GameForm::~GameForm()
{
    delete ui;
}

void GameForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /* set the round border */
    QPen pen(QColor(100, 100, 100, 80));
    pen.setWidth(1);
    painter.setPen(pen);
    QBrush brush(QColor(255, 255, 255)); // 改成 QColor(255, 255, 255, 100)实现透明效果
    painter.setBrush(brush);
    QRect rect = this->rect();
    rect.setWidth((rect.width() - 1));
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 10, 10);
}

void GameForm::mousePressEvent(QMouseEvent *event)
{
    //鼠标相对于桌面左上角，鼠标全局位置
    QPoint mousePos = event->globalPos();
    //窗口左上角相对于桌面位置，窗口位置
    QPoint winPos = this->geometry().topLeft();
    //定值不变
    this->delta = mousePos - winPos;
    if (delta.y() < ui->titleBar->height() && sizeFlag) {
        drag = true;
    }
}

void GameForm::mouseMoveEvent(QMouseEvent *event)
{
    if (drag) {
        QPoint mousePos = event->globalPos();
        QPoint winPos = mousePos - this->delta;
        this->move(winPos);
    }
}

void GameForm::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (drag) {
        drag = false;
    }
}

void GameForm::connectDataBase()
{
    // Connect to the database
    QString dbPath = QDir(QCoreApplication::applicationDirPath()).filePath("gameData.db");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Failed to open database!";
        QMessageBox::critical(this, tr("Error"), tr("Failed to open database!"));
        return;
    }
    // Create the table if it doesn't exist
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS record (id INTEGER PRIMARY KEY, time varChar(30), "
               "result bool)");

    // 查询数据模型初始化
    model = new QSqlQueryModel(this);
}

void GameForm::addRecord(bool res)
{
    QSqlQuery query;
    QDateTime dataTime = QDateTime::currentDateTime();
    query.prepare("INSERT INTO record(time,result) VALUES(:time, :result)");
    query.bindValue(":time", dataTime.toString());
    query.bindValue(":result", res);
    if (!query.exec()) //执行sql指令
    {
        qDebug() << "Error: insert error." << query.lastError();
    }
    query.clear();
}

void GameForm::clearRecord()
{
    QSqlQuery query;
    query.prepare("DELETE FROM record");
    if (!query.exec()) //执行sql指令
    {
        qDebug() << "Error: clear error." << query.lastError();
    }
    query.clear();
}
