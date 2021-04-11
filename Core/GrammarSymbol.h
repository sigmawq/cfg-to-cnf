//
// Created by swqd on 4/10/21.
//

#ifndef CFG_GRAMMARSYMBOL_H
#define CFG_GRAMMARSYMBOL_H

#include <string>

class GrammarSymbol {
    const bool isTerminal;
    const std::string value;

public:
    [[nodiscard]] bool IsTerminal() const { return isTerminal; };
    [[nodiscard]] std::string const& Value() const { return value; }

    GrammarSymbol(bool isTerminal, std::string const& value) : isTerminal(isTerminal), value(value) {}
};


#endif //CFG_GRAMMARSYMBOL_H
