#include <fstream>
#include <iostream>
#include <string>

int main(int, char** argv){
    std::ifstream input("/tmp/samplePipe");
    std::string line;
    //char dlm = ';';
    int i = 0;
    bool done = false;
    while(!done){
        while(getline(input, line)){
            std::cout << line << "\n";
        }
        if(input.eof()){
            input.clear();
        } else {
            done = true;
        }
    }
    //input >> line;
    //std::cout << line;
    input.close();
}
