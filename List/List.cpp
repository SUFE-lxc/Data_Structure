#include "List.h"

using namespace std;

List::~List()
{
	Node* x = m_head;//�����ͷ
	while (x) {//ֻҪ��Ϊnullptr
		Node* y = x;
		x = x->next;
		delete y;
	}
}
ostream& operator<<(ostream& out, const List& list)
{//friend����������ֱ�ӵ���˽�г�Ա�����ǿ��Ե�����Ķ����ٷ���˽�г�Ա
	out << "link list:" << '\n';
    //�����б�ͷ
	Node* x = list.m_head;
	while (x) {
		out << x->key << '\t';
		x = x->next;
	}
	return out;//������
	
}
Node* List::Search(int val)//return���ͷ�����ǰ��
{
	Node* x = m_head;
	while (x) {
		if (x->key == val)
			return x;
		x = x->next;
	}
	return nullptr;
}
Node* List::Insert(Node* node, int val)//�������
{
	Node* nd = new Node(val); //��ʼ�� ������
	if (node){//exist Ҳ����m_headһ������
		Node* x = node->next; //store	
		node->next = nd; nd->next = x;
	}
	if (!m_head){//�б�Ϊ�յ����
		m_head = nd;
		nd->next = nd;
	}
	return nd;
	//�����²���Ľڵ�
}
bool List::Delete(Node* node)//ɾ���㷨(����Ҫ֪��ǰ���) ������δ������һ���ڵ�?
{
	Node* x = node->next;
	if (x && node) {//node and node->next both exist 
		node->key = x->key;
		node->next = x->next;
		delete x; return true;
	}
	return false;
}
List::List(const initializer_list<int>& list) :m_head(nullptr)//�б��ʼ��
{
	Node* x=nullptr;//����սڵ�
	for (auto val : list)
		x = Insert(x, val);//��ȡlist�б��е�ֵ
	//�����´���Ľڵ� ���Ե�����ȥ
	Insert(x, INT_MAX);//INT_MAXΪ��������
}
Node* List::FindLast()//Ѱ��β�ڵ�
{
	if (m_head == nullptr || m_head->next == nullptr)
		return m_head;//ֻ��һ������û�� ֱ�ӷ���
	Node* x = m_head->next;
	while (x->next != nullptr) {
		x = x->next;//������ȥ
	}
	return x;
}
bool List::HasCycle()
{
	Node* slow = m_head;
	Node* fast = m_head;//����ָ��
	while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
		slow = slow->next; fast = fast->next->next;
		if (slow == fast)
			return true;
	}
	return false;
}