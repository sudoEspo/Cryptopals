#include "Xor.h"
#include "ConversionHelper.h"
#include "Utils.h"

Xor::Xor()
{
	// ETAOIN SHRDLU
	m_frequencyCount['e'] = 13; m_frequencyCount['E'] = 13;
	m_frequencyCount['t'] = 12;	m_frequencyCount['T'] = 12;
	m_frequencyCount['a'] = 11;	m_frequencyCount['A'] = 11;
	m_frequencyCount['o'] = 10;	m_frequencyCount['O'] = 10;
	m_frequencyCount['i'] = 9;	m_frequencyCount['I'] = 9;
	m_frequencyCount['N'] = 8;	m_frequencyCount['N'] = 8;
	
	m_frequencyCount[' '] = 7;

	m_frequencyCount['s'] = 6;  m_frequencyCount['S'] = 6;
	m_frequencyCount['h'] = 5;	m_frequencyCount['H'] = 5;
	m_frequencyCount['r'] = 4;	m_frequencyCount['R'] = 4;
	m_frequencyCount['d'] = 3;	m_frequencyCount['D'] = 3;
	m_frequencyCount['l'] = 2;	m_frequencyCount['L'] = 2;
	m_frequencyCount['u'] = 1;	m_frequencyCount['U'] = 1;
}

/// <summary>
/// Takes a value and and variable length xor key which is consequently xor'ed byte for byte.
/// </summary>
/// <param name="xorValue">A vector of bytes to be xor'ed.</param>
/// <param name="xorKey">Value to be xor'ed against.</param>
/// <returns>The xor'ed result as a vector.</returns>
std::vector<int> Xor::FixedXorKey(std::string& xorValue, std::string& xorKey)
{
	ConversionHelper conversion;

	auto xorBytes = conversion.ConvertToRawBytes(xorValue);
	auto byteKey = conversion.ConvertToRawBytes(xorKey);

	auto xorResult = std::vector<int>();

	if (xorValue.size() != xorKey.size())
	{
		for (size_t i = 0; i < byteKey.size(); i++)
		{
			auto result = byteKey.at(i) ^ xorBytes.at(i);
			xorResult.push_back(result);
		}
	}
	else
	{
		std::cout << "The key and value are not the same length" << std::endl;
	}

	return xorResult;
}

/// <summary>
/// Takes a value and and single xor key which is consequently xor'ed byte for byte.
/// </summary>
/// <param name="xorValue">A vector of bytes to be xor'ed.</param>
/// <param name="xorKey">Single byte to xor against.</param>
/// <returns>The xor'ed result as a vector.</returns>
std::vector<unsigned int> Xor::SingleXorKey(std::vector<int> xorValue, unsigned int xorKey)
{
	std::vector<unsigned int> xorBytes;

	for (auto const byte : xorValue)
	{
		auto xorByte = (byte ^ xorKey);
		xorBytes.push_back(xorByte);
	}

	return xorBytes;
}

/// <summary>
/// Takes a value to be tested against all 256 possibilities and prints out the values returned to the console.
/// </summary>
/// <param name="xorValue">A vector of bytes to be xor'ed.</param>
void Xor::TriggerSingleXor(std::vector<int> xorValue)
{
	Xor xorHelper;
	ConversionHelper conversion;
	
	auto topScore = 0;
	std::string topString = "";

	for (size_t i = 0; i < 256; i++)
	{
		auto xorBytes = xorHelper.SingleXorKey(xorValue, i);
		auto stringBytes = conversion.PrintBytesAsAscii(xorBytes);
		auto frequencyCount = xorHelper.CalculateFrequency(stringBytes);

		if (frequencyCount > topScore)
		{
			topScore = frequencyCount;
			topString = stringBytes;
		}
	}

	std::cout << topString << std::endl;
}

/// <summary>
/// Calculates a score using the most commonly used English letters.
/// </summary>
/// <param name="stringToCalculate">The string in question.</param>
/// <returns>The score composed of the frequency of the most commonly used English letters.</returns>
int Xor::CalculateFrequency(const std::string& stringToCalculate)
{
	int frequencyTotal = 0;
	std::map<char, int>::iterator iterate = m_frequencyCount.begin();

	while (iterate != m_frequencyCount.end())
	{
		size_t letterCount = std::count(stringToCalculate.begin(), stringToCalculate.end(), iterate->first);
		frequencyTotal += letterCount * iterate->second;
		iterate++;
	}

	return frequencyTotal;
}


void Xor::DetectSingleXor(const std::string& filePath)
{
	Xor xorHelper;
	ConversionHelper conversion;
	Utils utilsHelper;

	auto fileContents = utilsHelper.ReadFileByLine(filePath);
	auto iterationNumber = 0;

	auto bestScore = 0;
	std::string bestMatch = "";

	std::cout << "Iterating through file. Best match will be displayed below: " << std::endl;

	for (auto fileLine : fileContents)
	{
		auto bytes = conversion.ConvertToRawBytes(fileLine);
		auto topScore = 0;
		std::string topString = "";

		for (size_t i = 0; i < 256; i++)
		{
			auto xorBytes = xorHelper.SingleXorKey(bytes, i);
			auto stringBytes = conversion.PrintBytesAsAscii(xorBytes);
			auto frequencyCount = xorHelper.CalculateFrequency(stringBytes);

			utilsHelper.UpdateBestMatch(topString, topScore, stringBytes, frequencyCount);
		}

		utilsHelper.UpdateBestMatch(bestMatch, bestScore, topString, topScore);

		iterationNumber++;
	}

	std::cout << bestMatch << std::endl;

}

std::vector<int> Xor::EncryptFixedXor(std::string& bytes, std::string& key)
{
	ConversionHelper conversion;

	std::vector<int> retVal;
	auto rawBytes = conversion.ConvertAsciiToRawBytes(bytes);
	auto rawKey= conversion.ConvertAsciiToRawBytes(key);

	for (size_t i = 0; i < bytes.length(); i+= key.length())
	{
		auto currentByte = i;
		for (auto keyChar : rawKey)
		{
			try
			{
				retVal.push_back(keyChar ^ rawBytes.at(currentByte));
				currentByte++;
			}
			catch (const std::exception&)
			{
				break;
			}
		}
	}

	return retVal;
}