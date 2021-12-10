#include <iostream>
#include "Heap.h"

Node* Heap::ExtractMin()
{
    if (m_data.size() <= 1)
        return nullptr;
 
    Node* root = m_data[1];
    m_data[1] = m_data.back();
    m_data.pop_back();

    if (m_data.size() > 2)
    {
        MinHeapify(1);
    }

    return root;
}

void Heap::InsertKey(Node* nd)
{
    m_data.push_back(nd);
    int i = (int)m_data.size() - 1;//先插入到最后

    while (i > 1 && m_data[Parent(i)]->key > m_data[i]->key)
    {
        swap(m_data[i], m_data[Parent(i)]);
        i = Parent(i);
    }//往上比较传递
}

void Heap::MinHeapify(int i)
{
    int l = Left(i);
    int r = Right(i);
    int min = i;
    if (l < (int)m_data.size() && m_data[l]->key < m_data[min]->key)
    {
        min = l;
    }
    if (r < (int)m_data.size() && m_data[r]->key < m_data[min]->key)
    {
        min = r;
    }

    if (min != i)
    {
        swap(m_data[i], m_data[min]);
        MinHeapify(min);
    }
}