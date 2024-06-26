// CommandExecutor.cpp

#include "commandexecutor.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

CommandExecutor::CommandExecutor() {}

void CommandExecutor::execute_command(const std::vector<std::string>& args, bool background, int input_fd, int output_fd) {
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
