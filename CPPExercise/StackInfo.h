#pragma once
#include <iostream>
#include <stack>
#include <string.h>

struct Info
{
	void* Value = nullptr;
};

class StackInfo
{
public:
	StackInfo() = default;
	~StackInfo() = default;

	template<class T>
	void push(const T &InInfo);

	template<class T>
	void pop(T &InInfo);

private:
	std::stack<Info> Data;
};

template<class T>
void StackInfo::push(const T& InInfo)
{
	Info DataInfo;
	T* Ptr = new T();
	*Ptr = InInfo;
	DataInfo.Value = (void *)Ptr;
	Data.push(DataInfo);
}

template<class T>
void StackInfo::pop(T &InInfo)
{
	Info TopDataInfo = Data.top();
	T* Ptr = (T*)TopDataInfo.Value;
	InInfo = *Ptr;
	delete TopDataInfo.Value;
	Ptr = nullptr;
	Data.pop();
}
