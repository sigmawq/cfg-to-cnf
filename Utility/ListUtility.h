//
// Created by swqd on 4/12/21.
//

#ifndef CFG_LISTUTILITY_H
#define CFG_LISTUTILITY_H

#include <list>

// ListReplace(std::__cxx11::list<const GrammarSymbol*>::const_iterator, std::_List_const_iterator<const GrammarSymbol*>, const GrammarSymbol*&

template<typename T>
static void ListReplace(std::list<T> &list, typename std::list<T>::const_iterator &first,
                        typename std::list<T>::const_iterator &second,
                 T const& replaceBy){
    auto it = list.erase(first, second);
    list.insert(it, replaceBy);
}

template<typename T>
static std::list<T> ListLongestPrefix(std::list<T> const& list){
    auto result = std::list<T> { list.begin(), std::next(list.begin(), list.size() - 1) };
    return result;
}

#endif //CFG_LISTUTILITY_H
