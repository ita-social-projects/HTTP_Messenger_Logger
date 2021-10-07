#pragma once


#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

enum TYPE_OF_LOG{
    t_NO_TYPE = -1,

    t_DEBUG = 1,
    t_VERBOSE = 2,
    t_ERROR = 3,
    t_FATAL = 4,
};

#define INDENT "  "
#define INDENT_SIZE 2

#define SERIALIZED_LOG_TEMPLATE (std::string) \
    "PLACE_FOR_TYPE" + INDENT + \
    "PLACE_FOR_TIME" + INDENT + \
    "PLACE_FOR_FILE" + INDENT + \
    "PLACE_FOR_FUNCTION" + INDENT + \
    "PLACE_FOR_MESSAGE" + INDENT \

const int BUFFER_FOR_TYPE = 7;
const int BUFFER_FOR_TIME = 17;
const int BUFFER_FOR_FILE = 50;
const int BUFFER_FOR_FUNCTION = 70;
const int BUFFER_FOR_MESSAGE = 60;

class Log{
private:
    TYPE_OF_LOG m_type;
    std::string m_time;
    std::string m_file;
    std::string m_function;   
    std::string m_message;   

    std::string Replace_In_String(std::string& s, const std::string& toReplace, const std::string& replaceWith);
public:
    Log(TYPE_OF_LOG type_in, std::string time_in,std::string file_in,std::string function_in, std::string message_in);
    Log(std::string type_in, std::string time_in,std::string file_in,std::string function_in, std::string message_in);

    std::string Serialize();
    static std::string TypeToString(TYPE_OF_LOG type);
    static TYPE_OF_LOG StringToType(std::string type);
    
    TYPE_OF_LOG GetType();
    std::string GetTime();
    std::string GetFile();
    std::string GetMessage();
    std::string GetFunction();
};

#endif
