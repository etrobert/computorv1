#include <iostream>
#include <string>

#include "computorv1.h"

using std::cout;
using std::endl;
using std::string;

void usage(string prog_name) {
  cout << "usage: " << prog_name << " equation" << endl;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    usage(argv[0]);
    return 0;
  }
  computorv1(argv[1]);
  return (0);
}
