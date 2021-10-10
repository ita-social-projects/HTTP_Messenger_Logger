#include "../src/Logger.cpp"

#include <memory>
class CLASS_EXAMPLE{   
    static int another_function(){
        FATAL("oh no! i dont know what to write in message");
        //SET_LOG_LEVEL(t_ERROR);
        
        return 1;
    }
public:
    void function(int a, int b, std::string st){        
        int num;
        SET_LOGS_FILE("log_.txt");
        SET_MAX_AMOUNT_OF_LOGS(2);
        SHOW_LOGS_IN_CONSOLE(true);

        DEBUG("just test");
        ERROR("😐");
        VERBOSE("DEMO #2");
        VERBOSE("lol");
        VERBOSE("yeah");
        another_function();
    }
};