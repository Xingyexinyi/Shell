//author r,y,g 2024-6-26
// main.cpp

#include "shell.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Shell myshell;
    if (argc > 1) {
        // 处理 shell 脚本
        myshell.execute_script(argv[1]);
    } else {
        // 运行交互式 shell
        myshell.run();
    }

    return 0;
}

