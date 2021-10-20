#include <string>
#ifndef DESERIALIZER_CPP_INCLUDED
#define DESERIALIZER_CPP_INCLUDED
#include "DeSerializer.h"

        DeSerializer::DeSerializer(std::string path):m_file_with_logs(path){
            GetLogsFromFile();
        };

        void DeSerializer::ScanLines(){
            std::string line;
            std::fstream file;
            file.open(m_file_with_logs);
            while(std::getline(file, line)){
                m_all_lines.push_back(line);
            }
        }

        void DeSerializer::PushLogs(){
            for(auto line: m_all_lines){
                CreateLogFromLine(line);
            }
        }

        void DeSerializer::CreateLogFromLine(std::string& line){
            std::string type = GetNextProperty(line, BUFFER_FOR_TYPE);
            std::string time = GetNextProperty(line, BUFFER_FOR_TIME);
            std::string file = GetNextProperty(line, BUFFER_FOR_FILE);  
            std::string function = GetNextProperty(line, BUFFER_FOR_FUNCTION);   
            std::string message = GetNextProperty(line, BUFFER_FOR_MESSAGE);     

            m_all_logs.push_back(Log(type, time, file, function, message));
        }

        std::string DeSerializer::GetNextProperty(std::string& line, size_t size_of_buffer_for_property){
            // getting the result from where its supposed to be
            std::string result = line.substr(0, size_of_buffer_for_property);
            // deleting this part from the line
            if (size_of_buffer_for_property < line.size()){
                line = line.substr(INDENT_SIZE + size_of_buffer_for_property, line.size());
            }
            else{
                return line;
            }
            result = DeleteAllSpacesFromEndOfLine(result);
            return result;
        }

        std::string DeSerializer::DeleteAllSpacesFromEndOfLine(std::string line){
            std::string WHITESPACE = " \n\r\t\f\v";
            size_t end = line.find_last_not_of(WHITESPACE);
            return (end == std::string::npos) ? "" : line.substr(0, end + 1);
        }

        std::vector<Log> DeSerializer::GetAllLogs(){
            return m_all_logs;
        }
        void DeSerializer::GetLogsFromFile(){
            ScanLines();
            PushLogs();
            DeleteAllLines();
        } 

        void DeSerializer::SetPath(std::string path_in){
            m_file_with_logs = path_in;
            GetLogsFromFile();
        }

        void DeSerializer::DeleteAllLogs(){
            size_t amount_of_logs = m_all_logs.size();
            for(size_t i=0; i<amount_of_logs; i++){
                m_all_logs.pop_back();
            }
            DeleteAllLines();
        }

        void DeSerializer::DeleteAllLines(){
            size_t amount_of_lines = m_all_lines.size();
            for(size_t i=0; i<amount_of_lines; i++){
                m_all_lines.pop_back();
            }
        }
#endif
