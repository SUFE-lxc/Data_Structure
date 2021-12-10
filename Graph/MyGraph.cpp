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
	assert(uid < m_nodes.size() && vid < m_nodes.size());//确保不越界
	Node* U = m_nodes[uid];
	Node* V = m_nodes[vid];//取出U和V
	Edge* arc = new Edge(m_edges.size(),U,V,wt);//确定一条边
	
	U->outArcs.push_back(arc);//已声明为友元类，可以访问私有变量
	V->inArcs.push_back(arc);
	
	m_edges.push_back(arc);//进入私有变量
}

ostream& operator<<(ostream& out, const MyGraph& graph)
{
	for (auto nd : graph.m_nodes)
		out << *nd << endl;
	return out;
}

void MyGraph::Bfs(int start)
{
	bool* visited = new bool[m_nodes.size()]();//访问标记数组
	cout << "BFS:" << endl;

	queue<int> que;//存放nid
	que.push(start);
	visited[m_nodes[start]->NId()] = true;//标记已访问

	while (!que.empty())
	{//一次大循环代表一层遍历
		size_t sz = que.size();//更新这一层的节点数
		while (sz-- > 0) {
			Node* U = m_nodes[que.front()];//取出这个node
			que.pop();
			cout << "#" << U->NId() << ",";//输出node id

			for (auto arc : U->outArcs) {//通过outedge寻找邻node
				int vid = arc->GetV()->NId();
				if (!visited[vid]) {//如果没有访问
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
{//S到T的最短路径:基于BFS
//函数也可以用两个int参数传入node的id
	queue<Node*> que;
	que.push(S);
	
	bool* visited = new bool[m_nodes.size()]();
	visited[S->NId()] = true;
	int depth = 0;

	while (!que.empty())
	{
		size_t sz = que.size();
		depth++;//每一层遍历代表深度+1
		while (sz-- > 0) {
			auto U = que.front();//取出node
			que.pop();
			for (auto arc : U->outArcs)
			{//每一条outedge
				auto V = arc->GetV();//每个邻接顶点
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
{//封装
	bool* visited = new bool[m_nodes.size()]();
	DfsInternal(start, visited);

	cout << "DFS:" << endl;
	delete[] visited; 
}

void MyGraph::DfsInternal(int uid, bool* visited)
{
	visited[uid] = true;//从u开始
	cout << "#" << uid << ",";

	for (auto arc : m_nodes[uid]->outArcs)
	{//每一个邻接节点
		int vid = arc->GetV()->NId();
		if (visited[vid] = false)
			DfsInternal(vid, visited);//逐个递归
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
{//封装
	cout << "DFS TIME SEARCH:" << endl;
	bool* visited = new bool[m_nodes.size()]{ false };
	pair<int, int>* travelTimes = new pair<int, int>[m_nodes.size()];

	DfsTimeInternal(start, 0, visited, travelTimes);

	delete[] visited;
	delete[] travelTimes;
}

int MyGraph::DfsTimeInternal(int uid, int currentTime, bool* visited, pair<int, int>* travelTimes)
{
	visited[uid] = true;//新的根节点
	cout << "#" << uid << ",";
	travelTimes[uid].first = currentTime;

	for (auto arc : m_nodes[uid]->outArcs) {//根节点的每个邻接节点
		int vid = arc->GetV()->NId();
		if (!visited[vid])
			currentTime = DfsTimeInternal(vid, currentTime + 1, visited, travelTimes);
	}
	travelTimes[uid].second = ++currentTime;//这个根节点的所有邻接节点遍历完成
	//endtime
	return currentTime;
}

void MyGraph::TopologySort()
{//拓扑排序 适用于有向无环图
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
	topology.push(uid);//不同在stack的使用方式，其余与DFS基本一致

	return currentTime;
}

void MyGraph::DfsReverseInternal(int uid, bool* visited, vector<int>* pScc)
{//DFS:反向(rescursive)
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
	int Maxtime = DfsTimeInternal(start, 0, visited, travelTimes);//第一次遍历
	for (size_t i = 0; i < m_nodes.size(); ++i) {//查找未被遍历的点
		if (!visited[i])
			Maxtime = DfsTimeInternal(i, ++Maxtime, visited, travelTimes);
	}//遍历完成
	delete[] visited;

	cout << endl;

	bool* Revisited = new bool[m_nodes.size()]{ false };

	cout << "Strong Connected Components are:" << endl;
	for (int i = m_nodes.size() - 1; i >= 0; --i) {//第一次输出
		vector<int> vec;//存放结果的数组
		if (travelTimes[i].second == Maxtime && !Revisited[i])//找到最大endtime
			DfsReverseInternal(i, Revisited, &vec);//反向遍历
		for (size_t j = 0; j < vec.size(); j++)
			cout << "#" << vec[j] << ",";
		cout << endl;
	}
	int max = 0;
	for (size_t i = 0; i <= m_nodes.size(); ++i) {//接下来的输出
		int j = m_nodes.size();
		int flag = -1;
		vector<int> vec;
		while (j >= 0) {
			if (!Revisited[j] && travelTimes[j].second > max && travelTimes[j].second < Maxtime)
			{//找到未被遍历节点的最大endtime
			//条件：未被访问，小于访问完成的endtime的最大endtime
				flag = j;//不断更新位置
				max = travelTimes[j].second;//不断跟新max值
			}
			j--;
			if (j == -1 && flag != -1) {//flag=-1说明不存在未被遍历的节点
				DfsReverseInternal(flag, Revisited, &vec);//再次遍历
				for (size_t m = 0; m < vec.size(); m++)
					cout << "#" << vec[m] << ",";
				cout << endl;
				Maxtime = max;//跟新Maxtime
				max = 0;//重置
			}
		}
		if (flag == -1)
			break;//不存在直接退出即可
	}

	return results;
}