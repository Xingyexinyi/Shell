// CommandExecutor.h

#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <vector>
#include <string>

class CommandExecutor {
public:
    CommandExecutor();
    void execute_command(const std::vector<std::string>& args, bool background = false, int input_fd = -1, int output_fd = -1);
};

#endif // COMMAND_EXECUTOR_H
