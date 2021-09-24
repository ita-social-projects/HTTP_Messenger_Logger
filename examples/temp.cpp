#include "../src/Logger.cpp"

#include <memory>
class DATABASE_CLASS_EXAMPLE{   
    public:
    static void lol(int a, int b, std::string st,int* h()){
        //SET_LOG_LEVEL(t_DEBUG);
        DEBUG("yeah.. debug");
        VERBOSE("oopss ");
        FATAL("OOO fatality(");
        ERROR("just one error..");
    }
    static void foo(){
        //SET_LOG_LEVEL(t_DEBUG);
        DEBUG("yeah.. debug");
        VERBOSE("oopss ");
        FATAL("OOO fatality(");
        ERROR("just one error..");
    }
};