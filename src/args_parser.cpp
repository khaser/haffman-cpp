#include "args_parser.h"

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using std::string;
using std::vector;
using std::set;

khaser::ArgsParser::ArgsParser(const size_t argc, char** argv) : correct(true) {
    vector<string> args(argc);
    for (size_t i = 0; i < argc; ++i) {
        args[i] = string(argv[i]);
    }

    if (check_key(args, "-c")) {
        mode = compress;
    } else if (check_key(args, "-u")) {
        mode = uncompress;
    } else {
        mode = undefined;
    }

    in_filename = get_val_by_key(args, {"-f", "--file"});
    out_filename = get_val_by_key(args, {"-o", "--output"});

    if (mode == undefined || in_filename == "" || out_filename == "") {
        correct = false;
        mode = undefined;
        in_filename = out_filename = "";
    }
}

bool khaser::ArgsParser::is_correct() const noexcept {
    return correct;
}

bool khaser::ArgsParser::check_key(const vector<string>& args, const string& key) const noexcept {
    return std::find(args.begin(), args.end(), key) != args.end();
}

string khaser::ArgsParser::get_val_by_key(const vector<string>& args, const set<string>& keys) const noexcept {
    auto it = std::find_if(args.begin(), args.end(), [&keys] (const string& str) {
        return keys.find(str) != keys.end();
    });

    if (it == args.end() || it + 1 == args.end()) return "";
    return *(++it);
}
