#include "filesystemtraverserthread.h"
#include <QMutexLocker>
#include <QDir>
#include <QSharedPointer>
#include <QQueue>
#include <QFileInfoList>
#include <QScopedPointer>
#include <QDebug>

FileSystemTraverserThread::FileSystemTraverserThread(QObject* parrent) :
    QThread(parrent)
{
    restart_ = false;
    abort_  = false;
    if (parrent != 0){
        connect(this, SIGNAL(filesInfoHolderBuilded(QSharedPointer<FilesInfoHolder>)),
                parrent, SIGNAL(filesInfoHolderBuilded(QSharedPointer<FilesInfoHolder>)));
    }
}

FileSystemTraverserThread::~FileSystemTraverserThread()
{
    {
        QMutexLocker locker(&mutex_);
        abort_ = true;
        waitCondition_.wakeAll();
    }

    wait();
}

void FileSystemTraverserThread::traverse(const QString& initPath, const QString& tag) {
    QMutexLocker locker(&mutex_);
    // Set start information here
    path_   =   initPath;
    tag_    =   tag;
    //

    if(!isRunning()) {
        start();
    } else {
        restart_ = true;
        waitCondition_.wakeOne();
    }
}

void FileSystemTraverserThread::run()
{
    forever {
        mutex_.lock();
        QString path = path_;
        QString tag = tag_;
        mutex_.unlock();

        QSharedPointer<FilesInfoHolder> spInfoHolder(new FilesInfoHolder());

        QQueue<QSharedPointer<QDir> > q;
        q.push_back(QSharedPointer<QDir>(new QDir(path)));

        do {
            {
                QMutexLocker locker(&mutex_);
                if ( abort_ ) {
                    return;
                }
                if ( restart_ ){
                    break;
                }
            }
            QSharedPointer<QDir> spDirectory(q.dequeue());
            spDirectory->setFilter(QDir::NoDotAndDotDot|QDir::Dirs|QDir::Files);

            QScopedPointer<QFileInfoList> spList(new QFileInfoList(spDirectory->entryInfoList()));
            if (spList->size() > 2) {
                QList<QFileInfo> ::iterator iter = spList->begin();
                if (spList->size() > 10 ) {
                    QMutexLocker locker(&mutex_);
                    if ( abort_ || restart_ ) {
                        continue;
                    }
                 }

                for ( ; iter != spList->end(); ++ iter ) {
                    if (iter->isDir()) {
                        QSharedPointer<QDir> spDir(new QDir(iter->absoluteFilePath()));
                        q.enqueue(spDir);
                    }
                    if (iter->isFile()) {
                        const QString   fileName = iter->absoluteFilePath();
                        quint64         size = iter->size();
                        FileInfo* f = new FileInfo(fileName, size, tag);

                        spInfoHolder->add(QSharedPointer<FileInfo>(f));
                        //qDebug() << iter->absoluteFilePath();
                    }
                }
            }
        } while(!q.empty());
        qDebug() << " emitting filesInfoHolderBuilded(spInfoHolder)";
        emit filesInfoHolderBuilded(spInfoHolder);
        qDebug() << " was emitted filesInfoHolderBuilded(spInfoHolder)";
        /////////
        mutex_.lock();
        while(restart_ == false)
            waitCondition_.wait(&mutex_);
        restart_ = false;
        mutex_.unlock();
    }
}
