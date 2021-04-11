//
// Created by swqd on 4/10/21.
//

#ifndef CFG_PRODUCTION_H
#define CFG_PRODUCTION_H

#include <list>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "GrammarSymbol.h"

class Production {
    GrammarSymbol const& lhs;

    std::list<const GrammarSymbol*> rhs;

    friend class CFG_Engine;

public:
    Production(GrammarSymbol const& lhs) : lhs(lhs) {}

    Production(GrammarSymbol const& lhs, std::initializer_list<const GrammarSymbol*> const& rhs) : lhs(lhs), rhs(rhs) {}

    Production(GrammarSymbol const& lhs, std::list<const GrammarSymbol*> const& rhs) : lhs(lhs), rhs(rhs) {}

    [[nodiscard]] bool IsEpsilonProduction() const { return rhs.empty(); }

    [[nodiscard]] std::string ToString() const;

    [[nodiscard]] size_t Length() const { return rhs.size(); }

    [[nodiscard]] const std::list<const GrammarSymbol*>& GetRhs() const { return rhs; }

    [[nodiscard]] const GrammarSymbol& GetLhs() const { return lhs; }

    [[nodiscard]] std::vector<bool> FormRemovableSymbolsMap(const std::unordered_set<const GrammarSymbol *>
            &nullableSymbols) const;

    static Production CopyCreateProductionWithMask(Production const& other, std::vector<bool> &vector);

    bool operator==(Production const& other) const;
};


#endif //CFG_PRODUCTION_H
