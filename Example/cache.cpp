#include <vector>
#include <string>
#include "cache.h"

using namespace std;

int total_miss = 0;
ull Mask = 0;
vector<cache_line> Cache;

bool update_Cache(ull addr, int line, ull tag) {
// TODO: Handle cache access
// - Find cache line using index
// - Check ways in line for hit
// - Handle hit/miss cases
// Return: 1 for hit, 0 for miss
    cache_line &cache_set = Cache[line];
    // hit
    for (int i = 0; i < cache_set.associativity; i++) {
        if (cache_set.valid_bits[i] && cache_set.tags[i] == tag) {
            cache_set.ref_bits[i] = true;
            return true;
        }
    }
    // miss, find which way to replace and initialize
    int replacedWay = clock_replacement(cache_set);
    cache_set.valid_bits[replacedWay] = true;
    cache_set.tags[replacedWay] = tag;
    cache_set.ref_bits[replacedWay] = true;
    return false;
}

ull getIdx(ull addr, ull Mask, int offset_bits) {
// TODO: Extract index from address using mask
    return (addr & Mask) >> offset_bits;
}
ull getTag(ull addr, ull Mask, int offset_bits, int index_bits) {
    return addr >> (index_bits + offset_bits);
}

void create_mask(int index_bits, int offset_bits) {
    Mask = ((1ULL << index_bits) - 1) << offset_bits;
}

int clock_replacement(cache_line &cache_set) {
// TODO: Like a clock hand moving through ways
// - If current way's ref_bit is 0:
//   -> Select this way for replacement
// - If current way's ref_bit is 1:
//   -> Set it to 0 and move to next way
// Remember to advance clock pointer
    while (true) {
        // ref bit = 0
        if (cache_set.ref_bits[cache_set.clock_pointer] == false) {
            int tempWay = cache_set.clock_pointer;
            cache_set.clock_pointer = (cache_set.clock_pointer + 1) % cache_set.associativity;
            return tempWay;
        }
        // ref bit = 1
        cache_set.ref_bits[cache_set.clock_pointer] = false;
        cache_set.clock_pointer = (cache_set.clock_pointer + 1) % cache_set.associativity;
    }
}