#include <fstream>
#include <cstdio>


int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("instant language compiler\n");
    printf("Usage: %s file.ins\n", argv[0]);
    exit(1);
  }
  auto fileName = argv[1];

  std::fstream instantFile(fileName, std::ios_base::in);
  if (!instantFile.is_open()) {
    printf("Could not open file [%s]", fileName);
  }



}