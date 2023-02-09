#include "utils.h"

#include "definitions.h"

#include <algorithm>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<bool> to_bits(byte x) {
    std::vector<bool> res(bs);
    for (size_t i = 0; i < bs; ++i) {
        res[i] = x % 2;
        x /= 2;
    }

    std::reverse(res.begin(), res.end());
    return res;
}

byte to_byte(const std::vector<bool>& x) {
    if (x.size() != bs) 
        throw std::logic_error(
                    "argument size(" + std::to_string(x.size()) + ") != byte size(" + std::to_string(bs) + ")"
                );

    byte res = 0;
    for (bool i : x) {
        res = 2 * res + i;
    }
    return res;
}
