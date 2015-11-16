#include "md5hash.h"
#include <cassert>
#include <openssl/evp.h>
#include <fcntl.h>  // open() O_RDONLY
#include <unistd.h> //  read() close()
#include <cstdio>
#include <QScopedArrayPointer>
#include "fileinfo.h"
#include <QDebug>

Md5Hash::Md5Hash()
{
    digest_.reserve(128 /(sizeof(char)) + 1);
}

Md5Hash::~Md5Hash()
{

}

bool Md5Hash::fileHashCalculate(QSharedPointer<FileInfo> spFileInfo)
{
    assert(spFileInfo.data() && "Md5Hash::fileHashCalculate, Pointer is NULL");

    quint64 blocksQuantity = spFileInfo->size() / blockSize_;

    unsigned char mdValue[EVP_MAX_MD_SIZE]; // Hash will be here
    unsigned int mdLen; // Hash length

    OpenSSL_add_all_digests();

    const EVP_MD *md = EVP_get_digestbyname(getHashName(Algo::MD5).toStdString().c_str());
    if ( md == NULL ) {

        EVP_cleanup();
        return false;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_create();

    EVP_DigestInit_ex(mdctx, md, NULL);

    qint32 fileDescriptor = open(spFileInfo->fullName().toStdString().c_str(), O_RDONLY);
    if ( fileDescriptor <= 0 ) {

        EVP_MD_CTX_destroy(mdctx);
        EVP_cleanup();
        qDebug() << "Return false 1";
        return false;
    }

    QScopedArrayPointer<unsigned char> readBuff(new unsigned char[blockSize_]);
    quint32 readLength;
    for ( quint64 i = 0; i < blocksQuantity; ++i ) {
        readLength = read(fileDescriptor, &(*readBuff), blockSize_);
        if ( readLength != blockSize_ ) {

            close(fileDescriptor);
            EVP_MD_CTX_destroy(mdctx);
            EVP_cleanup();
            return false;
        }
        EVP_DigestUpdate(mdctx, &(*readBuff), readLength);
    };

    if ( spFileInfo->size() != blockSize_ * blocksQuantity ) {
        quint32 readLastBypes = spFileInfo->size() % blockSize_;
        readLength = read(fileDescriptor, &(*readBuff), readLastBypes);
        if ( readLength != readLastBypes ) {

            close(fileDescriptor);
            EVP_cleanup();
            EVP_MD_CTX_destroy(mdctx);
            return false;
        }
        EVP_DigestUpdate(mdctx, readBuff.data(), readLength);
    }
    EVP_DigestFinal_ex(mdctx, mdValue, &mdLen);

    char str[3] = {0};
    for ( unsigned int i = 0; i < mdLen; i++ ) {
        snprintf(str, 3, "%02x", mdValue[i]);
        str[2] ='\0'; //For reliability
        digest_.append(str);
    }

    EVP_MD_CTX_destroy(mdctx);
    close(fileDescriptor);
    EVP_cleanup(); // Cleans after OpenSSL_add_all_digests() OpenSSL_add_all_algorithms() OpenSSL_add_all_ciphers()

    return true;
}

