#include "IntVector.h"

IntVector::IntVector():m_size{0},m_capacity{16}
{
	m_data = new int [m_capacity] {0};
}
IntVector::IntVector(initializer_list<int> list)//�б��ʼ��
{
	m_size = list.size();//ȷ����С
	//���б�ͬ ����Ϊ�����Ŀռ� ������ȷ����С ��������Ҫ���ϵ���������
	m_capacity = max(2 * m_size, 16);
	m_data = new int [m_capacity] {0};//��ʼ��
	copy(list.begin(), list.end(), m_data);//ʹ�õ�����ֱ�Ӹ���
}
void IntVector::Reset()
{//�ͷ��ڴ� ˽�г�Ա����
	if (m_data) {
		delete[] m_data;
		m_data = nullptr;
		m_size = m_capacity = 0;
	}
}
void IntVector::Reserve(int cap)
{
	if (cap > m_capacity) {//cap>���������������
	    int sz = m_size;	
	    int* data = new int[cap];//����������
		if (data) {//data����
			for (int i = 0; i < sz; ++i)
				data[i] = m_data[i];
		}
		Reset();//�������˽�б���
		m_data = data; m_size = sz; m_capacity = cap;//����˽�б���
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
IntVector& IntVector::operator=(const IntVector& vec)//������������ǰ��
{//��ֵ����������Ѵ��ڶ���ĸ�ֵ������Ҫ�ȼ������������Ƿ���ȣ�������С���������ͷ����
	if(this == &vec)//��ȵ��������
		return *this;
	if (m_capacity < vec.m_size)//�������С��size
		Reserve(vec.m_capacity);//��������������is not vec��
	m_size = vec.m_size;//����m_size
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
void IntVector::Resize(int sz, int val)//����ʱ��Ĭ�ϲ������ں����Ķ���ʱ������д�ɸ�ֵ������ʽ��int val = 1(error)
{
	if (sz > 0) {
		Reserve(sz);//���С��capacity �����ã��������capcity����������
		for (int i = m_size; i < sz; i++)//���sz<m_size ��ֱ������ѭ��������ֱ���е�sz�����Ԫ�ؼ���
			m_data[i] = val;//�����һ��Ԫ�ؿ�ʼ��ֵ����ֻ��������������������
		m_size = sz;//����ȷ��m_size
	}	
}
void IntVector::Insert(int idx, int val)
{
	if (m_size == m_capacity) {//�����������ٲ���
		int* p = m_data;//����һ�������� ����¼ԭָ��ĵ�ַ�Ա������и���
		m_data = new int[m_capacity << 1];//���·����ڴ�
		for (int i = 0; i < m_size; i++)
			m_data[i] = p[i];
		Reserve(m_capacity << 1);
		delete p;//��������
	}
	if (m_size < m_capacity)
	{ //size��capacityС ������
		if (idx < m_size && idx >= 0)
		{//idx������size                                           
			for (int i = m_size; i >= idx + 1; --i) //����ƶ����Ӻ���ǰǨ��Ԫ�أ��Է�����
				m_data[i] = m_data[i - 1];
			m_data[idx] = val;
			m_size = m_size + 1;     //size����1
		}
		if (idx == m_size)
			Resize(m_size + 1, val);
	}
}
void IntVector::Delete(int idx)
{
	if (idx > 0 && idx < m_size-1) {//�������Ԫ�ز��Ҳ������
		for (int i = idx; i < m_size; i++)//��ǰ�ƶ�����ǰ����Ǩ��Ԫ�أ��Է�����
			m_data[i] = m_data[i + 1];
	}
	m_size = m_size - 1;	//Ԫ������-1
	//���봦��idxΪβԪ�ص������������Resize������sz<m_sizeʱ��ֱ����Сm_size����ն��
}