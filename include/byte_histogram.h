#pragma once

#include "definitions.h"
#include "buffered_reader.h"

#include <iostream>
#include <vector>
#include <map>

namespace khaser {

struct CharFreq {
    byte ch;
    ll freq;
};

class ByteHistogram {
private:
    std::map<byte, ll> hist;
public: 
    ByteHistogram(std::istream& stream);
    std::vector<CharFreq> get_dump() const noexcept;
};

} // khaser namespace
