#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include "Logger.h"


#ifdef _WIN32
#include <conio.h>
//#include <dir.h>
#include <process.h>
#endif

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

    void Logger::GoToTheEndOfFile(std::fstream& file){
        std::string line;
        std::streampos oldpos = file.tellg();

        while(std::getline(file, line)) {
            if(line.find("]") != std::string::npos){
                file.seekg(oldpos); 
                return;
            }
                
            oldpos = file.tellg();
        }
    }

    void Logger::WriteLogsToFile(){
        if(m_level == t_WRONG_TYPE || m_all_logs.size() == 0){
            return;
        }
        std::ofstream file;
        file.open(m_file_for_saving_logs);
        file << "{\n\t\"LOGS\":[\n";
        while(!m_all_logs.empty()){
            file << m_all_logs.top().Serialize();
            m_all_logs.pop();
            if(!m_all_logs.empty()){
                file << ",";
            }
            file << "\n";
        }
        file << "\t]\n}";
        file.close();
    }


    Logger::Logger(){
        m_file_for_saving_logs = (std::string)("log1.json");
    }

    Logger::~Logger(){
        WriteLogsToFile();
    }

    Logger& Logger::operator()(TYPE_OF_LOG type, std::string file, std::string function, std::string message){
        std::lock_guard<std::mutex> lock(m_mutex);
        if(type >= m_level){
            m_all_logs.push(Log(type, GetCurrentTime(), file, function, message));
        }
        return *this;
    }

    std::string Logger::GetCurrentTime(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
        std::string current_time(buffer);

        return current_time;
    }
