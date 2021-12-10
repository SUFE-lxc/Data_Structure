#pragma once
#include <iostream>
using namespace std;
class IntVector
{
public:
	IntVector();
	IntVector(initializer_list<int> list);//�б��ʼ��
	~IntVector() { Reset(); }
	//��̬����Ҫ���ƹ��캯���͸�ֵ���������
	IntVector& operator=(const IntVector&);
	IntVector(const IntVector&);

	void Insert(int idx, int val);
	void Delete(int idx);
	void Resize(int sz, int val = 0);//�������������С
	void Reserve(int cap);//�������Ŀռ�
	void InsertHead(int val) { Insert(0, val); }
	void InsertEnd(int val) { Insert(m_size, val); }

	int Size() const { return m_size; }
	int& At(int idx) {return m_data[idx]; }
	int& operator[](int idx) { return m_data[idx]; }
	const int& operator[](int idx) const { return m_data[idx]; }
	friend ostream& operator<<(ostream& out, const IntVector& arr);

private:
	void Reset();//�ͷ�ռ�õĶ�̬�ڴ�
	
	int* m_data;
	int m_size;
	int m_capacity;//max
};