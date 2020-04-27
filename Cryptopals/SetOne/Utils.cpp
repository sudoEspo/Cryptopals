#include "Utils.h"
#include <filesystem>
#include <iostream>
#include <fstream>

void Utils::UpdateBestMatch(std::string& iterationBest, int& topScore, const std::string& iterationMatch, const int iterationScore)
{
	if (iterationScore > topScore)
	{
		iterationBest = iterationMatch;
		topScore = iterationScore;
	}
}

/// <summary>
/// Converts a vector of bytes into its base64 representation.
/// Allows for padding to be implemented.
/// </summary>
/// <param name="bytes">A vector of bytes in hex to be converted.</param>
/// <returns>A vector of characters in their base64 representation.</returns>
std::vector<std::string> Utils::ReadFileByLine(const std::string& filePath)
{
	std::vector<std::string> fileContents;

	if (std::filesystem::exists(filePath))
	{
		std::ifstream inputFile(filePath);
		std::string currentLine;

		while (std::getline(inputFile, currentLine))
		{
			fileContents.push_back(currentLine);
		}

		inputFile.close();
	}
	else
	{
		std::cout << "The file path entered could not be identified. Please check the path" << std::endl;
	}

	return fileContents;
}

/// <summary>
/// Gets the input from the user and returns the received input back
/// </summary>
/// <returns>Value entered by the user</returns>
std::string Utils::GetInput()
{
	// Set One Challenge One: 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
	// Set One Challenge Thee: 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
	std::cout << "Enter the input string: " << std::endl;
	std::string input;
	std::getline(std::cin, input);

	return input;
}

/// <summary>
/// Gets the input from the user and returns the received input back
/// </summary>
/// <returns>Value entered by the user</returns>
std::string Utils::GetKey()
{
	std::cout << "Enter the key: " << std::endl;
	std::string input;
	std::getline(std::cin, input);

	return input;
}