#include "../include/Log.h"
#include <string>


        std::string Log::Replace_In_String(std::string &s, const std::string &toReplace, const std::string &replaceWith) {
            std::size_t pos = s.find(toReplace);
            if (pos == std::string::npos) {
                return s;
            }
            return s.replace(pos, toReplace.length(), replaceWith);
        }

        Log::Log(TYPE_OF_LOG type_in,
            std::string time_in,
            std::string file_in,
            std::string function_in,
            std::string message_in):
                m_type(type_in),
                m_time(time_in),
                m_file(file_in),
                m_function(function_in),
                m_message(message_in){};
        Log::Log(std::string type_in,
            std::string time_in,
            std::string file_in,
            std::string function_in,
            std::string message_in):
                m_type(StringToType(type_in)),
                m_time(time_in),
                m_file(file_in),
                m_function(function_in),
                m_message(message_in){};

        std::string Log::Serialize(){
            std::string serialized_log = SERIALIZED_LOG_TEMPLATE;

            std::string type = TypeToString(m_type);
            type.resize(BUFFER_FOR_TYPE, ' ');
            std::string time = m_time;
            time.resize(BUFFER_FOR_TIME, ' ');
            std::string file = m_file;
            file.resize(BUFFER_FOR_FILE, ' ');
            std::string function = m_function;
            function.resize(BUFFER_FOR_FUNCTION, ' ');
            std::string message = m_message;
            message.resize(BUFFER_FOR_MESSAGE, ' ');

            Replace_In_String(serialized_log, "PLACE_FOR_TYPE", type);
            Replace_In_String(serialized_log, "PLACE_FOR_TIME", time);
            Replace_In_String(serialized_log, "PLACE_FOR_FILE", file);           
            Replace_In_String(serialized_log, "PLACE_FOR_FUNCTION", function); 
            Replace_In_String(serialized_log, "PLACE_FOR_MESSAGE", message);
            
            return DeleteAllSpaces(serialized_log);
        }

        std::string Log::DeleteAllSpaces(std::string line){
            std::string WHITESPACE = " \n\r\t\f\v";
            size_t end = line.find_last_not_of(WHITESPACE);
            return (end == std::string::npos) ? "" : line.substr(0, end + 1);
        }

        void Log::PrintInConsole(){
            switch (m_type) {
                case t_DEBUG:{
                    SET_DEBUG_COLOR;
                }
                break;
                case t_VERBOSE:{
                    SET_VERBOSE_COLOR;
                }
                break;
                case t_ERROR:{
                    SET_ERROR_COLOR;
                }
                break;
                case t_FATAL:{
                    SET_FATAL_COLOR;   
                }
                break;
                default: { 
                    RESET_COLOR;
                }
            }
            std::cout << Serialize() << std::endl;
            RESET_COLOR;   
        }

        std::string Log::TypeToString(TYPE_OF_LOG type){
            switch (type) {                
                case t_VERBOSE:{
                    return "VERBOSE";
                }
                case t_FATAL:{
                    return "FATAL";
                }
                case t_ERROR:{
                    return "ERROR";
                }  
                case t_DEBUG:{
                    return "DEBUG";
                }
                default: {
                    return "NO TYPE";
                }
            }
        }
        TYPE_OF_LOG Log::StringToType(std::string type)
        {            
            if(type=="VERBOSE"){
                return t_VERBOSE;
            }
            if(type=="FATAL"){
                return t_FATAL;
            }
            if(type=="ERROR"){
                return t_ERROR;
            }  
            if(type=="DEBUG"){
                return t_DEBUG;
            }
            return t_NO_TYPE;
        }


        TYPE_OF_LOG Log::GetType(){
            return m_type;
        }
        std::string Log::GetTime(){
            return m_time;
        }
        std::string Log::GetFile(){
            return m_file;
        }
        std::string Log::GetMessage(){
            return m_message;
        }
        std::string Log::GetFunction(){
            return m_function;
        }
