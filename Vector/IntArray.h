#include <iostream>
#include <cassert>
#include <iterator>
 
class IntArray//动态数组的封装
{
public:
	IntArray(int size);//自定义构造函数
	~IntArray();//析构函数 即使用完后会销毁 ATTENTION！

	int Size() const { return m_size; }
	int& operator[](int idx) { return m_data[idx]; }
	const int& operator[](int idx) const { return m_data[idx]; }

private:
	int* m_data;
	int m_size;
	//禁止赋值运算符重载和复制构造函数(common) 先写在private中需要时再调用
	IntArray(const IntArray& other);
	IntArray& operator=(const IntArray& rhs) {
		//已存在的对象才可以使用赋值运算符
		//self check
		if (this == &rhs) return *this;//返回它自己
		if (m_data) delete[] m_data;//分配内存时先释放
		m_size = rhs.m_size; m_data = new int [m_size] {0};
		for (int i = 0; i < m_size; i++)
			m_data[i] = rhs[i];
		return *this;
	}
};
IntArray::IntArray(int size)
{
	assert(size > 0); m_size = size;
	m_data = new int[size] {0};//创立并赋值给私有成员
}
IntArray::~IntArray()
{
	delete[] m_data;//释放空间
}
IntArray::IntArray(const IntArray& other)//复制构造函数 当创建一个新变量时使用
{
	m_size = other.m_size;
	m_data = new int [m_size] {0};
	for (int i = 0; i < m_size; i++)
		m_data[i] = other[i];
}


