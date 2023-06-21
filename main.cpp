
#include "gameform.h"
#include "gamingForm.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameForm w;
    w.show();
    return a.exec();
}
