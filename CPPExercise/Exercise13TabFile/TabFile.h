#pragma once
#include <map>
#include <string>
#include <vector>

class TabFile
{
public:
	TabFile() = default;
	~TabFile() = default;
	void Load(const char *InPath);
	std::string Find(int InKey);

private:
	void Compress();
	void CompressSame();
	void CompressString();
	bool FindStringExist(std::string InDataValue, int& InIndex);
	std::string FindDecode(std::string InEnCodeString);

	std::map<int, std::string> Data;
	std::map<int, int> DataIndex;
	std::vector<std::string> DataString;
};