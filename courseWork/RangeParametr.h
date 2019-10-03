//
// Created by karimPhoenix on 18.04.2017.
//

#ifndef COURSEWORK_RANGEPARAMETR_H
#define COURSEWORK_RANGEPARAMETR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

enum typeBits{
    ZERO = 0,
    ONE,
    UNKNOWN,
    DONTCARE,
    MAX_FOR_CARRY = DONTCARE,
    MAX_BIT_TYPES,
};

//transfer function "int" to "typeBits" TODO: for all types
typeBits transfer(int i);

struct pairBits{
    typeBits first;
    typeBits second;
};

typedef pairBits TABLE[MAX_BIT_TYPES][MAX_BIT_TYPES][MAX_FOR_CARRY];
typedef typeBits TABLELOGICAL[MAX_BIT_TYPES][MAX_BIT_TYPES];

pairBits summurise(typeBits& a, typeBits& b, typeBits& carry);
pairBits subtraction(typeBits& a, typeBits& b, typeBits& borrow);

class RangeParametr {
private:
    string name;
    unsigned int countBits;
    unsigned int countImportantBits;


public:

    vector<typeBits> bitsValue;

    //TODO: types
    RangeParametr (){};
    RangeParametr (string iName, unsigned int iCountBits);

    //for initialise const
    RangeParametr (int numberOfConst, int constValue);

    void initialiseAllThisType(typeBits type){
        bitsValue.assign(countBits, type);
    }

    void initialiseCountThisType(unsigned int count, typeBits type){
        bitsValue.assign(count, type);
        countBits = count;
    }

    string getName(){
        return name;
    }

    unsigned int getCountBits(){
        return countBits;
    }

    void setCountBits(unsigned int newCount){
        countBits = newCount;
    }

    unsigned int resizeBitsValue(unsigned int count);

    void resizeBitsValue();

    void trasformDontCare();

    /*void getConts(unsigned int& counts){
        counts = countBits;
    }*/

    //test method
    void printBitsValue();

};

RangeParametr operator+(RangeParametr& left, RangeParametr& right);

RangeParametr operator*(RangeParametr& left, RangeParametr& right);

RangeParametr operator-(RangeParametr& left, RangeParametr& right);

RangeParametr operator|(RangeParametr& left, RangeParametr& right);

RangeParametr operator^(RangeParametr& left, RangeParametr& right);

RangeParametr operator&(RangeParametr& left, RangeParametr& right);

RangeParametr operator&&(RangeParametr& left, RangeParametr& right);

RangeParametr operator||(RangeParametr& left, RangeParametr& right);

RangeParametr operator/(RangeParametr& left, RangeParametr& right);

RangeParametr operator%(RangeParametr& left, RangeParametr& right);


//vector< vector<typeBits> > sumTable();

#endif //COURSEWORK_RANGEPARAMETR_H
