#include "Rsa.h"
#include <ctime>


using namespace std;


int main(int argc, char *argv[]) {
    srand(time(0));

    cout << "RSA Encryption/Decryption\n";

    try {
        if (argc < 4)
            throw ArgumentException();

        if (argv[1][0] == 'e') {
            if (argc == 4) {
                RsaKey publicKey, privateKey;


                ifstream test(argv[2]);
                if (!test.good())
                    throw FileIOException(argv[2]);
                test.close();


                cout << "Generating keys...\n";
                Rsa::generateKeys(publicKey, privateKey);
                publicKey.saveToFile("public_key");
                privateKey.saveToFile("private_key");


                cout << "Encrypting data...\n";
                Rsa::encryptTxtFile(argv[2], argv[3], publicKey);
            } else if (argc == 5) {
                RsaKey publicKey;


                if (!publicKey.retrieveFromFile(argv[4]))
                    throw FileIOException(argv[4]);


                cout << "Encrypting data...\n";
                Rsa::encryptTxtFile(argv[2], argv[3], publicKey);
            } else
                throw ArgumentException();
        } else if (argv[1][0] == 'g') {
            if (argc == 4) {
                RsaKey publicKey, privateKey;
                cout << "Generating keys...\n";

                Rsa::generateKeys(publicKey, privateKey);

                publicKey.saveToFile(argv[2]);
                privateKey.saveToFile(argv[3]);
            } else
                throw ArgumentException();
        } else if (argv[1][0] == 'd') {
            if (argc == 5) {
                RsaKey privateKey;


                if (!privateKey.retrieveFromFile(argv[4]))
                    throw FileIOException(argv[4]);


                cout << "Decrypting...\n";
                Rsa::decryptTxtFile(argv[2], argv[3], privateKey);
            } else
                throw ArgumentException();
        } else
            throw ArgumentException();


    }
    catch (RsaException &err) {
        cout << "Error (Rsa): " << err.getCause() << endl;
        return 1;
    }
    catch (MathException &err) {
        cout << "Error (BigInteger): " << err.getCause() << endl;
        return 1;
    }
    catch (ArgumentException) {
        cout << "Usage:\n";
        cout << " e <in> <out> <public_key_path> - Encrypt data from the file <in> to <out>.\n";
        cout << "    If the key is not specified, it will be automatically\n";
        cout << "    created and saved in the current directory.\n\n";
        cout << " g <pb_key_path> <pr_key_path> - Generate keys.\n\n";
        cout << " d <in> <out> <private_key_path> - Encrypt data from the file <in> to <out>.\n";
    }
    catch (FileIOException &err) {
        cout << "Error: unable to open file " << err.getFilename() << endl;
        return 1;
    }


    return 0;
}
