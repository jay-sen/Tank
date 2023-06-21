#ifndef RECORDFORM_H
#define RECORDFORM_H

#include <QPushButton>
#include <QTableView>
#include <QWidget>

namespace Ui {
class RecordForm;
}

class RecordForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecordForm(QWidget *parent = nullptr);
    ~RecordForm();

    QTableView *view; // 显示数据库表的内容

signals:
    void clear();

private:
    Ui::RecordForm *ui;
};

#endif // RECORDFORM_H
