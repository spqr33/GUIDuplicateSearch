#ifndef FILESINFOHOLDER_H
#define FILESINFOHOLDER_H
#include "fileinfo.h"
#include <QVector>
#include <QSharedPointer>
#include <QMutex>
#include <QMutexLocker>
#include "samesizeholderbuild_thread.h"
#include <QObject>

class FilesInfoHolder : public QObject
{
    Q_OBJECT
    friend class SameSizeHolderBuildThread;
public:
    FilesInfoHolder(QObject* parrent = 0);

    inline void add(QSharedPointer<FileInfo> fileInfo);
    //virtual ~FilesInfoHolder() {};

    inline bool isSorted() const;
    void sort();
private:
    FilesInfoHolder(const FilesInfoHolder& orig) = delete;
    const FilesInfoHolder& operator=(const FilesInfoHolder& rhs) = delete;

    QVector<QSharedPointer<FileInfo> > holder_;
    mutable QMutex mutexHolder_;
    bool sorted_;
};

Q_DECLARE_METATYPE(QSharedPointer<FilesInfoHolder>)

void FilesInfoHolder::add(QSharedPointer<FileInfo> fileInfo) {
    QMutexLocker locker(&mutexHolder_);
    holder_.push_back(fileInfo);
    sorted_ = false;
}

bool FilesInfoHolder::isSorted() const
{
    QMutexLocker locker(&mutexHolder_);

    return sorted_;
}

#endif // FILESINFOHOLDER_H
