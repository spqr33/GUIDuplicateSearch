#include "duplicatesholder.h"

DuplicatesHolder::DuplicatesHolder()
{

}

void DuplicatesHolder::deleteNodeWithOutDupliactes()
{
    QMutexLocker locker(&mutexHolder_);

    auto iter = holder_.begin();
    auto iterEnd = holder_.end();

    for (; iter != iterEnd; ) {
        if ( iter.value().size() <= 1 ) { // only one element in list
            iter = holder_.erase(iter);
        } else {
            ++iter;
        }
    }
}

