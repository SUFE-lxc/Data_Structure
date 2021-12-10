#include "Tire.h"

bool Tire::Serach(const char* szKey)
{
	int length = strlen(szKey);
	TireNode* node = this->m_root;//��ȡ���ڵ�

	for (int i = 0; i < length && node; ++i) {//�ڵ㲻������ֱ���˳�
		int idx = szKey[i] - 'a';
		node = node->children[idx];//����һ���ڵ�

		return node && node->isKeyEnd;//�ڵ������Ϊkeyend
	}
}

void Tire::Insert(const char* szKey)
{
	int length = strlen(szKey);
	TireNode* node = this->m_root;//��ȡ���ڵ�

	for (int i = 0; i < length; ++i) {
		int idx = szKey[i] - 'a';
		if (!node->children[idx])//����������ڵ�
			node->children[idx] = new TireNode();//�ʹ�������ڵ�
		node = node->children[idx];//ת����һ���ڵ�
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
			Reset(node->children[i]);//�ݹ�ɾ��
		delete node;
	}
}
