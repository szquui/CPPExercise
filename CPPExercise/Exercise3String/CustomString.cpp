#include "CustomString.h"
#include <string>

CustomString::CustomString()
{
	customString = new char[1];
	*customString = '\0';
}

CustomString::CustomString(const char* str)
{
	if (str == nullptr)
	{
		customString = new char[1];
		*customString = '\0';
	}
	else
	{
		int strLen = strlen(str) + 1;
		customString = new char[strLen];
		strcpy_s(customString, strLen, str);
	}
}

CustomString::CustomString(const CustomString& customStr)
{
	if (customStr.customString == nullptr)
	{
		customString = nullptr;
	}
	else
	{
		int customStrLen = strlen(customStr.customString) + 1;
		customString = new char[customStrLen];
		strcpy_s(customString, customStrLen, customStr.customString);
	}
}

CustomString::~CustomString()
{
	if (customString)
	{
		delete [] customString;
		customString = nullptr;
	}
}

CustomString& CustomString::operator=(const CustomString& customStr)
{
	if (&customStr == this)
	{
		return *this;
	}

	if (customString != nullptr)
	{
		delete[] customString;
	}

	int customStrLen = strlen(customStr.customString) + 1;
	customString = new char[customStrLen];
	strcpy_s(customString, customStrLen, customStr.customString);
	return *this;
}

bool CustomString::operator==(const CustomString& customStr)
{
	if (&customStr == this)
	{
		return true;
	}

	int customStrLen = customStr.len();
	int customStringLen = len();
	if (customStrLen != customStringLen)
	{
		return false;
	}
	else if (customStrLen == 0)
	{
		return true;
	}

	for(int i = 0; i < customStrLen; i++)
	{
		if (customStr.customString[i] != customString[i])
		{
			return false;
		}
	}

	return true;
}

int CustomString::len() const
{
	if (customString == nullptr)
	{
		return 0;
	}
	return strlen(customString);
}

void CustomString::printCustomString()
{
	std::cout << customString;
}

CustomString& CustomString::sub(int offset, int count)
{
	CustomString* outCustomStr = new CustomString();
	int length = len();
	if (offset + count > length + 1)
	{
		std::cout << "Get CustomString sub failed, input offset and count more than customString length!\n";
		return *outCustomStr;
	}

	outCustomStr->customString = new char[count + 1];
	for (int i = 0;i < count; i++)
	{
		outCustomStr->customString[i] = customString[offset + i];
	}
	outCustomStr->customString[count] = '\0';
	return *outCustomStr;
}

void CustomString::append(const char* str)
{
	if (str == nullptr)
	{
		return;
	}

	int strLen = strlen(str) + 1;
	if (customString == nullptr)
	{
		customString = new char[strLen];
		strcpy_s(customString, strLen, str);
	}
	else
	{
		int customStringLen = len();
		CustomString temp(customString);
		delete[] customString;
		customString = nullptr;
		customString = new char[strLen + customStringLen + 1];
		for (int i = 0; i < customStringLen; i++)
		{
			customString[i] = temp.customString[i];
		}
		for (int i = customStringLen; i < strLen + customStringLen; i++)
		{
			customString[i] = str[i - customStringLen];
		}
	}
}

int CustomString::find(const char* str)
{
	if (str == nullptr || customString == nullptr)
	{
		return -1;
	}

	int strLen = strlen(str);
	for (int i = 0; i < len(); i++)
	{
		if (customString[i] == str[0])
		{
			bool bEqual = true;
			for (int k = 1; k < strLen; k++)
			{
				if (customString[i + k] != str[k])
				{
					bEqual = false;
					break;
				}
			}
			if (bEqual)
			{
				return i;
			}
		}
	}

	return -1;
}

CustomString* CustomString::split(const char* str)
{
	CustomString temp(customString);
	int count = 0;
	int strLen = strlen(str);
	CustomString* result = nullptr;
	while (temp.len() > 0)
	{
		int index = temp.find(str);
		if (index < 0)
		{
			delete[] temp.customString;
			temp.customString = nullptr;
			count++;
		}
		else
		{
			temp = temp.sub(index + strLen, temp.len() - index - strLen);
			count++;
		}
	}

	if (count == 0)
	{
		return nullptr;
	}

	result = new CustomString[count];
	temp = *this;
	count = 0;
	while (temp.len() > 0)
	{
		int index = temp.find(str);
		if (index < 0)
		{
			result[count] = temp;
			delete[] temp.customString;
			temp.customString = nullptr;
		}
		else
		{
			result[count] = temp.sub(0, index + strLen - 1);
			temp = temp.sub(index + strLen, temp.len() - index - strLen);
			count++;
		}
	}
	return result;
}


int main()
{
	auto str1 = CustomString("test1");
	str1.printCustomString();
	std::cout << "\n";

	auto str2 = CustomString("test1,test3");
	str2.printCustomString();
	std::cout << "\n";

	str1 = "test3";
	str1.printCustomString();
	std::cout << "\n";

	int len = str1.len();
	std::cout << len <<"\n";

	CustomString sub1 = str1.sub(1, 2);
	sub1.printCustomString();
	std::cout << "\n";

	str1.append("append");
	str1.printCustomString();
	std::cout << "\n";

	bool equal = str1 ==str2;
	std::cout << equal <<"\n";

	int index = str1.find("es");
	std::cout << index << "\n";

	CustomString* ret = str2.split(",");
}