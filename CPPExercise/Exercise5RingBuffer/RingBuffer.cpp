#include "RingBuffer.h"

RingBuffer::RingBuffer(int InSize)
{
	Size = InSize;
	Data = new std::string[InSize];
	ValidNum = 0;
	CurrentEnd = 0;
	CurrentBegin = 0;
}

RingBuffer::~RingBuffer()
{
	if (Data != nullptr)
	{
		delete[] Data;
		Data = nullptr;
	}
}

void RingBuffer::push(const char* Str)
{
	if ((CurrentEnd > CurrentBegin && CurrentEnd - CurrentBegin >= Size) || (CurrentEnd == CurrentBegin && ValidNum > 0))
	{
		std::string* Temp = new std::string[Size];
		Temp = Data;
		Size = Size * 2;
		Data = new std::string[Size];
		if (CurrentBegin == CurrentEnd)
		{
			for (int i = 0; i <= Size / 2; i++)
			{
				int TempIndex = CurrentBegin + i > Size / 2 ? 0 : CurrentBegin + i;
				Data[0] = Temp[TempIndex];
			}
		}
		else
		{
			for (int i = 0; i < Size / 2; i++)
			{
				Data[i] = Temp[i];
			}
		}
		CurrentBegin = 0;
		CurrentEnd = Size / 2;
	}
	Data[CurrentEnd] = std::string(Str);
	CurrentEnd++;
	ValidNum++;
}

void RingBuffer::pop(char* Str)
{
	int Length = Data[CurrentBegin].length();
	Str = new char[Length + 1];
	for (int i = 0; i < Length; i++)
	{
		Str[i] = Data[CurrentBegin][i];
	}
	Str[Length] = '\0';
	Data[CurrentBegin] = "";
	ValidNum--;
	CurrentBegin = CurrentBegin + 1 > Size ? 0 : CurrentBegin + 1;
	if (ValidNum < Size / 2)
	{
		std::string* Temp = new std::string[Size];
		Temp = Data;
		Data = new std::string[Size / 2];
		for (int i = 0; i < ValidNum; i++)
		{
			int TempIndex = CurrentBegin + i > Size? 0 : CurrentBegin + i;
			Data[i] = Temp[TempIndex];
		}
		CurrentBegin = 0;
		CurrentEnd = ValidNum; 
		Size = Size / 2;
	}
}

void RingBuffer::printRingBuffer()
{
	for (int i = 0; i < Size; i++)
	{
		std::cout << "index: " << i <<", Value:" << Data[i];
		std::cout << ";";
	}
	std::cout << "\n";
}


//void lambda_value_capture() 
//{
//	int value = 1;
//	auto copy_value = [value] {
//		return value;
//	};
//	value = 100;
//	auto stored_value = copy_value();
//	std::cout << stored_value << "  " << value;
//}
//
//int main()
//{
//	lambda_value_capture();
//}