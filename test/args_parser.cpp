#include "doctest.h" 

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

#include "args_parser.h"

using std::vector;
using std::string;
using namespace khaser;

class ArgsMock {
private:
    size_t _argc;
    char** _argv;

public:
    ArgsMock(const char* str) {
        std::stringstream ss(str);
        vector<string> args;
        string tmp;
        while (ss >> tmp) {
            args.emplace_back(tmp);
        }

        _argc = args.size();
        _argv = new char*[args.size()];
        for (size_t i = 0; i < args.size(); ++i) {
            _argv[i] = new char[args[i].size()];
            strcpy(_argv[i], args[i].c_str());
        }
    }
     
    ~ArgsMock() {
        for (size_t i = 0; i < _argc; ++i) {
            delete _argv[i];
        }
        delete _argv;
    }

    char** argv() {
        return _argv;
    }
    
    size_t argc() {
        return _argc;
    }
};


TEST_CASE("Simple args") {
    ArgsMock mock("./huffman -c -f myfile.txt -o result.bin"); 
    ArgsParser parser(mock.argc(), mock.argv());
    CHECK(parser.is_correct() == true);
    CHECK(parser.mode == compress);
    CHECK(parser.in_filename == "myfile.txt");
    CHECK(parser.out_filename == "result.bin");
}

TEST_CASE("Without value for key") {
    ArgsMock mock("./huffman -c -f myfile.txt -o"); 
    ArgsParser parser(mock.argc(), mock.argv());
    CHECK(parser.is_correct() == false);
}

TEST_CASE("Without target") {
    ArgsMock mock("./huffman -f myfile.txt -o result.bin"); 
    ArgsParser parser(mock.argc(), mock.argv());
    CHECK(parser.is_correct() == false);
}

TEST_CASE("With fuzzy flags") {
    ArgsMock mock("./huffman -kek --lol -f myfile.txt -o result.bin -u"); 
    ArgsParser parser(mock.argc(), mock.argv());
    CHECK(parser.is_correct() == true);
    CHECK(parser.mode == uncompress);
    CHECK(parser.in_filename == "myfile.txt");
    CHECK(parser.out_filename == "result.bin");
}

TEST_CASE("Empty args") {
    ArgsMock mock(""); 
    ArgsParser parser(mock.argc(), mock.argv());
    CHECK(parser.is_correct() == false);
}
