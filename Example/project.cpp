#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <random>
#include "input.h"
#include "cache.h"

using namespace std;

string ullToString(ull num) {
    return bitset<64>(num).to_string();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <cache_config_file> <reference_list_file> <output_report_file>" << endl;
        return 1;
    }

    string cache_config_file = argv[1];
    string reference_list_file = argv[2];
    string output_report_file = argv[3];

    // Open the output report file
    ofstream outfile(output_report_file);
    if (!outfile) {
        cerr << "Unable to open output file: " << output_report_file << endl;
        return 1;
    }
    // Redirect cout to outfile
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(outfile.rdbuf());

    // Parse the cache configuration and reference list
    int offset_bits, index_bits_num, associativity;
    tie(offset_bits, index_bits_num, associativity) = parse_cache_config(cache_config_file);
    
    /// to do ///
    // use random seed to find the starting index bit
    // index bit = starting ~ starting + index_bits_num
    
    cout << "Indexing bits: " ;
    vector<int> index_bits;
    for (int i = index_bits_num-1; i >= 0; i--) {
        int temp = offset_bits + i; // choose LSB
        // store index bits inside index_bits vector
        cout << temp << " ";
        index_bits.push_back(temp);
    }
    cout << endl;
    cout << endl;
    //////// Start main logic
    // generate mask for getIdx function 
    create_mask(index_bits_num, offset_bits);
    
    // initialize cache with number of indexes, initialize cache line with associativity
    Cache.resize(1ULL << index_bits_num, cache_line(associativity));

    ifstream infile(reference_list_file);
    if (!infile) {
        cerr << "Unable to open file: " << reference_list_file << endl;
    }
    string line;
    while (getline(infile, line)) {
        if (line.empty() || line[0] == '.') {
            cout << line << endl;
            continue;
        }
        cout << line << " ";
        try {
            ull addr = stoull(line, nullptr, 2);
            ull idx = getIdx(addr, Mask, offset_bits);
            ull tag = getTag(addr, Mask, offset_bits, index_bits_num);
            
            // cout << "Address: " << addr << ", Index: " << idx << ", Tag: " << tag << " ";

            if (idx >= Cache.size()) {
                cerr << "Error: Index " << idx << " out of bounds (Cache size: " << Cache.size() << ")" << endl;
                continue;
            }
            if (!update_Cache(addr, idx, tag)) {
                cout << "miss" << endl;
                total_miss++;
            } else {
                cout << "hit" << endl;
            }
        } catch (const invalid_argument &e) {
            cerr << "Error: Invalid address format: " << line << endl;
        } catch (const out_of_range &e) {
            cerr << "Error: Address out of range: " << line << endl;
        }
    }
    cout << "Total cache miss count: " << total_miss << endl;
    infile.close();
    // Restore cout to its original state
    cout.rdbuf(coutbuf);

    return 0;
}

