#include <iostream>

int main(int argc, char* argv[]){
    std::cout << "Hello world!" << std::endl;
    std::cout << "Argument count: " << argc << std::endl;
    for(int i = 0; i < argc; ++i){
        std::cout << " argv[" << i << "] = " << argv[i] << std::endl;
    };

    if(argc < 1){
        return 1;
    };
    return 0;

};