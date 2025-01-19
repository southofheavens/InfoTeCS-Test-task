#include "../include/utils.h"

/*-----------------------------------------------------------------*/

namespace NUtils 
{

void ToLower(std::string& level) 
{
    for (size_t i = 0; i < level.length(); ++i) {
        level[i] = tolower(level[i]);
    }
}

std::vector<std::string> Split(const std::string& line) {
    std::vector<std::string> result;
    std::string intermediate;

    for (size_t i = 0; i < line.length(); ++i) 
    {
        if (!isspace(line[i])) 
        {
            intermediate += line[i];
            if (i == line.length() - 1) {
                result.push_back(intermediate);
            }
        } else 
        {
            if (intermediate.length() > 0) 
            {
                result.push_back(intermediate);
                intermediate = "";
            }
        }
    }

    return result;
}

TLogger::TLogLevels GetLevel(const std::string& potentialLevel) 
{
    if (potentialLevel == "debug") {
        return TLogger::TLogLevels::DEBUG;
    } 
    else if (potentialLevel == "info") {
        return TLogger::TLogLevels::INFO;
    } 
    else if (potentialLevel == "warning") {
        return TLogger::TLogLevels::WARNING;
    } 
    else if (potentialLevel == "error") {
        return TLogger::TLogLevels::ERROR;
    } 
    else if (potentialLevel == "fatal") {
        return TLogger::TLogLevels::FATAL;
    } 
    else {
        return TLogger::TLogLevels::NONE;
    }
}

} /* namespace Utils */

/*-----------------------------------------------------------------*/
