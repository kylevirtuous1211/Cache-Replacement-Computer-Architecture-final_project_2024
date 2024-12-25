#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <utility>
#include <tuple>
#define ull unsigned long long
using namespace std;

// Function to parse cache configuration from a file
tuple<int, int, int> parse_cache_config(const string &path_cache);

// Function to parse reference list from a file
vector<ull> parse_reference_list(const string &path_ref);

#endif // INPUT_H