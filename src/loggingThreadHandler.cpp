#include "../include/loggingThreadHandler.h"

/*-----------------------------------------------------------------*/

void TLoggingThreadHandler::operator()()
{
    while (!buffer.IsStop()) 
    {
        TLogMessage msg = buffer.Pop();
        if (msg.message.empty()) {
            continue;
        }
        switch (msg.level) 
        {
            case TLogger::TLogLevels::DEBUG:
                logger.Debug(msg.message);
                break;
            case TLogger::TLogLevels::INFO:
                logger.Info(msg.message);
                break;
            case TLogger::TLogLevels::WARNING:
                logger.Warning(msg.message);
                break;
            case TLogger::TLogLevels::ERROR:
                logger.Error(msg.message);
                break;
            case TLogger::TLogLevels::FATAL:
                logger.Fatal(msg.message);
                break;
            default:
                break;
        }
    }
}

/*-----------------------------------------------------------------*/
