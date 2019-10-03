#include <iostream>
#include "RangeParametr.h"

int main() {

    RangeParametr a, b;

    pairBits testPair;

    typeBits testA, testB, testCarry;
    testA = ZERO; testB = ONE; testCarry = ZERO;

    testPair = summurise(testA, testB, testCarry);
    std::cout<< testPair.first; std::cout<< testPair.second;
    std::cout<<std::endl;
    testPair = subtraction(testA, testB, testCarry);
    std::cout<< testPair.first; std::cout<< testPair.second;
    std::cout<<std::endl;
    a.initialiseCountThisType(3, ZERO);
    b.initialiseCountThisType(3, ONE);

    std::cout<< "a = ";a.printBitsValue();
    std::cout<< "b = ";b.printBitsValue();

    std::cout<< "a + b = ";
    (a + b).printBitsValue();
    std::cout<< "a - b = ";
    (a - b).printBitsValue();

    a.bitsValue[1] = ONE;
    std::cout<< "a = "; a.printBitsValue();

    std::cout<< "Power2 a * b = ";
    (a * b).printBitsValue();
    std::cout<< "a - b = ";
    (a - b).printBitsValue();


    a.bitsValue[2] = DONTCARE;
    std::cout<< "a = "; a.printBitsValue();
    std::cout<< "a * b = ";
    (a * b).printBitsValue();

    a.bitsValue[0] = UNKNOWN;
    b.bitsValue[2] = ZERO;
    std::cout<< "a = ";a.printBitsValue();
    std::cout<< "b = ";b.printBitsValue();
    std::cout<< "a + b = ";(a + b).printBitsValue();
    std::cout<< "a * b = ";(a * b).printBitsValue();
    std::cout<< "a - b = ";(a - b).printBitsValue();
    b.initialiseAllThisType(ONE);
    std::cout<< "a | b = ";(a|b).printBitsValue();
    std::cout<< "a ^ b = ";(a^b).printBitsValue();
    std::cout<< "a & b = ";(a&b).printBitsValue();
    std::cout<< "a || b = ";(a||b).printBitsValue();
    std::cout<< "a && b = ";(a&&b).printBitsValue();
    std::cout<< "a / b = ";(a/b).printBitsValue();
    std::cout<< "a % b = ";(a%b).printBitsValue();


    //std::cout<< "a = b  ";(a = b).printBitsValue();
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}