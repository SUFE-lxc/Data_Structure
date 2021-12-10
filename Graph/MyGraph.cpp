#include "MyGraph.h"
#include "Node.h"
#include "Edge.h"

MyGraph::MyGraph(int sz)
{
	for (int i = 0; i < sz; ++i) {
		Node* nd = new Node (m_nodes.size());
		m_nodes.push_back(nd);
	}
}
MyGraph::~MyGraph()
{
	for (auto node : m_nodes) delete node;
	for (auto edge : m_edges) delete edge;
}
void MyGraph::AddEdge(int uid, int vid, float wt)
{
	assert(uid < m_nodes.size() && vid < m_nodes.size());//ȷ����Խ��
	Node* U = m_nodes[uid];
	Node* V = m_nodes[vid];//ȡ��U��V
	Edge* arc = new Edge(m_edges.size(),U,V,wt);//ȷ��һ����
	
	U->outArcs.push_back(arc);//������Ϊ��Ԫ�࣬���Է���˽�б���
	V->inArcs.push_back(arc);
	
	m_edges.push_back(arc);//����˽�б���
}

ostream& operator<<(ostream& out, const MyGraph& graph)
{
	for (auto nd : graph.m_nodes)
		out << *nd << endl;
	return out;
}

void MyGraph::Bfs(int start)
{
	bool* visited = new bool[m_nodes.size()]();//���ʱ������
	cout << "BFS:" << endl;

	queue<int> que;//���nid
	que.push(start);
	visited[m_nodes[start]->NId()] = true;//����ѷ���

	while (!que.empty())
	{//һ�δ�ѭ������һ�����
		size_t sz = que.size();//������һ��Ľڵ���
		while (sz-- > 0) {
			Node* U = m_nodes[que.front()];//ȡ�����node
			que.pop();
			cout << "#" << U->NId() << ",";//���node id

			for (auto arc : U->outArcs) {//ͨ��outedgeѰ����node
				int vid = arc->GetV()->NId();
				if (!visited[vid]) {//���û�з���
					visited[vid] == true;
					que.push(vid);
				}
			}
		}
		cout << endl;
	}
	delete[] visited;
}
int MyGraph::ShortestPath(Node* S, Node* T)
{//S��T�����·��:����BFS
//����Ҳ����������int��������node��id
	queue<Node*> que;
	que.push(S);
	
	bool* visited = new bool[m_nodes.size()]();
	visited[S->NId()] = true;
	int depth = 0;

	while (!que.empty())
	{
		size_t sz = que.size();
		depth++;//ÿһ������������+1
		while (sz-- > 0) {
			auto U = que.front();//ȡ��node
			que.pop();
			for (auto arc : U->outArcs)
			{//ÿһ��outedge
				auto V = arc->GetV();//ÿ���ڽӶ���
				if (!visited[V->NId()]) {
					visited[V->NId()] == true;
					que.push(V);
					if (T->NId() == V->NId())
						return depth;
				}
			}
		}
	}
	delete[] visited;
}

void MyGraph::Dfs(int start)
{//��װ
	bool* visited = new bool[m_nodes.size()]();
	DfsInternal(start, visited);

	cout << "DFS:" << endl;
	delete[] visited; 
}

void MyGraph::DfsInternal(int uid, bool* visited)
{
	visited[uid] = true;//��u��ʼ
	cout << "#" << uid << ",";

	for (auto arc : m_nodes[uid]->outArcs)
	{//ÿһ���ڽӽڵ�
		int vid = arc->GetV()->NId();
		if (visited[vid] = false)
			DfsInternal(vid, visited);//����ݹ�
	}
}
void MyGraph::Dfs_Iterative(int start)
{
	cout << "DFS:" << endl;
	bool* visited = new bool[m_nodes.size()]();

	stack<int> stk;
	stk.push(start);
	
	while (!stk.empty())
	{
		int uid = m_nodes[stk.top()]->NId();
		stk.pop();
		cout << "#" << uid << ",";

		if (!visited[uid]) {
			visited[uid] = true;
			for (auto arc : m_nodes[uid]->outArcs) 
				stk.push(arc->GetV()->NId());
		}
	}
	delete[] visited;
}

void MyGraph::DfsTime(int start)
{//��װ
	cout << "DFS TIME SEARCH:" << endl;
	bool* visited = new bool[m_nodes.size()]{ false };
	pair<int, int>* travelTimes = new pair<int, int>[m_nodes.size()];

	DfsTimeInternal(start, 0, visited, travelTimes);

	delete[] visited;
	delete[] travelTimes;
}

int MyGraph::DfsTimeInternal(int uid, int currentTime, bool* visited, pair<int, int>* travelTimes)
{
	visited[uid] = true;//�µĸ��ڵ�
	cout << "#" << uid << ",";
	travelTimes[uid].first = currentTime;

	for (auto arc : m_nodes[uid]->outArcs) {//���ڵ��ÿ���ڽӽڵ�
		int vid = arc->GetV()->NId();
		if (!visited[vid])
			currentTime = DfsTimeInternal(vid, currentTime + 1, visited, travelTimes);
	}
	travelTimes[uid].second = ++currentTime;//������ڵ�������ڽӽڵ�������
	//endtime
	return currentTime;
}

void MyGraph::TopologySort()
{//�������� �����������޻�ͼ
	bool* visited = new bool[m_nodes.size()]{ false };
	pair<int, int>* travelTimes = new pair<int, int>[m_nodes.size()];

	stack<int> topology;
	DfsTimeInternal(0, 0,visited, travelTimes,topology);

	cout << "Topology Sort:" << endl;
	while (!topology.empty())
	{
		cout << topology.top() + 1 << "->";
		topology.pop();
	}

	delete[] visited;
	delete[] travelTimes;
}

int MyGraph::DfsTimeInternal(int uid, int currentTime, bool* visited,pair<int, int>* travelTimes,stack<int>& topology)
{
	travelTimes[uid].first = currentTime;
	visited[uid] = true;

	for (auto arc : m_nodes[uid]->outArcs)
	{
		int vid = arc->GetV()->NId();
		if (!visited[vid])
			currentTime = DfsTimeInternal(vid, currentTime + 1, visited, travelTimes, topology);
	}
	travelTimes[uid].second = ++currentTime;
	topology.push(uid);//��ͬ��stack��ʹ�÷�ʽ��������DFS����һ��

	return currentTime;
}

void MyGraph::DfsReverseInternal(int uid, bool* visited, vector<int>* pScc)
{//DFS:����(rescursive)
	visited[uid] = true;
	cout << "#" << uid << ",";
	pScc->push_back(uid);

	for (auto arc : m_nodes[uid]->inArcs)
	{
		int vid = arc->GetU()->NId();
		if (!visited[vid])
			DfsReverseInternal(vid, visited, pScc);
	}
}

vector<vector<int>> MyGraph::FindScc()
{
	vector<vector<int>> results;

	bool* visited = new bool[m_nodes.size()]{ false };
	pair<int, int>* travelTimes = new pair<int, int>[m_nodes.size()];

	cout << "DFS Time Search:" << endl;

	int start = 7;
	int Maxtime = DfsTimeInternal(start, 0, visited, travelTimes);//��һ�α���
	for (size_t i = 0; i < m_nodes.size(); ++i) {//����δ�������ĵ�
		if (!visited[i])
			Maxtime = DfsTimeInternal(i, ++Maxtime, visited, travelTimes);
	}//�������
	delete[] visited;

	cout << endl;

	bool* Revisited = new bool[m_nodes.size()]{ false };

	cout << "Strong Connected Components are:" << endl;
	for (int i = m_nodes.size() - 1; i >= 0; --i) {//��һ�����
		vector<int> vec;//��Ž��������
		if (travelTimes[i].second == Maxtime && !Revisited[i])//�ҵ����endtime
			DfsReverseInternal(i, Revisited, &vec);//�������
		for (size_t j = 0; j < vec.size(); j++)
			cout << "#" << vec[j] << ",";
		cout << endl;
	}
	int max = 0;
	for (size_t i = 0; i <= m_nodes.size(); ++i) {//�����������
		int j = m_nodes.size();
		int flag = -1;
		vector<int> vec;
		while (j >= 0) {
			if (!Revisited[j] && travelTimes[j].second > max && travelTimes[j].second < Maxtime)
			{//�ҵ�δ�������ڵ�����endtime
			//������δ�����ʣ�С�ڷ�����ɵ�endtime�����endtime
				flag = j;//���ϸ���λ��
				max = travelTimes[j].second;//���ϸ���maxֵ
			}
			j--;
			if (j == -1 && flag != -1) {//flag=-1˵��������δ�������Ľڵ�
				DfsReverseInternal(flag, Revisited, &vec);//�ٴα���
				for (size_t m = 0; m < vec.size(); m++)
					cout << "#" << vec[m] << ",";
				cout << endl;
				Maxtime = max;//����Maxtime
				max = 0;//����
			}
		}
		if (flag == -1)
			break;//������ֱ���˳�����
	}

	return results;
}