#include "doctest.h"

#include "buffered_reader.h"
#include "buffered_writer.h"

#include <random>
#include <algorithm>
#include <sstream>
#include <vector>
#include <random>

using std::stringstream;
using std::mt19937;
using std::vector;
using khaser::BufferedReader;
using khaser::BufferedWriter;

TEST_CASE("Fuzzy test") {
    for (int i = 1; i < 40; ++i) {
        stringstream ss;
        mt19937 azino(777);
        vector<byte> origin(i);
        std::generate(origin.begin(), origin.end(), azino);

        BufferedWriter writer(ss);
        for (byte j : origin) {
            writer.write(j);
        }
        writer.close();
        ss.flush();

        BufferedReader reader(ss);
        vector<byte> output;
        for (int j = 0; j < i; ++j) {
            byte ch;
            reader.read(ch);
            output.emplace_back(ch);
        }
        CHECK(output == origin);
    }
}
