#include "byte_histogram.h"

#include <algorithm>

using khaser::CharFreq;

khaser::ByteHistogram::ByteHistogram(std::istream& stream) {
    while (!stream.eof() && !stream.fail()) {
        byte ch = stream.get();
        if (stream.eof()) break;
        hist[ch]++;
    }
    stream.clear();
}

std::vector<CharFreq> khaser::ByteHistogram::get_dump() const noexcept {
    std::vector<CharFreq> res;
    for (auto [ch, freq] : hist) {
        res.push_back({ch, freq});
    }
    std::sort(res.begin(), res.end(), [] (const CharFreq& a, const CharFreq& b) {
        if (a.freq == b.freq) 
            return a.ch < b.ch;
        return a.freq < b.freq;
    });
    return res;
}
