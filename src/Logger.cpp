#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include "Logger.h"

#define TIME_FORMAT "%H:%M_%d-%m-%Y"

std::shared_ptr<Logger> Logger::LOGGER = nullptr;
std::mutex Logger::m_mutex;

    std::shared_ptr<Logger> Logger::GetInstance(){
        std::lock_guard<std::mutex> lock(m_mutex);
        if(LOGGER == nullptr){
            LOGGER = std::shared_ptr<Logger>(new Logger());
        }
        return LOGGER;
    }

    void Logger::SetLogLevel(TYPE_OF_LOG new_level){
        m_level = new_level;
    }

    void Logger::WriteLogsToFile(){
        if(m_level == t_NO_TYPE || m_all_logs.size() == 0){
            return;
        }
        std::ofstream file;
        file.open(m_file_for_saving_logs);
        while(!m_all_logs.empty()){
            file << m_all_logs.top().Serialize() << "\n";
            m_all_logs.pop();
        }
        file.close();
    }


    Logger::Logger(){
        m_file_for_saving_logs = (std::string)("log_") + GetCurrentTime() + (".txt");
    }

    Logger::~Logger(){
        WriteLogsToFile();
    }

    Logger& Logger::operator()(TYPE_OF_LOG type, std::string file, std::string function, std::string message){
        std::lock_guard<std::mutex> lock(m_mutex);
        if(type >= m_level){
            Log log(type, GetCurrentTime(), file, function, message);
            // !
            std::cout << log.Serialize() << std::endl;
            // !
            m_all_logs.push(log);
        }
        return *this;
    }

    std::string Logger::GetCurrentTime(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),TIME_FORMAT,timeinfo);
        std::string current_time(buffer);

        return current_time;
    }
