# Тестовое задание для стажера на направление "Разработчик C++"  

### Цель  
Разработать библиотеку для записи сообщений в журнал с разными уровнями важности и приложение, демонстрирующее работу библиотеки. 

### Часть 1.  

Разработать библиотеку для записи текстовых сообщений в журнал. В качестве журнала использовать текстовый файл.  

**Требования к разрабатываемой библиотеке**  

1. Библиотека должна быть динамической.  
2. Библиотека при инициализации должна принимать следующие параметры:  

    a. Имя файла журнала.  
    
    b. Уровень важности сообщения по умолчанию. Сообщения с уровнем ниже заданного не должны записываться в журнал. Уровень рекомендуется задавать с помощью перечисления с понятными именами. Достаточно трех уровней важности.  
    
3. В журнале должны быть сохранена следующая информация:  

    a. Текст сообщения.  
    
    b. Уровень важности.  

    c. Время получения сообщения.  
    
4. После инициализации должна быть возможность менять уровень важности сообщений по умолчанию.  

### Часть 2.  
 
Разработать консольное многопоточное приложение для проверки библиотеки записи сообщений в журнал.  

**Требования к приложению**  

1. Приложение должно:  

    a. Подключать и использовать библиотеку, реализованную в Части 1, для записи сообщений в журнал.  
    
    b. В консоли принимать от пользователя сообщение и его уровень важности. Уровень важности может отсутствовать.  
    
    c. Передавать принятые данные от пользователя в отдельный поток для записи в журнал. Передача данных должна быть потокобезопасной.  
    
    d. Ожидать нового ввода от пользователя после передачи данных.  
    
2. Параметрами приложения должны быть имя файла журнала и уровень важности сообщения по умолчанию.  
3. Внутреннюю логику приложения придумать самостоятельно.  

**Требования к выполнению задания**  

- Программный код должен быть написан на языке C++ стандарта C++17. Следует придерживаться подходов ООП к разработке.  
- Сборку проекта и запуск тестов оформить в Makefile. Использовать компилятор gcc для работы в среде Linux. Цели сборки библиотеки и тестового приложения должны быть разделены. Кроме того, должна быть задана цель clean для очистки каталога от временных файлов.  
- В папке с исходным кодом не должно быть мусора: неиспользуемых файлов исходных кодов или ресурсов, промежуточных файлов сборки и т.д.  
- Не использовать никаких сторонних библиотек помимо stl.  
- В качестве целевой операционной системы, на которой будет проверяться тестовое задание, стоит рассматривать актуальные версии ubuntu/debian.  
- Приложение должно корректно обрабатывать ошибки, связанные с записью в файлы.  
- Все файлы (исходный код библиотеки и приложения, Makefile) должны быть размещены в одном git-репозитории.  

**Описание проекта**  

Проект реализован с использованием стандарта C++17 и стандартной библиотеки (не считая файла tests.cpp, в котором используется библиотека googletest).  
Папка `include` содержит в себе заголовочные файлы.  
Папка `src` содержит в себе реализации классов и функций, описанных в заголовчных файлах.  
Папка `tests` содержит в себе файл `tests.cpp`, который запускает тесты.  
Файл main.cpp является точкой входа в программу.  

**Сборка**  

Для сборки библиотеки необходимо использовать команду:  
```bash
make logger
```   

Для сборки и запуска основной программы:  
```bash
make run 
```

Для сборки и запуска тестов:  
```bash
make run_tests
```

Для сборки всего:  
```bash
make all
```

Для очистки каталога от временных файлов:  
```bash
make clean
```   
   
**Пример**
```bash
semyonzhuravlev@MacBook-Air cpp-logger % make logger
g++ -std=c++17  -fPIC -c src/logger.cpp -o build/logger.o
g++ -std=c++17  -shared -o lib/liblogger.so build/logger.o
semyonzhuravlev@MacBook-Air cpp-logger % make all
g++ -std=c++17  -c src/buffer.cpp -o build/buffer.o
g++ -std=c++17  -c src/loggingThreadHandler.cpp -o build/loggingThreadHandler.o
g++ -std=c++17  -c src/mainThreadHandler.cpp -o build/mainThreadHandler.o
g++ -std=c++17  -c src/utils.cpp -o build/utils.o
g++ -std=c++17  main.cpp build/buffer.o build/loggingThreadHandler.o build/mainThreadHandler.o build/utils.o -L./lib -llogger -o main
g++ -std=c++17  tests/tests.cpp build/buffer.o build/loggingThreadHandler.o build/mainThreadHandler.o build/utils.o -L./lib -llogger -lgtest -o tests/tests
ld: warning: object file (/usr/local/lib/libgtest.a[2](gtest-all.cc.o)) was built for newer 'macOS' version (15.0) than being linked (14.4)
semyonzhuravlev@MacBook-Air cpp-logger % make run
./main log.txt warning
Логгер успешно инициализирован.
some debug debug
some info info
some warning warning
some error error
some fatal fatal
```   

Файл log.txt:   
[some warning] [WARNING] [2025-01-19 09:17:32]
[some error] [ERROR] [2025-01-19 09:17:40]
[some fatal] [FATAL] [2025-01-19 09:17:42]   

```bash
semyonzhuravlev@MacBook-Air cpp-logger % make run_tests
./tests/tests
[==========] Running 7 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from UtilsTest
[ RUN      ] UtilsTest.ToLower
[       OK ] UtilsTest.ToLower (0 ms)
[ RUN      ] UtilsTest.Split
[       OK ] UtilsTest.Split (0 ms)
[ RUN      ] UtilsTest.GetLevel
[       OK ] UtilsTest.GetLevel (0 ms)
[----------] 3 tests from UtilsTest (0 ms total)

[----------] 2 tests from BufferTest
[ RUN      ] BufferTest.PushPop
[       OK ] BufferTest.PushPop (0 ms)
[ RUN      ] BufferTest.IsStop
[       OK ] BufferTest.IsStop (0 ms)
[----------] 2 tests from BufferTest (0 ms total)

[----------] 2 tests from LoggerTest
[ RUN      ] LoggerTest.FileOutput
[       OK ] LoggerTest.FileOutput (2 ms)
[ RUN      ] LoggerTest.ChangeDefaultLevel
[       OK ] LoggerTest.ChangeDefaultLevel (0 ms)
[----------] 2 tests from LoggerTest (2 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 3 test suites ran. (2 ms total)
[  PASSED  ] 7 tests.
semyonzhuravlev@MacBook-Air cpp-logger % make clean
rm -rf build   
```   
