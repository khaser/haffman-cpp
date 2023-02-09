#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <set>

namespace khaser {

enum Target { compress, uncompress, undefined };

class ArgsParser {
public:
    Target mode;
    std::string in_filename;
    std::string out_filename;
private:
    bool correct;

public:
    ArgsParser(const size_t argc, char** argv);

    bool is_correct() const noexcept;

private:
    bool check_key(const std::vector<std::string>& args, const std::string& key) const noexcept; 

    std::string get_val_by_key(const std::vector<std::string>& args,
                                    const std::set<std::string>& keys) const noexcept; 
};

} // khaser namespace
