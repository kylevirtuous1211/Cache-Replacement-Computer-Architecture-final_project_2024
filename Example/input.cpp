#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <tuple>
#include "input.h"
#define ull unsigned long long

using namespace std;

tuple<int, int, int> parse_cache_config(const string &path_cache) {
    ifstream infile(path_cache);
    if (!infile) {
        cerr << "Unable to open file: " << path_cache << endl;
        return {0, 0, 0};
    }

    string line;
    int address_bits, block_size, cache_sets, associativity;

    while (getline(infile, line)) {
        if (line.find("Address_bits:") != string::npos) {
            address_bits = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("Block_size:") != string::npos) {
            block_size = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("Cache_sets:") != string::npos) {
            cache_sets = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("Associativity:") != string::npos) {
            associativity = stoi(line.substr(line.find(":") + 1));
        }
    }

    infile.close();

    // Output the parsed values for verification
    cout << "Address bits: " << address_bits << endl;
    cout << "Block size: " << block_size << endl;
    cout << "Cache sets: " << cache_sets << endl;
    cout << "Associativity: " << associativity << endl;
    
    int offset_bits = log2(block_size);
    int index_bits = log2(cache_sets);

    cout << "\n\nOffset bit count: " << offset_bits << endl;
    cout << "Indexing bit count: " << index_bits << endl;
    return {offset_bits, index_bits, associativity};
}


