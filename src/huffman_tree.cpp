#include "huffman_tree.h"

#include "buffered_reader.h"
#include "byte_histogram.h"   
#include "huffman_node.h"
#include "utils.h"
#include "definitions.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace khaser;

namespace {

std::vector<bool> read_code(BufferedReader& reader) {

    byte code_size;
    reader.read(code_size);

    std::vector<bool> code(code_size);
    reader.read(code);

    return code;
}

} //anon namespace

khaser::HuffmanTree::HuffmanTree(BufferedReader& reader) {
    root = new HuffmanNode();

    byte nodes_count;
    try {
        reader.read(nodes_count);
    } catch (const ReaderException& err) {
        return;
    }

    for (int _ = 0; _ <= nodes_count; ++_) {
        byte ch;
        reader.read(ch);
        add_to_code(ch, read_code(reader));
    }
}

namespace {

void rec_delete(HuffmanNode* root) {
    if (root->L != nullptr) rec_delete(root->L);
    if (root->R != nullptr) rec_delete(root->R);
    delete root;
}

}  // anon namespace

khaser::HuffmanTree::~HuffmanTree() {
    rec_delete(root);
}

void khaser::HuffmanTree::add_to_code(byte ch, std::vector<bool> code) {
    HuffmanNode* cur = root;
    for (bool sign : code) {
        HuffmanNode*& root_field = (!sign ? cur->L : cur->R);
        if (root_field == nullptr) {
            HuffmanNode* new_node = new HuffmanNode(sign);
            root_field = new_node;
            new_node->root = cur;
        }
        cur = root_field;
    }
    node[ch] = cur;
    cur->val.ch = ch;
}

struct cmp {
    bool operator() (const HuffmanNode* a, const HuffmanNode* b) const {
        if (a->val.freq == b->val.freq)
            return a->val.ch < b->val.ch;
        return a->val.freq < b->val.freq;
    }
};

khaser::HuffmanTree::HuffmanTree(ByteHistogram& hist) {
    std::multiset<HuffmanNode*, cmp> buff;
    for (CharFreq &i : hist.get_dump()) {
        node[i.ch] = new HuffmanNode(i);
        buff.insert(node[i.ch]);
    }

    if (buff.size() == 0) {
        root = new HuffmanNode();
        return;
    }

    if (buff.size() == 1) {
        root = new HuffmanNode();
        root->link_to_L(*buff.begin());
        return;
    }

    while (buff.size() > 1) {
        HuffmanNode* l_node = *buff.begin();
        buff.erase(buff.begin());
        HuffmanNode* r_node = *buff.begin();
        buff.erase(buff.begin());

        buff.insert(new HuffmanNode(l_node, r_node));
    }
    root = *buff.begin();
}

/* TODO: check char correctness */ 
std::vector<bool> khaser::HuffmanTree::encode(byte ch) const {
    return node.find(ch)->second->get_path();
}

/* TODO: check data correctness */ 
byte khaser::HuffmanTree::decode(BufferedReader& reader) const {
    HuffmanNode* cur = root;
    while (cur->L != nullptr || cur->R != nullptr)  {
        bool b;
        reader.read(b);
        if (!b) {
            cur = cur->L;
        } else {
            cur = cur->R;
        }
    }
    return cur->val.ch;
}

std::ostream& khaser::operator<<(std::ostream& stream, HuffmanTree& tree) {
    for (auto [ch, node] : tree.node) {
        stream << (int)node->val.ch << ' ';
        std::vector<bool> code = node->get_path();
        stream << code.size() << ' ';
        for (bool i : code) {
            stream << i << ' ';
        }
        stream << '\n';
    }
    return stream;
}
