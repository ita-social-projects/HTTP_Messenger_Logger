#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include "../include/Logger.h"


std::mutex Logger::m_mutex;

    Logger& Logger::GetInstance(){
        static Logger LOGGER;
        return LOGGER;
    }

    void Logger::SetLogLevel(TYPE_OF_LOG new_level){
        m_level = new_level;
    }

    void Logger::SaveLogsToFile(){
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_level == t_NO_TYPE || m_all_logs.size() == 0){
            return;
        }
        std::ofstream file;
        file.open(m_file_for_saving_logs, std::ios::app);
        while(!m_all_logs.empty()){
            file << m_all_logs.front().Serialize() << "\n";
            m_all_logs.pop();
        }
        file.close();
    }

    Logger::Logger(){
        m_file_for_saving_logs = (std::string)("logs_") + GetCurrentTime() + (".txt");
    }

    Logger::~Logger(){
        SaveLogsToFile();
    }

    Logger& Logger::operator()(TYPE_OF_LOG type, std::string file, std::string function, std::string message){
        std::unique_lock<std::mutex> lock(m_mutex);
        // remove new line chars
        message.erase(std::remove_if(message.begin(), message.end(), 
                        [&](char ch) 
                        { return std::iscntrl(static_cast<unsigned char>(ch));}), 
                        message.end());
        if(type >= m_level){
            Log log(type, GetCurrentTime(), file, function, message);
            if(show_logs_in_console){
                log.PrintInConsole();
            }
            m_all_logs.push(log);
        }
        lock.unlock();
        if(m_all_logs.size() <= m_max_amount_of_logs){
            SaveLogsToFile();
        }
        return *this;
    }

    void Logger::SetFileForLogs(std::string file_name){
        m_file_for_saving_logs = file_name;
    }
    void Logger::SetShowInConsole(bool show){
        show_logs_in_console = show;
    }
    void Logger::SetMaxAmountOfLogs(size_t amount){
        m_max_amount_of_logs = amount;
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
