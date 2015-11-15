#include "samesizeholderbuild_thread.h"
#include <QMutexLocker>
#include <QDebug>

SameSizeHolderBuildThread::SameSizeHolderBuildThread(QObject* parrent) :
    QThread(parrent)
{
    abort_ = false;
    restart_= false;
}

SameSizeHolderBuildThread::~SameSizeHolderBuildThread()
{
        if ( isRunning() ) {
            QMutexLocker locker(&mutex_);

            abort_ = true;
            waitCondition_.wakeOne();
        }

        wait();
}

void SameSizeHolderBuildThread::build(QSharedPointer<FilesInfoHolder> spFilesInfoHolder)
{
    QMutexLocker locker(&mutex_);
    spFilesInfoHolder_ = spFilesInfoHolder;

    if ( isRunning() ) {
        restart_ = true;
        waitCondition_.wakeOne();
    } else {
        start();
    }
}

void SameSizeHolderBuildThread::run()
{
    forever {
        mutex_.lock();
        QSharedPointer<FilesInfoHolder> spFilesInfoHolder = spFilesInfoHolder_;
        mutex_.unlock();

        QSharedPointer<SameSizeHolder> spSameSizeHolder( new SameSizeHolder());

        ///
        spFilesInfoHolder->sort();
        {
            QMutexLocker holdLock(&spFilesInfoHolder->mutexHolder_);
            if ( !spFilesInfoHolder->holder_.empty() ) {
                typedef QVector<QSharedPointer<FileInfo> >::ConstIterator Iter;

                Iter iter1 = spFilesInfoHolder->holder_.begin();
                Iter iter2 = iter1;
                Iter iterEnd = spFilesInfoHolder->holder_.cend();

                for ( quint64 sameSizeCounter = 0; iter2 != iterEnd; sameSizeCounter = 0 ) {
                    mutex_.lock();
                    if (restart_) break;
                    if (abort_) break;
                    mutex_.unlock();

                    while (iter2 != iterEnd) {
                        if ( (*iter2)->size() == (*iter1)->size() ) {
                            ++iter2;
                            ++sameSizeCounter;
                        } else {
                            break;
                        }
                    }
                    if ( sameSizeCounter > 1 ) {
                        for ( quint64 size = (*iter1)->size(); sameSizeCounter > 0; ++iter1, --sameSizeCounter ) {
                            spSameSizeHolder->addPair(size, *iter1);
                        }
                    }
                    iter1 = iter2;
                }
            }
        } // QMutexLocker holdLock(&spFilesInfoHolder->mutexHolder_) unlocked here
        qDebug() << "emitting SameSizeHolderBuilt(spSameSizeHolder)";
        emit SameSizeHolderBuilt(spSameSizeHolder);
        qDebug() << "emitted SameSizeHolderBuilt(spSameSizeHolder)";
        ///
        mutex_.lock();
        while(!restart_){
            waitCondition_.wait(&mutex_);
        }
        restart_ = false;
        mutex_.unlock();
    }
}
