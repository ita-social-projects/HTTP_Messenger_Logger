#include "../src/Logger.cpp"

#include <memory>
class CLASS_EXAMPLE{   
    static int another_function(){
        FATAL("oh no! i dont know what to write in message");
        
        return 1;
    }
public:
    void function(int a, int b, std::string st){
        DEBUG("just test");
        ERROR("😐");
        another_function();
    }
};