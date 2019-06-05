#include "rsacryptor.h"
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

void RSACryptor::genereateRandomKeyParams()
{
    params_.GenerateRandomWithKeySize(rng_, 4096);
}

void RSACryptor::generatePrivateKey()
{
    rsa_private_ = params_;
}

void RSACryptor::generatePublicKey()
{
    rsa_public_ = params_;
}

void RSACryptor::savePrivateKey(const std::string& filename, const PrivateKey& key)
{
    ByteQueue queue;
    key.Save(queue);
    saveHex(filename, queue);
}

void RSACryptor::savePublicKey(const std::string& filename, const PublicKey& key)
{
    ByteQueue queue;
    key.Save(queue);
    saveHex(filename, queue);
}

void RSACryptor::saveHex(const std::string& filename, const BufferedTransformation& bt)
{
    HexEncoder hex_encoder;
    bt.CopyTo(hex_encoder);
    hex_encoder.MessageEnd();
    save(filename, hex_encoder);
}

void RSACryptor::save(const std::string& filename, const BufferedTransformation& bt)
{
    FileSink file(filename.c_str());
    bt.CopyTo(file);
    file.MessageEnd();
}


void RSACryptor::loadPrivateKey(const std::string& filename, const CryptoPP::PrivateKey& key)
{
    ByteQueue queue;
    key.Save(queue);

    save(filename, queue);
}

void RSACryptor::loadPublicKey(const std::string& filename, const CryptoPP::PublicKey& key)
{
    ByteQueue queue;
    loadHex(filename, queue);
//    key.Load(queue);
}

void RSACryptor::loadHex(const std::string& filename, const BufferedTransformation& bt)
{
    load(filename, bt);
    HexDecoder hex_decoder;
    bt.CopyTo(hex_decoder);
    hex_decoder.MessageEnd();
}

void RSACryptor::load(const std::string& filename, const BufferedTransformation& bt)
{
    FileSource file(filename.c_str(), true);
//    file.TransferTo(bt);
//    bt.MessageEnd();
}
