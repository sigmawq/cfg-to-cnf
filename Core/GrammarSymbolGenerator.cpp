//
// Created by swqd on 4/12/21.
//

#include "GrammarSymbolGenerator.h"

std::string GrammarSymbolGenerator::NextSymbol() {
    std::string result {currentLetter};
    result += '_';
    result += currentNumber;
    IncrementState();
    return result;
}

void GrammarSymbolGenerator::IncrementState() {
    ++currentNumber;
    if (currentNumber > '9') {
        ++currentLetter;
        currentNumber = '0';
    }
}
