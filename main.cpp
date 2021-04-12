
#include <iostream>
#include "Core/CFG_Engine.h"
#include "CNF/CNF_Converter.h"

int main() {
    try{
        CFG_Engine engine { "S" };

        engine.AddProduction("S", {"D", "A"});
        engine.AddProduction("S", {"a", "B"});
        engine.AddProduction("A", {"a"});
        engine.AddProduction("A", {"B", "D"});
        engine.AddProduction("A", {"b", "D", "A", "B"});
        engine.AddProduction("B", {"b"});
        engine.AddProduction("B", {"B", "A"});
        engine.AddProduction("D", {"B", "A"});
        engine.AddProduction("C", {"B", "A"});
        engine.AddEpsilonProduction("D");

        CNF_Converter converter { engine };

    }
    catch (SymbolFormatError &err){
        std::cout << err.what();
    }

    return 0;
}
