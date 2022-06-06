#include "SkipList.h"
#include <random>
#include <iostream>

bool SkipList::search(const int& InTarget)
{
	ListNode* Ptr = Head;
	while (Ptr)
	{
		while (Ptr->Right && Ptr->Right->Value < InTarget)
		{
			Ptr = Ptr->Right;
		}
		if (Ptr->Right && Ptr->Right->Value == InTarget)
		{
			return true;
		}
		Ptr = Ptr->Down;
	}

	return false;
}

void SkipList::add(const int& InNum)
{
	std::vector<ListNode *> Path;
	ListNode* Ptr = Head;
	while (Ptr)
	{
		while (Ptr->Right && Ptr->Right->Value < InNum)
		{
			Ptr = Ptr->Right;
		}
		Path.push_back(Ptr);
		Ptr = Ptr->Down;
	}

	ListNode* Down = nullptr;
	bool bAddLevel = true;
	while (bAddLevel && !Path.empty())
	{
		ListNode* Node = new ListNode();
		Node->Value = InNum;
		ListNode* NodeUp = Path.back();
		Path.pop_back();
		Node->Right = NodeUp->Right;
		NodeUp->Right = Node;
		Node->Down = Down;
		Down = Node;
		int Rand = rand();
		bAddLevel = (rand() % 2) == 0;
	}

	if (bAddLevel)
	{
		ListNode* Node = new ListNode();
		ListNode* NewHead = new ListNode();
		Node->Value = InNum;
		Node->Down = Down;
		NewHead->Down = Head;
		NewHead->Right = Node;
		Head = NewHead;
	}
}

bool SkipList::erase(const int& InNum)
{
	if (!search(InNum))
	{
		return false;
	}

	ListNode* Ptr = Head;
	while (Ptr)
	{
		while (Ptr->Right && Ptr->Right->Value < InNum)
		{
			Ptr = Ptr->Right;
		}
		if (Head->Right == Ptr->Right && Ptr->Right && Ptr->Right->Right == nullptr &&  Ptr->Right->Value == InNum)
		{
			ListNode* Node = Head;
			delete Head->Right;
			Head = Head->Down;
			delete Node;
			Ptr = Head;
		}
		if (Ptr->Right && Ptr->Right->Value == InNum)
		{
			ListNode* Node = Ptr->Right;
			Ptr->Right = Node->Right;
			Node->Right = nullptr;
			Node->Down = nullptr;
			delete Node;
			Node = nullptr;
		}
		Ptr = Ptr->Down;
	}

	return true;
}

void SkipList::PrintSkipList()
{
	ListNode* Ptr = Head;
	ListNode* PtrHead = Head;
	while (Ptr)
	{
		while (Ptr->Right)
		{
			std::cout << Ptr->Right->Value << ",";
			Ptr = Ptr->Right;
		}

		std::cout << "\n";
		Ptr = PtrHead->Down;
		PtrHead = Ptr;
	}
	std::cout << "\n";
}

//int main()
//{
//	SkipList* obj = new SkipList();
//	bool param_1 = obj->search(3);
//	obj->add(30);
//	obj->PrintSkipList();
//	obj->add(60);
//	obj->PrintSkipList();
//	obj->add(15);
//	obj->PrintSkipList();
//	obj->add(40);
//	obj->PrintSkipList();
//	obj->add(50);
//	obj->PrintSkipList();
//	bool param_2 = obj->erase(40);
//	obj->PrintSkipList();
//}