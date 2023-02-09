#pragma once

#include "definitions.h"
#include "huffman_tree.h"

#include <iostream>
#include <queue>
#include <algorithm>

namespace khaser {

class BufferedWriter {
private:
    std::ostream& fout;
    std::queue<bool> buff;
    const bool salt;
    int state = 0;
    ll written;

public:

    BufferedWriter(std::ostream& fout, bool salt = true);

    ~BufferedWriter(); 

    void flush(); 
    
    void write(const std::vector<bool>& bits); 

    void write(const std::vector<byte>& bytes);

    void write(byte x);

    void write(const HuffmanTree& tree);

    void close();

    ll get_written_bytes() const noexcept;
};

} // khaser namespace
