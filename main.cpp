//author ranleixin 2024-6-20
// main.cpp

#include "shell.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        // 处理 shell 脚本
        execute_script(argv[1]);
    } else {
        // 运行交互式 shell
        run_shell();
    }

    return 0;
}

