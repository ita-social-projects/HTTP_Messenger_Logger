#include <iostream>
#include "../src/DeSerializer.cpp"
#include "../src/Log.cpp"

int main(){
    DeSerializer a("log2.txt");
    std::vector<Log> b = a.GetAllLogs();
    for(auto it: b){
        std::cout << it.Serialize() << std::endl;
    }
    return 0;
}