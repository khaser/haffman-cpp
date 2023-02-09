#pragma once

#include "definitions.h"
#include "byte_histogram.h"   
#include "huffman_node.h"
#include "buffered_reader.h"

#include <iostream>
#include <vector>

namespace khaser {

class HuffmanTree {
    friend std::ostream& operator<<(std::ostream& stream, HuffmanTree& tree);

public:
    HuffmanNode* root;
    std::map<byte, HuffmanNode*> node;

    HuffmanTree(BufferedReader& reader);

    HuffmanTree(ByteHistogram& hist); 

    ~HuffmanTree();

    std::vector<bool> encode(byte ch) const; 

    byte decode(BufferedReader& reader) const; 

private:
    void add_to_code(byte ch, std::vector<bool> code);
};

std::ostream& operator<<(std::ostream& stream, HuffmanTree& tree); 

} // khaser namespace
