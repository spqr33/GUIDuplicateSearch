#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QTreeView>
//#include <QStandardItemModel>
#include <QFileSystemModel>
#include "filesystemtraverserthread.h"

class LeftWidget : public QWidget
{
    Q_OBJECT
private:
    QString             init_path_;
    QTreeView*          p_fs_view_;
    QFileSystemModel*   p_fs_model_;
    FileSystemTraverserThread*  thread_;
public:
    explicit LeftWidget(QWidget *parent = 0);

signals:
    void directory_loaded(const QString&);
    void filesInfoHolderBuilded(QSharedPointer<FilesInfoHolder>);

public slots:
    void slot_set_init_path();
    void slot_stub(QSharedPointer<FilesInfoHolder>);
};

#endif // LEFTWIDGET_H
