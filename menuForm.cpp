#include "menuForm.h"
#include "ui_menuform.h"

MenuForm::MenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuForm)
{
    ui->setupUi(this);
    this->setFixedSize(1088, 832);
    connect(ui->btn_start, &QPushButton::clicked, this, &MenuForm::startGame);
    connect(ui->btn_record, &QPushButton::clicked, this, &MenuForm::recordQuery);

    pixmap.load(":/button/button/Sample.png");
}

MenuForm::~MenuForm()
{
    delete ui;
}

void MenuForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(80, 50, pixmap);
}
