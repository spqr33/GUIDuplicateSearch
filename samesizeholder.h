#ifndef SAMESIZEHOLDER_H
#define SAMESIZEHOLDER_H

#include <QMap>
#include <QList>
#include <QSharedPointer>
#include "fileinfo.h"
#include <QMutex>
#include <QObject>
//#include "samesizewidget.h"

class SameSizeHolder : public QObject
{
    Q_OBJECT
    friend class SameSizeWidget;
public:
    typedef quint64 fileSize;
    typedef QMap< fileSize, QList<QSharedPointer<FileInfo> > > HolderType;

    explicit        SameSizeHolder(QObject* parrent = 0);
    virtual         ~SameSizeHolder();

    inline void     addPair(quint64 fileSize, QSharedPointer<FileInfo> spFileInfo);
private:
    HolderType      holder_;
    mutable QMutex  mutexHolder_;

    SameSizeHolder(const SameSizeHolder& orig) = delete;
    const SameSizeHolder& operator=(const SameSizeHolder& rhs) = delete;
};

Q_DECLARE_METATYPE(QSharedPointer<SameSizeHolder>)

void SameSizeHolder::addPair(quint64 fileSize, QSharedPointer<FileInfo> spFileInfo)
{
    QMutexLocker locker(&mutexHolder_);
    holder_[fileSize].push_back(spFileInfo);
}

#endif // SAMESIZEHOLDER_H
