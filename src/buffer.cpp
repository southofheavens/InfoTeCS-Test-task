#include "../include/buffer.h"

/*-----------------------------------------------------------------*/

void TBuffer::Push(const TLogMessage& msg) 
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        logQueue.push(msg);
    }
    cv.notify_one();
}

TLogMessage TBuffer::Pop() 
{
    TLogMessage msg;
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [&]{ return !logQueue.empty() || stopThreads; });

        if (stopThreads && logQueue.empty()) {
            return TLogMessage();
        }
        msg = logQueue.front();
        logQueue.pop();
    }
    return msg;
}

bool TBuffer::IsStop() const
{
    return stopThreads;
}

void TBuffer::SetStop()
{
    stopThreads = true;
    cv.notify_one();
}

/*-----------------------------------------------------------------*/
