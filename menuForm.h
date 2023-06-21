#ifndef MENUFORM_H
#define MENUFORM_H

#include <QPainter>
#include <QWidget>

namespace Ui {
class MenuForm;
}

class MenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MenuForm(QWidget *parent = nullptr);
    ~MenuForm();
    void paintEvent(QPaintEvent *) override;

signals:
    void startGame();
    void recordQuery();

private:
    Ui::MenuForm *ui;
    QPixmap pixmap;
};

#endif // MENUFORM_H
