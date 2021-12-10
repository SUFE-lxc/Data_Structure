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

	//线索化二叉树
	Node* ConvertToThreaded(Node* root);

	//遍历算法
	void LevelOrder();
	void PreOrder();
	void InOrder();
	void PostOrder();

	void Reset();

	string FindPathBetweenRootAndNode(Node* node);
	void DeepLeaf(Node* outLeaf);//最深叶节点
	void DeepLeftLeaf(Node* outLeaf);//最深左叶节点
	vector<string> GetAllPaths();//根节点到所有叶节点的路径
	int maxPathsum();//任意两点路径和最大值

	//寻找最小共同父节点
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

	Node* Leftmost(Node* root);//左most节点
	Node* FindMin(Node* root);//最小值节点

	//二叉树算法
	Node* Search(Node* node, int x);//从node开始查找
	Node* Search(int x) { return Search(m_root, x); }//遍历
	Node* Insert(Node* node, int x);//插入
	Node* Insert(int x) { return Insert(m_root, x); }
	Node* Delete(Node* node, int x);
	Node* Delete(int x) { return Delete(m_root, x); }

	Node* m_root;
};