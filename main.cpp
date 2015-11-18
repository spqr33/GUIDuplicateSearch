#include <QApplication>
#include "dupsearchmainwindow.h"
#include  <QSharedPointer>
#include "filesinfoholder.h"
#include "samesizeholder.h"
#include "duplicatesholder.h"

//typedef QSharedPointer<FilesInfoHolder> SP_FilesInfoHolder;
//Q_DECLARE_METATYPE(SP_FilesInfoHolder)
//Q_DECLARE_METATYPE(QSharedPointer<SameSizeHolder>)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DuplicateSearchMainWindow mainWindow;

    qRegisterMetaType<QSharedPointer<FilesInfoHolder> >();
    qRegisterMetaType<QSharedPointer<SameSizeHolder> >();
    qRegisterMetaType<QSharedPointer<DuplicatesHolder> >();

    QObject::connect(&mainWindow, SIGNAL(destroyed(QObject*)), qApp, SLOT(quit()));

    mainWindow.show();

    return a.exec();
}
