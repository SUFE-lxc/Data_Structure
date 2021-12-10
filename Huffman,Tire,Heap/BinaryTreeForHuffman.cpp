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
    while (it1 != symbols.cend() && it2 != freq.cend()) {//一一对应
        Node* temp = new Node(*it2);
        temp->symbol = *it1;
        ++it1; ++it2;//向后迭代
        minheap.InsertKey(temp);//入堆
    }//创建完成

     //使用heap进行构造
    while (minheap.Size() >= 2) {//当只有一个节点时说明构建结束，退出循环
        Node* min1 = minheap.ExtractMin();
        Node* min2 = minheap.ExtractMin();//至此取得两个最小节点 且1<2
        Node* min = new Node(min1->key + min2->key);//进行合并
        min->symbol = '.';
        min->left = min1; min->right = min2;//链接
        if (minheap.Size() != 0)//即min为根节点时代表完成了构建，不必在放入堆
            minheap.InsertKey(min);
        else m_root = min;//此时已经合并完成,传给私有变量
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
{//封装
    map<char, string> Map;
    FindCodes(m_root, "", Map);
}
void BinaryTree::FindCodes(Node* root, string path, map<char, string>& output)
{
 //已在类中声明，并在正下方定义了对应的修改版GetAllPaths函数用来获取根节点到叶子节点的路径

    vector<string> result = GetAllPaths();//所有路径
    size_t i = 0;
    while (i < result.size()) {
        string path = result[i];
        char symbol = path[path.size() - 1];//标记
        path.pop_back();//去除标记 
        output[symbol] = path;//记录
        i++;//转向下一个路径
    }
}

//新加的GetAllPath函数
vector<string> BinaryTree::GetAllPaths()
{//封装:从根节点开始
    vector<string> result = {};//储存容器
    GetAllPaths(m_root, "", result, "");//新增加了一个string参数,构成huff编码
    return result;
}
void BinaryTree::GetAllPaths(Node* root, string pathTillNow, vector<string>& result, string s)
{//节点root到所有叶子节点的路径
 //result的结果原先由key组成 现在换成huff的0 1编码 
    if (root) {
        pathTillNow += s;//生成huff编码
        if (!root->left && !root->right) {
            pathTillNow += root->symbol;//字符串最后一位作为标记
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
    FindCodes(m_root, "", Map);//获得各个字符对应的huffcode
    auto it0 = txt.begin();
    while (it0 != txt.end()) {
        char symbol = *it0;//获取字母
        strbin += Map[symbol];//huffcode进入结果
        ++it0;
    }
    return strbin;
}

string BinaryTree::Decode(string binary)
{
    string strtxt;
    Node* node = m_root;
    string temp = "";//储存
    map<char, string> Map;
    FindCodes(m_root, "", Map);//获得各个字符对应的huffcode
    for (size_t i = 0; i <= binary.size(); ++i) {
        if (!node->left && !node->right)//hufftree一定是满二叉树
        {//到达叶子节点
            for (auto it = Map.begin(); it != Map.end(); ++it) {//通过value寻找key
                if (it->second == temp)
                {
                    strtxt += it->first;//找到即加入strtxt
                    break;
                }
            }
            node = m_root;//回到根节点
            temp = "";//重置
        }
        if (i < binary.size()) {//确保不越界
            //为了保证最后一个huff码decode成功,循环条件给出的i最后会越界
            temp += binary[i];
            if (binary[i] == '0')
            {
                node = node->left;
                continue;
            }
            else
            {
                node = node->right;//0则左，1则右
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