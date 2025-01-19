#ifndef MAIN_THREAD_HANDLER_H
#define MAIN_THREAD_HANDLER_H

#include <iostream>
#include "buffer.h"
#include "utils.h"

/*-----------------------------------------------------------------*/
/* Класс для обработки основного потока */
/*-----------------------------------------------------------------*/

class TMainThreadHandler 
{
public:
    TMainThreadHandler(TBuffer& buf, TLogger::TLogLevels defLevel) : 
        buffer{buf}, defaultLevel{defLevel} {}

    void operator()();

private:
    TBuffer& buffer;
    TLogger::TLogLevels defaultLevel;
};

#endif