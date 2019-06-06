#ifndef BLOCKCRYPTOR_H
#define BLOCKCRYPTOR_H

#include "aescipher.h"
#include "serpentcipher.h"
#include "twofishcipher.h"
#include "camelliacipher.h"

#include <memory>

class BlockCryptor
{
public:
    BlockCryptor();

    template<class T>
    void setCipher(size_t keySize) { block_cipher_.reset(new T(keySize)); }

    void generateKey() const;

    void saveSecretKey(const QString& filePath) const;
    void loadSecretKey() const;

    void encryptFile(const QString& filePath) const;
    void decryptFile(const QString& filePath) const;

private:
    std::unique_ptr<BlockCipher> block_cipher_;
};

#endif // BLOCKCRYPTOR_H

