// Shell.cpp

#include "shell.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

Shell::Shell() {}

void Shell::run() {
    std::string input;

    while (true) {
        std::cout << "myshell> ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input.empty()) {
            continue;
        }

        auto commands = parser.parse_command(input);

        // 处理退出命令
        if (commands[0] == "exit") {
            break;
        }

        // 处理 I/O 重定向和管道
        bool background = false;
        int input_fd = -1;
        int output_fd = -1;
        std::vector<std::string> command;
        for (size_t i = 0; i < commands.size(); ++i) {
            if (commands[i] == "<") {
                if (i + 1 < commands.size()) {
                    input_fd = open(commands[i + 1].c_str(), O_RDONLY);
                    if (input_fd == -1) {
                        perror("open input file failed");
                        return;
                    }
                    ++i;
                }
            } else if (commands[i] == ">") {
                if (i + 1 < commands.size()) {
                    output_fd = open(commands[i + 1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (output_fd == -1) {
                        perror("open output file failed");
                        return;
                    }
                    ++i;
                }
            } else if (commands[i] == "|") {
                int pipefd[2];
                if (pipe(pipefd) == -1) {
                    perror("pipe failed");
                    return;
                }

                executor.execute_command(command, false, input_fd, pipefd[1]);
                close(pipefd[1]);
                if (input_fd != -1) close(input_fd);
                command.clear();
                input_fd = pipefd[0];
            } else if (commands[i] == "&") {
                background = true;
            } else {
                command.push_back(commands[i]);
            }
        }

        if (!command.empty()) {
            executor.execute_command(command, background, input_fd, output_fd);
            if (input_fd != -1) close(input_fd);
            if (output_fd != -1) close(output_fd);
        }
    }
}

void Shell::execute_script(const std::string& script_filename) {
    std::ifstream script_file(script_filename);
    if (!script_file) {
        std::cerr << "Unable to open script file: " << script_filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(script_file, line)) {
        auto commands = parser.parse_command(line);
        executor.execute_command(commands);
    }
}
