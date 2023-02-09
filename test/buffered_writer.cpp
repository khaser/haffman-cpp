#include "doctest.h"

#include "buffered_writer.h"

#include <sstream>
#include <vector>

using std::stringstream;
using std::vector;
using khaser::BufferedWriter;

namespace {
    template<typename T>
    void check(const vector<T>& bits, stringstream& correct) {
        stringstream ss;

        BufferedWriter test(ss);
        test.write(bits);
        test.close();
        ss.flush();

        CHECK(ss.str() == correct.str());
        CHECK(ss.str().size() == test.get_written_bytes());
    }
}

TEST_CASE("simple bits write") {

    SUBCASE("write 10 false bits") {
        stringstream correct;
        correct.put((byte) 0);
        correct.put((byte) 0);
        correct.put((byte) 2);
        check(vector<bool> (10, false), correct);
    }

    SUBCASE("write 10 true bits") {
        stringstream correct;
        correct.put((byte) 255);
        correct.put((byte) 3);
        correct.put((byte) 2);
        check(vector<bool> (10, true), correct);
    }

    SUBCASE("write 5 random bits") {
        stringstream correct;
        correct.put((byte) 9);
        correct.put((byte) 5);
        check(vector<bool> {false, true, false, false, true}, correct);
    }
}

TEST_CASE("simple bytes write") {

    SUBCASE("write 2 false bytes") {
        stringstream correct;
        correct.put((byte) 0);
        correct.put((byte) 0);
        correct.put((byte) 8);
        check(vector<byte> (2, 0), correct);
    }

    SUBCASE("write 2 true bytes") {
        stringstream correct;
        correct.put((byte) 255);
        correct.put((byte) 255);
        correct.put((byte) 8);
        check(vector<byte> (2, 255), correct);
    }

    SUBCASE("write random byte") {
        stringstream correct;
        correct.put((byte) 228);
        correct.put((byte) 8);
        check(vector<byte> {228}, correct);
    }
}
