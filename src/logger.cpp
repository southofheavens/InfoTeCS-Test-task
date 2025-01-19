#include "../include/logger.h"

/*-----------------------------------------------------------------*/

TLogger::TLogger(const std::string& ffilename, TLogLevels ddefLevel)
{
    file.open(ffilename, std::ios::app);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл журнала: " + ffilename);
    }
    defLevel = ddefLevel;   
}

TLogger::~TLogger()
{
    file.close();
}

void TLogger::Debug(const std::string& message)
{
    if (defLevel <= TLogLevels::DEBUG) 
    {
        file << '[' << message << ']' << ' ' << "[DEBUG] " \
        << '[' << GetCurrentTime() << ']' << std::endl;
    }
}

void TLogger::Info(const std::string& message)
{
    if (defLevel <= TLogLevels::INFO) 
    {
        file << '[' << message << ']' << ' ' << "[INFO] " \
        << '[' << GetCurrentTime() << ']' << std::endl;
    }
}

void TLogger::Warning(const std::string& message)
{
    if (defLevel <= TLogLevels::WARNING) 
    {
        file << '[' << message << ']' << ' ' << "[WARNING] " \
        << '[' << GetCurrentTime() << ']' << std::endl;
    }
}

void TLogger::Error(const std::string& message)
{
    if (defLevel <= TLogLevels::ERROR) 
    {
        file << '[' << message << ']' << ' ' << "[ERROR] " \
        << '[' << GetCurrentTime() << ']' << std::endl;
    }
}

void TLogger::Fatal(const std::string& message)
{
    if (defLevel <= TLogLevels::FATAL) 
    {
        file << '[' << message << ']' << ' ' << "[FATAL] " \
        << '[' << GetCurrentTime() << ']' << std::endl;
    }
}

void TLogger::ChangeDefLevel(TLogLevels newDefLevel)
{
    defLevel = newDefLevel;
}

std::string TLogger::GetCurrentTime() 
{
    auto now = std::chrono::system_clock::now(); 
    auto nowC = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm;
    localtime_r(&nowC, &nowTm);

    std::stringstream ss;
    ss << std::put_time(&nowTm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

/*-----------------------------------------------------------------*/
