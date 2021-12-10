#pragma once
#include <vector>
#include "BinarytreeForHuffman.h"

class Heap
{
public:
	Heap() { m_data.push_back(NULL); }

	//ȥ����Сֵ
	Node* ExtractMin();

	// ����
	void InsertKey(Node* nd);

	bool IsEmpty() { return m_data.size() <= 1; }
	int Size() { return m_data.size() - 1; }

private:
	//ά�������(recursive)
	void MinHeapify(int i);

	int Parent(int i) { return i / 2; }
	int Left(int i) { return 2 * i; }
	int Right(int i) { return (2 * i + 1); }

	vector<Node*> m_data;
};
