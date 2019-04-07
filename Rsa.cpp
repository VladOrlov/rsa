#include "Rsa.h"

//key length (decimal digits)
#define KEY_LENGTH 80


void Rsa::generateKeys(RsaKey &publicKey, RsaKey &privateKey) {
    BigInteger p(KEY_LENGTH / 2);
    BigInteger q(KEY_LENGTH / 2);
    BigInteger d(KEY_LENGTH - 3);
    BigInteger n, eilerFunc, divider, e;

    //getting 2 prime numbers
    while (!p.prime())
        p.random(KEY_LENGTH / 2);

    while (!q.prime())
        q.random(KEY_LENGTH / 2);

    n = p * q;


    //Euler's function
    eilerFunc = (p - 1) * (q - 1);

    //getting private and public exponents
    do {
        do {
            d.random(KEY_LENGTH - 3);
            divider = d.getMaxDivider(eilerFunc);
        } while (divider != 1);

        extEuclid(eilerFunc, d, e);
    } while (e < 0);


    //keys
    publicKey.a = d;
    publicKey.b = n;
    privateKey.a = e;
    privateKey.b = n;


    /*
    vector <char> a = d.toBinary();
    BigInteger message = 153;
    BigInteger crypt;
    BigInteger decrypt;


    crypt = message.calcPowMod(a,n);


    a = e.toBinary();
    decrypt = crypt.calcPowMod(a,n);


    if (message == decrypt)
    cout << "Test passed\n";
    else
    cout << "Test failed\n";
    */
}


//extended Euclidean algorithm
// y - private exponent
void Rsa::extEuclid(BigInteger a, BigInteger b, BigInteger &y) {
    BigInteger r, q, a11, a12, a21, a22;
    BigInteger A11, A12, A21, A22;
    a11 = 1, a12 = 0, a21 = 0, a22 = 1;

    while (b > 0) {
        r = a % b;
        q = a / b;
        if (r == 0) {
            break;
        }

        A11 = a12;
        A12 = a11 + a12 * -q;
        A21 = a22;
        A22 = a21 + a22 * -q;

        a11 = A11, a12 = A12, a21 = A21, a22 = A22;

        a = b;
        b = r;
    }
    y = a22;
}

BigInteger Rsa::gcd(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    BigInteger x1, y1;
    BigInteger d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;

    return d;
}

//encrypt a string (a,b - values from key)
BigInteger Rsa::encrypt(string &data, const vector<char> &a, const BigInteger &b) {
    BigInteger block;
    block = 1;

    if (data.length() > (KEY_LENGTH - 4) / 3)
        throw RsaException("size of the input string is exceeds size limit");

    //input string > BigInteger
    //the first digit = 1, next 3 digits = code
    for (unsigned int i = 0; i < data.length(); i++) {
        BigInteger buff;
        buff = int(data[i]);

        //cp1251 support
        if (buff < 0)
            buff = 256 + buff;

        block = block * int(pow(10.0, 3 - buff.size()));
        block.concat(buff);
    }
    //encryption
    return block.calcPowMod(a, b);
}


//decrypt a string (a,b - values from key)
string Rsa::decrypt(BigInteger &data, const vector<char> &a, const BigInteger &b) {
    stringstream strStream;
    BigInteger temp, block;
    int bf;
    string buffer, res;

    block = data.calcPowMod(a, b);

    while (block.size() > 3) {
        temp = block;
        block = block / 1000;

        strStream.clear();
        strStream << temp - block * 1000;
        strStream >> bf;

        //cp1251 support
        if (bf > 127) {
            bf = bf - 256;
        }

        buffer += char(bf);
    }

    if (block != 1) {
        throw RsaException("Wrong input data!");
    }

    for (int i = buffer.length() - 1; i >= 0; i--) {
        res += buffer[i];
    }

    return res;
}


/*
 * Read data from source file,
 * encrypt data and save result to the target file
 */
void Rsa::encryptTxtFile(const char *sourceFile, const char *targetFile, RsaKey &key) {
    string buff;
    vector<char> a = key.a.toBinary();

    ifstream input(sourceFile);
    if (!input.good()) {
        throw RsaException("Failed to open input file");
    }
    ofstream output(targetFile);
    if (!output.good()) {
        throw RsaException("Failed to create output file");
    }

    while (!input.eof()) {
        buff.clear();

        for (int i = 0; i < (KEY_LENGTH - 4) / 3; i++) {
            char bf = input.get();
            if (input.eof()) {
                break;
            }
            buff += bf;
        }

        if (!buff.empty()) {
            output << encrypt(buff, a, key.b) << " ";
        }
    }

    input.close();
    output.close();
}


//decrypt the text file in, result to the text file out
void Rsa::decryptTxtFile(const char *in, const char *out, RsaKey &key) {
    vector<char> a = key.a.toBinary();
    BigInteger buff(KEY_LENGTH * 2);

    ifstream input(in);
    if (!input.good()) {
        throw RsaException("Failed to open input file");
    }
    ofstream output(out);
    if (!output.good()) {
        throw RsaException("Failed to create output file");
    }
    while (true) {
        input >> buff;
        if (input.eof()) {
            break;
        }
        output << decrypt(buff, a, key.b);
    }

    input.close();
    output.close();
}