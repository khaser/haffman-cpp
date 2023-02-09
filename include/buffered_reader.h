#pragma once

#include "definitions.h"

#include <ios>
#include <iostream>
#include <queue>
#include <ios>

namespace khaser {

class ReaderException : public std::ios_base::failure {
public:
    ReaderException(const char* str) : std::ios_base::failure(str) {};
};

class BufferedReader {
private:
    std::istream& fin;
    std::queue<bool> buff;
    bool ended;
    ll readed;

    void get_more();
public:

    BufferedReader(std::istream& fin);
    
    void read(std::vector<bool>& bits);

    void read(byte& x);

    void read(bool& x);

    bool is_ended() const noexcept;

    ll get_readed_bytes() const noexcept;
};

} //khaser namespace
