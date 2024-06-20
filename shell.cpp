// shell.cpp

#include "shell.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

void execute_command(const std::vector<std::string>& args, bool background, int input_fd, int output_fd) {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程
        if (input_fd != -1) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != -1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        std::vector<char*> cargs;
        for (const auto& arg : args) {
            cargs.push_back(const_cast<char*>(arg.c_str()));
        }
        cargs.push_back(nullptr);

        execvp(cargs[0], cargs.data());
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // 父进程
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        }
    } else {
        perror("fork failed");
    }
}

std::vector<std::string> parse_command(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void run_shell() {
    std::string input;

    while (true) {
        std::cout << "myshell> ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input.empty()) {
            continue;
        }

        auto commands = parse_command(input);

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

                execute_command(command, false, input_fd, pipefd[1]);
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
            execute_command(command, background, input_fd, output_fd);
            if (input_fd != -1) close(input_fd);
            if (output_fd != -1) close(output_fd);
        }
    }
}

void execute_script(const std::string& script_filename) {
    std::ifstream script_file(script_filename);
    if (!script_file) {
        std::cerr << "Unable to open script file: " << script_filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(script_file, line)) {
        auto commands = parse_command(line);
        execute_command(commands);
    }
}
