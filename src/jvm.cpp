
#include "antlr4-runtime.h"
#include "common.h"
#include "StaticAnalysis.h"
#include "LLVMCodeGen.h"
#include "JasminCodeGen.h"
#include "InstantLexer.h"
#include <iostream>


using namespace antlr4;

static std::string parseFilePath(const std::string& fullName) {
  auto dot = fullName.rfind('.');
  if (dot ==  std::string::npos)
    return fullName;
  return fullName.substr(0, dot);
}

static std::string getFileName(const std::string &filePath) {
  auto slash = filePath.rfind('/');
  if (slash == std::string::npos)
    return filePath;
  return filePath.substr(slash + 1);
}

static std::string getBasePath(const std::string &filePath) {
  auto slash = filePath.rfind('/');
  if (slash == std::string::npos)
    return filePath;
  return filePath.substr(0, slash);
}

static std::fstream openFile(const std::string &fileName) {
  std::fstream instantFile(fileName, std::ios_base::in);
  if (!instantFile.is_open()) {
    printf("Could not open file [%s]", fileName.c_str());
    exit(1);
  }
  return instantFile;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    printf("instant language compiler\n");
    printf("Usage: %s file.ins\n", argv[0]);
    exit(1);
  }

  std::string fileName = argv[1];
  std::fstream instantFile = openFile(fileName);

  auto parsedFile = parseFilePath(fileName);
  auto jasminFileName = parsedFile + ".j";
  std::fstream outFile(jasminFileName, std::ios_base::out);

  auto className = getFileName(parsedFile);

  ANTLRInputStream input(instantFile);
  InstantLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  InstantParser parser(&tokens);
  auto *ast = parser.program();

  Diagnostic diagnostic(fileName);
  StaticAnalysis staticAnalysis(diagnostic);
  staticAnalysis.visit(ast);
  //JasminCodeGenVisitor visitor(std::cout, className);
  //std::cout.flush();
  JasminCodeGenVisitor visitor(outFile, className);
  visitor.visit(ast);
  outFile.flush();


  auto classOutDir = getBasePath(parsedFile);
  std::string command = "java -jar lib/jasmin.jar " +
    jasminFileName + " -d " + classOutDir;

  std::system(command.c_str());
  return 0;
}

