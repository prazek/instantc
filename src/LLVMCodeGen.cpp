#include "LLVMCodeGen.h"

const std::string LLVMCodeGen::prelude =
  "@dnl = internal constant [4 x i8] c\"%d\\0A\\00\"\n"
  "declare i32 @printf(i8*, ...)\n"
  " \n"
  "define void @printInt(i32 %x) {\n"
  "  %t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0\n"
  "  call i32 (i8*, ...) @printf(i8* %t0, i32 %x)\n"
  "  ret void\n"
  "}\n";

