#pragma once
#include "IntVector.h"


class SortedintVector//组合IntVector
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
	bool Binary(int x); int BinarySearch(int, int, int);//递归实现 bool封装int
	bool Binary2(int x);//二分迭代实现  要求数组有序
	/*环形数组都是以递增环形数组为例*/
	bool CircularBinaryNoRepeat(int x);//迭代实现
	bool CircularBinaryRepeat(int x); int CircularBinaryRepeat2(int lo,int hi,int x);//递归实现 bool封装int
	int CircularBinaryFindMin();//递归实现
private:
	IntVector m_vec;
};