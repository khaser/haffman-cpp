#include "buffered_reader.h"

#include "utils.h"
#include <algorithm>
#include <queue>

namespace {

template <typename T>
void drop(std::queue<T>& buff, byte cnt) {
    for (size_t i = 0; i < (size_t) cnt; ++i) {
        buff.pop();
    }
}

}

void khaser::BufferedReader::get_more() {
    if (!fin.good()) {
        ended = true;
        throw ReaderException("Not enought bits in stream");
    }

    byte ch = fin.get();
    readed++;
    for (byte i : to_bits(ch)) {
        buff.push(i);
    }

    byte check = fin.get();
    if (!fin.good()) {
        drop(buff, bs);
        ended = true;
        throw ReaderException("Not enought bits in stream");
    }

    if (fin.peek() == (int) std::char_traits<wchar_t>::eof()) {
        readed++;
        drop(buff, bs - check);
        ended = true;
    } else {
        fin.unget();
    }
}

khaser::BufferedReader::BufferedReader(std::istream& fin) : fin(fin), ended(false), readed(0) {}

void khaser::BufferedReader::read(std::vector<bool>& bits) {
    std::generate(bits.begin(), bits.end(), [this]() { bool b; read(b); return b; });
}

void khaser::BufferedReader::read(byte& x) {
    std::vector<bool> block(bs);
    std::generate(block.begin(), block.end(), [this]() { 
        if (buff.empty()) {
            get_more();
        }
        bool b = buff.front();
        buff.pop();
        return b;
    });
    x = to_byte(block);
}

void khaser::BufferedReader::read(bool& x) {
    if (buff.empty()) {
        get_more();
    }
    x = buff.front();
    buff.pop();
}

bool khaser::BufferedReader::is_ended() const noexcept {
    return ended && buff.empty();
}

ll khaser::BufferedReader::get_readed_bytes() const noexcept {
    return readed;
}
