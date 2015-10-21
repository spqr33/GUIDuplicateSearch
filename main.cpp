#include <QApplication>
#include "dupsearchmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DuplicateSearchMainWindow mainWindow;

    mainWindow.show();

    return a.exec();
}
