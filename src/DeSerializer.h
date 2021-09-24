#pragma once

#ifndef DESERIALIZER_H_INCLUDED
#define DESERIALIZER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "../src/Log.h"

#define begin_of_log   "{"
#define end_of_log     "}"

class DeSerializer{
    private:
        std::string m_file_with_logs;
        std::vector<Log> m_all_logs;
        std::vector<std::string> m_all_lines;
        
        void ScanLines();
        void PushLogs();
        void CreateLogFromLine(std::string& line);
        std::string GetProperty(std::string line, std::string searched_property);        
        void DeleteAllLogs();
        void DeleteAllLines();
        void GetLogsFromJson();
    public:
        DeSerializer(std::string path);
        //:m_file_with_logs(path){};
        
        void SetPath(std::string path_in);
        std::vector<Log> GetAllLogs();
        

        void DeleteAllInfo();
};

#endif
