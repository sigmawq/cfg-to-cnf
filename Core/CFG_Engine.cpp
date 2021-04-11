//
// Created by swqd on 4/10/21.
//

#include "CFG_Engine.h"

const GrammarSymbol& CFG_Engine::AddSymbol(const std::string &value) {
    bool isTerminal;
    if (islower(value[0])) { isTerminal = true; }
    else if (isupper(value[0])) { isTerminal = false; }
    else {
        throw SymbolFormatError("Only symbols of lowercase or uppercase are allowed");
    }

    return this->symbolMap.emplace(std::pair<std::string, GrammarSymbol> { value, {isTerminal, value} }).first->second;
}

const GrammarSymbol* CFG_Engine::FindSymbol(const std::string &value) const {
    try{
        return &symbolMap.at(value);
    }
    catch (std::out_of_range &err){
        return nullptr;
    }
}

void CFG_Engine::AddProduction(const std::string &lhs, const std::vector<std::string> &rhs) {
    const GrammarSymbol & lhs_value = AddSymbol(lhs);
    std::list<const GrammarSymbol*> rhs_values;
    for (const auto &symbol : rhs){
        rhs_values.emplace_back(&AddSymbol(symbol));
    }
    AddProduction(lhs_value, rhs_values);
}

void CFG_Engine::AddProduction(GrammarSymbol const& lhs, std::list<const GrammarSymbol*> const& rhs) {
    if (lhs.IsTerminal()) throw SymbolFormatError("Terminal on LHS is not allowed");
    AddProduction_AvoidDuplicates(lhs, rhs);
}

std::string CFG_Engine::ToString() const {
    std::string result;
    for (const auto& el : productions){
        result += el.second.ToString();
        result += '\n';
    }
    return result;
}

std::vector<const Production *> CFG_Engine::GetAllProductionOfLhs(const std::string &lhs) const {
    std::vector<const Production *> result;
    auto it = productions.equal_range(lhs);
    while (it.first != it.second){
        result.push_back(&it.first->second);
        ++it.first;
    }
}

bool CFG_Engine::SymbolExists(std::string const& value) const {
    try{
        symbolMap.at(value);
        return true;
    }
    catch (std::out_of_range &err) {
        return false;
    }
}

const std::unordered_set<const GrammarSymbol *> & CFG_Engine::GetAllDirectlyNullableSymbols() const {
    return nullableSymbols;
}

void CFG_Engine::AddProductions(std::vector<Production> const& productions) {
    for (const Production& production : productions){
        AddProduction(production);
    }
}

void CFG_Engine::AddProduction(const Production & production) {
    for (const GrammarSymbol *symbol : production.GetRhs()){
        if (!this->FindSymbol(symbol)) throw std::runtime_error("Attempted to add production which partly or completely not represented in symbol map of target CFG Engine");
    }

    AddProduction_AvoidDuplicates(production.GetLhs(), production.GetRhs());
}

bool CFG_Engine::FindSymbol(const GrammarSymbol *symbol) const {
    try{
        auto &result = symbolMap.at(symbol->Value());
        return (&result == symbol);
    }
    catch (std::out_of_range &err){
        return false;
    }
}

void CFG_Engine::AddEpsilonProduction(const std::string &lhs) {
    GrammarSymbol const& lhsValue = AddSymbol(lhs);
    nullableSymbols.insert(&lhsValue);
}

void CFG_Engine::AddProduction_AvoidDuplicates(const GrammarSymbol &lhs, const std::list<const GrammarSymbol *> &rhs) {
    std::string combinedProduction = CombineProductionInString(lhs, rhs);
    if (ProductionAlreadyExists(combinedProduction)){
        return;
    }
    else{
        productions.insert({lhs.Value(), {lhs, rhs}});
        productionsHashed.insert(combinedProduction);
    }
}

std::string CFG_Engine::CombineProductionInString(const GrammarSymbol &lhs, std::list<const GrammarSymbol*> const& rhs) {
    std::string combinedProduction = lhs.Value();
    for (const GrammarSymbol * el : rhs){
        combinedProduction += el->Value();
    }
    return combinedProduction;
}

bool CFG_Engine::ProductionAlreadyExists(std::string &combinedProduction) const {
    auto it = productionsHashed.find(combinedProduction);
    if (it == productionsHashed.end()) return false;
    return true;
}