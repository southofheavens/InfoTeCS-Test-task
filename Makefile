CXX = g++
CXXFLAGS = -std=c++17 
LDFLAGS = -L./lib -llogger
GTEST_LIB = -lgtest

# Пути к исходникам и папкам
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib
TESTS_DIR = tests

# Имена файлов
LOGGER_SRC = $(SRC_DIR)/logger.cpp
LOGGER_OBJ = $(BUILD_DIR)/logger.o
LOGGER_LIB = $(LIB_DIR)/liblogger.so
TESTS_SRC = $(TESTS_DIR)/tests.cpp
TESTS_BIN = $(TESTS_DIR)/tests
MAIN_SRC = main.cpp
MAIN_BIN = main

# Список объектных файлов
SRC_FILES = $(SRC_DIR)/buffer.cpp $(SRC_DIR)/loggingThreadHandler.cpp $(SRC_DIR)/mainThreadHandler.cpp $(SRC_DIR)/utils.cpp
OBJS = $(BUILD_DIR)/buffer.o $(BUILD_DIR)/loggingThreadHandler.o $(BUILD_DIR)/mainThreadHandler.o $(BUILD_DIR)/utils.o

# Цели
all: $(LOGGER_LIB) $(MAIN_BIN) $(TESTS_BIN)

# Сборка объектного файла logger.o для библиотеки
$(LOGGER_OBJ): $(LOGGER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

# Сборка динамической библиотеки liblogger.so
$(LOGGER_LIB): $(LOGGER_OBJ)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

# Сборка объектных файлов из исходников
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка исполняемого файла main (приложения)
$(MAIN_BIN): $(LOGGER_LIB) $(MAIN_SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) $(OBJS) $(LDFLAGS) -o $@

# Сборка исполняемого файла tests (тестового приложения)
$(TESTS_BIN): $(LOGGER_LIB) $(TESTS_SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) $(TESTS_SRC) $(OBJS) $(LDFLAGS) $(GTEST_LIB) -o $@

# Цель для запуска приложения с параметрами
run: $(MAIN_BIN)
	./$(MAIN_BIN) log.txt warning

# Цель для сборки библиотеки
logger: $(LOGGER_LIB)

# Цель для запуска тестов
run_tests: $(TESTS_BIN)
	./$(TESTS_BIN)

# Цель для очистки каталога от временных файлов
clean:
	rm -rf $(BUILD_DIR)

# Специальные цели
.PHONY: all run logger run_tests clean