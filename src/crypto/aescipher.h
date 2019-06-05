#ifndef AESCIPHER_H
#define AESCIPHER_H

#include "blockcipher.h"

class AesCipher : public BlockCipher
{
public:
    AesCipher(size_t keySize);
    virtual ~AesCipher();

    void generateKey() override;
    void setKey(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) override;

    void saveSecretKey() const override;
    void loadSecretKey() override;

    void encryptFile(const QString& filePath) const override;
    void decryptFile(const QString& filePath) const override;
};

#endif // AESCIPHER_H
