#include "filesystemtraverserthread.h"
#include <QMutexLocker>
#include <QDir>
#include <QSharedPointer>
#include <QQueue>
#include <QFileInfoList>
#include <QScopedPointer>

FileSystemTraverserThread::FileSystemTraverserThread(QObject* parrent) :
    QThread(parrent)
{
    restart_ = false;
    abort_  = false;
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

void FileSystemTraverserThread::traverse(const QString& initPath) {
    QMutexLocker locker(&mutex_);
    // Set start information here
    path_ = initPath;
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
        mutex_.unlock();

        //TODO reset FileMetaDataHolder + its mutex

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
                        // Put it into holder.
                    }
                }
            }
        } while(!q.empty());

      /////////
        mutex_.lock();
        while(restart_ == false)
            waitCondition_.wait(&mutex_);
        restart_ = false;
        mutex_.unlock();
    }
}
