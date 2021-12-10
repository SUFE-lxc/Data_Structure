#include "SortedintVector.h"

void SortedintVector::SelectionSort()//选择排序 
{
	for (int i = 0; i < Size() ; i++) {//小于一个元素不进入循环
		int minpos = i;//记录最前面的值先作为最小值
		for (int j = i + 1; j < Size(); j++) {
			if (m_vec[j] < m_vec[minpos])//与最小值比较
				minpos = j;//不断更新最小值下标
				swap(m_vec[i], m_vec[minpos]);//交换首元素与最小值
		}
	}
}
void SortedintVector::MergeSort()
{
	if (Size() <= 1) return;//小于一个元素，无须排序直接返回
	SortedintVector v1, v2;
	for (int i = 0; i < Size(); i++) {//前后两个部分分进不同的数组
		if (i < Size() / 2)
			v1.Insert(i, m_vec[i]);
		else v2.Insert(i, m_vec[i]);
	}
	v1.Delete(0); v2.Delete(0);//以上从vi[1]开始insert 两个分数组的第一个元素为空，删除即可
	v1.MergeSort(); v2.MergeSort();//递归二分
	Resize(Size(),0);//清空*this的原始数据
	Merge( v1, v2);
}
void SortedintVector::Merge(SortedintVector& v1, SortedintVector& v2)
{
	int n1 = v1.Size(); int n2 = v2.Size();
	int p1 = 0; int p2 = 0; int i = 0;
	while (p1 < n1 && p2 < n2) {//两个子数组都剩元素
		if (v1[p1] < v2[p2])
			Insert(i++, v1[p1++]);
		else
			Insert(i++, v2[p2++]);	
	}
	while (p1 < n1) Insert(i++, v1[p1++]);//只有v1还剩，直接insert
	while (p2 < n2) Insert(i++, v2[p2++]);//只有v2还剩，直接insert
	Delete(0);
}
void SortedintVector::QuickSort(int start,int end)//快速排序
{
	if (end <= start) return;
	int j = Partition(start, end);//找到切分元素
	QuickSort(start, j - 1); QuickSort(j + 1, end);
}
int SortedintVector::Partition(int start, int end)
{
	int i = start; int j = end + 1;//左右指针
	int s = m_vec[start];//切分元素
	while (1) {
		while (m_vec[i++] < s) if (i = end) break;
		while (m_vec[j--] > s);//有s作为哨兵不可能越界
		if (j <= i) break;//如果已经扫描完毕则退出循环
		swap(m_vec[i], m_vec[j]);
	}
	swap(s, m_vec[j]);//此时已扫描完成 a[j]属于<s的部分
	return j;
}
bool SortedintVector::Binary(int x)//调用二分查找，验证是否有这个元素
{//前提是要排序好
	return BinarySearch(0, Size()-1, x)>=0;//封装
	//>=0是因为下面设置找不到时返回-1 找到的话返回下标0—Size
}
int SortedintVector::BinarySearch(int left, int right, int x)//递归实现
{
	if (left >= right) return -1;//即返回false 无法查找
	int mid = left + (right - left) / 2;
	if (m_vec[mid] == x)
		return mid;//返回搜寻到的位置
	if (m_vec[mid] > x)
		return BinarySearch(left, mid - 1, x);
	return BinarySearch(mid + 1, right, x);
}
bool SortedintVector::Binary2(int x)//迭代实现
{
	int lo = 0; int hi = Size() - 1;//上下界
	if (hi <= lo) return false;//base case
	while (lo<=hi) {//数组还未扫描完毕
		int mid = lo + (hi - lo) / 2;//更新中间值
		if (m_vec[mid] == x) return true;
		else if (m_vec[mid] > x)  lo = mid + 1; 
		else hi = mid - 1;
	}
	return false;
}
void SortedintVector::InsertionSort()//插入排序
{
	for (int i = 1; i < Size(); i++)
		for (int j = i; j > 0 && m_vec[j] < m_vec[j - 1]; j--)
			swap(m_vec[j], m_vec[j - 1]);
}
bool SortedintVector::CircularBinaryNoRepeat(int x)
{//以递增的circular sorted array为例  并且数组内没有重复元素
	int lo = 0; int hi = Size() - 1;
	while (hi >= lo) {
		int mid = lo + (hi - lo) / 2;
		if (m_vec[mid] == x)//中间值就是要找的值
			return true;
		if (m_vec[lo] > m_vec[mid]) {//证明lo到mid并不是递增 即包含转折点 mid到hi递增
			if (x > m_vec[mid] && x <= m_vec[hi]) //如果mid到hi这个递增区间之间
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		else {//lo < mid 即lo到mid是递增的 
			if (x < m_vec[mid] && x >= m_vec[lo])
				hi = mid - 1;
			else
				lo = mid + 1;
		}
	}
	return false;
}
bool SortedintVector::CircularBinaryRepeat(int x)
{//有重复元素的二分查找，需要列出多种情况最后else就是重复的情况
	return CircularBinaryRepeat2(0,Size()-1,x)>=0;//递归实现
}
int SortedintVector::CircularBinaryRepeat2(int lo,int hi,int x)
{
	if (lo <= hi) 
		return -1;//没有这个元素
	int mid = lo + (hi - lo) / 2;//中间元素
	if (m_vec[mid] == x) 
		return mid;
	if (m_vec[mid] > m_vec[lo] && m_vec[mid] < m_vec[hi]) {//普通二分
		if (x >= m_vec[mid])
			return CircularBinaryRepeat2(mid + 1, hi, x);
		else
			return CircularBinaryRepeat2(lo, mid - 1, x);
		//列出普通二分是为了排除除了重复元素的其他情况
	}
	if (m_vec[mid]<m_vec[lo] && m_vec[mid]<m_vec[hi]) {//转折点在左侧
		//因为普通二分和重复情况的存在，条件变得更加严谨
		if (x >m_vec[mid] && x <= m_vec[hi])
			return CircularBinaryRepeat2(mid + 1, hi, x);
		else
			return CircularBinaryRepeat2(lo, mid - 1, x);
	}
	if (m_vec[mid] > m_vec[lo] && m_vec[mid] > m_vec[hi]) {//转折点在右侧
		if (x >= m_vec[hi] && x < m_vec[mid])
			return CircularBinaryRepeat2(lo, mid - 1, x);
		else
			return CircularBinaryRepeat2(mid + 1, hi, x);
	}
	else //mid lo h有相等的情况无法判断
		return CircularBinaryRepeat2(lo, mid - 1, x) || CircularBinaryRepeat2(mid+1,hi,x);
	//两边都要同时检查
}
int SortedintVector::CircularBinaryFindMin()
{//环形有序数组查找最小元素
	int lo = 0, hi = Size()-1;
	while (lo <= hi) {
	    int mid = lo + (hi - lo) / 2;
		if (lo = hi) return m_vec[lo];//缩小范围至一个元素
		if (m_vec[mid] > m_vec[mid + 1] && m_vec[mid] < m_vec[mid - 1])
			return m_vec[mid];//中间点是转折点即最小点直接返回
		if (m_vec[mid] < m_vec[lo]) //转折点在左边
			hi = mid - 1;
		if (m_vec[mid] > m_vec[lo])
			lo = mid + 1;
	}
}
