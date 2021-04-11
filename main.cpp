#include <iostream>
#include "Core/CFG_Engine.h"
#include "CNF/CNF_Converter.h"

int main() {
    try{
        CFG_Engine engine { "S" };

        engine.AddProduction("S", {"A", "B", "C", "d"});
        engine.AddEpsilonProduction("A");
        engine.AddEpsilonProduction("B");
        engine.AddEpsilonProduction("C");

        CNF_Converter converter { engine };
        std::cout << engine.ToString();

    }
    catch (SymbolFormatError &err){
        std::cout << err.what();
    }


    return 0;
}
