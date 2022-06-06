#pragma once

class ListNode
{
public:
	ListNode() = default;
	~ListNode() = default;

public:
	ListNode* Right = nullptr;
	ListNode* Down = nullptr;
	int Value = 0;
};


class SkipList
{
public:
	SkipList() = default;
	~SkipList() = default;
	bool search(const int &InTarget);
	void add(const int &InNum);
	bool erase(const int &InNum);
	void PrintSkipList();

private:
	ListNode* Head = nullptr;
};

