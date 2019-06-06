#include "twofishcipher.h"
#include <cryptopp/twofish.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

TwofishCipher::TwofishCipher(size_t keySize)
{
    if (keySize == 128)
        key_size_ = Twofish::DEFAULT_KEYLENGTH;
    else if (keySize == 256)
        key_size_ = Twofish::MAX_KEYLENGTH;
    else
        key_size_ = 24;
}

TwofishCipher::~TwofishCipher()
{
    qDebug() << "Twofish removed";
}

void TwofishCipher::generateKey()
{
    AutoSeededRandomPool prng;

    SecByteBlock key(key_size_);
    prng.GenerateBlock(key, key.size());

    SecByteBlock iv(Twofish::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());

    setKey(key, iv);
}

void TwofishCipher::setKey(const SecByteBlock& key, const SecByteBlock& iv)
{
    key_ = key;
    iv_ = iv;
    key_size_ = key.size();
}

void TwofishCipher::saveSecretKey(const QString &filePath) const
{
    std::cerr << "Saving Twofish secret key and IV..." << std::endl;

    std::string iv_content;
    ArraySource(iv_, iv_.size(), true, new HexEncoder(new StringSink(iv_content)));

    iv_content += "2";
    if (key_size_ == 32)
        iv_content += "1";
    else if (key_size_ == 24)
        iv_content += "2";
    else
        iv_content += "3";

    const std::string secretKeyFile(iv_content + ".crb");
    ArraySource(key_, key_.size(), true, new HexEncoder(new FileSink(secretKeyFile.c_str())));

//    const std::string filename_prefix = "__Twofish_" + std::to_string(key_size_);
//    const std::string sec_key_file = filename_prefix + "_SecretKey.crb";
//    const std::string iv_file = filename_prefix + "_IV.iv";

//    ArraySource(key_, key_.size(), true, new HexEncoder(new FileSink(sec_key_file.c_str())));
//    ArraySource(iv_, iv_.size(), true, new HexEncoder(new FileSink(iv_file.c_str())));
}

void TwofishCipher::loadSecretKey()
{
    std::cerr << "Loading Twofish SecKey and IV..." << std::endl;

    const std::string filename_prefix = "__Twofish_" + std::to_string(key_size_);
    const std::string sec_key_file = filename_prefix + "_SecretKey.crb";
    const std::string iv_file = filename_prefix + "_IV.iv";

    key_.resize(key_size_);
    FileSource(sec_key_file.c_str(), true, new HexDecoder(new ArraySink(key_.begin(), key_.size())));

    iv_.resize(Twofish::BLOCKSIZE);
    FileSource(iv_file.c_str(), true, new HexDecoder(new ArraySink(iv_.begin(), iv_.size())));
}

void TwofishCipher::encryptFile(const QString& filePath) const
{
    const QString fileEncryptedExt = createDefaultSeedingDir()
                                     + QFileInfo(filePath).fileName() + ".enf";
    const auto outFile = fileEncryptedExt.toUtf8().constData();

    try {
        CBC_Mode<Twofish>::Encryption encryptor(key_, key_size_, iv_);
        FileSource fs(filePath.toUtf8().constData(), true,
                      new StreamTransformationFilter(encryptor,
                          new FileSink(outFile)));

        const QString outputMessage = "Encrypt to '" + fileEncryptedExt + "' using Twofish-"
                                      + QString::number(8 * key_size_);
        qDebug() << outputMessage;
    } catch (const Exception& e) {
        qDebug() << e.what();
        return;
    }
}

void TwofishCipher::decryptFile(const QString& filePath) const
{
    const QByteArray inFile = QFileInfo(filePath).filePath().toUtf8();
    const QByteArray outFile = inFile + ".clear";

    try {
        CBC_Mode<Twofish>::Decryption decryptor(key_, key_size_, iv_);
        FileSource fs(inFile.constData(), true,
                      new StreamTransformationFilter(decryptor,
                          new FileSink(outFile.constData())));

        const QString outputMessage = "Decrypt to '" + outFile + "' using Twofish-"
                                      + QString::number(8 * key_size_);
        qDebug() << outputMessage;
    } catch (const Exception& e) {
        qDebug() << e.what();
        return;
    }
}
