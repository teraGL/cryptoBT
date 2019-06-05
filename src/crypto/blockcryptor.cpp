#include "blockcryptor.h"

BlockCryptor::BlockCryptor()
    : block_cipher_{nullptr}
{
}

void BlockCryptor::generateKey() const
{
    block_cipher_->generateKey();
}

void BlockCryptor::saveSecretKey() const
{
    block_cipher_->saveSecretKey();
}

void BlockCryptor::loadSecretKey() const
{
    block_cipher_->loadSecretKey();
}

void BlockCryptor::encryptFile(const QString& filePath) const
{
    block_cipher_->encryptFile(filePath);
}

void BlockCryptor::decryptFile(const QString& filePath) const
{
    block_cipher_->decryptFile(filePath);
}
