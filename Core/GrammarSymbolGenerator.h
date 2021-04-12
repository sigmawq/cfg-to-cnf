//
// Created by swqd on 4/12/21.
//

#ifndef CFG_GRAMMARSYMBOLGENERATOR_H
#define CFG_GRAMMARSYMBOLGENERATOR_H

#include <string>

class GrammarSymbolGenerator {
    char currentLetter = 'A';
    char currentNumber = '0';

    void IncrementState();

public:

    std::string NextSymbol();
};


#endif //CFG_GRAMMARSYMBOLGENERATOR_H
