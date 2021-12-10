#pragma once
#include <iostream>
#include <cassert>
using namespace std;

class IntStack
{
public:
	IntStack() :m_top(0) {}

	inline bool IsEmpty() { return m_top <= 0; }

	int peek()
	{
		assert(m_top > 0);
		return m_data[m_top - 1];
	}
	void push(int i)
	{
		assert(m_top < 100);
		m_data[m_top++] = i;
	}
	void pop()
	{
		assert(m_top > 0);
		m_top--;
	}
	
	int EvaluatePostfix(const string& expression);//后缀表达式的计算
	string ConvertToPostfix(const string& infix);//调度场算法
private:
	int m_data[100];
	int m_top;
};