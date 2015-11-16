#include "abstracthash.h"

QString AbstractHash::getHashName(AbstractHash::Algo name)
{
    if( name == Algo::MD5 ) {
        //moved down
    }
    return QString("md5");
}
