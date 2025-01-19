#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/utils.h"
#include "../include/buffer.h"
#include "../include/logger.h"

/*-----------------------------------------------------------------*/
/* Test utils */
/*-----------------------------------------------------------------*/

TEST(UtilsTest, ToLower) 
{
    std::string str = "TEST";
    NUtils::ToLower(str);
    ASSERT_EQ(str, "test");

    str = "mIxEd";
    NUtils::ToLower(str);
    ASSERT_EQ(str, "mixed");

    str = "";
    NUtils::ToLower(str);
    ASSERT_EQ(str, "");
}

TEST(UtilsTest, Split) 
{
    std::string str = "test string";
    std::vector<std::string> words = NUtils::Split(str);
    ASSERT_EQ(words.size(), 2);
    ASSERT_EQ(words[0], "test");
    ASSERT_EQ(words[1], "string");

    str = "test  string   with     spaces";
    words = NUtils::Split(str);
    ASSERT_EQ(words.size(), 4);
    ASSERT_EQ(words[0], "test");
    ASSERT_EQ(words[1], "string");
     ASSERT_EQ(words[2], "with");
    ASSERT_EQ(words[3], "spaces");

    str = "";
    words = NUtils::Split(str);
    ASSERT_TRUE(words.empty());
}

TEST(UtilsTest, GetLevel) 
{
    ASSERT_EQ(NUtils::GetLevel("debug"), TLogger::TLogLevels::DEBUG);
    ASSERT_EQ(NUtils::GetLevel("info"), TLogger::TLogLevels::INFO);
    ASSERT_EQ(NUtils::GetLevel("warning"), TLogger::TLogLevels::WARNING);
    ASSERT_EQ(NUtils::GetLevel("error"), TLogger::TLogLevels::ERROR);
    ASSERT_EQ(NUtils::GetLevel("fatal"), TLogger::TLogLevels::FATAL);
    ASSERT_EQ(NUtils::GetLevel("invalid"), TLogger::TLogLevels::NONE);
}

/*-----------------------------------------------------------------*/
/* Test Buffer */
/*-----------------------------------------------------------------*/

TEST(BufferTest, PushPop) 
{
    TBuffer buffer;
    TLogMessage msg1("test message 1", TLogger::TLogLevels::INFO);
    TLogMessage msg2("test message 2", TLogger::TLogLevels::ERROR);
    
    buffer.Push(msg1);
    buffer.Push(msg2);
    
    TLogMessage result1 = buffer.Pop();
    TLogMessage result2 = buffer.Pop();

    ASSERT_EQ(result1.message, msg1.message);
    ASSERT_EQ(result1.level, msg1.level);
    ASSERT_EQ(result2.message, msg2.message);
    ASSERT_EQ(result2.level, msg2.level);
}

TEST(BufferTest, IsStop) 
{
    TBuffer buffer;
    ASSERT_FALSE(buffer.IsStop());
    buffer.SetStop();
    ASSERT_TRUE(buffer.IsStop());
}

/*-----------------------------------------------------------------*/
/* Test Logger */
/*-----------------------------------------------------------------*/

TEST(LoggerTest, FileOutput) 
{
    std::string filename = "test_log.txt";
    TLogger logger(filename, TLogger::TLogLevels::DEBUG);

    logger.Debug("debug message");
    logger.Info("info message");
    logger.Warning("warning message");
    logger.Error("error message");
    logger.Fatal("fatal message");
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    ASSERT_EQ(lines.size(), 5);
    
    ASSERT_NE(lines[0].find("debug message"), std::string::npos);
    ASSERT_NE(lines[0].find("[DEBUG]"), std::string::npos);
    ASSERT_NE(lines[1].find("info message"), std::string::npos);
    ASSERT_NE(lines[1].find("[INFO]"), std::string::npos);
    ASSERT_NE(lines[2].find("warning message"), std::string::npos);
    ASSERT_NE(lines[2].find("[WARNING]"), std::string::npos);
    ASSERT_NE(lines[3].find("error message"), std::string::npos);
    ASSERT_NE(lines[3].find("[ERROR]"), std::string::npos);
     ASSERT_NE(lines[4].find("fatal message"), std::string::npos);
    ASSERT_NE(lines[4].find("[FATAL]"), std::string::npos);

    std::remove(filename.c_str());
}

TEST(LoggerTest, ChangeDefaultLevel) 
{
    std::string filename = "test_log_2.txt";
    TLogger logger(filename, TLogger::TLogLevels::INFO);
    
    logger.Debug("debug message");
    logger.Info("info message");
    logger.ChangeDefLevel(TLogger::TLogLevels::WARNING);
    logger.Debug("debug message 2");
    logger.Warning("warning message");
     
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    ASSERT_EQ(lines.size(), 2);
    
    ASSERT_NE(lines[0].find("info message"), std::string::npos);
    ASSERT_NE(lines[0].find("[INFO]"), std::string::npos);
    ASSERT_NE(lines[1].find("warning message"), std::string::npos);
    ASSERT_NE(lines[1].find("[WARNING]"), std::string::npos);

    std::remove(filename.c_str());
}

/*-----------------------------------------------------------------*/

int main(int argc, char *argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
