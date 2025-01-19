#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cctype>
#include "logger.h"

/*-----------------------------------------------------------------*/

namespace NUtils 
{

/* ToLower: преобразование строки в нижний регистр */
void ToLower(std::string& level);

/* Split: разбивает строку по пробелам */
std::vector<std::string> Split(const std::string& line);

/* GetLevel: конвертирует уровень важности из std::string в TLogger::TLogLevels */
TLogger::TLogLevels GetLevel(const std::string& potentialLevel);

} /* namespace Utils */

/*-----------------------------------------------------------------*/

#endif