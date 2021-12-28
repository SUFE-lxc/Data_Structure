#include "BinaryTree.h"

BinaryTree::BinaryTree(const vector<int>& preorder, const vector<int>& inorder)
{
	if (preorder.size() != inorder.size())
	{
		cout << "Invaild size";
		return;
	}
	m_root = BuildTree(preorder, 0, inorder, 0, inorder.size() - 1);
}
Node* BinaryTree::BuildTree(const vector<int>& preorder, int pre, const vector<int>& inorder, int lh, int rh)
{//递归实现
	if (lh >= rh)
		return nullptr;
	int val = preorder[pre];//第一个根节点
	Node* root = new Node(val);//赋值
	int index = lh;
	for (; index <= rh; index++) {
		if (inorder[index] == val)
			break;//在中序遍历向量中找出根节点
		//在其左边且未遍历过的为其左child，反之亦然，用于下面的递归
	}
	assert(index <= rh);
	root->left = BuildTree(preorder, pre + 1, inorder, lh, index - 1);
	root->right = BuildTree(preorder, pre + index - lh + 1, inorder, index + 1, lh);
	return root;
}
Node* BinaryTree::BuildTree_Iterative(const vector<int>& preorder, const vector<int>& inorder)
{//迭代实现
	assert(preorder.size() == inorder.size());
	size_t pre = 0, in = 0;//size_t用来对数组的大小或者索引的计算
	Node* root = new Node(preorder[pre++]);//创建第一个节点
	stack<Node*> stk;
	stk.push(root);
	while (1) {
		if (inorder[in] == stk.top()->key) {//inorder[0]为leftmost节点
			Node* top = stk.top();
			stk.pop();
			in++;
			//检查
			if (in == inorder.size())//已经完成
				break;
			if (!stk.empty() && inorder[in] == stk.top()->key)
				continue;//这个节点没有右孩子
			top->right = new Node(preorder[pre++]);
			stk.push(top->right);	
		}
		else {//确定leftmost节点
			Node* nd = new Node(preorder[pre++]);
			stk.top()->left = nd;//为旧栈顶的左节点
			stk.push(nd);//选定新的leftmost节点在栈顶
		}
	}
	return root;
}
BinaryTree::BinaryTree(const BinaryTree& other) :m_root(nullptr)
{
	m_root = Clone(other.m_root);//直接构造
}
BinaryTree& BinaryTree::operator=(const BinaryTree& rhs)
{
	if (this == &rhs)//先检查是否相等
		return *this;
	Reset();//清空
	m_root = Clone(rhs.m_root);
	return *this;
}
void BinaryTree::Reset()
{//release the all tree
	Release(m_root);
	m_root = nullptr;
}
void BinaryTree::Release(Node *root)
{//delete the some node you select and its children
	if (root == nullptr)
		return;
	Release(root->left);
	Release(root->right);
	delete root;//delete
}
Node* BinaryTree::Clone(const Node* root)
{//make a tree by recursion
	if (root == nullptr)
		return nullptr;
	Node* nd = new Node(root->key);
	nd->left = Clone(root->left);
	nd->right = Clone(root->right);
}

Node* BinaryTree::ConvertToThreaded(Node* root)
{
	if (root == nullptr)
		return nullptr;
	if (root->left) {
		Node* rightmost = ConvertToThreaded(root->left);
		rightmost->right = root;
		/*rightmost->rightThread = true;*/
	}
	if (root->right)
		return ConvertToThreaded(root->right);
	return root;
}
void BinaryTree::PreOrder()
{//前序遍历迭代解法
	stack<const Node*> stk;//创立栈
	if (m_root)
		stk.push(m_root);//根节点入栈
	while (!stk.empty())//只要栈中还存在元素
	{
		const Node* curr = stk.top();
		stk.pop();//取出第一个节点
		cout << curr->key << endl;
		if (curr->right)//右节点先入栈后访问
			stk.push(curr->right);
		if (curr->left)//左节点反之
			stk.push(curr->left);
	}
}
void BinaryTree::InOrder()
{//中序遍历迭代解法
	stack<const Node*> stk;
	const Node* curr = m_root;
	while (!stk.empty() || curr)
	{
		if (curr) {//检查节点是否存在  if(curr->left)形式不便于检查右节点
			stk.push(curr);
			curr = curr->left;
			continue;//入栈后直接寻找下一个左子节点
		}
		//达到栈顶
		curr = stk.top();
		stk.pop();
		cout << curr->key << endl;//输出顶节点
		curr = curr->right;//转向右节点
	}
}
void BinaryTree::PostOrder()
{//后序遍历迭代解法
	stack<const Node*> stk;
	stack<const Node*> output;
	if (m_root)
		stk.push(m_root);
	while (!stk.empty()) 
	{
		const Node* curr = stk.top();
		stk.pop();
		output.push(curr);
		if (curr->left)
			stk.push(curr->left);
		if (curr->right)
			stk.push(curr->right);//右节点后入栈先出，先入输出栈，后打印
	}
	while (!output.empty()) {
		cout << output.top()->key << endl;
		output.pop();
	}
}
void BinaryTree::LevelOrder()
{//层次遍历迭代解法
	queue<const Node*> levelorder;
	if (m_root)
		levelorder.push(m_root);
	while (!levelorder.empty()) {
		const Node* curr = levelorder.front();
		levelorder.pop();
		cout << curr->key << endl;
		if (curr->left)
			levelorder.push(curr->left);
		if (curr->right)
			levelorder.push(curr->right);
	}
}
void BinaryTree::DeepLeaf(Node* outLeaf)
{//封装
	int maxDepth = -1;
	DeepLeaf(m_root, 0, &maxDepth, outLeaf);
	//maxDepth传入引用改变其值
	cout <<" max deepth is" << maxDepth << endl;
}
void BinaryTree::DeepLeaf(Node* root, int lvl, int* maxDepth, Node* outLeaf)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		if (*maxDepth < lvl) {//记录最大深度和和对应的节点
			*maxDepth = lvl;
			outLeaf = root;
		}
	}
	DeepLeaf(root->left, lvl + 1, maxDepth, outLeaf);//递归深入
	DeepLeaf(root->right, lvl + 1, maxDepth, outLeaf);
}

void BinaryTree::DeepLeftLeaf(Node* outLeaf)
{
	int maxDepth = -1;
	DeepLeftLeaf(m_root, true, 0, &maxDepth, outLeaf);
	cout << " max deepth is" << maxDepth << endl;
}
void BinaryTree::DeepLeftLeaf(Node* root, bool isleft, int lvl, int* maxDepth, Node* outLeaf)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right && isleft) {
		*maxDepth = max(lvl, *maxDepth);//记录最大值
		outLeaf = root;//记录所对应节点
	}

	DeepLeftLeaf(root->left, true, lvl + 1, maxDepth, outLeaf);
	DeepLeftLeaf(root->right, false, lvl + 1, maxDepth, outLeaf);
}

vector<string> BinaryTree:: GetAllPaths()
{
	vector<string> result;
	GetAllPaths(m_root, " ", &result);
	return result;
}
void BinaryTree::GetAllPaths(Node* root, string pathTillNow, vector<string>* result)
{
	if (root != nullptr) {
		pathTillNow += to_string(root->key);
		if (!root->left && !root->right)
			result->push_back(pathTillNow);
		else {
			pathTillNow += "->";
			GetAllPaths(root->left, pathTillNow, result);
			GetAllPaths(root->left, pathTillNow, result);
		}
	}
	else return;
}    
int BinaryTree::maxPathsum()
{
	int maxValue = INT_MIN;
	maxPathsum(m_root, maxValue);
	return maxValue;
}
int BinaryTree::maxPathsum(Node* node, int& maxValue)
{
	if (node == nullptr)
		return 0;

	int left = max(0, maxPathsum(node->left, maxValue));
	int right = max(0, maxPathsum(node->right, maxValue));
	
	maxValue = max(maxValue, left + right + node->key);
	return max(left, right) + node->key;
}

string BinaryTree::FindPathBetweenRootAndNode(Node* node)
{
	assert(m_root != nullptr);
	string result;
	Node* flag = m_root;//记录当前节点位置
	while (1) {
		if (node->key == flag->key)//找到这个根节点
		{
			result+=to_string(flag->key);
			return result;
		}
		else if (node->key < flag->key)
		{
			flag = flag->left;
			result+=to_string(flag->key);
		}
		else {
			flag = flag->right;
			result+=to_string(flag->key);
		}
	}
}

string BinaryTree::FindLeastCommonAncestor(Node* node1, Node* node2)
{
	string path1 = FindPathBetweenRootAndNode(node1);
	string path2 = FindPathBetweenRootAndNode(node2);
	int pos = path1.find_last_of(path2);
	if (pos == string::npos)
		return " ";
	else return to_string(path1[pos]);
}

Node* BinaryTree::FindLeastCommonAncestorByRecursion(Node* node1, Node* node2)
{
	return FindLeastCommonAncestorByRecursion(m_root, node1, node2);
}
Node* BinaryTree::FindLeastCommonAncestorByRecursion(Node* root, Node* node1, Node* node2)
{
	if (node1->key >= root->key && node2->key <= m_root->key)
		return root;
	else if (node1->key <= m_root->key && node2->key >= root->key)
		return root;
	else {
		if (node1->key < root->key) //都在左子树
			FindLeastCommonAncestorByRecursion(root->left,node1,node2);
		else
			FindLeastCommonAncestorByRecursion(root->right,node1,node2);
	}
}
Node* BinaryTree::Leftmost(Node* root)
{
	while (root && root->left) 
		root = root->left;
	return root;
}
Node* BinaryTree::FindMin(Node* root)
{
	return Leftmost(root);
}

Node* BinaryTree::Search(Node* node, int x)
{
	if (!node)
		return nullptr;
	if (x == node->key)
		return node;
	else if (x < node->key)
		return Search(node->left, x);
	else return Search(node->right, x);
}

Node* BinaryTree::Insert(Node* node, int x)
{
	if (!node)//即递归到最后一个节点后再调用函数时，node->next是空节点，也是插入的位置
		return new Node(x);
	if (x < node->key)
		node->left = Insert(node->left, x);
	else
		node->right = Insert(node->right, x);
	return node;
}

Node* BinaryTree::Delete(Node* node, int x)
{
	if (!node)//递归到最后没有找到
		return nullptr;
	if (x < node->key)
		node->left = Delete(node->left, x);
	else if (x > node->key)
		node->right = Delete(node->right, x);
	else {//找到了这个节点
		if (node->left && node->right) {//有两个孩子
			//首先找出直接后继节点
			Node* Suc = FindMin(node->right);//直接后继在右孩子的leftmost节点
			node->key = Suc->key;//转到node
			Suc->key = x;//转且设置为x
			Delete(node->right, x);//删除新node在右子树上被标记为x的节点
		}
		else {//只有一个孩子或者没有孩子
			Node* curr = node;//记录
			node = node->left ? node->left : node->right;//只有一个子结点或者没有
			delete curr;//删除
		}
	}
}
