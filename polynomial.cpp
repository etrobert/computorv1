#include "polynomial.h"

using std::string;

static void delete_spaces_after_char(string& s, char c) {
  size_t pos = s.find(c, 0);
  while (pos != string::npos) {
    s.erase(pos + 1, 1);
    pos = s.find(c, pos + 1);
  }
}

void delete_spaces_after_signs(string& s) {
  delete_spaces_after_char(s, '+');
  delete_spaces_after_char(s, '-');
}
