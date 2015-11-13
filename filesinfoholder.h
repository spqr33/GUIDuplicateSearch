#ifndef FILESINFOHOLDER_H
#define FILESINFOHOLDER_H
#include "fileinfo.h"
#include <QVector>
#include <QSharedPointer>
#include <QMutex>
#include <QMutexLocker>

class FilesInfoHolder
{
public:
    FilesInfoHolder();

    inline void add(QSharedPointer<FileInfo> fileInfo);
protected:
    ~FilesInfoHolder();
private:
    FilesInfoHolder(const FilesInfoHolder& orig) = delete;
    const FilesInfoHolder& operator=(const FilesInfoHolder& rhs) = delete;

    QVector<QSharedPointer<FileInfo> > holder_;
    QMutex mutexHolder_;
};

void FilesInfoHolder::add(QSharedPointer<FileInfo> fileInfo) {
    QMutexLocker locker(&mutexHolder_);
    holder_.push_back(fileInfo);
}

#endif // FILESINFOHOLDER_H
