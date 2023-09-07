#include "menu.h"
#include "FileWork.h"

void ManualInput(std::vector<std::string>& text);
std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);

int main() {
    Menu menu{};
    menu.StartInformation();
    bool isExit = false;
    if (menu.ModularTestsAsk() == Answer::YES) {
        //Make tests
    }
    while (!isExit) {
        std::vector<std::string> text;

        switch (menu.InputAsk()) {
            case InputType::FILE: {
                    std::string path;
                    bool isErrors = true;
                    while (isErrors) {
                        std::cout << "Input the filename: ";
                        getline(std::cin, path);
                        if (std::filesystem::exists(path)) {
                            isErrors = false;
                        }
                    }
                    FileWork inputFile{ path };
                    text = inputFile.Input();
                    break;
                }
            case InputType::MANUAL: {
                    ManualInput(text);
                    break;
                }
        }

        //Check empty text
        
        //Make work

        //Ask about saves

        //Rewrite checks

        if (menu.RepeatAsk() == Answer::YES) {
            isExit = true;
        } else {
            isExit = false;
        }
    }
}

void ManualInput(std::vector<std::string>& text) {
    std::string row;
    bool stopInput = false;
    do {
        std::cout << "Input row:" << std::endl;
        getline(std::cin, row);
        text.push_back(row);
        std::cout << "Do you want to input another line? 1 - Yes / 0 - No: ";
        if (Menu::Ask() == Answer::YES) {
            stopInput = false;
        } else {
            stopInput = true;
        }
    } while (!stopInput);
}

std::string ltrim(const std::string& s) {
    size_t start = s.find_first_not_of(" \n\r\t\f\v");
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s) {
    size_t end = s.find_last_not_of(" \n\r\t\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}