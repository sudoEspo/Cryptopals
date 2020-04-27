#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>

class Xor
{
public:
	Xor();
	std::vector<int> FixedXorKey(std::string& xorValue, std::string& xorKey);
	std::vector<unsigned int> SingleXorKey(std::vector<int> xorValue, unsigned int xorKey);
	void TriggerSingleXor(std::vector<int> xorValue);
	int CalculateFrequency(const std::string& stringToCalculate);
	void DetectSingleXor(const std::string& filePath);
	std::vector<int> EncryptFixedXor(std::string& bytes, std::string& key);

public:
	std::map<char, int> m_frequencyCount;

};

