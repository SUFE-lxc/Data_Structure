#pragma once
#include <iostream>
#include <stack>

using namespace std;

#define ALPHABET_SIZE  26

struct TireNode
{
	bool isKeyEnd;
	TireNode* children[ALPHABET_SIZE];
	TireNode() : isKeyEnd(false), children{ nullptr }{}
};
class Tire
{
public:
	Tire():m_root(new TireNode()) {}
	~Tire() { Reset(m_root); }

	bool Serach(const char* szKey);
	void Insert(const char* szKey);
	void Delete(const char* szKey);
private:
	Tire(const Tire& other);
	Tire operator=(const Tire& rhs);

	bool LeafNode(TireNode* nd);
	void Break(TireNode* parent, TireNode* child);
	void Reset(TireNode* nd);

	TireNode* m_root;
};