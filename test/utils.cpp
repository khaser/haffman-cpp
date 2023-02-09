#include "doctest.h"

#include "utils.h"
#include "definitions.h"

#include <functional>
#include <random>
#include <algorithm>
#include <stdexcept>

using std::vector;

TEST_CASE("to_bits simple") {
    SUBCASE("zero byte") {
        CHECK(to_bits(0) == vector<bool> (8, false));
    }
    SUBCASE("full byte") {
        CHECK(to_bits(255) == vector<bool> (8, true));
    }
    SUBCASE("one random byte") {
        CHECK(to_bits(19) == vector<bool> {false,false,false,true,false,false,true,true});
    }
}

TEST_CASE("to_byte simple") {
    SUBCASE("zero byte") {
        CHECK(0 == to_byte(vector<bool> (8, false)));
    }
    SUBCASE("full byte") {
        CHECK(255 == to_byte(vector<bool> (8, true)));
    }
    SUBCASE("one random byte") {
        CHECK(19 == to_byte(vector<bool> {false,false,false,true,false,false,true,true}));
    }
    SUBCASE("incorrect size") {
        CHECK_THROWS_AS(to_byte(vector<bool> (bs + 1)), const std::logic_error&);
    }
}
