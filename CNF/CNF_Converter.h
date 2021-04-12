//
// Created by swqd on 4/10/21.
//
#define CFG_CNF_CONVERSION_VERBOSE

#ifndef CFG_CNF_CONVERTER_H
#define CFG_CNF_CONVERTER_H

#include <unordered_map>
#include <set>
#include "../Core/CFG_Engine.h"
#include "../Core/GrammarSymbolGenerator.h"

#include "../Utility/ListUtility.h"

class CNF_Converter {

    CFG_Engine &cfgEngine;

    [[maybe_unused]] GrammarSymbolGenerator symbolGenerator;

    void Convert();

    void AddNewStartSymbol();

    void RemoveEpsilonProductions();

    void TransitUnitProduction(Production & production, std::unordered_multimap<std::string,
                               Production> const& guf);

    void RemoveUnitProductions();

    void DepthFirstSearch(std::unordered_map<std::string, bool> &reachabilityMap
                          , const Production * currentProduction,
                          std::set<const Production *> &visitedNodes);

    void RemoveUnreachableProductions();

    const GrammarSymbol * RecursiveReplace(std::list<const GrammarSymbol *> const& currentString);

    void ApplyCNF();

public:

    CNF_Converter(CFG_Engine &cfgEngine1) : cfgEngine(cfgEngine1) { Convert(); }

};


#endif //CFG_CNF_CONVERTER_H
