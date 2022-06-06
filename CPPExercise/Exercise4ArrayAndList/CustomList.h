#pragma once
class CustomListNode
{
public:
	CustomListNode() {};
	CustomListNode(int num) { value = num; };
	CustomListNode(CustomListNode* listNode) { value = listNode->value; };
	~CustomListNode();

public:
	int value = 0;
	CustomListNode* pre = nullptr;
	CustomListNode* next = nullptr;
};


class CustomList
{
public:
	CustomList() {};
	~CustomList();
	CustomListNode* push(int num);
	CustomListNode* insert(CustomListNode* listNode, int index);
	CustomListNode* find(int index);
	void remove(CustomListNode* listNode);
	void popAll();
	void printCustomList();

private:
	CustomListNode* getEnd();

private:
	CustomListNode* head = nullptr;
	int end = 0;
};

