#include "TabFile.h"
#include <fstream>
#include <iostream>


void TabFile::Load(const char* InPath)
{
	std::ifstream File;
	File.open(InPath, std::ios_base::in);
	if (!File)
	{
		return;
	}
	
	std::string Str;
	int LineNum = 0;
	while (getline(File, Str))
	{
		Data[LineNum] = Str;
		++LineNum;
	}
	File.close();
	Compress();
}

std::string TabFile::Find(int InKey)
{
	auto Result = DataIndex.find(InKey);
	if (Result != DataIndex.end())
	{
		return FindDecode(DataString[DataIndex[InKey]]);
	}
	
	return std::string();
}

void TabFile::Compress()
{
	CompressSame();
	CompressString();
	Data.erase(Data.begin(), Data.end());
}

void TabFile::CompressSame()
{
	int LineNum = 0;
	for (auto It = Data.begin(); It != Data.end(); ++It)
	{
		int Index = 0;
		int Offset = It->second.find("\t");
		std::string Content = It->second.substr(Offset + 1, It->second.size() - Offset + 1);
		if (!FindStringExist(Content, Index))
		{
			DataString.push_back(Content);
		}
		DataIndex[LineNum] = Index;
		++LineNum;
	}
}

void TabFile::CompressString()
{
	int DataStringIndex = 0;
	for (auto It = DataString.begin(); It != DataString.end(); ++It)
	{
		int StringSize = It->size();
		std::string OutString;
		int SameCount = 1;
		std::string LastString;
		for (int i = 0; i < StringSize; ++i)
		{
			if ((It[0][i] >= 'a' && It[0][i] <= 'z') || (It[0][i] >= 'A' && It[0][i] <= 'Z'))
			{
				if (LastString == "")
				{
					LastString = It[0][i];
				}
				else
				{
					if (It[0][i] == LastString[0])
					{
						SameCount = SameCount + 1;
					}
					else
					{
						if (SameCount > 1)
						{
							OutString = OutString + std::to_string(SameCount) + LastString;
						}
						else
						{
							OutString = OutString + LastString;
						}
						SameCount = 1;
						LastString = It[0][i];
					}
				}
			}
			else
			{
				if (SameCount > 1)
				{
					OutString = OutString + std::to_string(SameCount) + LastString + It[0][i];
				}
				else if(LastString == "")
				{
					OutString = OutString + It[0][i];
				}
				else
				{
					OutString = OutString + LastString + It[0][i];
				}
				SameCount = 1;
				LastString = "";
			}
		}
		DataString[DataStringIndex] = OutString;
		++DataStringIndex;
	}
}

bool TabFile::FindStringExist(std::string InDataValue, int& InIndex)
{
	int Index = 0;
	for (auto It = DataString.begin(); It != DataString.end(); ++It)
	{
		if (*It == InDataValue)
		{
			InIndex = Index;
			return true;
		}
		++Index;
	}

	InIndex = Index;
	return false;
}

std::string TabFile::FindDecode(std::string InEnCodeString)
{
	int StringSize = InEnCodeString.size();
	std::string OutString;
	int FirstNumIndex = -1;
	int LastNumIndex = 0;
	int LastNum = 0;
	for (int i = 0; i < StringSize; ++i)
	{
		if (InEnCodeString[i] <= '9' && InEnCodeString[i] >= '0')
		{
			FirstNumIndex = FirstNumIndex > 0 ? FirstNumIndex : i;
			LastNumIndex = i;
		}
		else
		{
			std::string NumStr = "";
			if (FirstNumIndex >= 0)
			{
				NumStr = InEnCodeString.substr(FirstNumIndex, LastNumIndex - FirstNumIndex + 1);
				LastNum = atoi(NumStr.c_str());
			}
			if ((InEnCodeString[i] >= 'a' && InEnCodeString[i] <= 'z') || (InEnCodeString[i] >= 'A' && InEnCodeString[i] <= 'Z') && LastNum > 0)
			{
				for (int j = 0; j < LastNum - 1; j++)
				{
					OutString = OutString + InEnCodeString[i];
				}
			}
			else
			{
				OutString = OutString + NumStr;
			}
			OutString = OutString + InEnCodeString[i];
			LastNum = 0;
			FirstNumIndex = -1;
		}
	}

	if (FirstNumIndex > 0)
	{
		std::string EndStr = InEnCodeString.substr(FirstNumIndex, 1);
		OutString = OutString + EndStr;
	}
	return OutString;
}