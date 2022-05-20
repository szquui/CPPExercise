#include "CustomArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

CustomArray::CustomArray()
{
}

CustomArray::~CustomArray()
{
	if (customArray != nullptr)
	{
		free(customArray);
		customArray = nullptr;
		length = 0;
		top = 0;
	}
}

void CustomArray::reserve(int size)
{
	if (customArray != nullptr)
	{
		free(customArray);
		customArray = nullptr;
	}
	customArray = (int *) malloc(sizeof(int) * size);
	length = size;
	top = 0;
}

void CustomArray::push(int num)
{
	if (length == top)
	{
		bool expandSuccess = expand(1);
		if (!expandSuccess)
		{
			return;
		}
	}
	customArray[top] = num;
	top++;
}

void CustomArray::insert(int index, int num)
{
	if (index < 0)
	{
		insert(0, num);
		return;
	}
	if (index >= top)
	{
		push(num);
		return;
	}
	if (length == top)
	{
		bool expandSuccess = expand(1);
		if (!expandSuccess)
		{
			return;
		}
	}
	for (int i = top; i > index; i--)
	{
		customArray[i] = customArray[i - 1];
	}
	customArray[index] = num;
	top++;
}

void CustomArray::remove(int index)
{
	if (customArray == nullptr)
	{
		return;
	}
	if (index < 0)
	{
		remove(0);
		return;
	}
	if (index >= top)
	{
		remove(top - 1);
		return;
	}
	if (index == top - 1)
	{
		top--;
		return;
	}
	for (int i = index; i < top; i++)
	{
		customArray[i] = customArray[i + 1];
	}
	top--;
}

void CustomArray::pop()
{
	if (top == 0)
	{
		return;
	}
	remove(top - 1);
}

void CustomArray::clear()
{
	top = 0;
}

int CustomArray::findIndex(int num)
{
	if (customArray == nullptr)
	{
		return -1;
	}
	for (int i = 0; i < top; i++)
	{
		if (customArray[i] == num)
		{
			return i;
		}
	}
	return -1;
}

void CustomArray::printCustomArray()
{
	if (customArray == nullptr)
	{
		return;
	}
	std::cout << "Array Length:" << length << ",Array Top:" << top << " Array:";
	for (int i = 0; i < top; i++)
	{
		std::cout << customArray[i] << ",";
	}
	std::cout << "\n";
}

bool CustomArray::expand(int size)
{
	int* temp = (int*)realloc(customArray, sizeof(int) * (length + size));
	if (temp != nullptr)
	{
		customArray = temp;
		length = length + size;
		return true;
	}
	return false;
}


//int main()
//{
//	auto arr = new CustomArray();
//	arr->reserve(4);
//	arr->printCustomArray();
//
//	arr->push(1);
//	arr->push(2);
//	arr->printCustomArray();
//
//	arr->insert(1, 3);
//	arr->printCustomArray();
//
//	arr->remove(1);
//	arr->printCustomArray();
//
//	arr->pop();
//	arr->printCustomArray();
//
//	arr->clear();
//	arr->printCustomArray();
//
//	int index = arr->findIndex(1);
//	std::cout << index;
//	return 0;
//}