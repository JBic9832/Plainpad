#include "Buffers/TextFile.h"
#include <iostream>
#include <string>

int main() {

    bool running = true;
    bool insert;

    TextFile file{};

    while (running) {
        char ioe;


        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue; 
        }

        if (input[0] == 'q') { 
            running = false; 
            continue; 
        }

        if (input[0] == 'i') {
            insert = true;
        } else {
            insert = false;
        }

        int line = static_cast<int>(input[1] - '0');
        std::string text = input.substr(2);

        if (insert) 
            file.InsertLine(line, text);
        else
            file.EditLine(line, text);
    }

    int count = 1;
    for (const auto& l : file.GetLines()) {
        std::cout << count<< " " << l << std::endl;
        ++count;
    }

    return 0;
}