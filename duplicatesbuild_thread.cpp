#include "duplicatesbuild_thread.h"
#include <QMutexLocker>
#include "samesizeholder.h"
#include "duplicatesholder.h"
#include "md5hash.h"
#include <QDebug>

DuplicatesBuildThread::DuplicatesBuildThread(QObject* parrent) :
    QThread(parrent)
{
    abort_ = false;
    restart_ = false;
}

DuplicatesBuildThread::~DuplicatesBuildThread()
{
    if ( isRunning() ) {
        QMutexLocker locker(&mutex_);

        abort_ = true;
        waitCondition_.wakeOne();
    }

    wait();
}

void DuplicatesBuildThread::build(QSharedPointer<SameSizeHolder> spSameSizeHolder)
{
    QMutexLocker locker(&mutex_);

    spSameSize_ = spSameSizeHolder;
    if ( isRunning() ) {
        restart_ = true;
        waitCondition_.wakeOne();
    } else {
        start();
    }
}

void DuplicatesBuildThread::run()
{
    forever {
        mutex_.lock();
        QSharedPointer<SameSizeHolder> spSameSizeHolder = spSameSize_;
        mutex_.unlock();

        QSharedPointer<DuplicatesHolder> spDupHolder( new DuplicatesHolder);
        ///
        auto iter       = spSameSizeHolder->holder_.cbegin();
        auto iterEnd    = spSameSizeHolder->holder_.cend();

        for ( ; iter != iterEnd; ++iter ) {
            {
                QMutexLocker locker(&mutex_);
                if ( restart_ == true ) { break; }
                if ( abort_ == true ) { return; }
            }

            //auto iterList = iter.value().cbegin();
            //auto iterListEnd = iter.value().cend();

            for ( auto& spFileInfo: iter.value() ) {
                //static int j = 1;
                //qDebug() << j++;
                QSharedPointer<AbstractHash> spHash( new Md5Hash );
                bool res = spHash->fileHashCalculate(spFileInfo);

                if ( res == true ) {
                    spFileInfo->setHash(spHash);
                    qDebug() <<  spHash->getDigest();
                    spDupHolder->addPair(spHash->getDigest(), spFileInfo);
                }
            }
        }
        spDupHolder->deleteNodeWithOutDupliactes();
        qDebug() << spDupHolder->holder_.size();
        ///
        emit DuplicatesHolderBuilt(spDupHolder);

        // all done, sleep
        mutex_.lock();
        while(restart_ == false){
            waitCondition_.wait(&mutex_);
        }
        restart_ = false;
        mutex_.unlock();
    }
}

