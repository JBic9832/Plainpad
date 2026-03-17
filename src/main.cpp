#include "Buffers/TextFile.h"
#include <iostream>
#include <string>

int main() {

    bool running = true;

    TextFile file{};

    while (running) {
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue; 
        }

        if (input[0] == 'q') { 
            running = false; 
            continue; 
        }

        int line = static_cast<int>(input[0] - '0');
        std::string text = input.substr(1);

        file.InsertLine(line, text);
    }

    int count = 1;
    for (const auto& l : file.GetLines()) {
        std::cout << count<< " " << l << std::endl;
        ++count;
    }

    return 0;
}