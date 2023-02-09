#include "huffman_node.h"
#include "byte_histogram.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
    
khaser::HuffmanNode::HuffmanNode() : sign(0), val({0, 0}), L(nullptr), R(nullptr), root(nullptr) {}

khaser::HuffmanNode::HuffmanNode(bool sign) : sign(sign), val({0, 0}), L(nullptr), R(nullptr), root(nullptr) {};

khaser::HuffmanNode::HuffmanNode(CharFreq val) : sign(0), val(val), L(nullptr), R(nullptr), root(nullptr) {}

khaser::HuffmanNode::HuffmanNode(HuffmanNode* a, HuffmanNode* b) : sign(0), root(nullptr) {
    link_to_L(a);
    link_to_R(b);
    val.freq = a->val.freq + b->val.freq;
    val.ch = 0;
}

void khaser::HuffmanNode::link_to_L(HuffmanNode* other) {
    other->sign = 0;
    this->L = other;
    other->root = this;
}

void khaser::HuffmanNode::link_to_R(HuffmanNode* other) {
    other->sign = 1;
    this->R = other;
    other->root = this;
}

std::vector<bool> khaser::HuffmanNode::get_path() const {
    std::vector<bool> res;
    const HuffmanNode* cur = this;

    while (cur->root != nullptr) {
        res.emplace_back(cur->sign);
        cur = cur->root;
    }

    std::reverse(res.begin(), res.end());
    return res;
}

bool khaser::HuffmanNode::operator<(const HuffmanNode& other) const noexcept {
    if (val.freq == other.val.freq)
        return val.ch < other.val.ch;
    return val.freq < other.val.freq;
}
