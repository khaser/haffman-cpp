#include "doctest.h"

#include "byte_histogram.h"
#include "huffman_node.h"
#include "huffman_tree.h"
#include "buffered_reader.h"
#include "buffered_writer.h"

#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::stringstream;
using namespace khaser;

namespace {

bool fano_compatibility(const vector<bool>& a, const vector<bool>& b) {
    auto [it_a, it_b] = std::mismatch(a.begin(), a.end(), b.begin(), b.end());
    return (it_a != a.end() && it_b != b.end());
}

bool fano_compatibility(const vector<vector<bool>> &codes) {
    for (auto i = codes.begin(); i != codes.end(); ++i) {
        for (auto j = i + 1; j != codes.end(); ++j) {
            if (!fano_compatibility(*i, *j)) return false;
        }
    }
    return true;
}

}

TEST_CASE("construction correct fano check") {
    stringstream ss("abacaba");
    ByteHistogram hist(ss);
    HuffmanTree tree(hist);
    vector<vector<bool>> codes;

    SUBCASE("from ByteHistogram") {
        for (byte i = 'a'; i <= 'c'; ++i) {
            codes.emplace_back(tree.encode(i));
        }
    }

    SUBCASE("from BufferedReader") {
        stringstream file;
        BufferedWriter writer(file);
        writer.write(tree);
        writer.close();
        file.flush();
        BufferedReader reader(file);
        HuffmanTree new_tree(reader);

        vector<vector<bool>> codes;
        for (byte i = 'a'; i <= 'c'; ++i) {
            codes.emplace_back(new_tree.encode(i));
        }
    }

    CHECK(fano_compatibility(codes));
}

