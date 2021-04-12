//
// Created by swqd on 4/10/21.
//

#ifndef CFG_CFG_ENGINE_H
#define CFG_CFG_ENGINE_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>

#include "GrammarSymbol.h"
#include "Production.h"

class CFG_Engine {

    std::unordered_map<std::string, GrammarSymbol> symbolMap;

    std::unordered_multimap<std::string, Production> productions;

    std::unordered_set<std::string> productionsHashed;

    std::unordered_set<const GrammarSymbol *> nullableSymbols;

    const GrammarSymbol *startSymbol;

    friend class CNF_Converter;

    bool ProductionAlreadyExists(std::string &combinedProduction) const;

    static
    std::string CombineProductionInString(const GrammarSymbol &lhs, std::list<const GrammarSymbol*> const& rhs);

    void AddProduction_AvoidDuplicates(const GrammarSymbol &lhs, std::list<const GrammarSymbol*> const& rhs);

public:

    explicit CFG_Engine(std::string const& startSymbol) : startSymbol(nullptr) { this->startSymbol = &AddSymbol(
                startSymbol); }

    const GrammarSymbol* FindSymbol(std::string const& value) const;

    bool FindSymbol(const GrammarSymbol * symbol) const;

    // Convert productions to string
    std::string ToString() const;

    // Get all productions of given symbol
    std::vector<const Production*> GetAllProductionOfLhs(std::string const& lhs) const;

    // Check if given symbol exists in CFG
    bool SymbolExists(std::string const& value) const;

    // Return start symbol
    const GrammarSymbol* GetStartSymbol() const { return startSymbol; }

    // Add symbol from string, if symbol exists nothing will happen.
    const GrammarSymbol & AddSymbol(std::string const& value);

    // Get all nullable symbols
    // Only symbols directly containing epsilon are considered
    const std::unordered_set<const GrammarSymbol *> & GetAllDirectlyNullableSymbols() const;

    // Any symbol starting with a lowercase is considered a TERMINAL
    const GrammarSymbol & AddProduction(std::string const& lhs, std::vector<std::string> const& rhs);

    // Establish production between existing symbols
    void AddProduction(const GrammarSymbol &lhs, std::list<const GrammarSymbol*> const& rhs);

    // Add existing production, it will be checked that every symbol exists in symbol map
    void AddProduction(const Production & production);

    // Add multiple productions
    void AddProductions(std::vector<Production> const& productions);

    void AddEpsilonProduction(std::string const& lhs);

    void RemoveAllEpsilonProductions() { nullableSymbols.erase(nullableSymbols.begin(),
                                                                     nullableSymbols.end()); }

    bool IfHasEpsilonProductions() const { return !nullableSymbols.empty(); }

    void RemoveGhostProductions();

    void RemoveDuplicateProductions();
};

class SymbolFormatError : public std::runtime_error {
public:
    explicit SymbolFormatError(std::string const& message) : std::runtime_error(message) {}
};


#endif //CFG_CFG_ENGINE_H
