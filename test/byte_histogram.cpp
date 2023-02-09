#include "doctest.h"

#include "byte_histogram.h"

#include <vector>
#include <sstream>

using std::vector;
using khaser::ByteHistogram;
using khaser::CharFreq;

namespace khaser {

bool operator==(const CharFreq a, const CharFreq b) {
    return a.ch == b.ch && a.freq == b.freq;
}

}

TEST_CASE("Simple stat text") {
    std::stringstream ss("abacaba");
    vector<CharFreq> correct = {{'c', 1}, {'b', 2}, {'a', 4}};
    CHECK(ByteHistogram(ss).get_dump() == correct);
}
