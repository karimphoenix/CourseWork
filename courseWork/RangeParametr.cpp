//
// Created by karimPhoenix on 18.04.2017.
//

#include "RangeParametr.h"
#include <iostream>

//transfer function "int" to "typeBits" TODO: for all types


//TODO: types
RangeParametr::RangeParametr (string iName, unsigned int iCountBits) {
    name = iName;
    countBits = iCountBits;
    bitsValue.assign(countBits, UNKNOWN);
}

typeBits transfer(int i){
    if (i == 1) return ONE;
    if (i == 0) return ZERO;
}


TABLE summTable =
        {
                {
                        {
                                { ZERO, ZERO },     { ZERO, ONE },   { ZERO, UNKNOWN }
                        },

                        {
                                { ZERO, ONE },     { ONE, ZERO },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, UNKNOWN },      { UNKNOWN, UNKNOWN },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, ZERO },  { ZERO, ONE },   { ZERO, UNKNOWN }
                        }
                },

                {
                        {
                                { ZERO, ONE },      { ONE, ZERO },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ONE, ZERO },      { ONE, ONE },   { ONE, UNKNOWN }
                        },

                        {
                                { UNKNOWN, UNKNOWN },      { ONE, UNKNOWN },    { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, ONE },   { ONE, ZERO },  { UNKNOWN, UNKNOWN }
                        }
                },

                {
                        {
                                { ZERO, UNKNOWN },  { UNKNOWN, UNKNOWN }, { UNKNOWN, UNKNOWN }
                        },

                        {
                                { UNKNOWN, UNKNOWN },   { ONE, UNKNOWN }, { UNKNOWN, UNKNOWN }
                        },

                        {
                                { UNKNOWN, UNKNOWN },   { UNKNOWN, UNKNOWN },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, UNKNOWN },  { UNKNOWN, UNKNOWN }, { UNKNOWN, UNKNOWN }
                        }
                },

                {
                        {
                                { ZERO, ZERO },     { ZERO, ONE },  { ZERO, UNKNOWN }
                        },

                        {
                                { ZERO, ONE },     { ONE, ZERO },  { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, UNKNOWN }, { UNKNOWN, UNKNOWN },  { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, DONTCARE }, { ZERO, ONE },  { ZERO, UNKNOWN }
                        }
                }
        };

TABLE borrowTable =
        {
                {
                        {
                                { ZERO, ZERO },     { ONE, ONE },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ONE, ONE },     { ONE, ZERO },   { ONE, UNKNOWN }
                        },

                        {
                                { UNKNOWN, UNKNOWN },      { ONE, UNKNOWN },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, ZERO },  { ZERO, ONE },   { UNKNOWN, UNKNOWN }
                        }
                },

                {
                        {
                                { ZERO, ONE },      { ZERO, ZERO },   { ZERO, UNKNOWN }
                        },

                        {
                                { ZERO, ZERO },      { ONE, ONE },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, UNKNOWN },      { UNKNOWN, UNKNOWN },    { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, ZERO },   { ZERO, ZERO },  { ZERO, UNKNOWN }
                        }
                },

                {
                        {
                                { ZERO, UNKNOWN },  { UNKNOWN, UNKNOWN }, { UNKNOWN, UNKNOWN }
                        },

                        {
                                { UNKNOWN, UNKNOWN },   { ONE, UNKNOWN }, { UNKNOWN, UNKNOWN }
                        },

                        {
                                { UNKNOWN, UNKNOWN },   { UNKNOWN, UNKNOWN },   { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, UNKNOWN },  { UNKNOWN, UNKNOWN }, { UNKNOWN, UNKNOWN }
                        }
                },

                {
                        {
                                { ZERO, ZERO }, { ZERO, ZERO },  { ZERO, ZERO }
                        },

                        {
                                { ZERO, ZERO },     { ONE, ZERO },  { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, ZERO },      { ZERO, UNKNOWN },  { UNKNOWN, UNKNOWN }
                        },

                        {
                                { ZERO, ZERO }, { ZERO, ZERO },  { ZERO, ZERO }
                        }
                }
        };


TABLELOGICAL bOrTable =
        {
                {ZERO,  ONE,    UNKNOWN,    DONTCARE},
                {ONE,   ONE,    ONE,    ONE},
                {UNKNOWN,   ONE,    UNKNOWN,    DONTCARE},
                {DONTCARE,  ONE,    DONTCARE,   DONTCARE}
        };

TABLELOGICAL bXorTable =
        {
                {ZERO,  ONE,    UNKNOWN,    DONTCARE},
                {ONE,   ZERO,   UNKNOWN,    DONTCARE},
                {UNKNOWN,   UNKNOWN,    UNKNOWN,    DONTCARE},
                {DONTCARE,  DONTCARE,   DONTCARE,   DONTCARE}
        };

TABLELOGICAL bAndTable =
        {
                {ZERO,  ZERO,   ZERO,   ZERO},
                {ZERO,  ONE,    UNKNOWN,    DONTCARE},
                {ZERO,  UNKNOWN,    UNKNOWN,    DONTCARE},
                {ZERO,  DONTCARE,   DONTCARE,   DONTCARE}
        };




//after all use in operator + be+twen RangeParametr elements
pairBits summurise(typeBits& a, typeBits& b, typeBits& carry) {
    pairBits retValue; //TODO: ask about memmory and next loops
    retValue.first = summTable[a][b][carry].first;
    retValue.second = summTable[a][b][carry].second;
    return retValue;
}

pairBits subtraction(typeBits& a, typeBits& b, typeBits& borrow) {
    pairBits retValue;
    retValue = borrowTable[a][b][borrow];
    /*
    retValue.first = borrowTable[a][b][borrow].first;
    retValue.second = borrowTable[a][b][borrow].second;
     */
    return retValue;
}


//for initialise const
RangeParametr::RangeParametr (int numberOfConst, int constValue){
    name = "Const" + numberOfConst;
    bitsValue.resize(32);
    vector<int> retValue(32);
    int i, j;
    for (i = 0; constValue; constValue >>=1 , i++) retValue[i] = (constValue&1)?('1'):('0');
    for (j = 0; j < i; j++) bitsValue[j] = transfer(retValue[i-j-1]);
}

unsigned int RangeParametr::resizeBitsValue(unsigned int count) {
    if (count != 0) {
        std::vector<typeBits> temp;
        temp.assign(bitsValue.begin(), bitsValue.end());
        bitsValue.assign(count + countBits, ZERO);
        std::copy(temp.begin(), temp.end(), bitsValue.begin() + count);
        //countBits = count + countBits; TODO:: we need to save this?
        return count + bitsValue.size();
    }
    else
        return bitsValue.size();
}

void RangeParametr::resizeBitsValue() { //return the "true" lenght and bits
    bitsValue.assign(bitsValue.begin() + countBits - 1, bitsValue.end());
    bitsValue.resize(countBits);
}

void RangeParametr::trasformDontCare() {
    countImportantBits = 0;
    for (int i = 0; i < bitsValue.size(); ++i){
        if (bitsValue[i] != DONTCARE) countImportantBits++;
    }
}

RangeParametr operator+(RangeParametr& left, RangeParametr& right){
    unsigned int lenght = std::max(left.getCountBits(), right.getCountBits()) + 1;
    //unsigned int minLenght = std::min(left.getCountBits(), right.getCountBits());
    RangeParametr retValue("NameRet", lenght);
    typeBits carry = ZERO;

    //if left.countBits != right.countBits
    left.resizeBitsValue(lenght - left.getCountBits() - 1);
    right.resizeBitsValue(lenght - right.getCountBits() - 1);

    pairBits retPair;
    for (int i = lenght - 1; i > 0; i--){
        retPair = summurise(left.bitsValue[i - 1], right.bitsValue[i - 1], carry);
        retValue.bitsValue[i] = retPair.second;
        carry = retPair.first;
    }
    retValue.bitsValue[0] = carry;

    left.resizeBitsValue();
    right.resizeBitsValue();

    return retValue;
}


RangeParametr operator*(RangeParametr& left, RangeParametr& right){
    bool power2Flag;
    power2Flag = true;
    unsigned int j = 0, countOne = 0, countZeros = 0;

    RangeParametr tempConcatenate;

    while (power2Flag && j < left.bitsValue.size()){
       if (left.bitsValue[j] == ONE) { countOne++; countZeros++; };
        if (countOne > 1) power2Flag = false;
        ++j;
    }
    if (power2Flag){ //porblems!
        tempConcatenate.initialiseCountThisType(right.getCountBits() + left.getCountBits(), ZERO);
        std::copy(left.bitsValue.begin(), left.bitsValue.end(), tempConcatenate.bitsValue.begin() + right.getCountBits());
        return tempConcatenate;
    }
    power2Flag = true;
    while (power2Flag && j < right.getCountBits()){
        if (right.bitsValue[j] == ONE) countOne++;
        if (countOne > 1) power2Flag = false;
        ++j;
    }
    if (power2Flag){
        tempConcatenate.initialiseCountThisType(right.getCountBits() + left.getCountBits(), ZERO);
        std::copy(right.bitsValue.begin(), right.bitsValue.end(), tempConcatenate.bitsValue.begin() + left.getCountBits());
        return tempConcatenate;
    }

    //count of trailing and leading zeros in left and right
    unsigned int tleft, tright, lleft, lright;
    unsigned int  i = 0;
    countZeros = 0;
    while (left.bitsValue[i] == ZERO){
        ++i; ++countZeros;
    }
    lleft = countZeros; i = countZeros = 0;

    while (left.bitsValue[left.bitsValue.size() - i] == ZERO){
        ++i; ++countZeros;
    }
    tleft = countZeros; i = countZeros = 0;

    while (right.bitsValue[i] == ZERO){
        ++i; ++countZeros;
    }
    lright = countZeros; i = countZeros = 0;

    while (right.bitsValue[right.bitsValue.size() - i] == ZERO){
        ++i; ++countZeros;
    }
    tright = countZeros; i = countZeros = 0;

    unsigned int lenght = std::max((left.bitsValue.size() + right.bitsValue.size() - tleft - tright - lleft - lright),
                                   (tleft + tright))+1;
    RangeParametr retValue("NameRet", lenght);
    retValue.initialiseAllThisType(UNKNOWN);

    //RangeParametr tempConcatenate("conc", tleft+tright);
    tempConcatenate.initialiseCountThisType(tleft + tright, ZERO);

    return retValue + tempConcatenate; //TODO: WHY?!?!?!?!?!?


}

RangeParametr operator-(RangeParametr& left, RangeParametr& right){
    unsigned int lenght = std::max(left.getCountBits(), right.getCountBits()) + 1;
    //unsigned int minLenght = std::min(left.getCountBits(), right.getCountBits());
    RangeParametr retValue("NameRet", lenght);
    typeBits borrow = ZERO;

    //if left.countBits != right.countBits
    left.resizeBitsValue(lenght - left.getCountBits() - 1);
    right.resizeBitsValue(lenght - right.getCountBits() - 1);

    pairBits retPair;
    for (int i = lenght - 1; i > 0; i--){
        retPair = subtraction(left.bitsValue[i - 1], right.bitsValue[i - 1], borrow);
        retValue.bitsValue[i] = retPair.second;
        borrow = retPair.first;
    }
    retValue.bitsValue[0] = borrow;

    left.resizeBitsValue();
    right.resizeBitsValue();

    return retValue;
}


void RangeParametr::printBitsValue(){
    for (auto x:bitsValue) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}

RangeParametr operator|(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("bOr", std::max(left.getCountBits(), right.getCountBits()));
    retValue.initialiseAllThisType(ZERO);

    unsigned int countsStep = std::min(left.getCountBits(), right.getCountBits());

    for (int i = countsStep - 1; i >= 0; i--){
        retValue.bitsValue[i] = bOrTable[left.bitsValue[i]][right.bitsValue[i]];
    }

    return retValue;
}

RangeParametr operator^(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("bXor", std::max(left.getCountBits(), right.getCountBits()));
    retValue.initialiseAllThisType(ZERO);

    unsigned int countsStep = std::min(left.getCountBits(), right.getCountBits());

    for (int i = countsStep - 1; i >= 0; i--){
        retValue.bitsValue[i] = bXorTable[left.bitsValue[i]][right.bitsValue[i]];
    }

    return retValue;
}

RangeParametr operator&(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("bXor", std::max(left.getCountBits(), right.getCountBits()));
    retValue.initialiseAllThisType(ZERO);

    unsigned int countsStep = std::min(left.getCountBits(), right.getCountBits());

    for (int i = countsStep - 1; i >= 0; i--){
        retValue.bitsValue[i] = bAndTable[left.bitsValue[i]][right.bitsValue[i]];
    }

    return retValue;
}

RangeParametr operator&&(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("And", 1);
    bool leftHas = false, rightHas = false;
    for (int i = 0; i < left.getCountBits(); ++i){
        if (left.bitsValue[i] == ONE){
            leftHas = true;
            break;
        }
    }
    for (int i = 0; i < right.getCountBits(); ++i){
        if (right.bitsValue[i] == ONE){
            rightHas = true;
            break;
        }
    }
    if (leftHas && rightHas){ //if a and b has 1
        retValue.bitsValue[0] = ONE;
        return retValue;
    }


    for (int i = 0; i < left.getCountBits(); ++i){
        if (left.bitsValue[i] == ONE){
            return retValue;
        }
    }
    for (int i = 0; i < right.getCountBits(); ++i){
        if (right.bitsValue[i] == ONE){
            return retValue;
        }
    }

    retValue.initialiseAllThisType(ZERO);
    return retValue;

}

RangeParametr operator||(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("Or", 1);
    for (int i = 0; i < left.getCountBits(); ++i){
        if (left.bitsValue[i] == ONE){
            retValue.bitsValue[0] = ONE;
            return retValue;
        }
    }
    for (int i = 0; i < right.getCountBits(); ++i){
        if (right.bitsValue[i] == ONE){
            retValue.bitsValue[0] = ONE;
            return retValue;
        }
    }

    for (int i = 0; i < left.getCountBits(); ++i){
        if (left.bitsValue[i] == UNKNOWN){
            retValue.bitsValue[0] = UNKNOWN;
            return retValue;
        }
    }
    for (int i = 0; i < right.getCountBits(); ++i){
        if (right.bitsValue[i] == UNKNOWN){
            retValue.bitsValue[0] = UNKNOWN;
            return retValue;
        }
    }

    retValue.bitsValue[0] = ZERO;
    return retValue;
}


RangeParametr operator/(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("Div", left.getCountBits());
    return retValue;
}

RangeParametr operator%(RangeParametr& left, RangeParametr& right){
    RangeParametr retValue("Mod", std::min(left.getCountBits(), right.getCountBits()));
    return retValue;
}



//UNREACHEBLE CODE!!! TODO: DELETE THIS!!!
/*RangeParametr operator=(RangeParametr& left){
    RangeParametr retValue("Copy", left.getCountBits());
    std::copy(left.bitsValue.begin(), left.bitsValue.end(), retValue.bitsValue.begin());
    return retValue;
}*/