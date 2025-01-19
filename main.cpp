#include "include/logger.h"
#include "include/utils.h"
#include "include/buffer.h"
#include "include/mainThreadHandler.h"
#include "include/loggingThreadHandler.h"
#include <iostream>
#include <thread>

/*-----------------------------------------------------------------*/

int main(int argc, char *argv[]) 
try 
{
    if (argc != 3) 
    {
        std::cerr << "Параметрами приложения должны быть имя файла журнала и уровень ";
        std::cerr << "важности сообщения по умолчанию." << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    std::string strLevel(argv[2]);

    NUtils::ToLower(strLevel);
    TLogger::TLogLevels defLevel;
    if ((defLevel = NUtils::GetLevel(strLevel)) == TLogger::TLogLevels::NONE) 
    {
        std::cout << "Введён некорректный уровень важности сообщения по умолчанию." << std::endl;
        std::cout << "В качестве уровня важности сообщения по умолчанию будет ";
        std::cout << "установлен DEBUG." << std::endl;
        defLevel = TLogger::TLogLevels::DEBUG;
    }

    /* Определяем логгер */
    TLogger logger(filename, defLevel);
    std::cout << "Логгер успешно инициализирован." << std::endl;

    /* Определяем буфер для обмена данных между потоками */
    TBuffer buffer;

    /* Определяем обработчики потоков */
    TMainThreadHandler mainHandler(buffer, defLevel);
    TLoggingThreadHandler loggingHandler(logger, buffer);

    /* Запускаем поток логирования */
    std::thread loggingThread(loggingHandler);

    /* Запускаем обработку ввода в основном потоке */
    mainHandler();

    loggingThread.join();

    return 0;
} 
catch (const std::runtime_error& e) 
{
    std::cerr << e.what() << std::endl;
    return 1;
}

/*-----------------------------------------------------------------*/
