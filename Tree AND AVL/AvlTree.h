#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;
struct Node
{
	int key;
	int height;
	Node* left;
	Node* right;
	Node(int val) : key(val), height(0), left(nullptr), right(nullptr) {}
};

class AvlTree
{
public:
	// Build a binary tree based on preorder and inorder array
	AvlTree(const std::vector<int>& preorder, const std::vector<int>& inorder);

	// Release tree memory recursively
	~AvlTree() { Reset(); }

	// Copy a tree structure, not pointer.
	AvlTree(const AvlTree& other);
	// Implement assigment overloading, the same as copy constructor
	AvlTree& operator=(const AvlTree& rhs);

	Node* Search(int x) { return Search(m_root, x); }
	void Insert(int x) { m_root = Insert(m_root, x); }
	void Delete(int x) { m_root = Delete(m_root, x); }

	// implement iterative version of traversals.
	void LevelOrder();
	void PreOrder_Iterative();
	void InOrder_Iterative();
	void PostOrder_Iterative();

	void Reset();

private:
	void Release(Node* node);
	Node* Clone(const Node* node);
	Node* BuildTree_Iterative(const vector<int>& preorder, const vector<int>& inorder);
	Node* BuildTree(const vector<int>& preorder, int pre, const vector<int>& inorder, int lh, int rh);

	int Height(Node* node);
	int GetBalance(Node* node);
	Node* FindMin(Node* node);
	Node* FindMax(Node* node);
	Node* Search(Node* node, int x);
	Node* Insert(Node* node, int x);
	Node* Delete(Node* node, int x);

	Node* RightRotate(Node* node);
	Node* LeftRotate(Node* node);
	Node* RightLeftRotate(Node* node);
	Node* LeftRightRotate(Node* node);

	Node* m_root;
};

