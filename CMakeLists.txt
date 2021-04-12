cmake_minimum_required(VERSION 3.17)
project(CFG)

set(CMAKE_CXX_STANDARD 17)

add_executable(CFG main.cpp Core/CFG_Engine.cpp Core/CFG_Engine.h Core/GrammarSymbol.cpp Core/GrammarSymbol.h Core/Production.cpp Core/Production.h CNF/CNF_Converter.cpp CNF/CNF_Converter.h CNF/StringCombinatorics.cpp CNF/StringCombinatorics.h Utility/VectorUtility.h Core/GrammarSymbolGenerator.cpp Core/GrammarSymbolGenerator.h Utility/ListUtility.h)