#ifndef LOGGING_THREAD_HANDLER_H
#define LOGGING_THREAD_HANDLER_H

#include "logger.h"
#include "buffer.h"

/*-----------------------------------------------------------------*/
/* Класс для обработки потока логирования */
/*-----------------------------------------------------------------*/

class TLoggingThreadHandler 
{
public:
    TLoggingThreadHandler(TLogger& log, TBuffer& buf) : 
        logger{log}, buffer{buf} {}

    void operator()();

private:
    TLogger& logger;
    TBuffer& buffer;
};

#endif