#include <fstream>
#include <cstdlib>
#include "Lexer.h"
#include "LexStream.h"
#include "Parser.h"
#include "JasminCodeGen.h"


std::string parseFileName(const std::string& fullName) {
  auto dot = fullName.rfind('.');
  if (dot ==  std::string::npos)
    return fullName;
  return fullName.substr(0, dot);
}

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

  Lexer lexer(instantFile);
  LexStream stream(lexer);
  Parser parser(stream);
  auto ast = parser.runParser();

  auto parsedFile = parseFileName(argv[1]);
  auto jasminFileName = parsedFile + ".j";
  auto bcFileName = parsedFile + ".bc";
  std::fstream outFile(jasminFileName, std::ios_base::out);

  JasminCodeGen CG(outFile, parsedFile);
  CG.emit(ast);

  std::string command = "java -jar jasmin.jar " + jasminFileName;
  std::system(command.c_str());
}