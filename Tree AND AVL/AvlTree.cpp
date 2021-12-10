#include "avltree.h"


AvlTree::AvlTree(const vector<int>& preorder, const vector<int>& inorder)
{//construct by pre and in order
    if (preorder.size() != inorder.size())
    {
        cout << "Invaild Size";
        return;//base case
    }
    m_root = BuildTree(preorder, 0, inorder, 0, inorder.size()-1);
    //m_root = BuildTree_Iterative(preorder,inorder)
}

AvlTree::AvlTree(const AvlTree& other) :m_root(nullptr)
{//copy constructor
    m_root = Clone(other.m_root);
}

AvlTree& AvlTree::operator=(const AvlTree& rhs)
{
    if (&rhs == this)//same
        return *this;
    Reset();//Œˆππ
    m_root = Clone(rhs.m_root);
    return *this;
}

int AvlTree::Height(Node* node)
{
    return (node == nullptr ? -1 : node->height);
}

int AvlTree::GetBalance(Node* node)
{
    return (node == nullptr) ? 0 : Height(node->left) - Height(node->right);
}

Node* AvlTree::FindMin(Node* node)
{
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}

Node* AvlTree::FindMax(Node* node)
{
    while (node && node->right)
    {
        node = node->right;
    }
    return node;
}

Node* AvlTree::RightRotate(Node* ndQ)
{//root = ndQ
    Node* ndP = ndQ->left;
    ndQ->left = ndP->right;
    ndP->right = ndQ;

    return ndP;
}

Node* AvlTree::LeftRotate(Node* ndP)
{
    Node* ndQ = ndP->right;
    ndP->right = ndQ->left;
    ndQ->left = ndP;

    return ndQ;
}

Node* AvlTree::RightLeftRotate(Node* nd)
{
    Node* x = nd->left;
    nd->left = LeftRotate(x);
    return RightRotate(nd);
}

Node* AvlTree::LeftRightRotate(Node* nd)
{
    Node* x = nd->right;
    nd->right = RightRotate(x);
    return LeftRotate(nd);
}

Node* AvlTree::Search(Node* node, int x)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // case of searching left subtree
    if (x < node->key)
    {
        return Search(node->left, x);
    }
    // case of searching right subtree
    if (x > node->key)
    {
        return Search(node->right, x);
    }

    // found matching node
    return node;
}

Node* AvlTree::Insert(Node* node, int x)
{
    if (node == nullptr)
        return new Node(x);
    if (x < node->key)
    {
        node->left = Insert(node->left, x);
    }
    else if (x > node->key)
    {
        node->right = Insert(node->right, x);
    }
    else
    {
        // not insert a node with the same key
        return node;
    }
    node->height = max(Height(node->left), Height(node->right)) + 1;
    int balance = GetBalance(node);

    // ◊Û◊Û ß∫‚
    if (balance > 1 && GetBalance(node->left) >= 0)
        return RightRotate(node);
    // ”“”“ ß∫‚
    if (balance < -1 && GetBalance(node->right) <= 0)
        return LeftRotate(node);
    // ◊Û”“ ß∫‚
    if (balance > 1 && GetBalance(node->left) < 0)
        return LeftRightRotate(node);
    // ”“◊Û ß∫‚
    if (balance < -1 && GetBalance(node->right) >0)
        return RightLeftRotate(node);
    return node;
}

Node* AvlTree::Delete(Node* node, int x)
{
    // Element not found
    if (node == nullptr)
    {
        return nullptr;
    }

    // Searching for element
    if (x < node->key)
    {
        node->left = Delete(node->left, x);
    }
    else if (x > node->key)
    {
        node->right = Delete(node->right, x);
    }
    else
    {
        // have two children
        if (node->left && node->right)
        {
            Node* leftmost = FindMin(node->right);
            node->key = leftmost->key;
            leftmost->key = x;
            Delete(node->right, x);
        }
        // With one or zero child
        else
        {
            Node* curr = node;
            node = node->left ? node->left : node->right;
            delete curr;
        }
    }

    // handle balance if necessary; same as that in Insert()
    if (node)
    {
        node->height = max(Height(node->left), Height(node->right)) + 1;
        int balance = GetBalance(node);

        // ◊Û◊Û ß∫‚
        if (balance > 1 && GetBalance(node->left) >= 0)
            return RightRotate(node);
        // ”“”“ ß∫‚
        if (balance < -1 && GetBalance(node->right) <= 0)
            return LeftRotate(node);
        // ◊Û”“ ß∫‚
        if (balance > 1 && GetBalance(node->left) < 0)
            return LeftRightRotate(node);
        // ”“◊Û ß∫‚
        if (balance < -1 && GetBalance(node->right) >0)
            return RightLeftRotate(node);
        
    }
    return node;
}

void AvlTree::LevelOrder()
{
    queue<const Node*> level;
    level.push(m_root);
    while (!level.empty()) {//∑«ø’
     const Node* curr = level.front();
     cout << curr->key << endl;
     level.pop();
     if (curr->left)
         level.push(curr->left);
     if (curr->right)
         level.push(curr->right);
    }
}

void AvlTree::PreOrder_Iterative()
{
    if (m_root == nullptr)
        return;
    stack<const Node*> stk;
    stk.push(m_root);
    while (!stk.empty()) {
        const Node* x = stk.top();
        stk.pop();
        cout << x->key << endl;
        if (x->right)
            stk.push(x->right);
        if (x->left)
            stk.push(x->left);
    }
}

void AvlTree::InOrder_Iterative()
{
    stack<const Node*> stk;
    const Node* curr = m_root;
    while (curr || !stk.empty()) {
        if (curr) {
            stk.push(curr);
            curr = curr->left;
            continue;
        }
        curr = stk.top();
        stk.pop();
        cout << curr->key << endl;
        curr = curr->right;
    }
}

void AvlTree::PostOrder_Iterative()
{
    stack<const Node*> stk;
    stack<const Node*> output;
    if (m_root)
        stk.push(m_root);
    while (!stk.empty()) {
        const Node* curr = stk.top();
        stk.pop();
        output.push(curr);
        if (curr->left)
            stk.push(curr->left);
        if (curr->right)
            stk.push(curr->right);
    }
    while (!output.empty()) {
        cout << output.top()->key << endl;
        output.pop();
    }
}

void AvlTree::Reset()
{//destructor
    Release(m_root);
    m_root = nullptr;
}

void AvlTree::Release(Node* node)
{
    if (!node)
        return;
    Release(node->left);
    Release(node->right);
    delete node;
}

Node* AvlTree::Clone(const Node* root)
{//recursion 
  //construct function's tool
    if (root == nullptr)//not exist
        return nullptr;
    Node* node = new Node(root->key);
    Clone(root->left);//recursion
    Clone(root->right);
    return node;//finally return
}

Node* AvlTree::BuildTree(const vector<int>& preorder, int pre, const vector<int>& inorder, int lh, int rh)
{
    if (lh > rh)
        return nullptr;
    Node* root = new Node(preorder[pre]);
    int index = lh;
    for (; index <= rh; index++)
        if (inorder[index] == preorder[pre])
            break;
    assert(index <= rh);
    root->left = BuildTree(preorder, pre + 1, inorder, lh, index - 1);//¡¨Ω” ˜
    root->right = BuildTree(preorder, pre + index - lh + 1, inorder, index + 1, rh);
    root->height = max(Height(root->left), Height(root->right)) + 1;//∏¸–¬∏ﬂ∂»
    return root;
}

Node* AvlTree::BuildTree_Iterative(const vector<int>& preorder, const vector<int>& inorder)
{
    assert(preorder.size() == inorder.size());
    // pre always points to inorder node, which is created next
    // in always points to leftmost child of right subtree, or stack top itself
    size_t pre = 0, in = 0;
    Node* node = new Node(preorder.at(pre++));

    stack<Node*> stk;
    stk.push(node);
    while (1)
    {
        if (inorder[in] == stk.top()->key)
        {
            Node* top = stk.top();
            stk.pop();
            in++;
            // all done
            if (in == inorder.size())
                break;
            // the case that right child is empty
            if (!stk.empty() && inorder[in] == stk.top()->key)
                continue;
            // set right child and push to stk.
            // Then process right subtree like a new one
            top->right = new Node(preorder[pre++]);
            stk.push(top->right);
        }
        else
        {
            // Keep pushing left child to stk until leftmost child.
            Node* nd = new Node(preorder[pre++]);
            stk.top()->left = nd;
            stk.push(nd);
        }
    }

    return node;
}
