#include "fileinfo.h"

FileInfo::FileInfo(const QString& fullname, quint64 size, const QString& tag) :
    fullName_(fullname), size_(size), tag_(tag)
{

}

void FileInfo::setHash(QSharedPointer<AbstractHash> spHash)
{
    spHash_ = spHash;
}

