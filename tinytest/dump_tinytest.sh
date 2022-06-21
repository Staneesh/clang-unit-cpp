#clang-check -std=c++20 -Xclang -ast-dump -ast-dump-filter=func_with_auto_inline -fsyntax-only tinytest.cpp
clang-check --extra-arg="-std=c++20" --ast-dump -ast-dump-filter=A tinytest.cpp