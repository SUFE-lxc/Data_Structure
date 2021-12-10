#include "IntVector.h"

IntVector::IntVector():m_size{0},m_capacity{16}
{
	m_data = new int [m_capacity] {0};
}
IntVector::IntVector(initializer_list<int> list)//列表初始化
{
	m_size = list.size();//确定大小
	//与列表不同 数组为连续的空间 可以先确定大小 而链表需要不断迭代来创建
	m_capacity = max(2 * m_size, 16);
	m_data = new int [m_capacity] {0};//初始化
	copy(list.begin(), list.end(), m_data);//使用迭代器直接复制
}
void IntVector::Reset()
{//释放内存 私有成员归零
	if (m_data) {
		delete[] m_data;
		m_data = nullptr;
		m_size = m_capacity = 0;
	}
}
void IntVector::Reserve(int cap)
{
	if (cap > m_capacity) {//cap>最大容量才能扩容
	    int sz = m_size;	
	    int* data = new int[cap];//创建新数组
		if (data) {//data存在
			for (int i = 0; i < sz; ++i)
				data[i] = m_data[i];
		}
		Reset();//清除所有私有变量
		m_data = data; m_size = sz; m_capacity = cap;//重置私有变量
	}
}
IntVector::IntVector(const IntVector& vec):m_data(nullptr),m_size(0),m_capacity(0)
{
	m_capacity = vec.m_capacity;
	m_size = vec.m_size;
	m_data = new int[m_capacity] {0};
	for (int i = 0; i < m_size;i++)
		m_data[i] = vec[i];
}
IntVector& IntVector::operator=(const IntVector& vec)//类型名放在最前面
{//赋值运算符用于已存在对象的赋值，所以要先检查运算符左右是否相等，容量大小，并且先释放左边
	if(this == &vec)//相等的特殊情况
		return *this;
	if (m_capacity < vec.m_size)//最大容量小于size
		Reserve(vec.m_capacity);//扩大对象的容量（is not vec）
	m_size = vec.m_size;//更新m_size
	if (m_data) delete[] m_data;
	m_data = new int[m_capacity];
	for (int i = 0; i < m_size; i++)
		m_data[i] = vec[i];
	return *this;
}
ostream& operator<<(ostream& out,const IntVector& vec)
{
	int i = vec.m_size;
	int* p = vec.m_data;
	if (i == 0 || p == nullptr) return out;
	for (int j = 0; j < i; j++)
		out << p[i];
	return out;
}
void IntVector::Resize(int sz, int val)//定义时有默认参数后在函数的定义时不可再写成赋值参数形式：int val = 1(error)
{
	if (sz > 0) {
		Reserve(sz);//如果小于capacity 则无用，如果大于capcity则扩大数组
		for (int i = m_size; i < sz; i++)//如果sz<m_size 则直接跳过循环，下面直接切掉sz后面的元素即可
			m_data[i] = val;//从最后一个元素开始赋值，但只用于用于扩大数组的情况
		m_size = sz;//最终确定m_size
	}	
}
void IntVector::Insert(int idx, int val)
{
	if (m_size == m_capacity) {//容量不足以再插入
		int* p = m_data;//创建一个新数组 并记录原指针的地址以便后面进行复制
		m_data = new int[m_capacity << 1];//重新分配内存
		for (int i = 0; i < m_size; i++)
			m_data[i] = p[i];
		Reserve(m_capacity << 1);
		delete p;//用完清理
	}
	if (m_size < m_capacity)
	{ //size比capacity小 容量够
		if (idx < m_size && idx >= 0)
		{//idx不大于size                                           
			for (int i = m_size; i >= idx + 1; --i) //向后移动，从后往前迁移元素，以防覆盖
				m_data[i] = m_data[i - 1];
			m_data[idx] = val;
			m_size = m_size + 1;     //size扩大1
		}
		if (idx == m_size)
			Resize(m_size + 1, val);
	}
}
void IntVector::Delete(int idx)
{
	if (idx > 0 && idx < m_size-1) {//存在这个元素并且不在最后
		for (int i = idx; i < m_size; i++)//向前移动，从前往后迁移元素，以防覆盖
			m_data[i] = m_data[i + 1];
	}
	m_size = m_size - 1;	//元素数量-1
	//无须处理idx为尾元素的情况，类似于Resize函数中sz<m_size时，直接缩小m_size即可斩断
}