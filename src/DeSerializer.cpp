#pragma once

#ifndef DESERIALIZER_CPP_INCLUDED
#define DESERIALIZER_CPP_INCLUDED
#include "DeSerializer.h"

        DeSerializer::DeSerializer(std::string path):m_file_with_logs(path){
            GetLogsFromJson();
        };

        void DeSerializer::ScanLines(){
            std::string temp_line;
            std::string line;
            bool logStarted = false;
            std::fstream file;
            file.open(m_file_with_logs);
            while(std::getline(file, temp_line)){
                if(temp_line.find(begin_of_log) != std::string::npos){
                    logStarted = true;
                }
                if(temp_line.find(end_of_log) != std::string::npos){
                    logStarted = false;
                    m_all_lines.push_back(line);
                    line = "";  
                    continue;
                }
                if(logStarted){
                    line += temp_line;                   
                }
            }
        }

        void DeSerializer::PushLogs(){
            for(auto line: m_all_lines){
                CreateLogFromLine(line);
            }
        }

        void DeSerializer::CreateLogFromLine(std::string& line){
            std::string type;
            std::string time;
            std::string file;
            std::string function;
            std::string message;
            try{
                type = GetProperty(line, "\"type\":\"");
                time = GetProperty(line, "\"time\":\"");
                file = GetProperty(line, "\"file\":\"");        
                function = GetProperty(line, "\"function\":\"");   
                message = GetProperty(line, "\"message\":\"");     
            }catch(std::exception& ex){
                return;
            }
            m_all_logs.push_back(Log(type, time, file, function, message));
        }
        std::string DeSerializer::GetProperty(std::string line, std::string searched_property){
            int properity_begin = line.find(searched_property);
            if(properity_begin == std::string::npos){
                throw std::invalid_argument("cant find properity in string");
            }
            line = line.substr(properity_begin + searched_property.length());
            line = line.substr(0, line.find('\"'));

            return line;
        }

        std::vector<Log> DeSerializer::GetAllLogs(){
            return m_all_logs;
        }
        void DeSerializer::GetLogsFromJson(){
            ScanLines();
            PushLogs();
            DeleteAllLines();
        } 

        void DeSerializer::SetPath(std::string path_in){
            m_file_with_logs = path_in;
            GetLogsFromJson();
        }

        void DeSerializer::DeleteAllLogs(){
            size_t amount_of_logs = m_all_logs.size();
            for(int i=0; i<amount_of_logs; i++){
                m_all_logs.pop_back();
            }

        }

        void DeSerializer::DeleteAllLines(){
            size_t amount_of_lines = m_all_lines.size();
            for(int i=0; i<amount_of_lines; i++){
                m_all_lines.pop_back();
            }
        }
        void DeSerializer::DeleteAllInfo(){
            DeleteAllLogs();
            DeleteAllLines();
        }
#endif
