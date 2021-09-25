#pragma once

#ifndef DESERIALIZER_H_INCLUDED
#define DESERIALIZER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "../src/Log.h"


class DeSerializer{
    private:
        std::string m_file_with_logs;
        std::vector<Log> m_all_logs;
        std::vector<std::string> m_all_lines;
        
        void ScanLines();
        void PushLogs();
        void CreateLogFromLine(std::string& line);
        std::string GetNextProperty(std::string& line, int size_of_buffer_for_property);        
        std::string DeleteAllSpacesFromEndOfLine(std::string line);

        void DeleteAllLines();
        void GetLogsFromJson();
    public:
        DeSerializer(std::string path);
        
        void SetPath(std::string path_in);
        std::vector<Log> GetAllLogs();

        void DeleteAllLogs();
};

#endif
