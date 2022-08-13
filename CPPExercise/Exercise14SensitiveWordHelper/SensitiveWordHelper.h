#pragma once


class SensitiveWordHelper
{
public:
	SensitiveWordHelper() = default;
	~SensitiveWordHelper() = default;
	void Load(const char* InPath);
	bool Check(const char* InStr);

private:
	void DataAppend(const char* InStr);

private:
	char* Data = nullptr;
	int DataLength = 0;
};

