#pragma once
#include<iostream>
#include<ctime>

struct Node
{
	int data;
	Node* next;
	Node* prev;
};
struct dualList
{
	Node* head;
	Node* tail;
	size_t size;
};

void initDualList(dualList& list)
{
	list.head = nullptr;
	list.tail = nullptr;
	list.size = 0;
}
void pushFront(dualList& list, int key)
{
	//creating new node
	Node* temp = new Node;
	temp->data = key;
	temp->prev = nullptr;
	temp->next = list.head;

	if (list.size == 0)
		list.tail = temp;
	else
		list.head->prev = temp;

	list.head = temp;
	list.size++;
}
void pushBack(dualList& list, int key)
{
	Node* temp = new Node;
	temp->data = key;
	temp->prev = list.tail;
	temp->next = nullptr;

	if (list.size == 0)
		list.head = temp;
	else
		list.tail->next = temp;

	list.tail = temp;
	list.size++;
}
void insert(dualList& list, size_t index, int key)
{
	if (list.size < index)
	{
		std::cout << "Cannot insert\n";
		return;
	}

	if (index == 0)
	{
		pushFront(list, key);
		return;
	}
	if (index == list.size)
	{
		pushBack(list, key);
		return;
	}

	Node* temp = new Node;
	temp->data = key;
	
	Node* i = list.head;
	size_t count = 0;

	for (; count < index; count++, i = i->next);

	temp->next = i;
	temp->prev = i->prev;// first "->" is like ".", second one appeals to entire previous element
	i->prev->next = temp;
	i->prev = temp;
	list.size++;

}
void insertSort(dualList& list, int key)
{
	if (list.size == 0)
	{
		pushBack(list, key);
		return;
	}

	Node* i = list.head;
	size_t count = 0;
	for (; i != nullptr && key > i->data; i = i->next, count++);
		
	if (i == nullptr)
	{
		pushBack(list, key);
		return;
	}
	insert(list, count, key);

	return;
}

int popFront(dualList& list)
{
	if (list.size == 0)
	{
		std::cout << "List is empty\n";
		return -1;
	}

	int key = list.head->data;
	Node* temp = list.head;
	
	if (list.size == 1)
		list.head = list.tail = nullptr;
	else if (list.size > 1)
	{
		list.head = temp->next;
		list.head->prev = nullptr;
	}

	delete temp;
	list.size--;
	return key;
}
int popBack(dualList& list)
{
	if (list.size == 0)
	{
		std::cout << "List is empty\n";
		return -1;
	}

	int key = list.tail->data;
	Node* temp = list.tail;

	if (list.size == 1)
		list.head = list.tail = nullptr;
	else if (list.size > 1)
	{
		list.tail = temp->prev;
		list.tail->next = nullptr;
	}

	delete temp;
	list.size--;
	return key;
}
int erasePostition(dualList& list, size_t index)
{
	if (list.size < index)
	{
		std::cout << "Cannot erase\n";
		return -1;
	}

	if (index == 0)
		return popFront(list);
	if (index == list.size - 1)
		return popBack(list);

	Node* i = list.head;
	size_t count = 0;

	for (; count < index; count++, i = i->next);

	i->prev->next = i->next;//i->prev - THE element, i->prev->next - pointer
	i->next->prev = i->prev;
	int key = i->data;
	delete i;
	list.size--;
	return key;
}
int getIndex(dualList list, size_t index)
{
	if (index > list.size)
	{
		std::cout << "No such index\n";
		return -1;
	}

	Node* i = list.head;
	size_t count = 0;

	for (; count < index; count++, i = i->next);

	return i->data;
}
void eraseKey(dualList& list, int key)
{
	for (size_t i = 0; i < list.size; i++)
	{
		if (getIndex(list, i) == key)
		{
			erasePostition(list, i);
			return;
		}
	}
	std::cout << "No such element\n";
	return;
}

void printList(dualList& list)
{
	for (Node* i = list.head; i != nullptr; i = i->next)
	{
		std::cout << i->data << " ";
	}
	std::cout << std::endl;
}

int maxElement(dualList& list)
{
	int max = list.head->data;
	Node* i = list.head;

	for (; i != nullptr; i = i->next)
	{
		if (i->data > max)
			max = i->data;
	}
	return max;
}

void choiceSort(dualList& list, dualList& result)
{
	Node* i = list.head;

	for (; i != nullptr; i = i->next)
	{
		int max = maxElement(list);
		eraseKey(list, max);
		pushBack(result, max);
	}
}

dualList mice(dualList& list, int N, int M, int K, int L, int s)
{
	for (; N + M > list.size;)
	{
		if (M > L)
		{
			for (size_t i = 0; i < M && N + M > list.size&& L < M; i += s, L++)
				insert(list, i, 0);
		}
		if (N > K)
		{
			for (size_t i = 0; i < N && N + M > list.size && K < N; i += s, K++)
				insert(list, i, 1);
		}
	}
	return list;
}