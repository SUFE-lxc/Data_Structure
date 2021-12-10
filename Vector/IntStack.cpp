#include "IntStack.h"

int IntStack::EvaluatePostfix(const string& expression)
{
	for (int i = 0; i < expression.size(); ++i) {
		int ch = expression[i];
		if (isspace(ch)) {
			continue;
		}
		if (isdigit(ch)) {
			int val = ch - '0';
			while (i + 1 < expression.size() && isdigit(expression[i + 1]))
				val = val * 10 + expression[++i] - '0';
			push(val);//²Ù×÷ÊýÈëÕ»
			continue;
		}
		int op2 = peek(); pop();
		int op1 = peek(); pop();
		switch (ch)
		{
		case '+':
			push(op1 + op2);
			break;
		case '-':
			push(op1 - op2);
			break;
		case '*':
			push(op1 * op2);
			break;
		case '/' :
			push(op1 / op2);
			break;
		case '^' :
			{	
				int val = 1;
				for (int j = 0; j < op2; ++j)
					val *= op1;
				push(val);
				break;
			}
		default:
			assert(false);
			break;
		}
	}
	return peek();
}
