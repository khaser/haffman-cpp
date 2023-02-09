#pragma once

#include "byte_histogram.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

namespace khaser {

class HuffmanNode {
public:
    bool sign;
    CharFreq val;
    HuffmanNode* L;
    HuffmanNode* R;
    HuffmanNode* root;

    HuffmanNode();
    HuffmanNode(bool sign);
    HuffmanNode(CharFreq val);
    HuffmanNode(HuffmanNode* a, HuffmanNode* b);

    std::vector<bool> get_path() const; 
    bool operator<(const HuffmanNode& other) const noexcept;

    void link_to_L(HuffmanNode* other); 

    void link_to_R(HuffmanNode* other);
};

} // khaser namespace
