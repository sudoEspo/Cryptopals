#pragma once
#include <string>
#include <vector>

class ConversionHelper
{
public:
	bool VerifyLength(size_t inputLength);
	std::vector<int> ConvertToRawBytes(std::string& input);
	std::vector<int> ConvertAsciiToRawBytes(std::string& input);
	std::vector<char> ConvertToBase64(std::vector<int> bytes);
	std::string PrintBytesAsAscii(const std::vector<unsigned int> bytesToPrint);

private:

};