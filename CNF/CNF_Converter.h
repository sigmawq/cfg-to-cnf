//
// Created by swqd on 4/10/21.
//

#ifndef CFG_CNF_CONVERTER_H
#define CFG_CNF_CONVERTER_H

#include "../Core/CFG_Engine.h"

class CNF_Converter {

    CFG_Engine &cfgEngine;

    void Convert();

    void AddNewStartSymbol();

    void RemoveEpsilonProductions();

    void RemoveUnitProductions();

public:

    CNF_Converter(CFG_Engine &cfgEngine1) : cfgEngine(cfgEngine1) { Convert(); }

};


#endif //CFG_CNF_CONVERTER_H
