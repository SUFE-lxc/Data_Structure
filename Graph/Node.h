#pragma once
#include <vector>
using namespace std;
class Edge;

class Node
{
public:
	Node(int id, float val = 0) :
		m_nid(id),
		m_active(true),
		m_key(val)
	{	
	}
	int NId() const{ return m_nid; }

	friend ostream& operator<<(ostream& out, const Node& nd);
	friend class MyGraph;//ÉèÖÃÎªÓÑÔª
private:
	vector<Edge*> outArcs;
	vector<Edge*> inArcs;
	
	int m_nid;
	bool m_active;
	float m_key;
};