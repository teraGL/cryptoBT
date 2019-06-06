#ifndef SERPETCIPHER_H
#define SERPETCIPHER_H

#include "blockcipher.h"

class SerpentCipher : public BlockCipher
{
public:
    SerpentCipher(size_t keySize);
    virtual ~SerpentCipher();

    void generateKey() override;
    void setKey(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) override;

    void saveSecretKey(const QString& filePath) const override;
    void loadSecretKey() override;

    void encryptFile(const QString& filePath) const override;
    void decryptFile(const QString& filePath) const override;
};

#endif // SERPETCIPHER_H
