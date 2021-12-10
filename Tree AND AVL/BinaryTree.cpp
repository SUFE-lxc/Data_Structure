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
{//�ݹ�ʵ��
	if (lh >= rh)
		return nullptr;
	int val = preorder[pre];//��һ�����ڵ�
	Node* root = new Node(val);//��ֵ
	int index = lh;
	for (; index <= rh; index++) {
		if (inorder[index] == val)
			break;//����������������ҳ����ڵ�
		//���������δ��������Ϊ����child����֮��Ȼ����������ĵݹ�
	}
	assert(index <= rh);
	root->left = BuildTree(preorder, pre + 1, inorder, lh, index - 1);
	root->right = BuildTree(preorder, pre + index - lh + 1, inorder, index + 1, lh);
	return root;
}
Node* BinaryTree::BuildTree_Iterative(const vector<int>& preorder, const vector<int>& inorder)
{//����ʵ��
	assert(preorder.size() == inorder.size());
	size_t pre = 0, in = 0;//size_t����������Ĵ�С���������ļ���
	Node* root = new Node(preorder[pre++]);//������һ���ڵ�
	stack<Node*> stk;
	stk.push(root);
	while (1) {
		if (inorder[in] == stk.top()->key) {//inorder[0]Ϊleftmost�ڵ�
			Node* top = stk.top();
			stk.pop();
			in++;
			//���
			if (in == inorder.size())//�Ѿ����
				break;
			if (!stk.empty() && inorder[in] == stk.top()->key)
				continue;//����ڵ�û���Һ���
			top->right = new Node(preorder[pre++]);
			stk.push(top->right);	
		}
		else {//ȷ��leftmost�ڵ�
			Node* nd = new Node(preorder[pre++]);
			stk.top()->left = nd;//Ϊ��ջ������ڵ�
			stk.push(nd);//ѡ���µ�leftmost�ڵ���ջ��
		}
	}
	return root;
}
BinaryTree::BinaryTree(const BinaryTree& other) :m_root(nullptr)
{
	m_root = Clone(other.m_root);//ֱ�ӹ���
}
BinaryTree& BinaryTree::operator=(const BinaryTree& rhs)
{
	if (this == &rhs)//�ȼ���Ƿ����
		return *this;
	Reset();//���
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
{//ǰ����������ⷨ
	stack<const Node*> stk;//����ջ
	if (m_root)
		stk.push(m_root);//���ڵ���ջ
	while (!stk.empty())//ֻҪջ�л�����Ԫ��
	{
		const Node* curr = stk.top();
		stk.pop();//ȡ����һ���ڵ�
		cout << curr->key << endl;
		if (curr->right)//�ҽڵ�����ջ�����
			stk.push(curr->right);
		if (curr->left)//��ڵ㷴֮
			stk.push(curr->left);
	}
}
void BinaryTree::InOrder()
{//������������ⷨ
	stack<const Node*> stk;
	const Node* curr = m_root;
	while (!stk.empty() || curr)
	{
		if (curr) {//���ڵ��Ƿ����  if(curr->left)��ʽ�����ڼ���ҽڵ�
			stk.push(curr);
			curr = curr->left;
			continue;//��ջ��ֱ��Ѱ����һ�����ӽڵ�
		}
		//�ﵽջ��
		curr = stk.top();
		stk.pop();
		cout << curr->key << endl;//������ڵ�
		curr = curr->right;//ת���ҽڵ�
	}
}
void BinaryTree::PostOrder()
{//������������ⷨ
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
			stk.push(curr->right);//�ҽڵ����ջ�ȳ����������ջ�����ӡ
	}
	while (!output.empty()) {
		cout << output.top()->key << endl;
		output.pop();
	}
}
void BinaryTree::LevelOrder()
{//��α��������ⷨ
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
{//��װ
	int maxDepth = -1;
	DeepLeaf(m_root, 0, &maxDepth, outLeaf);
	//maxDepth�������øı���ֵ
	cout <<" max deepth is" << maxDepth << endl;
}
void BinaryTree::DeepLeaf(Node* root, int lvl, int* maxDepth, Node* outLeaf)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		if (*maxDepth < lvl) {//��¼�����ȺͺͶ�Ӧ�Ľڵ�
			*maxDepth = lvl;
			outLeaf = root;
		}
	}
	DeepLeaf(root->left, lvl + 1, maxDepth, outLeaf);//�ݹ�����
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
		*maxDepth = max(lvl, *maxDepth);//��¼���ֵ
		outLeaf = root;//��¼����Ӧ�ڵ�
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
	Node* flag = m_root;//��¼��ǰ�ڵ�λ��
	while (1) {
		if (node->key == flag->key)//�ҵ�������ڵ�
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
		if (node1->key < root->key) //����������
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
	if (!node)//���ݹ鵽���һ���ڵ���ٵ��ú���ʱ��node->next�ǿսڵ㣬Ҳ�ǲ����λ��
		return new Node(x);
	if (x < node->key)
		node->left = Insert(node->left, x);
	else
		node->right = Insert(node->right, x);
	return node;
}

Node* BinaryTree::Delete(Node* node, int x)
{
	if (!node)//�ݹ鵽���û���ҵ�
		return nullptr;
	if (x < node->key)
		Delete(node->left, x);
	else if (x > node->key)
		Delete(node->right, x);
	else {//�ҵ�������ڵ�
		if (node->left && node->right) {//����������
			//�����ҳ�ֱ�Ӻ�̽ڵ�
			Node* Suc = FindMin(node->right);//ֱ�Ӻ�����Һ��ӵ�leftmost�ڵ�
			node->key = Suc->key;//ת��node
			Suc->key = x;//ת������Ϊx
			Delete(node->right, x);//ɾ����node���������ϱ����Ϊx�Ľڵ�
		}
		else {//ֻ��һ�����ӻ���û�к���
			Node* curr = node;//��¼
			node = node->left ? node->left : node->right;//ֻ��һ���ӽ�����û��
			delete curr;//ɾ��
		}
	}
}
