#pragma once

class Node;
class Edge
{
public:
	Edge(int id, Node* src, Node* dst,float weight=1.0):
		m_eid(id),
		m_active(true)
	{
		m_src = src;
		m_dst = dst;
	}
	Node* GetU() const { return m_src; }
	Node* GetV() const { return m_dst; }

	void SetWeight(float val) { m_weight = val; }
	float GetWieght() const { return m_weight; }

	int EId() const { return m_eid; }
private:
	int m_eid;
	bool m_active;
	float m_weight;

	Node* m_src;
	Node* m_dst;
};