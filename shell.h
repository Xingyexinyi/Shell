// Shell.h

#ifndef SHELL_H
#define SHELL_H

#include <string>
#include "commandparser.h"
#include "commandexecutor.h"

class Shell {
private:
    CommandParser parser;
    CommandExecutor executor;

public:
    Shell();
    void run();
    void execute_script(const std::string& script_filename);
};

#endif // SHELL_H
