#ifndef FILESYSTEMTRAVERSERTHREAD_H
#define FILESYSTEMTRAVERSERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QObject>
#include "filesinfoholder.h"
#include "fileinfo.h"


class FileSystemTraverserThread : public QThread
{
    Q_OBJECT
public:
    explicit FileSystemTraverserThread(QObject* parrent = 0);
    ~FileSystemTraverserThread();

    void traverse(const QString& initialPath, const QString& tag);

protected:
    void run();

signals:
    void filesInfoHolderBuilded(QSharedPointer<FilesInfoHolder>);
private:
    bool restart_;
    bool abort_;
    QMutex mutex_;
    QWaitCondition waitCondition_;
    QString path_;
    QString tag_;
};

#endif // FILESYSTEMTRAVERSERTHREAD_H
