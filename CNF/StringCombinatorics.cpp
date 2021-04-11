//
// Created by swqd on 4/10/21.
//

#include "StringCombinatorics.h"

std::vector<Production> StringCombinatorics::GetAllCombinations() {
    auto productionRhs = production.GetRhs();
    GenerateAllCombinations(productionRhs, {}, productionRhs.begin(), 0);
    return allCombinations;
}

void StringCombinatorics::GenerateAllCombinations(const std::list<const GrammarSymbol*> &rhs,
                                                  std::vector<bool> combinationMap, std::list<const GrammarSymbol*>::const_iterator iterator,
                                                  size_t index) {
    bool generateNewProduction = false;
    if (iterator == --std::end(rhs)){
        generateNewProduction = true;
    }
    auto &currentElement = *iterator;
    if (SymbolIsRemovable(index)){
        if (generateNewProduction){
            combinationMap.push_back(true);
            FinalizeCombination(combinationMap);
            combinationMap.back() = false;
            FinalizeCombination(combinationMap);
        }
        else{
            combinationMap.push_back(true);
            GenerateAllCombinations(rhs, combinationMap, std::next(iterator), index + 1);
            combinationMap.back() = false;
            GenerateAllCombinations(rhs, combinationMap, std::next(iterator), index + 1);
        }
    }
    else{
        if (generateNewProduction){
            combinationMap.push_back(true);
            FinalizeCombination(combinationMap);
        }
        else{
            combinationMap.push_back(true);
            GenerateAllCombinations(rhs, combinationMap, std::next(iterator), index + 1);
        }
    }

}

void StringCombinatorics::FinalizeCombination(std::vector<bool> &combinationMap) {
    bool mapCompletelyFalse = true;
    for (int i = 0; i < combinationMap.size(); i++){
        if (combinationMap[i]) mapCompletelyFalse = false;
    }
    if (mapCompletelyFalse) {
        newEpsilons.push_back(&production.GetLhs());
        return;
    }
    allCombinations.push_back(Production::CopyCreateProductionWithMask(production, combinationMap));
}
