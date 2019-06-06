#ifndef BLOCKCIPHER_H
#define BLOCKCIPHER_H

#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>
#include <cryptopp/modes.h>
#include <cryptopp/secblock.h>

#include <QString>
#include <QFileInfo>
#include <QDebug>


class BlockCipher
{
public:
    virtual ~BlockCipher() {}

    virtual void generateKey() = 0;
    virtual void setKey(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) = 0;

    virtual void saveSecretKey(const QString& filePath) const = 0;
    virtual void loadSecretKey() = 0;

    virtual void encryptFile(const QString& filePath) const = 0;
    virtual void decryptFile(const QString& filePath) const = 0;

protected:
    CryptoPP::SecByteBlock key_;
    CryptoPP::SecByteBlock iv_;
    size_t key_size_;
};

QString createDefaultSeedingDir();
QString createDirForFileWithKey(const QString &dirname);

#endif // BLOCKCIPHER_H
