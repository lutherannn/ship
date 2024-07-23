#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> cmdStack = {};
std::vector<int> stack = {0};

void outputStack(){
    for (int i = 0; i < stack.size(); i++) {
        std::cout << stack[i] << ' ';
    }
    std::cout << std::endl;
}

int getSingleNumber(std::string inp) {
    int n;
    std::regex regex(R"(\d+)");
    std::smatch match;

    while (std::regex_search(inp, match, regex)) {
        n = std::stoi(match.str());
        inp = match.suffix();
    }
    return n;
}

std::vector<int> getNumbers(std::string inp) {
    std::vector<int> numbers = {};
    for (int i = 0; i < inp.length(); i++) {
        if (!isalpha(inp[i])) {
            numbers.push_back(inp[i]);
        }
    }
    return numbers;
}

void readInputFile(std::string fileName) {
    std::ifstream file(fileName);
    std::string l;
    while (std::getline(file, l)) {
        if (l == "#") {
            break;
        }
        cmdStack.push_back(l);
    }
}

int processCmd() {
    int ptr = 0;
    for (int i = 0; i < cmdStack.size(); i++) {
        //outputStack();
        if (cmdStack[i].rfind("BOARD", 0) == 0) {
            ptr = 0;
        }
        if (cmdStack[i].rfind("STARBOARD", 0) == 0) {
            ptr++;
            if (stack.size() - 1 < ptr) {
                stack.push_back(0);
            }
        }
        if (cmdStack[i].rfind("PORT", 0) == 0 && ptr >=  1) {
            ptr--;
        }
        if (cmdStack[i].rfind("SAIL HOME", 0) == 0) {
            ptr = 0;
        }
        if (cmdStack[i].rfind("LOAD", 0) == 0) {
            stack[ptr] = getSingleNumber(cmdStack[i]);
        }
        if (cmdStack[i].rfind("UNLOAD", 0) == 0) {

        }
        if (cmdStack[i].rfind("OVERLOAD", 0) == 0) {
            stack[ptr] = getSingleNumber(cmdStack[i]);
            std::cout << char(stack[ptr]);
        }
        if (cmdStack[i].rfind("CALL NO ANSWER", 0) == 0) {
            std::cout << char(stack[ptr]);
        }
        if (cmdStack[i].rfind("CALL", 0) == 0) {
            if (cmdStack[i].find("N") == std::string::npos) {
                std::cout << char(stack[ptr]) << std::endl;
            }
        }
        if (cmdStack[i].rfind("MOOR", 0) == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    readInputFile("input.shp");
    if (processCmd() == 0) {
        std::cout << "program exited code 0" << std::endl;
    } else {
        std::cout << "program exited code 1" << std::endl;
    }
    return 0;
}