//
// Created by swqd on 4/10/21.
//

#ifndef CFG_STRINGCOMBINATORICS_H
#define CFG_STRINGCOMBINATORICS_H

#include <vector>

#include "../Core/Production.h"

// Generates all combinations of given production string. Any character may be either constant or disabled/enabled
class StringCombinatorics {

    Production production;

    std::vector<bool> removableSymbolsMap;

    std::vector<Production> allCombinations;

    std::vector<const GrammarSymbol *> newEpsilons;

    bool SymbolIsRemovable(size_t index) const { return removableSymbolsMap[index]; }

    void FinalizeCombination(std::vector<bool> &combinationMap);

    void GenerateAllCombinations(const std::list<const GrammarSymbol*> &rhs,
                                 std::vector<bool> combinationMap, std::list<const GrammarSymbol*>::const_iterator iterator, size_t index);

public:

    StringCombinatorics(Production const& production1, std::vector<bool> const& removableSymbolsMap) : production(production1), removableSymbolsMap(removableSymbolsMap) {}

    std::vector<Production> GetAllCombinations();

    [[nodiscard]]
    std::vector<const GrammarSymbol *> const& GetNewEpsilonSymbols() const { return newEpsilons; }

};


#endif //CFG_STRINGCOMBINATORICS_H
