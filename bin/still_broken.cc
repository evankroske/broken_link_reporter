#include <cstdio>
#include <memory>
#include <string>

int main(int argc, char **argv) {
  using std::string;
  std::unique_ptr<char[]> buf(new char[1000]);
  while (true) {
    int status = scanf("%999s", buf.get());
    if (status == EOF) {
      break;
    }
    string source(buf.get());
    scanf("%999s", buf.get());
    string href(buf.get());
    printf("%s -> %s\n", source.c_str(), href.c_str());
  }
  return 0;
}
