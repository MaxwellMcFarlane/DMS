#include <fstream>
#include <iostream>
#include <string>

int main(int, char** argv){
    std::ifstream input("/tmp/myfifo");
    std::string line;
    //char dlm = ';';
    int i = 0;
    while(getline(input, line)){
        std::cout << line << "\n";
        for(int i = 0; i < 999; i++){
           i++;
           i--;
        }
    }
    //input >> line;
    //std::cout << line;
    input.close();
}
