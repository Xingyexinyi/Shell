//author ranleixin 2024-6-20
#ifndef SHELL_H
#define SHELL_H
#include<vector>
#include<string>

void execute_command(const std::vector<std::string>& args,bool background = false, int input_fd = -1,int output_fd = -1);

std::vector<std::string> parse_command(const std::string& input);

void run_shell();

void execute_script(const std::string& script_filename);

#endif // SHELL_H
