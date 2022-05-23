#include "CustomString.h"
#include <string>

CustomString::CustomString(const char* Str)
{
	if (Str && *Str)
	{
		int StrLen = strlen(Str) + 1;
		Data = new char[StrLen];
		strcpy_s(Data, StrLen, Str);
	}
}

CustomString::CustomString(const CustomString& CustomStr)
{
	if (CustomStr.Data == nullptr)
	{
		if (Data != nullptr)
		{
			delete[] Data;
			Data = nullptr;
		}
	}
	else
	{
		int CustomStrLen = strlen(CustomStr.Data) + 1;
		Data = new char[CustomStrLen];
		strcpy_s(Data, CustomStrLen, CustomStr.Data);
	}
}

CustomString::~CustomString()
{
	if (Data)
	{
		delete[] Data;
		Data = nullptr;
	}
}

CustomString& CustomString::operator=(const CustomString& CustomStr)
{
	if (&CustomStr == this)
	{
		return *this;
	}

	if (Data != nullptr)
	{
		delete[] Data;
	}

	int CustomStrLen = strlen(CustomStr.Data) + 1;
	Data = new char[CustomStrLen];
	strcpy_s(Data, CustomStrLen, CustomStr.Data);
	return *this;
}

bool CustomString::operator==(const CustomString& CustomStr)
{
	if (&CustomStr == this)
	{
		return true;
	}

	int CustomStrLen = CustomStr.len();
	int CustomStringLen = len();
	if (CustomStrLen != CustomStringLen)
	{
		return false;
	}
	else if (CustomStrLen == 0)
	{
		return true;
	}

	for(int i = 0; i < CustomStrLen; i++)
	{
		if (CustomStr.Data[i] != Data[i])
		{
			return false;
		}
	}

	return true;
}

int CustomString::len() const
{
	if (Data == nullptr)
	{
		return 0;
	}
	return strlen(Data);
}

void CustomString::printCustomString()
{
	if (Data != nullptr)
	{
		std::cout << Data;
	}
}

CustomString CustomString::sub(int Offset, int Count)
{
	CustomString OutCustomStr = CustomString();
	int length = len();
	if (Offset + Count > length)
	{
		std::cout << "Get CustomString sub failed, input Offset and Count more than Data length!\n";
		return OutCustomStr;
	}

	OutCustomStr.Data = new char[Count + 1];
	for (int i = 0;i < Count; i++)
	{
		OutCustomStr.Data[i] = Data[Offset + i];
	}
	OutCustomStr.Data[Count] = '\0';
	return OutCustomStr;
}

void CustomString::append(const char* Str)
{
	if (Str == nullptr)
	{
		return;
	}

	int StrLen = strlen(Str);
	if (Data == nullptr)
	{
		Data = new char[StrLen + 1];
		strcpy_s(Data, StrLen, Str);
	}
	else
	{
		int CustomStringLen = len();
		CustomString Temp(Data);
		delete[] Data;
		Data = nullptr;
		Data = new char[StrLen + CustomStringLen + 1];
		for (int i = 0; i < CustomStringLen; i++)
		{
			Data[i] = Temp.Data[i];
		}
		for (int i = CustomStringLen; i < StrLen + CustomStringLen; i++)
		{
			Data[i] = Str[i - CustomStringLen];
		}
		Data[StrLen + CustomStringLen] = '\0';
	}
}

int CustomString::find(const char* Str)
{
	if (Str == nullptr || Data == nullptr)
	{
		return -1;
	}

	int StrLen = strlen(Str);
	for (int i = 0; i < len(); i++)
	{
		if (Data[i] == Str[0])
		{
			bool bEqual = true;
			for (int k = 1; k < StrLen; k++)
			{
				if (Data[i + k] != Str[k])
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

CustomString* CustomString::split(const char* Str)
{
	if (Data == nullptr)
	{
		return nullptr;
	}

	CustomString Temp(Data);
	int Count = 0;
	int StrLen = strlen(Str);
	CustomString* Result = nullptr;
	while (Temp.len() > 0)
	{
		int Index = Temp.find(Str);
		if (Index < 0)
		{
			delete[] Temp.Data;
			Temp.Data = nullptr;
			Count++;
		}
		else
		{
			Temp = Temp.sub(Index + StrLen, Temp.len() - Index - StrLen);
			Count++;
		}
	}

	if (Count == 0)
	{
		return nullptr;
	}

	Result = new CustomString[Count];
	Temp = *this;
	Count = 0;
	while (Temp.len() > 0)
	{
		int Index = Temp.find(Str);
		if (Index < 0)
		{
			Result[Count] = Temp;
			delete[] Temp.Data;
			Temp.Data = nullptr;
		}
		else
		{
			Result[Count] = Temp.sub(0, Index + StrLen - 1);
			Temp = Temp.sub(Index + StrLen, Temp.len() - Index - StrLen);
			Count++;
		}
	}
	return Result;
}


//int main()
//{
//	auto Str1 = CustomString("test1");
//	Str1.printCustomString();
//	std::cout << "\n";
//
//	auto Str2 = CustomString("test1,test3");
//	Str2.printCustomString();
//	std::cout << "\n";
//
//	Str1 = "test3";
//	Str1.printCustomString();
//	std::cout << "\n";
//
//	int Len = Str1.len();
//	std::cout << Len <<"\n";
//
//	CustomString Sub1 = Str1.sub(1, 2);
//	Sub1.printCustomString();
//	std::cout << "\n";
//
//	Str1.append("append");
//	Str1.printCustomString();
//	std::cout << "\n";
//
//	bool bEqual = Str1 ==Str2;
//	std::cout << bEqual <<"\n";
//
//	int Index = Str1.find("es");
//	std::cout << Index << "\n";
//
//	CustomString* Ret = Str2.split(",");
//}