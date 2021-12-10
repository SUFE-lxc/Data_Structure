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
	Mystring();//构造空字符串
	Mystring(const char* szStr);
	~Mystring() { Reset(); }
	
	Mystring(const Mystring& other);//复制构造函数
	Mystring& operator =(const Mystring& rhs);//赋值运算符重载
	
	Mystring& Substring(int,int);//返回某个子串
	Mystring& Append(const Mystring& str);//尾后插入
	//当函数返回引用类型时没有复制返回值,返回的是对象本身。
	//！！因此也不能返回局部变量的引用或者指向局部变量的指针(会自动释放
	Mystring& operator+=(const Mystring& rhs);
	Mystring operator+(const Mystring& rhs);//返回一个新字符串 因此无须设置成返回引用类型
	int operator==(const Mystring& str) const;//比较两个字符串
	
	void Resize(int sz, char c = '\0');
	void Reserve(int cap);
	
	bool Insert(int idx, const char* szStr);
	bool Insert(int  idx, const Mystring& str) {return Insert(idx, str.Data()); }
	void Remove(int idx, int len);//删除从某个元素开始的固定长度的元素
	
	char& operator[](int idx) { return m_data[idx]; }
	const char& operator[](int idx) const { return m_data[idx]; }
	const char* Data() const { return m_data; }

	inline int Length() const { return m_size - 1; }
	inline bool IsEmpty() const { return Length() <= 0 || m_data == nullptr; }

	friend ostream& operator<<(ostream& out, const Mystring& str);
	friend Mystring& operator>>(istream& in,Mystring& str);

	Mystring& Inverse();//翻转单词次序
	Mystring& MaxPalindromePre();//输出最长回文前缀
	

	//匹配算法
	int FindBasic(const Mystring& pattern) const;
	
	int FindKR(const Mystring& pattern) const;//需要哈希函数
	
	long Hashing(int len) const; long ReHashing(long hashing, int a, int b, int offset) const; 
	bool Check(const char*,const char*, int) const;
	
	int FindKMP(const Mystring& pattern) const; 
	vector<int> GetNext(const char*, int) const;//KMP附带的next表
	
	int FindBM(const Mystring& pattern) const;
	vector<int> GetBadCharTable(const char*, int) const;//坏字符规则表
	vector<int> GetSuffixTable(const char*, int) const;//与pattern后缀匹配的最长子串
	vector<int> GetGoodSuffixTable(const char*, int) const;//好后缀规则表

private:
	void Reset();
	
	char* m_data;
	int m_capacity;
	int m_size;
};