#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <ctime>

/*-----------------------------------------------------------------*/
/* Класс для записи сообщений в журнал с разными уровнями важности */
/*-----------------------------------------------------------------*/

class TLogger
{
public:
    enum class TLogLevels {NONE, DEBUG, INFO, WARNING, ERROR, FATAL};

    TLogger(const std::string&, TLogLevels);
    ~TLogger();

    TLogger& operator=(const TLogger&) = delete;
    TLogger(const TLogger&) = delete;

    void Debug(const std::string&);
    void Info(const std::string&);
    void Warning(const std::string&);
    void Error(const std::string&);
    void Fatal(const std::string&);
    void ChangeDefLevel(TLogLevels);

    static std::string GetCurrentTime();

private:
    TLogLevels defLevel;
    std::ofstream file;    
};

/*-----------------------------------------------------------------*/

#endif