#ifndef CAMELLIACIPHER_H
#define CAMELLIACIPHER_H

#include "blockcipher.h"

class CamelliaCipher : public BlockCipher
{
public:
    CamelliaCipher(size_t keySize);
    virtual ~CamelliaCipher();

    void generateKey() override;
    void setKey(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) override;

    void saveSecretKey() const override;
    void loadSecretKey() override;

    void encryptFile(const QString& filePath) const override;
    void decryptFile(const QString& filePath) const override;
};

#endif // CAMELLIACIPHER_H
