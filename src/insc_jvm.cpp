#include <fstream>
#include <cstdlib>
#include "Lexer.h"
#include "LexStream.h"
#include "Parser.h"
#include "JasminCodeGen.h"


std::string parseFilePath(const std::string& fullName) {
  auto dot = fullName.rfind('.');
  if (dot ==  std::string::npos)
    return fullName;
  return fullName.substr(0, dot);
}

std::string getFileName(const std::string &filePath) {
  auto slash = filePath.rfind('/');
  if (slash == std::string::npos)
    return filePath;
  return filePath.substr(slash + 1);
}

std::string getBasePath(const std::string &filePath) {
  auto slash = filePath.rfind('/');
  if (slash == std::string::npos)
    return filePath;
  return filePath.substr(0, slash);
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

  auto parsedFile = parseFilePath(argv[1]);
  auto jasminFileName = parsedFile + ".j";
  std::fstream outFile(jasminFileName, std::ios_base::out);

  auto className = getFileName(parsedFile);

  JasminCodeGen CG(outFile, className);
  CG.emit(ast);
  outFile.flush();
  outFile.close();

  auto classOutDir = getBasePath(parsedFile);
  std::string command = "java -jar lib/jasmin.jar " +
    jasminFileName + " -d " + classOutDir;
  //std::cout << "executing [" << command + "]\n";
  std::system(command.c_str());
}