#ifndef TWOFISHCIPHER_H
#define TWOFISHCIPHER_H

#include "blockcipher.h"

class TwofishCipher : public BlockCipher
{
public:
    TwofishCipher(size_t keySize);
    virtual ~TwofishCipher();

    void generateKey() override;
    void setKey(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) override;

    void saveSecretKey() const override;
    void loadSecretKey() override;

    void encryptFile(const QString& filePath) const override;
    void decryptFile(const QString& filePath) const override;
};

#endif // TWOFISHCIPHER_H
