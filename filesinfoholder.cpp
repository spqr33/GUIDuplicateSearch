#include "filesinfoholder.h"
#include <algorithm>

FilesInfoHolder::FilesInfoHolder(QObject* parrent) :
    QObject(parrent)
{
    holder_.reserve(128);
    //qRegisterMetaType<SP_FilesInfoHolder>("SP_FilesInfoHolder");
    //qRegisterMetaType<QSharedPointer<FilesInfoHolder> >();
}

void FilesInfoHolder::sort()
{
    QMutexLocker locker(&mutexHolder_);

    if ( sorted_ == false) {
        std::sort(holder_.begin(), holder_.end(),
                  [](QSharedPointer<FileInfo> a, QSharedPointer<FileInfo> b) -> bool{
                  if ( a->size() < b->size() ){
                      return true;
                  }
                  return false;
        });
    }
}

