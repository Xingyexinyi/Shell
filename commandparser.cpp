// CommandParser.cpp

#include "commandparser.h"
#include <sstream>

CommandParser::CommandParser() {}

std::vector<std::string> CommandParser::parse_command(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}
