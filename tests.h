#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Tests {
public:
	Tests();
	~Tests();

	void MakeTests();

private:
	std::vector<std::string> testingData;
	std::vector<int> answers;
};