#include <iostream>
#include <map>
#include "Xor.h"
#include "ConversionHelper.h"
#include "Utils.h"
#include <iomanip>

int main()
{
	Utils utilsHelper;
	Xor xorHelper;

	//auto input = utilsHelper.GetInput();
	auto key = utilsHelper.GetKey();

	std::string input = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	auto encryptedBytes = xorHelper.EncryptFixedXor(input, key);


	for (auto byte : encryptedBytes)
	{
		std::cout << std::setfill('0') << std::setw(2) << std::hex << byte;
	}

	return 0;
}

