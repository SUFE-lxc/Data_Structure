#pragma on
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <cassert>
#include <string.h>
using namespace std;
const int Prime = 1000007;
class Mystring
{
public:
	Mystring();//������ַ���
	Mystring(const char* szStr);
	~Mystring() { Reset(); }
	
	Mystring(const Mystring& other);//���ƹ��캯��
	Mystring& operator =(const Mystring& rhs);//��ֵ���������
	
	Mystring& Substring(int,int);//����ĳ���Ӵ�
	Mystring& Append(const Mystring& str);//β�����
	//������������������ʱû�и��Ʒ���ֵ,���ص��Ƕ�����
	//�������Ҳ���ܷ��ؾֲ����������û���ָ��ֲ�������ָ��(���Զ��ͷ�
	Mystring& operator+=(const Mystring& rhs);
	Mystring operator+(const Mystring& rhs);//����һ�����ַ��� ����������óɷ�����������
	int operator==(const Mystring& str) const;//�Ƚ������ַ���
	
	void Resize(int sz, char c = '\0');
	void Reserve(int cap);
	
	bool Insert(int idx, const char* szStr);
	bool Insert(int  idx, const Mystring& str) {return Insert(idx, str.Data()); }
	void Remove(int idx, int len);//ɾ����ĳ��Ԫ�ؿ�ʼ�Ĺ̶����ȵ�Ԫ��
	
	char& operator[](int idx) { return m_data[idx]; }
	const char& operator[](int idx) const { return m_data[idx]; }
	const char* Data() const { return m_data; }

	inline int Length() const { return m_size - 1; }
	inline bool IsEmpty() const { return Length() <= 0 || m_data == nullptr; }

	friend ostream& operator<<(ostream& out, const Mystring& str);
	friend Mystring& operator>>(istream& in,Mystring& str);

	Mystring& Inverse();//��ת���ʴ���
	Mystring& MaxPalindromePre();//��������ǰ׺
	

	//ƥ���㷨
	int FindBasic(const Mystring& pattern) const;
	
	int FindKR(const Mystring& pattern) const;//��Ҫ��ϣ����
	
	long Hashing(int len) const; long ReHashing(long hashing, int a, int b, int offset) const; 
	bool Check(const char*,const char*, int) const;
	
	int FindKMP(const Mystring& pattern) const; 
	vector<int> GetNext(const char*, int) const;//KMP������next��
	
	int FindBM(const Mystring& pattern) const;
	vector<int> GetBadCharTable(const char*, int) const;//���ַ������
	vector<int> GetSuffixTable(const char*, int) const;//��pattern��׺ƥ�����Ӵ�
	vector<int> GetGoodSuffixTable(const char*, int) const;//�ú�׺�����

private:
	void Reset();
	
	char* m_data;
	int m_capacity;
	int m_size;
};