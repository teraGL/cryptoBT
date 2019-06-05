#ifndef RSACRYPTOR_H
#define RSACRYPTOR_H

#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/cryptlib.h>

class RSACryptor
{
public:
    void genereateRandomKeyParams();

    void generatePrivateKey();
    void generatePublicKey();

    void savePrivateKey(const std::string& filename, const CryptoPP::PrivateKey& key);
    void savePublicKey(const std::string& filename, const CryptoPP::PublicKey& key);

    void loadPrivateKey(const std::string& filename, const CryptoPP::PrivateKey& key);
    void loadPublicKey(const std::string& filename, const CryptoPP::PublicKey& key);

private:
    void saveHex(const std::string& filename, const CryptoPP::BufferedTransformation& bt);
    void loadHex(const std::string& filename, const CryptoPP::BufferedTransformation& bt);
    void save(const std::string& filename, const CryptoPP::BufferedTransformation& bt);
    void load(const std::string& filename, const CryptoPP::BufferedTransformation& bt);

    CryptoPP::InvertibleRSAFunction params_;
    CryptoPP::AutoSeededRandomPool rng_;
    CryptoPP::RSA::PrivateKey rsa_private_;
    CryptoPP::RSA::PublicKey rsa_public_;
};

#endif // RSACRYPTOR_H
