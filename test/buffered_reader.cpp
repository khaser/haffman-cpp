#include "doctest.h"

#include "buffered_reader.h"

#include <sstream>
#include <vector>

using std::stringstream;
using std::vector;
using khaser::BufferedReader;
using khaser::ReaderException;

namespace {

void check(stringstream& ss, const vector<bool>& correct) {
    ss.flush();

    BufferedReader test(ss);
    vector<bool> bits(correct.size());
    test.read(bits);

    CHECK(bits == correct);
    ss.clear();
    CHECK(test.get_readed_bytes() == ss.tellg());
}

} //anon namespace 

TEST_CASE("bits read") {

    SUBCASE("read 10 false bits") {
        stringstream ss;
        ss.put((byte) 0);
        ss.put((byte) 0);
        ss.put((byte) 2);
        check(ss, vector<bool> (10, false));
    }

    SUBCASE("read 10 true bits") {
        stringstream ss;
        ss.put((byte) 255);
        ss.put((byte) 3);
        ss.put((byte) 2);
        check(ss, vector<bool> (10, true));
    }

    SUBCASE("read 5 random bits") {
        stringstream ss;
        ss.put((byte) 9);
        ss.put((byte) 5);
        check(ss, vector<bool> {false, true, false, false, true});
    }

    SUBCASE("empty stream") {
        stringstream ss;
        CHECK_THROWS_AS(check(ss, vector<bool> (5)), const ReaderException&);
    }
}

TEST_CASE("bytes read") {
    stringstream ss;
    ss.put((byte) 9);
    ss.put((byte) 8);
    ss.flush();
    BufferedReader reader(ss);
    byte ch;
    reader.read(ch);
    CHECK(ch == 9);
    CHECK(reader.get_readed_bytes() == 2);
}
