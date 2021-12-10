#pragma once
#include <iostream>
#include <cassert>
#include <iterator>
using namespace std;
//单链表
struct Node
{
	int key;
	Node* next;
	Node(int val) :key(val), next(nullptr) {}//构造
};
class List
{
private:
	List(const List& other);
	List& operator=(const List rhs);//forbidden

	Node* m_head;
public:
	List(const initializer_list<int>& list);
	~List();
	Node* Search(int val);//查找
	Node* Insert(Node* node, int val);
	Node* FindLast();
	bool Delete(Node* node);
	bool HasCycle();
	void Reverse(List &list);
	friend ostream& operator<<(ostream& out, const List& list);
};
