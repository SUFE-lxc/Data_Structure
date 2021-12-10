#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cassert>
#include "Heap.h"
#include "binarytreeForHuffman.h"
using namespace std;

BinaryTree::BinaryTree(const vector<int>& preorder, const vector<int>& inorder)
{
    if (preorder.size() != inorder.size())
    {
        cout << "Invalid size" << endl;
        return;
    }

    m_root = BuildTree_Iterative(preorder, inorder);
}

BinaryTree::BinaryTree(const vector<char>& symbols, const vector<int>& freq) : m_root(nullptr)
{
    Heap minheap;
    auto it1 = symbols.cbegin();
    auto it2 = freq.cbegin();
    while (it1 != symbols.cend() && it2 != freq.cend()) {//һһ��Ӧ
        Node* temp = new Node(*it2);
        temp->symbol = *it1;
        ++it1; ++it2;//������
        minheap.InsertKey(temp);//���
    }//�������

     //ʹ��heap���й���
    while (minheap.Size() >= 2) {//��ֻ��һ���ڵ�ʱ˵�������������˳�ѭ��
        Node* min1 = minheap.ExtractMin();
        Node* min2 = minheap.ExtractMin();//����ȡ��������С�ڵ� ��1<2
        Node* min = new Node(min1->key + min2->key);//���кϲ�
        min->symbol = '.';
        min->left = min1; min->right = min2;//����
        if (minheap.Size() != 0)//��minΪ���ڵ�ʱ��������˹����������ڷ����
            minheap.InsertKey(min);
        else m_root = min;//��ʱ�Ѿ��ϲ����,����˽�б���
    }
}

BinaryTree::BinaryTree(const BinaryTree& other)
    : m_root(nullptr)
{
    m_root = Clone(other.m_root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Reset();
    m_root = Clone(rhs.m_root);

    return *this;
}
void BinaryTree::FindCodes()
{//��װ
    map<char, string> Map;
    FindCodes(m_root, "", Map);
}
void BinaryTree::FindCodes(Node* root, string path, map<char, string>& output)
{
 //���������������������·������˶�Ӧ���޸İ�GetAllPaths����������ȡ���ڵ㵽Ҷ�ӽڵ��·��

    vector<string> result = GetAllPaths();//����·��
    size_t i = 0;
    while (i < result.size()) {
        string path = result[i];
        char symbol = path[path.size() - 1];//���
        path.pop_back();//ȥ����� 
        output[symbol] = path;//��¼
        i++;//ת����һ��·��
    }
}

//�¼ӵ�GetAllPath����
vector<string> BinaryTree::GetAllPaths()
{//��װ:�Ӹ��ڵ㿪ʼ
    vector<string> result = {};//��������
    GetAllPaths(m_root, "", result, "");//��������һ��string����,����huff����
    return result;
}
void BinaryTree::GetAllPaths(Node* root, string pathTillNow, vector<string>& result, string s)
{//�ڵ�root������Ҷ�ӽڵ��·��
 //result�Ľ��ԭ����key��� ���ڻ���huff��0 1���� 
    if (root) {
        pathTillNow += s;//����huff����
        if (!root->left && !root->right) {
            pathTillNow += root->symbol;//�ַ������һλ��Ϊ���
            result.push_back(pathTillNow);
        }
        else {
            GetAllPaths(root->left, pathTillNow, result, "0");
            GetAllPaths(root->right, pathTillNow, result, "1");
        }
    }
    else return;
}

string BinaryTree::Encode(string txt)
{
    string strbin = "";
    map<char, string> Map;
    FindCodes(m_root, "", Map);//��ø����ַ���Ӧ��huffcode
    auto it0 = txt.begin();
    while (it0 != txt.end()) {
        char symbol = *it0;//��ȡ��ĸ
        strbin += Map[symbol];//huffcode������
        ++it0;
    }
    return strbin;
}

string BinaryTree::Decode(string binary)
{
    string strtxt;
    Node* node = m_root;
    string temp = "";//����
    map<char, string> Map;
    FindCodes(m_root, "", Map);//��ø����ַ���Ӧ��huffcode
    for (size_t i = 0; i <= binary.size(); ++i) {
        if (!node->left && !node->right)//hufftreeһ������������
        {//����Ҷ�ӽڵ�
            for (auto it = Map.begin(); it != Map.end(); ++it) {//ͨ��valueѰ��key
                if (it->second == temp)
                {
                    strtxt += it->first;//�ҵ�������strtxt
                    break;
                }
            }
            node = m_root;//�ص����ڵ�
            temp = "";//����
        }
        if (i < binary.size()) {//ȷ����Խ��
            //Ϊ�˱�֤���һ��huff��decode�ɹ�,ѭ������������i����Խ��
            temp += binary[i];
            if (binary[i] == '0')
            {
                node = node->left;
                continue;
            }
            else
            {
                node = node->right;//0����1����
                continue;
            }
        }
    }
    return strtxt;
}

void BinaryTree::LevelOrder()
{
    queue<const Node*> treeQueue;

    if (m_root != nullptr)
    {
        treeQueue.push(m_root);
    }

    int size = 1;
    while (!treeQueue.empty())
    {
        const Node* node = treeQueue.front();
        treeQueue.pop();
        if (node)
        {
            cout << node->key << "," << node->symbol << " ";
            treeQueue.push(node->left);
            treeQueue.push(node->right);
        }
        else
        {
            cout << "$ ";
        }

        if (--size == 0)
        {
            cout << endl;
            size = treeQueue.size();
        }
    }
}

void BinaryTree::PostOrder_Iterative()
{
    if (m_root == nullptr)
    {
        return;
    }

    stack<const Node*> output;
    stack<const Node*> stk;
    stk.push(m_root);

    while (!stk.empty())
    {
        // Pop top element from stk;
        const Node* top = stk.top();
        stk.pop();

        // Push top element to output
        output.push(top);

        // push left and right node to stk;
        if (top->left != nullptr)
        {
            stk.push(top->left);
        }

        if (top->right != nullptr)
        {
            stk.push(top->right);
        }
    }

    // print result in output stack
    while (!output.empty())
    {
        cout << output.top()->key << " ";
        output.pop();
    }
    cout << endl;
}

void BinaryTree::InOrder_Iterative()
{
    stack<const Node*> stk;
    const Node* curr = m_root;

    while (!stk.empty() || curr)
    {
        while (curr)
        {
            stk.push(curr);
            curr = curr->left;
        }

        curr = stk.top();
        stk.pop();

        cout << curr->key << " ";
        curr = curr->right;
    }
    cout << endl;
}

void BinaryTree::PreOrder_Iterative()
{
    stack<const Node*> stk;
    if (m_root)
    {
        stk.push(m_root);
    }

    while (!stk.empty())
    {
        const Node* node = stk.top();
        stk.pop();

        cout << node->key << " ";

        if (node->right)
        {
            stk.push(node->right);
        }
        if (node->left)
        {
            stk.push(node->left);
        }
    }
    cout << endl;
}

void BinaryTree::Reset()
{
    Release(m_root);
    m_root = nullptr;
}

void BinaryTree::Release(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    Release(root->left);
    Release(root->right);
    delete root;
}

Node* BinaryTree::Clone(const Node* root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    Node* nd = new Node(root->key);
    nd->left = Clone(root->left);
    nd->right = Clone(root->right);

    return nd;
}

Node* BinaryTree::BuildTree(
    const vector<int>& preorder, int pre,
    const vector<int>& inorder, int lh, int rh)
{
    if (lh > rh)
    {
        return nullptr;
    }
    int key = preorder.at(pre);
    Node* root = new Node(key);

    int index = lh;
    for (; index <= rh; index++)
    {
        if (inorder.at(index) == key)
        {
            break;
        }
    }
    assert(index <= rh);

    root->left = BuildTree(preorder, pre + 1, inorder, lh, index - 1);
    root->right = BuildTree(preorder, index - lh + pre + 1, inorder, index + 1, rh);
    return root;
}

Node* BinaryTree::BuildTree_Iterative(
    const vector<int>& preorder, const vector<int>& inorder)
{
    assert(preorder.size() == inorder.size());
    // pre always points to inorder node, which is created next
    // in always points to leftmost child of right subtree, or stack top itself
    size_t pre = 0, in = 0;
    Node* root = new Node(preorder.at(pre++));

    stack<Node*> stk;
    stk.push(root);
    while (true)
    {
        if (inorder[in] == stk.top()->key)
        {
            Node* top = stk.top();
            stk.pop();
            in++;

            // all done
            if (in == inorder.size())
            {
                break;
            }
            // the case that right child is empty
            if (!stk.empty() && inorder[in] == stk.top()->key)
            {
                continue;
            }
            // set right child and push to stk.
            // Then process right subtree like a new one
            top->right = new Node(preorder.at(pre++));
            stk.push(top->right);
        }
        else
        {
            // Keep pushing left child to stk until leftmost child.
            Node* nd = new Node(preorder.at(pre++));
            stk.top()->left = nd;
            stk.push(nd);
        }
    }

    return root;
}