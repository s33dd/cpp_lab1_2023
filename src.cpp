#include "menu.h"
#include "FileWork.h"
#include <regex>

void ManualInput(std::vector<std::string>& text);
std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);
bool IsEmpty(std::vector<std::string>& text);

int main() {
    Menu menu{};
    menu.StartInformation();
    bool isExit = false;
    if (menu.ModularTestsAsk() == Answer::YES) {
        //Make tests
    }
    while (!isExit) {
        std::vector<std::string> text;
        std::vector<std::string> answer;

        bool isFileInput = false;

        const std::regex wordFilter("[a-zA-Z0-9]+");

        switch (menu.InputAsk()) {
            case InputType::FILE: {
                    isFileInput = true;
                    std::string path;
                    bool isErrors = true;
                    while (isErrors) {
                        std::cout << "Input the filename: ";
                        getline(std::cin, path);
                        if (std::filesystem::exists(path)) {
                            isErrors = false;
                        } else {
                            std::cout << "File doesn`t exist." << std::endl;
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
        bool reInputFlag = false;
        bool keepEmptyFlag = false;
        if (IsEmpty(text)) {
            std::cout << "Inputed text is empty. Do you want to keep it?" << std::endl;
            std::cout << "1 - Yes / 0 - No: ";
            switch (Menu::Ask()) {
                case Answer::YES:
                    keepEmptyFlag = true;
                    break;
                case Answer::NO:
                    reInputFlag = true;
                    break;
            }
        }
        if (reInputFlag == true) {
            continue;
        }
        
        //Make work
        std::cout << "Inputed text:" << std::endl;
        for (auto line : text) {
            std::cout << line << std::endl;
        }
        if (keepEmptyFlag == true) {
            answer.push_back("Average word length: 0");
        } else {
            for (int i = 0; i < text.size(); i++) {
                std::sregex_iterator begin {text[i].begin(), text[i].end(), wordFilter};
                std::sregex_iterator end {};
                int wordsCount = std::distance(begin, end);
                const std::regex removeFilter("[^a-zA-Z0-9]+");
                std::string filteredLine = std::regex_replace(text[i], removeFilter, "");
                int result = std::round(static_cast<double>(filteredLine.size()) / wordsCount);
                answer.push_back("Average word length for line " + std::to_string(i + 1) + ": " + std::to_string(result));
            }
        }
        std::cout << "Result:" << std::endl;
        for (auto line : answer) {
            std::cout << line << std::endl;
        }

        //Ask about saves
        bool isInputSave = false;
        bool isOutputSave = false;
        if (!isFileInput) {
            switch (menu.SaveInputAsk()) {
                case Answer::YES:
                    isInputSave = true;
                    break;
                case Answer::NO:
                    break;
            }
        }
        if (isInputSave) {
            std::string path;
            bool isErrors = true;
            bool rewriteFlag = false;
            while (isErrors) {
                std::cout << "Input the filename: ";
                getline(std::cin, path);
                if (FileWork::NameForbidden(path)) {
                    std::cout << "Invalid filename." << std::endl;
                    continue;
                }
                if (std::filesystem::exists(path)) {
                    switch (menu.RewriteAsk()) {
                        case Answer::NO:
                            rewriteFlag = false;
                            break;
                        case Answer::YES:
                            rewriteFlag = true;
                            break;
                    }
                }
                if (rewriteFlag == false) {
                    continue;
                }
                if (rewriteFlag == true and FileWork::IsReadOnly(path)) {
                    std::cout << "The file is readonly." << std::endl;
                    continue;
                }
                isErrors = false;
            }
            FileWork inputSaveFile{ path };
            inputSaveFile.Save(text);
        }

        switch (menu.OutputFileAsk()) {
            case Answer::NO:
                break;
            case Answer::YES: {
                std::string path;
                bool isErrors = true;
                bool rewriteFlag = false;
                while (isErrors) {
                    std::cout << "Input the filename: ";
                    getline(std::cin, path);
                    if (FileWork::NameForbidden(path)) {
                        std::cout << "Invalid filename." << std::endl;
                        continue;
                    }
                    if (std::filesystem::exists(path)) {
                        switch (menu.RewriteAsk()) {
                        case Answer::NO:
                            rewriteFlag = false;
                            break;
                        case Answer::YES:
                            rewriteFlag = true;
                            break;
                        }
                    }
                    if (rewriteFlag == false) {
                        continue;
                    }
                    if (rewriteFlag == true and FileWork::IsReadOnly(path)) {
                        std::cout << "The file is readonly." << std::endl;
                        continue;
                    }
                    isErrors = false;
                }
                FileWork outputSaveFile{ path };
                outputSaveFile.Save(answer);
            }
        }

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

bool IsEmpty(std::vector<std::string>& text) {
    int count = 0;
    for (auto line : text) {
        if (trim(line).empty()) {
            count++;
        }
    }
    if (count == text.size()) {
        return true;
    }
    else {
        return false;
    }
}