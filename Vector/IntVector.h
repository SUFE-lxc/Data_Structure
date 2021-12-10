#pragma once
#include <iostream>
using namespace std;
class IntVector
{
public:
	IntVector();
	IntVector(initializer_list<int> list);//列表初始化
	~IntVector() { Reset(); }
	//动态数组要求复制构造函数和赋值运算符重载
	IntVector& operator=(const IntVector&);
	IntVector(const IntVector&);

	void Insert(int idx, int val);
	void Delete(int idx);
	void Resize(int sz, int val = 0);//重新设置数组大小
	void Reserve(int cap);//申请更大的空间
	void InsertHead(int val) { Insert(0, val); }
	void InsertEnd(int val) { Insert(m_size, val); }

	int Size() const { return m_size; }
	int& At(int idx) {return m_data[idx]; }
	int& operator[](int idx) { return m_data[idx]; }
	const int& operator[](int idx) const { return m_data[idx]; }
	friend ostream& operator<<(ostream& out, const IntVector& arr);

private:
	void Reset();//释放占用的动态内存
	
	int* m_data;
	int m_size;
	int m_capacity;//max
};