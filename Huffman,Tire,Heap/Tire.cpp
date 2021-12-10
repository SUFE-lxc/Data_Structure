#include "Tire.h"

bool Tire::Serach(const char* szKey)
{
	int length = strlen(szKey);
	TireNode* node = this->m_root;//获取根节点

	for (int i = 0; i < length && node; ++i) {//节点不存在则直接退出
		int idx = szKey[i] - 'a';
		node = node->children[idx];//往下一个节点

		return node && node->isKeyEnd;//节点存在且为keyend
	}
}

void Tire::Insert(const char* szKey)
{
	int length = strlen(szKey);
	TireNode* node = this->m_root;//获取根节点

	for (int i = 0; i < length; ++i) {
		int idx = szKey[i] - 'a';
		if (!node->children[idx])//不存在这个节点
			node->children[idx] = new TireNode();//就创造这个节点
		node = node->children[idx];//转到下一个节点
	}

	node->isKeyEnd = true;
}

void Tire::Delete(const char* seKey)
{
	
}

Tire::Tire(const Tire& other)
{

}

Tire Tire::operator=(const Tire& rhs)
{
	if (this == &rhs)
		return *this;
	Reset(m_root);
	m_root = rhs.m_root;
	return *this;
}

bool Tire::LeafNode(TireNode* node)
{
	for (int i = 1; i <= ALPHABET_SIZE; ++i) {
		if (node->children[i])
			return false;
	}
	return true;
}

void Tire::Break(TireNode* parent, TireNode* child)
{

}

void Tire::Reset(TireNode* node)
{
	if (node == nullptr)
		return;
	for (int i = 1; i <= ALPHABET_SIZE; ++i) {
		if (node->children[i]) 
			Reset(node->children[i]);//递归删除
		delete node;
	}
}
