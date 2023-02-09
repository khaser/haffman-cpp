#include "doctest.h"

#include "huffman_node.h"

#include <vector>
#include <string>

using std::vector;
using std::string;
using khaser::HuffmanNode;

TEST_CASE("Basic node test") {
    HuffmanNode* a = new HuffmanNode({'a', 10});
    HuffmanNode* b = new HuffmanNode({'b', 4});
    
    HuffmanNode* root = nullptr;
    SUBCASE("Creating by constructor from two nodes") {
        root = new HuffmanNode(a, b);
    }

    SUBCASE("Creating by default constructor and link_to_L and link_to_R") {
        root = new HuffmanNode();
        root->link_to_L(a);
        root->link_to_R(b);
    }

    CHECK(a->sign == 0);
    CHECK(b->sign == 1);
    CHECK(a->get_path() == vector<bool> {0});
    CHECK(b->get_path() == vector<bool> {1});
    CHECK(root->get_path() == vector<bool> (0));
    CHECK(a->root == root);
    CHECK(b->root == root);
    CHECK(root->L == a);
    CHECK(root->R == b);
}

