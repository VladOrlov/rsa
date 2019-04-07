#include <fstream>
#include "BigInteger.h"

struct RsaKey {
    BigInteger a;
    BigInteger b;

    bool retrieveFromFile(const char *filename) {
        BigInteger temp(800);

        ifstream in(filename);
        if (in.good()) {
            in >> temp;
            a = temp;
            in >> temp;
            b = temp;
            in.close();
            return true;
        }
        return false;
    }

    bool saveToFile(const char *filename) {
        ofstream out(filename);
        if (out.good()) {
            out << a << endl;
            out << b << endl;
            out.close();
            return true;
        }
        return false;
    }
};