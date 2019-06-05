#ifndef GPGKEYCREATOR_H
#define GPGKEYCREATOR_H


class GPGKeyCreator
{
public:
    GPGKeyCreator();

    void generateKeys();
    void createPassphrase();
    void exportPrivateKey();
    void exportPublicKey();
};

#endif // GPGKEYCREATOR_H
