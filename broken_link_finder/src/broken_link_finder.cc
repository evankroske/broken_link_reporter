#include <cstdio>

#include <string>
#include <vector>

using std::vector;
using std::string;

int main(int argc, char *argv[]) {
  vector<string> args(argv + 1, argv + argc);
  for (const auto &arg : args) {
    printf("%s\n", arg.c_str());
  }
  return 0;
}
