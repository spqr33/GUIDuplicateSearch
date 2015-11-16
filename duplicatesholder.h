#ifndef DUPLICATESHOLDER_H
#define DUPLICATESHOLDER_H
#include <QSharedPointer>
#include "fileinfo.h"
#include <QMap>
#include <QList>
#include <QMutex>
#include <duplicatesbuild_thread.h>

class DuplicatesBuildThread;

class DuplicatesHolder
{
    friend class DuplicatesBuildThread;
public:
    typedef QMap< QString, QList<QSharedPointer<FileInfo> > > HolderType;

    DuplicatesHolder();
    inline void addPair(const QString& hash, QSharedPointer<FileInfo> spFileInfo);
    void deleteNodeWithOutDupliactes();
private:
    DuplicatesHolder(const DuplicatesHolder& orig) = delete;
    DuplicatesHolder& operator=(const DuplicatesHolder& rhs) = delete;

    HolderType  holder_;
    mutable QMutex  mutexHolder_;
};

Q_DECLARE_METATYPE(QSharedPointer<DuplicatesHolder>)

void DuplicatesHolder::addPair(const QString &hash, QSharedPointer<FileInfo> spFileInfo)
{
    QMutexLocker locker(&mutexHolder_);
    holder_[hash].push_front(spFileInfo);
}

#endif // DUPLICATESHOLDER_H
