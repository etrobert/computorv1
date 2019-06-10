#include "split_string.h"

#include <sstream>

using std::vector;
using std::string;
using std::istringstream;
using std::getline;

vector<string> split_string(const string& s, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream stream(s);
  while (getline(stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}
