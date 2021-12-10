#pragma once
#include "IntVector.h"


class SortedintVector//���IntVector
{
public:
	SortedintVector() {}
	SortedintVector(initializer_list<int> list) : m_vec(list) {}
	
	void Delete(int idx) { m_vec.Delete(idx); }
	void Insert(int idx, int val) { m_vec.Insert(idx, val); }
	void Resize(int sz, int val = 0) { m_vec.Resize(sz, val); }
	void Reserve(int cap) { m_vec.Reserve(cap); }
	int Size() const { return m_vec.Size(); }
	//int Capacity() const { return m_vec.m_Capacity(); }
	int& operator[](int idx) { return m_vec[idx]; }
	const int& operator[](int idx) const { return m_vec[idx]; }
	
	void MergeSort();void Merge(SortedintVector&,SortedintVector&);
	void QuickSort(int start,int end); int Partition(int start,int end);
	void InsertionSort();
	void SelectionSort();
	bool Binary(int x); int BinarySearch(int, int, int);//�ݹ�ʵ�� bool��װint
	bool Binary2(int x);//���ֵ���ʵ��  Ҫ����������
	/*�������鶼���Ե�����������Ϊ��*/
	bool CircularBinaryNoRepeat(int x);//����ʵ��
	bool CircularBinaryRepeat(int x); int CircularBinaryRepeat2(int lo,int hi,int x);//�ݹ�ʵ�� bool��װint
	int CircularBinaryFindMin();//�ݹ�ʵ��
private:
	IntVector m_vec;
};