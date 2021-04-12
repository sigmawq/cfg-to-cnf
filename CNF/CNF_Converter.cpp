//
// Created by swqd on 4/10/21.
//

#include <iostream>
#include <set>

#include "CNF_Converter.h"
#include "StringCombinatorics.h"
#include "../Utility/VectorUtility.h"

void CNF_Converter::Convert() {

#ifdef CFG_CNF_CONVERSION_VERBOSE
    std::cout << "Original CFG: " << std::endl;
    std::cout << cfgEngine.ToString() << std::endl;
#endif

    RemoveUnreachableProductions();
#ifdef CFG_CNF_CONVERSION_VERBOSE
    std::cout << "After removing unreachable productions: ";
    std::cout << cfgEngine.ToString() << std::endl;
#endif

    AddNewStartSymbol();
#ifdef CFG_CNF_CONVERSION_VERBOSE
    std::cout << "Add new start symbol: " << std::endl;
    std::cout << cfgEngine.ToString() << std::endl;
#endif

    RemoveEpsilonProductions();
#ifdef CFG_CNF_CONVERSION_VERBOSE
    std::cout << "After removing epsilon productions: " << std::endl;
    std::cout << cfgEngine.ToString() << std::endl;
#endif

    RemoveUnitProductions();
#ifdef CFG_CNF_CONVERSION_VERBOSE
    std::cout << "After removing unit productions:" << std::endl;
    std::cout << cfgEngine.ToString() << std::endl;
#endif
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
    std::vector<const GrammarSymbol *> newEpsilonSymbols;

    while (cfgEngine.IfHasEpsilonProductions()){
        auto nullableProductions = cfgEngine.GetAllDirectlyNullableSymbols();
        for (const auto &pair : cfgEngine.productions){
            auto nullableMap =
                    pair.second.FormRemovableSymbolsMap(nullableProductions);
            StringCombinatorics stringCombinatorics { pair.second, nullableMap };
            cfgEngine.AddProductions(stringCombinatorics.GetAllCombinations());
            VectorMerge(newEpsilonSymbols, stringCombinatorics.GetNewEpsilonSymbols());
        }
        cfgEngine.RemoveAllEpsilonProductions();
        for (const GrammarSymbol * symbol : newEpsilonSymbols){
            cfgEngine.AddEpsilonProduction(symbol->Value());
        }
        newEpsilonSymbols.clear();
    }
    cfgEngine.RemoveGhostProductions();
    cfgEngine.RemoveDuplicateProductions();
}

void CNF_Converter::RemoveUnitProductions() {
    std::unordered_multimap<std::string, Production> guf;

    auto it = cfgEngine.productions.begin();
    while (it != cfgEngine.productions.end()){
        if (!it->second.IsUnitProduction()){
            guf.insert(*it);
        }
        it++;
    }

    bool changes = true;
    while (changes){
        changes = false;
        it = cfgEngine.productions.begin();
        while (it != cfgEngine.productions.end()){
            if (it->second.IsUnitProduction()){
                TransitUnitProduction(it->second, guf);
                it = cfgEngine.productions.erase(it);
                changes = true;
            }
            else{
                it++;
            }

        }
    }
}

void CNF_Converter::TransitUnitProduction(const Production &production,
                                          const std::unordered_multimap<std::string, Production> &guf) {
    std::string const& rhs = (*production.GetRhs().begin())->Value();
    auto range = guf.equal_range(rhs);
    while (range.first != range.second){
        cfgEngine.AddProduction(production.GetLhs(), range.first->second.GetRhs());
        range.first++;
    }
}

void CNF_Converter::RemoveUnreachableProductions() {
    std::unordered_map<std::string, bool> reachabilityMap;
    for (const auto & pair : cfgEngine.symbolMap){
        reachabilityMap.emplace(pair.first, false);
    }

    std::set<const Production *> visitedNodes;
    std::vector<const Production *> startSymbolProductions = cfgEngine.GetAllProductionOfLhs(cfgEngine.startSymbol->Value());
    for (const Production * p : startSymbolProductions){
        DepthFirstSearch(reachabilityMap, p, visitedNodes);
    }

    for (const auto& pair : reachabilityMap){
        if (!pair.second) cfgEngine.productions.erase(pair.first);
    }
}

void CNF_Converter::DepthFirstSearch(std::unordered_map<std::string, bool> &reachabilityMap, const Production * currentProduction,
                                     std::set<const Production *> &visitedNodes) {

    auto foundNode = visitedNodes.find(currentProduction);
    if (foundNode != visitedNodes.end()) return;

    visitedNodes.emplace(currentProduction);

    reachabilityMap.at(currentProduction->GetLhs().Value()) = true;

    for (const GrammarSymbol * nextSymbol : currentProduction->GetRhs()){
        std::vector<const Production*> allProductions = cfgEngine.GetAllProductionOfLhs(nextSymbol->Value());
        for (const Production * nextProduction : allProductions){
            DepthFirstSearch(reachabilityMap, nextProduction, visitedNodes);
        }
    }
}
