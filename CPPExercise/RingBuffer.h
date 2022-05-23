#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

class RingBuffer
{
public:
	RingBuffer() = default;
	RingBuffer(int InSize);
	~RingBuffer();
	void push(const char* Str);
	void pop(char* Str);
	void printRingBuffer();

private:
	int Size = 0;
	int ValidNum = 0;
	int CurrentBegin = 0;
	int CurrentEnd = 0;
	std::string* Data = nullptr;
};

