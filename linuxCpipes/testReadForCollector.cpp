#include <fstream>
#include <iostream>
#include <string>
 
int main(int, char** argv){
    bool keepGoing = true;
    while(keepGoing){
        std::ifstream input("/tmp/samplePipe");
        std::string line;
        std::cout << "after input open\n";
        //char dlm = ';';
        int i = 0;
        if(getline(input, line)){
            std::cout << line << "\n";
            for(int i = 0; i < 999; i++){
                i++;
                i--;
            }
       } else {
           keepGoing = false;
           input.close();
       }
    }
    //input >> line;
    //std::cout << line;
}
