#include "List.h"

using namespace std;

List::~List()
{
	Node* x = m_head;//接入表头
	while (x) {//只要不为nullptr
		Node* y = x;
		x = x->next;
		delete y;
	}
}
ostream& operator<<(ostream& out, const List& list)
{//friend函数不可以直接调用私有成员，但是可以调用类的对象再访问私有成员
	out << "link list:" << '\n';
    //接入列表头
	Node* x = list.m_head;
	while (x) {
		out << x->key << '\t';
		x = x->next;
	}
	return out;//返回流
	
}
Node* List::Search(int val)//return类型放在最前面
{
	Node* x = m_head;
	while (x) {
		if (x->key == val)
			return x;
		x = x->next;
	}
	return nullptr;
}
Node* List::Insert(Node* node, int val)//往后插入
{
	Node* nd = new Node(val); //初始化 （？）
	if (node){//exist 也表明m_head一定存在
		Node* x = node->next; //store	
		node->next = nd; nd->next = x;
	}
	if (!m_head){//列表为空的情况
		m_head = nd;
		nd->next = nd;
	}
	return nd;
	//返回新插入的节点
}
bool List::Delete(Node* node)//删除算法(不需要知道前结点) 不过如何处理最后一个节点?
{
	Node* x = node->next;
	if (x && node) {//node and node->next both exist 
		node->key = x->key;
		node->next = x->next;
		delete x; return true;
	}
	return false;
}
List::List(const initializer_list<int>& list) :m_head(nullptr)//列表初始化
{
	Node* x=nullptr;//创造空节点
	for (auto val : list)
		x = Insert(x, val);//读取list列表中的值
	//返回新创造的节点 得以迭代下去
	Insert(x, INT_MAX);//INT_MAX为上限整数
}
Node* List::FindLast()//寻找尾节点
{
	if (m_head == nullptr || m_head->next == nullptr)
		return m_head;//只有一个或者没有 直接返回
	Node* x = m_head->next;
	while (x->next != nullptr) {
		x = x->next;//迭代下去
	}
	return x;
}
bool List::HasCycle()
{
	Node* slow = m_head;
	Node* fast = m_head;//快慢指针
	while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
		slow = slow->next; fast = fast->next->next;
		if (slow == fast)
			return true;
	}
	return false;
}