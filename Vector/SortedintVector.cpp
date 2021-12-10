#include "SortedintVector.h"

void SortedintVector::SelectionSort()//ѡ������ 
{
	for (int i = 0; i < Size() ; i++) {//С��һ��Ԫ�ز�����ѭ��
		int minpos = i;//��¼��ǰ���ֵ����Ϊ��Сֵ
		for (int j = i + 1; j < Size(); j++) {
			if (m_vec[j] < m_vec[minpos])//����Сֵ�Ƚ�
				minpos = j;//���ϸ�����Сֵ�±�
				swap(m_vec[i], m_vec[minpos]);//������Ԫ������Сֵ
		}
	}
}
void SortedintVector::MergeSort()
{
	if (Size() <= 1) return;//С��һ��Ԫ�أ���������ֱ�ӷ���
	SortedintVector v1, v2;
	for (int i = 0; i < Size(); i++) {//ǰ���������ַֽ���ͬ������
		if (i < Size() / 2)
			v1.Insert(i, m_vec[i]);
		else v2.Insert(i, m_vec[i]);
	}
	v1.Delete(0); v2.Delete(0);//���ϴ�vi[1]��ʼinsert ����������ĵ�һ��Ԫ��Ϊ�գ�ɾ������
	v1.MergeSort(); v2.MergeSort();//�ݹ����
	Resize(Size(),0);//���*this��ԭʼ����
	Merge( v1, v2);
}
void SortedintVector::Merge(SortedintVector& v1, SortedintVector& v2)
{
	int n1 = v1.Size(); int n2 = v2.Size();
	int p1 = 0; int p2 = 0; int i = 0;
	while (p1 < n1 && p2 < n2) {//���������鶼ʣԪ��
		if (v1[p1] < v2[p2])
			Insert(i++, v1[p1++]);
		else
			Insert(i++, v2[p2++]);	
	}
	while (p1 < n1) Insert(i++, v1[p1++]);//ֻ��v1��ʣ��ֱ��insert
	while (p2 < n2) Insert(i++, v2[p2++]);//ֻ��v2��ʣ��ֱ��insert
	Delete(0);
}
void SortedintVector::QuickSort(int start,int end)//��������
{
	if (end <= start) return;
	int j = Partition(start, end);//�ҵ��з�Ԫ��
	QuickSort(start, j - 1); QuickSort(j + 1, end);
}
int SortedintVector::Partition(int start, int end)
{
	int i = start; int j = end + 1;//����ָ��
	int s = m_vec[start];//�з�Ԫ��
	while (1) {
		while (m_vec[i++] < s) if (i = end) break;
		while (m_vec[j--] > s);//��s��Ϊ�ڱ�������Խ��
		if (j <= i) break;//����Ѿ�ɨ��������˳�ѭ��
		swap(m_vec[i], m_vec[j]);
	}
	swap(s, m_vec[j]);//��ʱ��ɨ����� a[j]����<s�Ĳ���
	return j;
}
bool SortedintVector::Binary(int x)//���ö��ֲ��ң���֤�Ƿ������Ԫ��
{//ǰ����Ҫ�����
	return BinarySearch(0, Size()-1, x)>=0;//��װ
	//>=0����Ϊ���������Ҳ���ʱ����-1 �ҵ��Ļ������±�0��Size
}
int SortedintVector::BinarySearch(int left, int right, int x)//�ݹ�ʵ��
{
	if (left >= right) return -1;//������false �޷�����
	int mid = left + (right - left) / 2;
	if (m_vec[mid] == x)
		return mid;//������Ѱ����λ��
	if (m_vec[mid] > x)
		return BinarySearch(left, mid - 1, x);
	return BinarySearch(mid + 1, right, x);
}
bool SortedintVector::Binary2(int x)//����ʵ��
{
	int lo = 0; int hi = Size() - 1;//���½�
	if (hi <= lo) return false;//base case
	while (lo<=hi) {//���黹δɨ�����
		int mid = lo + (hi - lo) / 2;//�����м�ֵ
		if (m_vec[mid] == x) return true;
		else if (m_vec[mid] > x)  lo = mid + 1; 
		else hi = mid - 1;
	}
	return false;
}
void SortedintVector::InsertionSort()//��������
{
	for (int i = 1; i < Size(); i++)
		for (int j = i; j > 0 && m_vec[j] < m_vec[j - 1]; j--)
			swap(m_vec[j], m_vec[j - 1]);
}
bool SortedintVector::CircularBinaryNoRepeat(int x)
{//�Ե�����circular sorted arrayΪ��  ����������û���ظ�Ԫ��
	int lo = 0; int hi = Size() - 1;
	while (hi >= lo) {
		int mid = lo + (hi - lo) / 2;
		if (m_vec[mid] == x)//�м�ֵ����Ҫ�ҵ�ֵ
			return true;
		if (m_vec[lo] > m_vec[mid]) {//֤��lo��mid�����ǵ��� ������ת�۵� mid��hi����
			if (x > m_vec[mid] && x <= m_vec[hi]) //���mid��hi�����������֮��
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		else {//lo < mid ��lo��mid�ǵ����� 
			if (x < m_vec[mid] && x >= m_vec[lo])
				hi = mid - 1;
			else
				lo = mid + 1;
		}
	}
	return false;
}
bool SortedintVector::CircularBinaryRepeat(int x)
{//���ظ�Ԫ�صĶ��ֲ��ң���Ҫ�г�����������else�����ظ������
	return CircularBinaryRepeat2(0,Size()-1,x)>=0;//�ݹ�ʵ��
}
int SortedintVector::CircularBinaryRepeat2(int lo,int hi,int x)
{
	if (lo <= hi) 
		return -1;//û�����Ԫ��
	int mid = lo + (hi - lo) / 2;//�м�Ԫ��
	if (m_vec[mid] == x) 
		return mid;
	if (m_vec[mid] > m_vec[lo] && m_vec[mid] < m_vec[hi]) {//��ͨ����
		if (x >= m_vec[mid])
			return CircularBinaryRepeat2(mid + 1, hi, x);
		else
			return CircularBinaryRepeat2(lo, mid - 1, x);
		//�г���ͨ������Ϊ���ų������ظ�Ԫ�ص��������
	}
	if (m_vec[mid]<m_vec[lo] && m_vec[mid]<m_vec[hi]) {//ת�۵������
		//��Ϊ��ͨ���ֺ��ظ�����Ĵ��ڣ�������ø����Ͻ�
		if (x >m_vec[mid] && x <= m_vec[hi])
			return CircularBinaryRepeat2(mid + 1, hi, x);
		else
			return CircularBinaryRepeat2(lo, mid - 1, x);
	}
	if (m_vec[mid] > m_vec[lo] && m_vec[mid] > m_vec[hi]) {//ת�۵����Ҳ�
		if (x >= m_vec[hi] && x < m_vec[mid])
			return CircularBinaryRepeat2(lo, mid - 1, x);
		else
			return CircularBinaryRepeat2(mid + 1, hi, x);
	}
	else //mid lo h����ȵ�����޷��ж�
		return CircularBinaryRepeat2(lo, mid - 1, x) || CircularBinaryRepeat2(mid+1,hi,x);
	//���߶�Ҫͬʱ���
}
int SortedintVector::CircularBinaryFindMin()
{//�����������������СԪ��
	int lo = 0, hi = Size()-1;
	while (lo <= hi) {
	    int mid = lo + (hi - lo) / 2;
		if (lo = hi) return m_vec[lo];//��С��Χ��һ��Ԫ��
		if (m_vec[mid] > m_vec[mid + 1] && m_vec[mid] < m_vec[mid - 1])
			return m_vec[mid];//�м����ת�۵㼴��С��ֱ�ӷ���
		if (m_vec[mid] < m_vec[lo]) //ת�۵������
			hi = mid - 1;
		if (m_vec[mid] > m_vec[lo])
			lo = mid + 1;
	}
}
