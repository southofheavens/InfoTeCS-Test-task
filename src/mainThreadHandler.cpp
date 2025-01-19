#include "../include/mainThreadHandler.h"

/*-----------------------------------------------------------------*/

void TMainThreadHandler::operator()()
{
    std::string line;
    std::vector<std::string> words;
    while (std::getline(std::cin, line)) 
    {
        /* Разбиваем введённую строку по пробелам */
        words = NUtils::Split(line);
        if (words.empty()) {
            continue;
        }

        /* Формируем сообщение */
        std::string message;
        for (size_t i = 0; i < words.size() - 1; ++i) {
            message += (i != words.size() - 2 ? words[i] + ' ' : words[i]);
        }

        std::string levelStr = words[words.size() - 1];
        NUtils::ToLower(levelStr);
        TLogger::TLogLevels level = NUtils::GetLevel(levelStr);
        if (level == TLogger::TLogLevels::NONE) 
        {
            /* Уровень важности сообщения не указан / указан некорректно */
            /* прибавляем это слово к сообщению, уровень важности делаем по умолчанию */
            message += (message.length() != 0 ? ' ' + levelStr : levelStr);
            level = defaultLevel;
        } 
        else 
        {
            /* Уровень важности указан корректно, но само сообщение отсутствует */
            /* поэтому ничего не записываем */
            if (message.length() == 0) {
                continue;
            }
        }
        buffer.Push(TLogMessage(message, level)); 
    }
    buffer.SetStop();
}

/*-----------------------------------------------------------------*/
