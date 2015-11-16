#ifndef MD5HASH_H
#define MD5HASH_H

#include "abstracthash.h"

class FileInfo;

class Md5Hash : public AbstractHash {
public:
    Md5Hash();
    virtual ~Md5Hash();

    virtual bool fileHashCalculate(QSharedPointer<FileInfo> spFileInfo);
    virtual const QString& getDigest() const { return digest_; }
private:
    QString digest_;
    static const uint32_t blockSize_ = 512;
};

#endif // MD5HASH_H
