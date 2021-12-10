#pragma once
#include <iostream>
#include<vector>
#include <cassert>
#include <stack>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	Node(int val) :key(val), left(nullptr), right(nullptr) {}
};
class BinaryTree {
public:
	BinaryTree(const vector<int>& preorder, const vector<int>& inorder);
	~BinaryTree() { Reset(); }

	BinaryTree(const BinaryTree& other);//copy constructor
	BinaryTree& operator=(const BinaryTree& rhs);//=

	//������������
	Node* ConvertToThreaded(Node* root);

	//�����㷨
	void LevelOrder();
	void PreOrder();
	void InOrder();
	void PostOrder();

	void Reset();

	string FindPathBetweenRootAndNode(Node* node);
	void DeepLeaf(Node* outLeaf);//����Ҷ�ڵ�
	void DeepLeftLeaf(Node* outLeaf);//������Ҷ�ڵ�
	vector<string> GetAllPaths();//���ڵ㵽����Ҷ�ڵ��·��
	int maxPathsum();//��������·�������ֵ

	//Ѱ����С��ͬ���ڵ�
	string FindLeastCommonAncestor(Node* node1, Node* node2);
	Node* FindLeastCommonAncestorByRecursion(Node* node1, Node* node2);
	Node* FindLeastCommonAncestorByRecursion(Node* node, Node* node1, Node* node2);

private:
	void Release(Node* root);

	Node* Clone(const Node* root);

	Node* BuildTree_Iterative(const vector<int>& preorder, const vector<int>& inorder);
	Node* BuildTree(const vector<int>& preorder, int pre, const vector<int>& inorder, int lh, int rh);

	void DeepLeaf(Node* root, int lvl, int* maxDepth, Node* outLeaf);
	void DeepLeftLeaf(Node* root, bool isleft, int lvl, int* maxDepth, Node* outLeaf);
	void GetAllPaths(Node* root, string pathTillNow, vector<string>* result);
	int maxPathsum(Node* node, int& maxValue);

	Node* Leftmost(Node* root);//��most�ڵ�
	Node* FindMin(Node* root);//��Сֵ�ڵ�

	//�������㷨
	Node* Search(Node* node, int x);//��node��ʼ����
	Node* Search(int x) { return Search(m_root, x); }//����
	Node* Insert(Node* node, int x);//����
	Node* Insert(int x) { return Insert(m_root, x); }
	Node* Delete(Node* node, int x);
	Node* Delete(int x) { return Delete(m_root, x); }

	Node* m_root;
};