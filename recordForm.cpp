#include "recordForm.h"
#include "ui_recordform.h"

#include <QHeaderView>

RecordForm::RecordForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordForm)
{
    ui->setupUi(this);
    view = new QTableView(this);
    view->setGeometry(100, 50, 800, 700);
    view->show();
    view->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    view->horizontalHeader()->setStretchLastSection(true);
    //view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(ui->btn_clear, &QPushButton::clicked, this, &RecordForm::clear);
}

RecordForm::~RecordForm()
{
    delete ui;
}
