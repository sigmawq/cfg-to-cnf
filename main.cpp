
#include <iostream>
#include "Core/CFG_Engine.h"
#include "CNF/CNF_Converter.h"

int main() {
    try{
        CFG_Engine engine { "S" };

        engine.AddProduction("S", {"A", "B", "C"});
        engine.AddProduction("C", {"a"});
        engine.AddProduction("B", {"d"});
        engine.AddProduction("T", {"S"});
        engine.AddEpsilonProduction("A");
        engine.AddEpsilonProduction("B");
        engine.AddEpsilonProduction("C");

        std::cout << engine.ToString();

        CNF_Converter converter { engine };

    }
    catch (SymbolFormatError &err){
        std::cout << err.what();
    }

    return 0;
}
