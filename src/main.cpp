#include <vector>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <filesystem>

#include "definitions.h"
#include "args_parser.h"
#include "byte_histogram.h"
#include "huffman_tree.h"
#include "buffered_reader.h"
#include "buffered_writer.h"

using std::cout;
using namespace khaser;

int main(int argc, char** argv) {

    ArgsParser args(argc, argv);
    if (!args.is_correct()) {
        cout << "Incorrect arguments\n";
        return 1;
    }

    std::ifstream fin(args.in_filename, std::ios_base::binary);
    std::ofstream fout(args.out_filename, std::ios_base::binary);


    switch (args.mode) {
        case compress: {
            ByteHistogram signature(fin);
            HuffmanTree tree(signature);

            BufferedWriter writer(fout, true);
            writer.write(tree);
            ll tree_size = writer.get_written_bytes();

            fin.seekg(0);
            while (true) {
                byte ch = fin.get();
                if (!fin.good()) break;
                std::vector<bool> block = tree.encode(ch);
                writer.write(block);
            }
            writer.close();

            ll full_size = writer.get_written_bytes();
            fin.clear();
            cout << fin.tellg() << '\n' << full_size - tree_size - 1 << '\n' << tree_size + 1 << '\n';

            break;
        }
        case uncompress: {
            BufferedReader reader(fin);
            HuffmanTree tree(reader);
            ll tree_size = reader.get_readed_bytes();

            BufferedWriter writer(fout, false);
            try {
                while (!reader.is_ended()) {
                    byte ch = tree.decode(reader);
                    writer.write(ch);
                } 
            } catch (const ReaderException& err) {
                break;
            } 
            writer.close();

            ll full_input_size = reader.get_readed_bytes();
            ll full_output_size = writer.get_written_bytes();

            if (tree_size != full_input_size) {
                cout << full_input_size - tree_size  - 1 << '\n' << full_output_size << '\n'\
                     << tree_size + 1 << '\n';
            } else {
                cout << full_input_size - tree_size  << '\n' << full_output_size << '\n'\
                     << tree_size << '\n';
            }
            break;
        }
        case undefined: {
            cout << "Undefined mode\n";
            return 1;
        }
    } 
    return 0;
}
