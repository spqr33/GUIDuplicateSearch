#ifndef ABSTRACTHASH_H
#define ABSTRACTHASH_H

#include <QSharedPointer>

class FileInfo;

class AbstractHash
{
public:
    enum class Algo { MD5 };

    AbstractHash() {}
    virtual ~AbstractHash() {}

    virtual bool fileHashCalculate(QSharedPointer<FileInfo> spFileInfo) = 0;

    virtual const QString& getDigest() const = 0;
    static QString getHashName(Algo name);
};

#endif // ABSTRACTHASH_H
