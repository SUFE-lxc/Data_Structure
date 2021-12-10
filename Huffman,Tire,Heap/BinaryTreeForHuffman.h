#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

struct Node
{
    int key;     // binarytree node key or huffman symbol frequency
    char symbol; // huffman symbol
    Node* left;
    Node* right;
    Node(int val) : key(val), symbol(0), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
public:
    // Build a binary tree based on preorder and inorder array
    BinaryTree(const vector<int>& preorder, const vector<int>& inorder);
    BinaryTree(const vector<char>& symbols, const vector<int>& freq);

    // Release tree memory recursively
    ~BinaryTree() { Reset(); }

    // Copy a tree structure, not pointer.
    BinaryTree(const BinaryTree& other);
    // Implement assigment overloading, the same as copy constructor
    BinaryTree& operator=(const BinaryTree& rhs);

   
    string Encode(string txt);
    string Decode(string binary);

    // implement iterative version of traversals.
    void LevelOrder();
    void PreOrder_Iterative();
    void InOrder_Iterative();
    void PostOrder_Iterative();

    void Reset();
    void FindCodes();
    vector<string> GetAllPaths();
private:
    void Release(Node* root);
    Node* Clone(const Node* root);
    Node* BuildTree_Iterative(
        const vector<int>& preorder,
        const vector<int>& inorder);
    Node* BuildTree(
        const vector<int>& preorder, int pre,
        const vector<int>& inorder, int lh, int rh);

    void GetAllPaths(Node* root, string pathTillNow, vector<string>& result, string);
    
    void FindCodes(Node* root, string path, map<char, string>& output);

    Node* m_root;
};
