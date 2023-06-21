#ifndef MODECHOOSEFORM_H
#define MODECHOOSEFORM_H

#include <QPainter>
#include <QWidget>

namespace Ui {
class ModeChooseForm;
}

class ModeChooseForm : public QWidget
{
    Q_OBJECT

public:
    explicit ModeChooseForm(QWidget *parent = nullptr);
    ~ModeChooseForm();

    void paintEvent(QPaintEvent *) override;

signals:
    void siglePlayerMode();
    void multiPlayerMode();

private:
    Ui::ModeChooseForm *ui;
    QPixmap pixmap;
};

#endif // MODECHOOSEFORM_H
