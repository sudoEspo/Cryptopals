#pragma once
#include <string>
#include <vector>
class Utils
{
public:
	void UpdateBestMatch(std::string& iterationBest, int& topScore, const std::string& iterationMatch, const int iterationScore);
	std::vector<std::string> ReadFileByLine(const std::string& filePath);
	std::string GetInput();
	std::string GetKey();
};

