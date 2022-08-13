#include "SensitiveWordHelper.h"
#include <fstream>
#include <iostream>
#include <string>

void SensitiveWordHelper::Load(const char* InPath)
{
	std::ifstream File;
	File.open(InPath, std::ios_base::in);
	if (!File)
	{
		return;
	}

	char Buff[1024];
	int LineNum = 0;
	while (File.getline(Buff, 1024))
	{
		DataAppend(Buff);
	}
	File.close();
}

bool SensitiveWordHelper::Check(const char* InStr)
{
	if (InStr == nullptr || Data == nullptr)
	{
		return false;
	}

	int StrLen = strlen(InStr);
	for (int i = 0; i < DataLength; i++)
	{
		if (Data[i] == InStr[0])
		{
			bool bEqual = true;
			for (int k = 1; k < StrLen; k++)
			{
				if (Data[i + k] != InStr[k])
				{
					bEqual = false;
					break;
				}
			}
			if (bEqual)
			{
				return true;
			}
		}
	}

	return false;
}

void SensitiveWordHelper::DataAppend(const char* InStr)
{
	int BuffLen = strlen(InStr);
	if (Data == nullptr)
	{
		Data = new char[BuffLen + 1];
		strcpy_s(Data, BuffLen + 1, InStr);
		DataLength = BuffLen;
	}
	else
	{
		char *Temp = nullptr;
		Temp = new char[DataLength + 1];
		strcpy_s(Temp, DataLength + 1, Data);
		delete[] Data;
		Data = nullptr;
		Data = new char[BuffLen + DataLength + 1];
		for (int i = 0; i < DataLength; i++)
		{
			Data[i] = Temp[i];
		}
		for (int i = DataLength; i < BuffLen + DataLength; i++)
		{
			Data[i] = InStr[i - DataLength];
		}
		Data[BuffLen + DataLength] = '\0';
		DataLength = DataLength + BuffLen;
	}
}