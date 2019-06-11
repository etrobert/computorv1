#include "split_string.h"

#include <sstream>

using std::vector;
using std::string;
using std::istringstream;
using std::getline;
using std::string_view;

vector<string> split_string(const string& s, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream stream(s);
  while (getline(stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

vector<string_view> split_string(string_view s, char delimiter) {
  vector<string_view> tokens;
  size_t start(0), pos(0);
  while ((pos = s.find(delimiter, start)) != string_view::npos) {
    tokens.push_back(s.substr(start, pos - start));
    start = pos + 1;
  }
  // Add the end of the string if it did not end with a delimiter
  if (start != s.length())
    tokens.push_back(s.substr(start));
  return tokens;
}
