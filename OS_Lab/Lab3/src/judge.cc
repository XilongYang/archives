#include "judge.h"
#include <regex>

using std::regex;
using std::regex_match;

bool IsNum(const string& str) {
    regex num_r("[0-9]+");
    return regex_match(str, num_r);
}