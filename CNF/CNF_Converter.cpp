//
// Created by swqd on 4/10/21.
//

#include "CNF_Converter.h"
#include "StringCombinatorics.h"

void CNF_Converter::Convert() {
    AddNewStartSymbol();
    RemoveEpsilonProductions();
}

void CNF_Converter::AddNewStartSymbol() {
    auto currentStartSymbol = cfgEngine.GetStartSymbol();
    std::string newStartSymbolName = currentStartSymbol->Value() + "_0";
    while (cfgEngine.SymbolExists(newStartSymbolName)){
        newStartSymbolName += "_0";
    }
    const GrammarSymbol &newStartSymbol = cfgEngine.AddSymbol(newStartSymbolName);
    cfgEngine.AddProduction(newStartSymbol, {currentStartSymbol});
}

void CNF_Converter::RemoveEpsilonProductions() {
    auto nullableProductions = cfgEngine.GetAllDirectlyNullableSymbols();
    for (const auto &pair : cfgEngine.productions){
        auto nullableMap =
                pair.second.FormRemovableSymbolsMap(nullableProductions);
        StringCombinatorics stringCombinatorics { pair.second, nullableMap };
        cfgEngine.AddProductions(stringCombinatorics.GetAllCombinations());
    }
}
