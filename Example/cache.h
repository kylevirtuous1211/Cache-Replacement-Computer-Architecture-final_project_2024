#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <vector>
#define ull unsigned long long
using namespace std;

// cache sets has a vector (len = associativity) cache blocks
struct cache_line {    // Represents a cache line (equivalent to a set)
 // TODO: Define data structures for cache line
 // - Valid bits for each way
 // - Tags for each way
 // - Reference bits for clock policy
 // - Clock pointer for replacement
    vector<bool> valid_bits;
    vector<ull> tags;
    vector<bool> ref_bits;
    int clock_pointer;
    int associativity;
    cache_line(int associativity) {
        this->associativity = associativity;
        valid_bits.resize(associativity, false);
        tags.resize(associativity, 0);
        ref_bits.resize(associativity, false);
        clock_pointer = 0;
    }
};
extern int total_miss;
extern ull Mask;
extern vector<cache_line> Cache;  // All cache lines (sets)

void create_mask(int index_bits, int offset_bits); // create mask
ull getIdx(ull addr, ull Mask, int offset_bits); // find Idx
ull getTag(ull addr, ull Mask, int offset_bits, int index_bits); // find Tag
bool update_Cache(ull addr, int line, ull tag); // update cache
int clock_replacement(cache_line &cache_set); // when cache miss, replace policy

#endif // CACHE_H