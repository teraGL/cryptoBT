#include "camelliacipher.h"
#include <cryptopp/camellia.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

CamelliaCipher::CamelliaCipher(size_t keySize)
{
    if (keySize == 128)
        key_size_ = Camellia::DEFAULT_KEYLENGTH;
    else if (keySize == 256)
        key_size_ = Camellia::MAX_KEYLENGTH;
    else
        key_size_ = 24;
}

CamelliaCipher::~CamelliaCipher()
{
    qDebug() << "Camellia removed";
}

void CamelliaCipher::generateKey()
{
    AutoSeededRandomPool prng;

    SecByteBlock key(key_size_);
    prng.GenerateBlock(key, key.size());

    SecByteBlock iv(Camellia::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());

    setKey(key, iv);
}

void CamelliaCipher::setKey(const SecByteBlock& key, const SecByteBlock& iv)
{
     key_ = key;
     iv_ = iv;
     key_size_ = key.size();
}

void CamelliaCipher::saveSecretKey() const
{
    std::cerr << "Saving Camellia secret key and IV..." << std::endl;

    const std::string filename_prefix = "__Camellia_" + std::to_string(key_size_);
    const std::string sec_key_file = filename_prefix + "_SecretKey.crb";
    const std::string iv_file = filename_prefix + "_IV.iv";

    ArraySource(key_, key_.size(), true, new HexEncoder(new FileSink(sec_key_file.c_str())));
    ArraySource(iv_, iv_.size(), true, new HexEncoder(new FileSink(iv_file.c_str())));
}

void CamelliaCipher::loadSecretKey()
{
    std::cerr << "Loading Camellia SecKey and IV..." << std::endl;

    const std::string filename_prefix = "__Camellia_" + std::to_string(key_size_);
    const std::string sec_key_file = filename_prefix + "_SecretKey.crb";
    const std::string iv_file = filename_prefix + "_IV.iv";

    key_.resize(key_size_);
    FileSource(sec_key_file.c_str(), true, new HexDecoder(new ArraySink(key_.begin(), key_.size())));

    iv_.resize(Camellia::BLOCKSIZE);
    FileSource(iv_file.c_str(), true, new HexDecoder(new ArraySink(iv_.begin(), iv_.size())));
}

void CamelliaCipher::encryptFile(const QString& filePath) const
{
    const QString fileEncryptedExt = createDefaultSeedingDir()
                                     + QFileInfo(filePath).fileName() + ".enf";
    const auto outFile = fileEncryptedExt.toUtf8().constData();

    try {
        CBC_Mode<Camellia>::Encryption encryptor(key_, key_size_, iv_);
        FileSource fs(filePath.toUtf8().constData(), true,
                      new StreamTransformationFilter(encryptor,
                          new FileSink(outFile)));

        const QString outputMessage = "Encrypt to '" + fileEncryptedExt + "' using camellia-"
                                      + QString::number(8 * key_size_);
        qDebug() << outputMessage;
    } catch (const Exception& e) {
        qDebug() << e.what();
        return;
    }
}

void CamelliaCipher::decryptFile(const QString& filePath) const
{
    const QByteArray inFile = QFileInfo(filePath).filePath().toUtf8();
    const QByteArray outFile = inFile + ".clear";

    try {
        CBC_Mode<Camellia>::Decryption decryptor(key_, key_size_, iv_);
        FileSource fs(inFile.constData(), true,
                      new StreamTransformationFilter(decryptor,
                          new FileSink(outFile.constData())));

        const QString outputMessage = "Decrypt to '" + outFile + "' using camellia-"
                                      + QString::number(8 * key_size_);
        qDebug() << outputMessage;
    } catch (const Exception& e) {
        qDebug() << e.what();
        return;
    }
}
