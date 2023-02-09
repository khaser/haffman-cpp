#include "buffered_writer.h"

#include "buffered_reader.h"
#include "utils.h"

void khaser::BufferedWriter::flush() {
    if (state >= 2) return;

    byte last_size = buff.size();
    while (buff.size() >= bs || (state && !buff.empty())) {
        byte block = 0;
        std::size_t bits_in_block = std::min((size_t) bs, buff.size());
        for (std::size_t i = 0; i < bits_in_block; ++i) {
            block = 2 * block + buff.front();
            buff.pop();
        }
        fout.put(block);
        written++;
    }

    if (state && salt) {
        fout.put(last_size != 0 ? last_size : 8);
        written++;
        state = 2;
    }
}

khaser::BufferedWriter::BufferedWriter(std::ostream& fout, bool salt) : fout(fout), salt(salt), written(0) { }

khaser::BufferedWriter::~BufferedWriter() {
    close();
    flush();
}

void khaser::BufferedWriter::write(const std::vector<bool>& bits) {
    for (const bool& i : bits) {
        buff.push(i);
    }
    flush();
}

void khaser::BufferedWriter::write(const std::vector<byte>& bytes) {
    for (const byte& i : bytes) {
        write(i);
    }
    flush();
}

void khaser::BufferedWriter::write(byte x) {
    for (byte i : to_bits(x)) {
        buff.push(i);
    }
    flush();
}

void khaser::BufferedWriter::write(const HuffmanTree& tree) {
    if (tree.node.size() == 0) return;

    write((byte) tree.node.size() - 1);
    for (auto [ch, node] : tree.node) {
        write((byte) node->val.ch);
        std::vector<bool> code = node->get_path();
        write((byte) code.size());
        write(code);
    }
    flush();
}

// WARNING: не учитывает буферизацию
ll khaser::BufferedWriter::get_written_bytes() const noexcept {
    /* flush(); */
    return written + ((buff.size() + bs - 1) / bs);
}

void khaser::BufferedWriter::close() {
    if (state == 0)
        state++;
    flush();
}
