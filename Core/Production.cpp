//
// Created by swqd on 4/10/21.
//

#include "Production.h"
#include <unordered_set>

std::string Production::ToString() const {
    std::string result = lhs.Value();
    result += " -> ";

    for (auto &el : rhs){
        result += el->Value();
    }

    if (IsEpsilonProduction()) result = "ε";

    return result;
}

Production Production::CopyCreateProductionWithMask(Production const& other, std::vector<bool> &mask) {
    Production newProduction { other.lhs };

    int i = 0;
    for (const GrammarSymbol* symbol : other.rhs){
        if (mask[i]) newProduction.rhs.push_back(symbol);
        ++i;
    }
    return newProduction;
}

std::vector<bool> Production::FormRemovableSymbolsMap(const std::unordered_set<const GrammarSymbol *> &nullableSymbols) const {
    std::vector<bool> result;
    auto nullable = [&nullableSymbols](const GrammarSymbol * symbol){
        auto result = nullableSymbols.find(symbol);
        bool _t = result != nullableSymbols.end();
        return _t;
    };
    result.resize(rhs.size());

    int i = 0;
    for (const GrammarSymbol * symbol : rhs){
        result[i] = nullable(symbol);
        ++i;
    }

    return result;
}

bool Production::operator==(const Production &other) const {
    return std::hash<std::string>{}(other.ToString()) ==
            std::hash<std::string>{}(this->ToString());
}
