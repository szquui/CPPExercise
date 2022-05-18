#pragma once
#include <iostream>

class CustomString
{
public:
	CustomString();
	CustomString(const char* str);
	CustomString(const CustomString& customStr);
	~CustomString();

	CustomString& operator=(const CustomString& customStr);
	bool operator==(const CustomString& customStr);

	int len() const;
	void printCustomString();
	CustomString& sub(int offset, int count);
	void append(const char* str);
	int find(const char* str);
	CustomString* split(const char* str);

private:
	char* customString = nullptr;
};

