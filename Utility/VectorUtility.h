//
// Created by swqd on 4/11/21.
//

#ifndef CFG_VECTORUTILITY_H
#define CFG_VECTORUTILITY_H

#include <vector>

template<typename T>
void VectorMerge(std::vector<T> &destination, std::vector<T> const& source){
    destination.reserve(source.size());
    for (const T& el : source){
        destination.push_back(el);
    }
}

#endif //CFG_VECTORUTILITY_H
