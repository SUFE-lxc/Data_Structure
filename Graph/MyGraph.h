#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

class Node;
class Edge;

class MyGraph
{
public:
	MyGraph(int sz);
	~MyGraph();

	void AddEdge(int uid, int vid, float wt);

	
	void Bfs(int start);
	void Dfs(int start);
	void DfsTime(int start);
	void Dfs_Iterative(int start);
	
	void TopologySort();
	int ShortestPath(Node*, Node*);
	
	vector<vector<int>> FindScc();
	
	friend ostream& operator << (ostream& out, const MyGraph& graph);

private:
	//禁止等号运算符重载和赋值运算符
	MyGraph(const MyGraph& other);
	MyGraph& operator=(const MyGraph& rhs);

	void DfsInternal(int uid, bool* visited);
	int DfsTimeInternal(int uid, int currentTime, bool* visited, pair<int, int>* travelTimes);
	int DfsTimeInternal(int uid, int currentTime, bool* visited, pair<int, int>* travelTimes,stack<int>& topology);

	void DfsReverseInternal(int uid, bool* visited, vector<int>* pScc);

	vector<Node*> m_nodes;
	vector<Edge*> m_edges;
};