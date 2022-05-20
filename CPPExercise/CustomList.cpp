#include "CustomList.h"
#include <iostream>

CustomListNode::~CustomListNode()
{
	if (pre != nullptr)
	{
		delete pre;
		pre = nullptr;
	}
	if (next != nullptr)
	{
		delete next;
		next = nullptr;
	}
}

CustomList::~CustomList()
{
	if (head != nullptr)
	{
		delete head;
		head = nullptr;
	}
}

CustomListNode* CustomList::push(int num)
{
	CustomListNode* customListNode = new CustomListNode(num);
	CustomListNode* listEnd = getEnd();
	if (listEnd == nullptr)
	{
		head = customListNode;
		end++;
		return customListNode;
	}
	listEnd->next = customListNode;
	customListNode->pre = listEnd;
	end++;
	return customListNode;
}

CustomListNode* CustomList::insert(CustomListNode* listNode, int index)
{
	if (index < 0)
	{
		return insert(listNode, 0);
	}
	if (index > end)
	{
		return insert(listNode, end);
	}
	CustomListNode* customListNode = new CustomListNode(listNode);
	if (index == 0)
	{
		customListNode->next = head;
		head->pre = customListNode;
		head = customListNode;
		end++;
		return customListNode;
	}
	if (index == end)
	{
		CustomListNode* listEnd = getEnd();
		listEnd->next = customListNode;
		customListNode->pre = listEnd;
		end++;
		return customListNode;
	}
	CustomListNode* nextCustomListNode = find(index);
	customListNode->next = nextCustomListNode;
	customListNode->pre = nextCustomListNode->pre;
	nextCustomListNode->pre->next = customListNode;
	nextCustomListNode->pre = customListNode;
	end++;
	return customListNode;
}

CustomListNode* CustomList::find(int index)
{
	if (index > end - 1)
	{
		return nullptr;
	}
	CustomListNode* customListNode = head;
	for (int i = 0; i < index; i++)
	{
		customListNode = customListNode->next;
	}
	return customListNode;
}

void CustomList::remove(CustomListNode* listNode)
{
	if (listNode->pre != nullptr)
	{
		listNode->pre->next = listNode->next;
	}
	if (listNode->next != nullptr)
	{
		listNode->next->pre = listNode->pre;
	}
	listNode->pre = nullptr;
	listNode->next = nullptr;
	delete listNode;
	end--;
}

void CustomList::popAll()
{
	if (head == nullptr)
	{
		return;
	}
	int endBefore = end;
	for (int i = 0; i < endBefore; i++)
	{
		CustomListNode* customListNode = head->next;
		if (customListNode != nullptr)
		{
			customListNode->pre = nullptr;
		}
		head->next = nullptr;
		delete head;
		head = customListNode;
	}
	end = 0;
}

void CustomList::printCustomList()
{
	std::cout << "List length:" << end << "\n";
	CustomListNode* customListNode = head;
	for (int i = 0; i < end; i++)
	{
		if (customListNode != nullptr)
		{
			std::cout << "ListNode" << i << "Value:" << customListNode->value << ", Address:" << &*customListNode << "\n";
			customListNode = customListNode->next;
		}
	}
}

CustomListNode* CustomList::getEnd()
{
	return find(end - 1);
}

int main()
{
	auto list1 = new CustomList();
	auto node1 = list1->push(1);
	list1->printCustomList();

	auto node2 = list1->push(2);
	list1->printCustomList();

	auto node3 = list1->insert(node2, 3);
	list1->printCustomList();

	auto ret = list1->find(2);
	std::cout << &*ret << "\n";

	list1->remove(node2);
	list1->printCustomList();

	list1->popAll();
	list1->printCustomList();
	return 0;
}