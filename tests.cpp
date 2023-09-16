#include "tests.h"

void Tests::MakeTests() {
	const std::regex wordFilter("[a-zA-Z0-9]+");
	const std::regex removeFilter("[^a-zA-Z0-9]+");
	const int testsQuantity = 5;
	int count = 0;

	for (int i = 0; i < testsQuantity; i++) {
		int result;
		std::sregex_iterator begin {testingData[i].begin(), testingData[i].end(), wordFilter};
		std::sregex_iterator end {};
		__int64 wordsCount = std::distance(begin, end);
		if (wordsCount == 0) {
			result = 0;
		} else {
			std::string filteredLine = std::regex_replace(testingData[i], removeFilter, "");
			result = static_cast<int>(std::round(static_cast<double>(filteredLine.size()) / wordsCount));
		}
		if (result == answers[i]) {
			count++;
		}
	}

	if (count < testsQuantity) {
		std::cout << "Tests failed" << std::endl;
	} else {
		std::cout << "Tests passed" << std::endl;
	}
}

Tests::Tests() {
	testingData.push_back("word, word and word");
	testingData.push_back("");
	testingData.push_back("abc");
	testingData.push_back("aaa765 ghj no: spoon");
	testingData.push_back("wzexrvbyui, oplkjhg                  fghjkl;");

	answers.push_back(4);
	answers.push_back(0);
	answers.push_back(3);
	answers.push_back(4);
	answers.push_back(8);
}

Tests::~Tests() {}