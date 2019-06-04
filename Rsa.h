#include "RsaKey.h"
#include <fstream>


using namespace std;


class Rsa {
public:
    //extended Euclidean algorithm
    void static extEuclid(BigInteger a, BigInteger b, BigInteger &y);

    BigInteger gcd(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y);

    //Generate public and private keys
    void static generateKeys(RsaKey &publicKey, RsaKey &privateKey);

    //encrypt a string
    BigInteger static encrypt(string &data, const vector<char> &a, const BigInteger &b);

    //decrypt a string
    string static decrypt(BigInteger &data, const vector<char> &a, const BigInteger &b);

    //encrypt a text file
    void static encryptTxtFile(const char *sourceFile, const char *targetFile, RsaKey &key);

    //decrypt a text file
    void static decryptTxtFile(const char *in, const char *out, RsaKey &key);
};