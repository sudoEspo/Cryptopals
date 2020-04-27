#include <iostream>
#include "ConversionHelper.h"

std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/// <summary>
/// Checks to see whether the given string has a convertible amount of bytes.
/// </summary>
/// <param name="inputLength">Length of input</param>
/// <returns>TRUE if input can be used, FALSE otherwise</returns>
bool ConversionHelper::VerifyLength(size_t inputLength)
{
	auto retVal = false;
	if (inputLength % 2 == 0)
	{
		retVal = true;
	}

	return retVal;
}

/// <summary>
/// Converts the string passed by the user into a vector of bytes
/// </summary>
/// <param name="input">The string passed to the input prompt</param>
/// <returns>A vector of bytes</returns>
std::vector<int> ConversionHelper::ConvertToRawBytes(std::string& input)
{
	std::vector<int> retBytes;

	try
	{
		for (size_t i = 0; i < input.length(); i += 2)
		{
			auto hexRepresntation = std::stoi(input.substr(i, 2), nullptr, 16);
			retBytes.push_back(hexRepresntation);
		}
	}
	catch (const std::exception ex)
	{
		std::cout << "Error converting the requested action." << std::endl << ex.what() << std::endl;
	}

	return retBytes;
}

/// <summary>
/// Converts the string passed by the user into a vector of bytes
/// </summary>
/// <param name="input">The string passed to the input prompt</param>
/// <returns>A vector of bytes</returns>
std::vector<int> ConversionHelper::ConvertAsciiToRawBytes(std::string& input)
{
	std::vector<int> retBytes;

	try
	{
		for (size_t i = 0; i < input.length(); i++)
		{
			auto intRepresentation = static_cast<int>(input.at(i));
			retBytes.push_back(intRepresentation);
		}
	}
	catch (const std::exception ex)
	{
		std::cout << "Error converting the requested action." << std::endl << ex.what() << std::endl;
	}

	return retBytes;
}

/// <summary>
/// Converts a vector of bytes into its base64 representation.
/// Allows for padding to be implemented.
/// </summary>
/// <param name="bytes">A vector of bytes in hex to be converted.</param>
/// <returns>A vector of characters in their base64 representation.</returns>
std::vector<char> ConversionHelper::ConvertToBase64(std::vector<int> bytes)
{
	std::vector<char> retVal;
	auto paddingRequired = bytes.size() % 3;
	if (paddingRequired > 0)
	{
		for (size_t i = 1; i < paddingRequired; i++)
		{
			bytes.push_back(0);
		}
	}

	for (size_t i = 0; i < bytes.size(); i+=3)
	{
		auto currentCount = i;
		auto firstByte = bytes.at(currentCount);
		auto secondByte = bytes.at(++currentCount);
		auto thirdByte = bytes.at(++currentCount);

		// Extract the first portion of the 64 encoding.
		auto first64 = firstByte >> 2;
		
		// Extract the second portion of the 64 encoding.
		auto remainder = (first64 << 2) ^ firstByte;
		auto second64 = remainder << 4;
		second64 += (secondByte >> 4);

		// Extract the third portion of the 64 encoding.
		remainder = secondByte >> 4;
		auto third64 = (remainder << 4) ^ secondByte;
		third64 = third64 << 2;
		third64 += (thirdByte >> 6);

		// Extract the fourth portion of the 64 encoding.
		remainder = thirdByte >> 6;
		auto fourth64 = (remainder << 6) ^ thirdByte;

		retVal.push_back(base64[first64]);
		retVal.push_back(base64[second64]);
		retVal.push_back(base64[third64]);
		retVal.push_back(base64[fourth64]);
	}

	return retVal;
}

/// <summary>
/// Take a vector of bytes and attempts to print them to their ascii representative.
/// </summary>
/// <param name="bytes">A vector of bytes in hex to be printed to their ascii form.</param>
std::string ConversionHelper::PrintBytesAsAscii(const std::vector<unsigned int> bytesToPrint)
{
	std::string retVal;

	try
	{
		for (const auto& byte : bytesToPrint)
		{
			auto convertedChar = (char)byte;
			//std::cout << convertedChar;
			retVal += convertedChar;
		}

		//std::cout << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << "Error converting to char" << std::endl;
	}
	
	return retVal;
}