#ifndef BUFFER_H
#define BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include "logger.h"

/*-----------------------------------------------------------------*/

struct TLogMessage 
{
    std::string message;
    TLogger::TLogLevels level;

    TLogMessage() {}
    TLogMessage(const std::string& m, const TLogger::TLogLevels& ll) : message{m}, level{ll} {}
};

/*-----------------------------------------------------------------*/
/*     Класс для буффера, с помощью которого происходит обмен      */
/*                   данных между потоками                         */
/*-----------------------------------------------------------------*/

class TBuffer 
{
public:
    void Push(const TLogMessage& msg);
    TLogMessage Pop();
    bool IsStop() const;
    void SetStop();
private:
    std::queue<TLogMessage> logQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool stopThreads = false;
};

/*-----------------------------------------------------------------*/

#endif