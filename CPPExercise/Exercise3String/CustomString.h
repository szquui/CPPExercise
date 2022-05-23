#pragma once
#include <iostream>

class CustomString
{
public:
	CustomString() = default;
	CustomString(const char* Str);
	CustomString(const CustomString& CustomStr);
	~CustomString();

	CustomString& operator=(const CustomString& CustomStr);
	bool operator==(const CustomString& CustomStr);

	int len() const;
	void printCustomString();
	CustomString sub(int Offset, int Count);
	void append(const char* Str);
	int find(const char* Str);
	CustomString* split(const char* Str);

private:
	char* Data = nullptr;
};

