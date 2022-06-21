#cd test/Hyprland && ../../../../build/bin/clang-unit  src/CalcManager/CalculatorManager.cpp -- -std=c++20
#cd src && ../../../build/bin/clang-unit *.cpp -p ../../../build/compile_commands.json -- -std=c++20
../../build/bin/clang-unit test/test.cpp -- -std=c++20