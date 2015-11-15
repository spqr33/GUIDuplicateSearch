#include <QApplication>
#include "dupsearchmainwindow.h"
#include  <QSharedPointer>
#include "filesinfoholder.h"
#include "samesizeholder.h"

//typedef QSharedPointer<FilesInfoHolder> SP_FilesInfoHolder;
//Q_DECLARE_METATYPE(SP_FilesInfoHolder)
//Q_DECLARE_METATYPE(QSharedPointer<SameSizeHolder>)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DuplicateSearchMainWindow mainWindow;


    qRegisterMetaType<QSharedPointer<FilesInfoHolder> >();
    qRegisterMetaType<QSharedPointer<SameSizeHolder> >();

    mainWindow.show();

    return a.exec();
}
