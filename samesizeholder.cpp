#include "samesizeholder.h"

SameSizeHolder::SameSizeHolder(QObject* parrent) :
    QObject(parrent)
{
    //qRegisterMetaType<QSharedPointer<SameSizeHolder> >("QSharedPointer<SameSizeHolder>");
}

SameSizeHolder::~SameSizeHolder()
{

}

