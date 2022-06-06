#pragma once
class CustomArray
{
public:
	CustomArray();
	~CustomArray();

	void reserve(int size);
	void push(int num);
	void insert(int index, int num);
	void remove(int index);
	void pop();
	void clear();
	int findIndex(int num);
	void printCustomArray();

private:
	bool expand(int size);

private:
	int* customArray = nullptr;
	int top = 0;
	int length = 0;
};

