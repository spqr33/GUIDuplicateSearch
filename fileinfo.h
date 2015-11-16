#ifndef FILEINFO_H
#define FILEINFO_H
#include <QSharedPointer>
#include "md5hash.h"

class AbstractHash;

class FileInfo
{
public:
    FileInfo(const QString& fullname, quint64 size, const QString& tag);

    const QString&  fullName() const    { return fullName_;}
    quint64         size() const        { return size_; }
    const QString&  tag() const         { return tag_; }

    void            setHash(QSharedPointer<AbstractHash> spHash);
 private:
     QString                        fullName_;
     quint64                        size_;
     QSharedPointer<AbstractHash>   spHash_;
     QString                        tag_;
};

#endif // FILEINFO_H
