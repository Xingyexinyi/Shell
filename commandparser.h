#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <vector>
#include <string>


class CommandParser
{
public:
    CommandParser();
    std::vector<std::string> parse_command(const std::string& input);
};

#endif // COMMANDPARSER_H
