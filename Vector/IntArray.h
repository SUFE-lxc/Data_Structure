#include <iostream>
#include <cassert>
#include <iterator>
 
class IntArray//��̬����ķ�װ
{
public:
	IntArray(int size);//�Զ��幹�캯��
	~IntArray();//�������� ��ʹ���������� ATTENTION��

	int Size() const { return m_size; }
	int& operator[](int idx) { return m_data[idx]; }
	const int& operator[](int idx) const { return m_data[idx]; }

private:
	int* m_data;
	int m_size;
	//��ֹ��ֵ��������غ͸��ƹ��캯��(common) ��д��private����Ҫʱ�ٵ���
	IntArray(const IntArray& other);
	IntArray& operator=(const IntArray& rhs) {
		//�Ѵ��ڵĶ���ſ���ʹ�ø�ֵ�����
		//self check
		if (this == &rhs) return *this;//�������Լ�
		if (m_data) delete[] m_data;//�����ڴ�ʱ���ͷ�
		m_size = rhs.m_size; m_data = new int [m_size] {0};
		for (int i = 0; i < m_size; i++)
			m_data[i] = rhs[i];
		return *this;
	}
};
IntArray::IntArray(int size)
{
	assert(size > 0); m_size = size;
	m_data = new int[size] {0};//��������ֵ��˽�г�Ա
}
IntArray::~IntArray()
{
	delete[] m_data;//�ͷſռ�
}
IntArray::IntArray(const IntArray& other)//���ƹ��캯�� ������һ���±���ʱʹ��
{
	m_size = other.m_size;
	m_data = new int [m_size] {0};
	for (int i = 0; i < m_size; i++)
		m_data[i] = other[i];
}


