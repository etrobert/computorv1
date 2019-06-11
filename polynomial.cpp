#include "polynomial.h"

using std::string;
using std::string_view;

static void delete_spaces_after_char(string& s, char c) {
  size_t pos = s.find(c, 0);
  while (pos != string::npos) {
    s.erase(pos + 1, 1);
    pos = s.find(c, pos + 1);
  }
}

string delete_spaces_after_signs(string_view s) {
  string r(s);
  delete_spaces_after_char(r, '+');
  delete_spaces_after_char(r, '-');
  return r;
}
