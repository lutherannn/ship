#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> cmdStack = {};
std::vector<int> stack = {0};

//tokenizes a string into an array by a delimiter. i love reinventing the wheel
std::vector<std::string> tokenizeString(std::string inp, char delim, bool popFirst) {
    std::vector<std::string> r = {};
    std::string t = "";
    for (int i = 0; i < inp.size(); i++) {
        t += inp[i];
        if (inp[i] == delim) {
            r.push_back(t);
            t = "";
        }
        if (i == inp.size() - 1) {
            r.push_back(t);
        }
    }
    if (popFirst) {
        r.erase(r.begin());
        return r;
    } else {
        return r;
    }
}

//debug shit
void outputStack(){
    for (int i = 0; i < stack.size(); i++) {
        std::cout << stack[i] << ' ';
    }
    std::cout << std::endl;
}

//technically idk if i really need this since i can tokenize it
//plus i know which elements will be where but i'll keep it to avoid refactoring for now
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

//reads the input file
void readInputFile(std::string fileName) {
    std::ifstream file(fileName);
    std::string l;
    while (std::getline(file, l)) {
        cmdStack.push_back(l);
    }
}

//the meat and potatoes, yikes.
int processCmd() {
    //where the pointer is on the stack, default 0
    int ptr = 0;
    //loops over each line in the input file stack we created
    for (int i = 0; i < cmdStack.size(); i++) {
        //program entry point, sets the pointer to 0 if it isn't already
        if (cmdStack[i].rfind("BOARD", 0) == 0) {
            ptr = 0;
        }
        //moves the pointer to the right and if that spot is empty it will automatically make it 0
        if (cmdStack[i].rfind("STARBOARD", 0) == 0) {
            ptr++;
            if (stack.size() - 1 < ptr) {
                stack.push_back(0);
            }
        }
        //moves pointer to the left
        if (cmdStack[i].rfind("PORT", 0) == 0 && ptr >=  1) {
            ptr--;
        }
        //returns the pointer to 0
        if (cmdStack[i].rfind("SAIL HOME", 0) == 0) {
            ptr = 0;
        }
        //loads a value into the current position on the stack
        if (cmdStack[i].rfind("LOAD", 0) == 0) {
            stack[ptr] = getSingleNumber(cmdStack[i]);
        }
        //will remove a value once i need to implement it
        if (cmdStack[i].rfind("UNLOAD", 0) == 0) {

        }
        //loads a value into the stack and then prints it to stdout, will also be removed after
        if (cmdStack[i].rfind("OVERLOAD", 0) == 0) {
            stack[ptr] = getSingleNumber(cmdStack[i]);
            std::cout << char(stack[ptr]);
        }
        //prints the char of the ascii number at the current position of the stack to stdout with no newline
        if (cmdStack[i].rfind("CALL NO ANSWER", 0) == 0) {
            std::cout << char(stack[ptr]);
        }
        //does the same as above but with a newline
        if (cmdStack[i].rfind("CALL", 0) == 0) {
            if (cmdStack[i].find("N") == std::string::npos) {
                std::cout << char(stack[ptr]) << std::endl;
            }
        }
        //outputs the actual value of the position on the stack
        if (cmdStack[i].rfind("SPEAK PLAINLY", 0) == 0) {
            std::cout << stack[ptr] << std::endl;
        }
        //adds two elements on the stack together and appends it to the stack
        if (cmdStack[i].rfind("RECRUIT", 0) == 0) {
            std::vector<std::string> tokenizedInp = tokenizeString(cmdStack[i], ' ', true);
            stack.push_back(stoi(tokenizedInp[0]) + stoi(tokenizedInp[1]));
        }
        //subtracts two elements on the stack and appends it to the stack
        if (cmdStack[i].rfind("KEELHAUL", 0) == 0) {
            std::vector<std::string> tokenizedInp = tokenizeString(cmdStack[i], ' ', true);
            stack.push_back(stoi(tokenizedInp[0]) - stoi(tokenizedInp[1]));
        }
        //divides two elements on the stack and appends it to the stack
        if (cmdStack[i].rfind("DIVVY", 0) == 0) {
            std::vector<std::string> tokenizedInp = tokenizeString(cmdStack[i], ' ', true);
            stack.push_back(stoi(tokenizedInp[0]) / stoi(tokenizedInp[1]));
        }
        if (cmdStack[i].rfind("RAID", 0) == 0) {
            std::vector<std::string> tokenizedInp = tokenizeString(cmdStack[i], ' ', true);
            stack.push_back(stoi(tokenizedInp[0]) * stoi(tokenizedInp[1]));
        }
        //ends the program
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
        return 0;
    } else {
        std::cout << "program exited code 1" << std::endl;
        return 1;
    }
}