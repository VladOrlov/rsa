/* 
* BigInteger - the class to work with a big integers.
* The capacity of the number can be given as an argument
* of the constructor(10 by default).
* This class is compatible with int.
*/


#include<iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include "exceptions.h"


using namespace std;


class BigInteger {
    short *number;
    unsigned int currentSize;
    unsigned int maxSize;
    //if true then number is positive
    bool positive;

    void reflect();

    //remove leading zeros (for example 00054 -> 54)
    void removeSpace();

    /*
     * return true if compared BigInteger object
     * bigger than current object in absolute value
     */
    bool isAbsBigger(const BigInteger &obj);

    //integer division/remainder
    BigInteger divMod(const BigInteger &obj, BigInteger &reminder);

public:
    BigInteger();

    BigInteger(unsigned int n);

    ~BigInteger();

    BigInteger(const BigInteger &obj);

    //add obj to the current value as string
    void concat(const BigInteger &obj);

    vector<char> toBinary();

    //get current size
    int size();

    //power
    BigInteger pow(const unsigned int power);

    //returns A^d(mod m)
    //A = *this
    BigInteger calcPowMod(const vector<char> &d, const BigInteger m);

    void random(unsigned int length);

    //returns true if this value is even
    bool even();

    //MillerRabin primality test
    bool prime();

    BigInteger getMaxDivider(BigInteger b);

    BigInteger abs();

    BigInteger operator=(const BigInteger &obj);

    BigInteger operator=(const int b);

    BigInteger operator+(const BigInteger &obj);

    BigInteger operator+(const int b);

    BigInteger operator*(const BigInteger &obj);

    BigInteger operator*(const int b);

    BigInteger operator-(const BigInteger &obj);

    BigInteger operator-(const int b);

    BigInteger operator%(const BigInteger &obj);

    BigInteger operator%(const int b);

    BigInteger operator/(const BigInteger &obj);

    BigInteger operator/(const int b);

    BigInteger operator+=(const BigInteger &obj);

    BigInteger operator+=(const int b);

    BigInteger operator-=(const BigInteger &obj);

    BigInteger operator-=(const int b);

    bool operator>(const BigInteger &obj);

    bool operator>(const int b);

    bool operator<(const BigInteger &obj);

    bool operator<(const int b);

    bool operator==(const BigInteger &obj);

    bool operator==(const int b);

    bool operator!=(const BigInteger &obj);

    bool operator!=(const int b);

    bool operator>=(const BigInteger &obj);

    bool operator>=(const int b);

    bool operator<=(const BigInteger &obj);

    bool operator<=(const int b);

    friend BigInteger operator-(const BigInteger &obj);

    friend BigInteger operator+(const int a, const BigInteger &b);

    friend BigInteger operator-(const int a, const BigInteger &b);

    friend BigInteger operator*(const int a, const BigInteger &b);

    friend BigInteger operator/(const int a, const BigInteger &b);

    friend BigInteger operator%(const int a, const BigInteger &b);

    friend bool operator>(const int a, const BigInteger &b);

    friend bool operator<(const int a, const BigInteger &b);

    friend bool operator==(const int a, const BigInteger &b);

    friend bool operator!=(const int a, const BigInteger &b);

    friend bool operator>=(const int a, const BigInteger &b);

    friend bool operator<=(const int a, const BigInteger &b);

    friend ostream &operator<<(ostream &out, const BigInteger &obj);

    friend istream &operator>>(istream &in, BigInteger &obj);
};
