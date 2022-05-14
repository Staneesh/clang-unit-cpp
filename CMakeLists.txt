set(LLVM_LINK_COMPONENTS support)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_clang_executable(clang-unit 
	src/main.cpp 
	src/ClangUnit.cpp 
	src/ClangUnitChild.cpp 
	src/ClangUnitCtor.cpp
	src/interfaces/GeneratesIncludes.cpp
	src/interfaces/HandlesOutputFiles.cpp
	src/interfaces/Printable.cpp
	src/interfaces/TestsMethods.cpp
	src/interfaces/TestsFunctions.cpp
	src/interfaces/SharedGenericTestGen.cpp
	src/InputParser.cpp
	src/ParsedMethod.cpp
	src/ParsedFunction.cpp
	src/ParsedClass.cpp
	src/ClassField.cpp
	src/FunctionalParameter.cpp
	src/TestCase.cpp
	src/TestCasesForParsedInput.cpp
	src/TestsWriter.cpp
	src/RandomValueByType.cpp
)
target_link_libraries(clang-unit
	PRIVATE
	clangAST
	clangASTMatchers
	clangBasic
	clangFrontend
	clangSerialization
	clangTooling
)

target_compile_options(clang-unit PUBLIC -Wno-deprecated-enum-enum-conversion)