#ifndef FILESYSTEMTRAVERSERTHREAD_H
#define FILESYSTEMTRAVERSERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QObject>

class FileSystemTraverserThread : public QThread
{
    Q_OBJECT
public:
    FileSystemTraverserThread(QObject* parrent = 0);
    ~FileSystemTraverserThread();

    void traverse(const QString& initialPath);

protected:
    void run();

private:
    bool restart_;
    bool abort_;
    QMutex mutex_;
    QWaitCondition waitCondition_;
    QString path_;

};

#endif // FILESYSTEMTRAVERSERTHREAD_H
