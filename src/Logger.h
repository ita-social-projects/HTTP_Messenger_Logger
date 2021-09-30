#pragma once
#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <mutex>
#include <chrono>
#include <thread>
#include <memory>

#include "Log.h"

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#define DEBUG(X)    (*Logger::GetInstance())(t_DEBUG,      __FILE__, __PRETTY_FUNCTION__, X)
#define ERROR(X)    (*Logger::GetInstance())(t_ERROR,      __FILE__, __PRETTY_FUNCTION__, X)
#define FATAL(X)    (*Logger::GetInstance())(t_FATAL,      __FILE__, __PRETTY_FUNCTION__, X)
#define VERBOSE(X)  (*Logger::GetInstance())(t_VERBOSE,    __FILE__, __PRETTY_FUNCTION__, X)

#define SET_LOG_LEVEL(X) (Logger::GetInstance())->SetLogLevel(X)

class Logger{
private:
    std::string m_file_for_saving_logs;
    std::stack<Log> m_all_logs;
    // contains the lowest type_of_logs that can be contained in logger
    TYPE_OF_LOG m_level = t_DEBUG;

    void WriteLogsToFile();
    std::string GetCurrentTime();

    static std::shared_ptr<Logger> LOGGER;  
    static std::mutex m_mutex;
    
    Logger();
    Logger(const Logger&);	 
    Logger& operator=(const Logger&);

public:      
    ~Logger();   
    void SetLogLevel(TYPE_OF_LOG new_level);
    Logger& operator()( TYPE_OF_LOG type, 
                        std::string file, 
                        std::string function,
                        std::string message);
    static std::shared_ptr<Logger> GetInstance();
};

#endif 
