#pragma once
#include <iostream>
#include <cassert>
#include <iterator>
using namespace std;
//������
struct Node
{
	int key;
	Node* next;
	Node(int val) :key(val), next(nullptr) {}//����
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
	Node* Search(int val);//����
	Node* Insert(Node* node, int val);
	Node* FindLast();
	bool Delete(Node* node);
	bool HasCycle();
	void Reverse(List &list);
	friend ostream& operator<<(ostream& out, const List& list);
};
