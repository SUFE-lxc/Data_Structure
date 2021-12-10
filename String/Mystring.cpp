#include "Mystring.h"
Mystring::Mystring()//构造空字符串
{
	m_data = new char[1];
	m_data[0] = '\0';
	m_size = 0; m_capacity = 1;
}
Mystring::Mystring(const char* szStr)
{
	if (szStr) {
		m_size = strlen(szStr);
		m_capacity = m_size << 1;
		m_data = new char[m_capacity] {'\0'};
		strcpy_s(m_data,m_size+1, szStr);
	}
	else
		Mystring();
}
void Mystring::Reset()//重置私有成员
{
	if (m_data) {
		delete[] m_data;
		m_data = nullptr;
		m_size = m_capacity = 0;
	}
}
Mystring::Mystring(const Mystring& other):m_data{nullptr},m_size{0},m_capacity{0}
{
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = new char[m_capacity] {'\0'};
	for (int i = 0; i <= other.Length(); ++i)
		m_data[i] = other[i];
}
Mystring& Mystring::operator=(const Mystring& other)
{//用于已存在的Mystringlei对象的赋值
	if (*this == other) return *this;//相等
	if (m_data) delete[]m_data;//不相等则清除原有元素
	if (other.IsEmpty()) {//other为空，直接重置
		Reset(); 
	}
	if (m_capacity < other.m_size)//左值的最大容量无法容纳右值
		Reserve(other.m_capacity);//扩容
	m_data = new char[m_capacity] {'\0'};
	for (int i = 0; i < other.Length(); ++i)
		m_data[i] = other[i];
	m_size = other.m_size;
}
Mystring& Mystring::Substring(int lo, int hi)
{
	assert(lo >= 0 && hi >= 0 && hi >= lo);
	Mystring result;
	result.m_data = new char[m_capacity];
	result.m_size = hi - lo;
	result.m_capacity = m_capacity;
	if (hi = lo)
		result.m_data[0] = m_data[lo];
	else 
		for (int i = lo; i <= hi; ++i)
			result.m_data[i - lo] = m_data[i];
	return result;
}
Mystring& Mystring::Append(const Mystring& str)
{
	assert(!str.IsEmpty());//要加的字符不为空
	if (str.Length() + m_size > m_capacity)
		Reserve(m_capacity << 1);//扩容
	int L = m_size;//记录原长度
	m_size +=str.Length();//扩
	for (int i = L; i < m_size; ++i)
		m_data[i] = str[i - L];//转移进m_data
	return *this;
}
Mystring& Mystring::operator+=(const Mystring& str)
{
	assert(str.IsEmpty());//要加的字符为空
	if (str.Length() + m_size > m_capacity)
		Reserve(m_capacity << 1);//扩容
	int L = m_size;//记录原长度
	m_size += str.Length();//扩
	for (int i = L; i < m_size; ++i)
		m_data[i] = str[i - L];//转移进m_data
	return *this;
}
int Mystring::operator==(const Mystring& rhs) const
{
	if (m_size != rhs.m_size) return 0;//base case长度不相等
	for (int i = 0; i < m_size; i++)
		if (m_data[i] != rhs.m_data[i])//逐个比较
			return 0;
	return 1;
}
Mystring Mystring::operator+(const Mystring& rhs)//返回一个新字符串
{
	Mystring str;//创造一个新对象
	str.m_capacity = m_capacity;
	str.m_size = m_size;
	str.m_data = new char[str.m_capacity];
	for (int i = 0; i < m_size; i++)
		str.m_data[i] = m_data[i];
	Reset();
	str.Append(rhs);
	return str;
}
void Mystring::Resize(int sz, char c)
{
	if (sz > 0) {
		if (sz < m_size) {//需要舍弃元素
			char* ptr = new char[m_capacity];
			for (int i = 0; i < sz; ++i)
				ptr[i] = m_data[i];//保存留下的元素
			delete[] m_data; 
			m_data = ptr;
		}
		else {//不需要舍弃元素
			Reserve(sz);//sz大于capacity则扩容，否则什么都不做
			for (int i = m_size; i < sz; ++i)
				m_data[i] = c;
		}
		m_size = sz;//最后确定sz
	}
}
void Mystring::Reserve(int cap)//扩容
{
	if (cap > m_capacity) {//指定的容量大于原容量
		char* ptr = new char[cap];
		int sz = m_size;
		for (int i = 0; i < m_size; ++i)//先转移到新字符里
			ptr[i] = m_data[i];
		Reset();//重置
		m_data = ptr; m_size = sz; m_capacity = cap;
	}
}
bool Mystring::Insert(int idx, const char* szStr)
{
	if (idx > m_size) return false;//base case 1
	if (szStr == nullptr) return false;//base case 2
	Mystring str;//新对象保存idx后面的元素
	str.m_size = m_size-idx; 
	str.m_capacity = m_size;
	str.m_data = new char[str.m_capacity];
	int L = strlen(szStr);
	for (int i = idx; i < m_size; ++i)//保存idx的后半部分
		str.m_data[i] = m_data[i];
	Reserve(m_size + L);//如果总长度大于m_capicity则扩容
	Resize(idx);//只剩前idx个元素
	for (int i = idx; i < idx + L; ++i)//正式插入
		m_data[i] = szStr[i - idx];
	Append(str);//再加入原先的后半部分
	m_size += L;//更新m_size
}
void Mystring::Remove(int idx, int len)
{
	if (idx < 0 || idx >= m_size) return;
	if (len <= 0) return;
    char* ptr = new char[m_size];
	if (len >= m_size - idx - 1) {//超出界限 
		//删除idx后面的所有值
		len = m_size - idx - 1;//当len>最大值时 化成最大len
		for (int i = 0; i <= idx; ++i)
			ptr[i] = m_data[i];//存入ptr
		delete[] m_data;//清除所有元素
		m_data = ptr;//再传入
	}
	else {
		for (int i = 0; i <= idx; ++i)
			ptr[i] = m_data[i];
		for (int i = idx + len + 1 + idx; i < m_size + idx; ++i)//沿着上个循环继续存入
			ptr[i] = m_data[i - idx];
		delete[] m_data;
		m_data = ptr;//再传入
	}
	m_size -= len;//更新m_size
}
ostream& operator<<(ostream& out, const Mystring& str)
{//输出流
	char* p = str.m_data;
	int m = str.Length();
	if (m == 0 || p == nullptr) return out;
	for (int i = 0; i < m; ++i)
		out << p[i];
	return out;
}
Mystring& operator>>(istream& in, Mystring& str)
{//输入流 str为空字符串
	
	int i = 0;
	while (in) 
		in >> str.m_data[i++];
	str.m_size = i; str.m_capacity = 2 * i;
	return str;
}
Mystring& Mystring::Inverse()
{//翻转单词次序
	Mystring result;//新字符串
	result.m_data = new char[m_capacity];//预先申请空间
	result.m_capacity = m_capacity;
	result.m_size = m_size;
	Mystring s;//空串
	int m = Length()-1;
	int i = m; int j = i;
	while (j >= 0) {
		while (j >= 0 && m_data[j] != ' ')
			j--;//退出循环时的i就是空格位置
		result.Append(Substring(j + 1, i)+s);//单词＋' \0'
		while (j >= 0 && m_data[j] == ' ')
			j--;//跳出空格(可能有多个空格)
		//此时j为倒数第二个单词的最后一个字母的位置
		i = j;//更新i
	}
	return result;
}
Mystring& Mystring::MaxPalindromePre()
{//寻找最长回文前缀
	Mystring Inversestr = Inverse();//逆序字符串
	Mystring mid; mid.m_data[0] = '#';
	Append(mid+Inversestr);
	int L = 1 + 2 * Length();
	vector<int> Next = GetNext(Data(), L);
	int m = Next.back();//取出Next表中最后一个值
	return Substring(0, m-1);
}
int Mystring::FindBasic(const Mystring& pattern) const
{
	int M = pattern.Length();//匹配串的长度
	if (M > Length()) return 0;
	for (int i = 0; i <= Length() - M; ++i) {//最大匹配位置再length()-M
		int j = 0;//每次移位过后都重新开始
		while (j < M && pattern[j] == m_data[i + j])
			j++;
		if (j == M) return i;//返回匹配位置
	}
	return -1;
}
long Mystring::Hashing(int len) const
{
	long result = 0;
	for (int i = 0; i < len; ++i)
		result = (result << 1 + m_data[i]) % Prime;
	return result;
}
long Mystring::ReHashing(long hashing, int a, int b, int offset) const
{
	long result = (hashing + Prime - (a << offset) % Prime) % Prime;
	result = ((result << 1) + b) % Prime;
	return result;
}
int Mystring::FindKR(const Mystring& pattern) const
{
	int M = pattern.Length();//匹配串的长度
	if (M > Length()) return -1;
	
	long patHash = pattern.Hashing(M);
	long txtHsah = Hashing(M);//计算指纹值

	if(patHash == txtHsah)//第一次比对就指纹值相等进行下一步比对
		if(Check(m_data,pattern.Data(),M))//匹配成功
			return 0;//返回匹配位 即为第0位
	
	for (int i = M; i < Length(); ++i) {//进行滑动
		txtHsah = ReHashing(txtHsah, m_data[i - M], m_data[i], M - 1);
		if (patHash == txtHsah)
			if (Check(m_data + i - M + 1, pattern.Data(), M))//传入滑动后的字符穿
				return i - M + 1;
	}
	return -1;
}
bool Mystring::Check(const char* data, const char* pdata, int M) const
{//比较两个相同长度的字符串
	for (int i = 0; i <= M; ++i) {
		if (data[i] != pdata[i])
			return false;
	}
	return true;
}
vector<int> Mystring::GetNext(const char* szpattern, int M) const
{
	vector<int> next;
	next.push_back(-1);//next[0]=-1 作为哨兵
	int j = 0; int i = -1;

	while (j < M) {//M位p串长度
		while (i >= 0 && szpattern[j] != szpattern[i])
			i = next[i];//迭代
		//若迭代到-1，i = next[0] = -1即最大长度位0 则next[j+1] = 0  ++i后i=0，以后比较p[0]和p[j]
		//若迭代到0 则p[0] = p[j] next[j+1] = 1  以后比较p[1] 和 p[j]
		next.push_back(++i);//++i位当前的最大长度，由上个循环可以缩减，若跳过上个循环则最大长度直接增加
		++j;
	}
	return next;
}
int Mystring::FindKMP(const Mystring& pattern) const
{
	int M = pattern.Length();//匹配串的长度
	if (M > Length()) return -1;  

	vector<int> vecNext = GetNext(pattern.Data(), M);//找patterm对应的next串
	
	int i = 0; int j = 0;
	while (i < Length() && j < M)//在范围内
	{
		if (j < 0 || m_data[i] == pattern[j]) {
			i++; j++;//字母匹配
		}
		else
			j = vecNext[j];//若vecNext[j]=0
	}
	if (j == M) //如果匹配的话总会到达M，此时匹配位置就是i-j
		return i - j;
	return -1;
}
vector<int> Mystring::GetBadCharTable(const char* szPattern, int M) const
{//坏字符表      ！！ 根据字符进行索引 ！！
	vector<int> vecBadChars(M, -1);
	for (int i = 0; i < M; ++i)
		vecBadChars[(int)szPattern[i]] = i;//记录每个字符在串里最靠右的位置
	return vecBadChars;
	//滑动长度为i-b(x)
}
vector<int> Mystring::GetSuffixTable(const char* szPattern, int M) const
{//suffix[i]是从i向左，与pattern后缀匹配的最大子串长度
	vector<int> vecSuffixes(M, 0);
	vecSuffixes[M - 1] = M;//初始化，最后一位开始的suffix与pattern重合
	for (int i = M - 2; i >= 0; --i) {//从右往左
		int prev = i;
		while(prev >= 0 && szPattern[prev] == szPattern[M - 1 - (i - prev)])
			prev--;//相等时就可以不断向前迭代
		vecSuffixes[i] = i - prev;//迭代的距离就是从i向左的字串的最大长度
	}
	return vecSuffixes;
}
vector<int> Mystring::GetGoodSuffixTable(const char* szPattern, int M) const
{//case 3 -> case2 -> case 1 不断更新
	vector<int> Suffix = GetSuffixTable(szPattern, M);//获得suffix表

	vector<int> GoodSuffixes(M, M);//case 1,位移为M,没有相同的字串和字符

	int j = 0;
	for (int i = M - 1; i >= 0; --i) {
		if (Suffix[i] = i + 1) {//pattern[i]到pattern[0]是preffix  i向左的前缀和后缀相同 
			//即case 2
			for (; j < M - 1 - i; ++j)//在这个前缀中扫描
				if (GoodSuffixes[j] == M)//如果是case 3就更新
					GoodSuffixes[j] = M - 1 - i;//更新移动长度 前缀中的字符都是移动M-1-i个距离
		}
	}
	for (int i = 0; i < M - 1; ++i) //case 1
		GoodSuffixes[M - 1 - Suffix[i]] = M - 1 - i;//后缀前一个元素不同，移动M-1-i个单位
	return GoodSuffixes;
}
int Mystring::FindBM(const Mystring& pattern) const
{
	int M = pattern.Length();

	vector<int> BadCharTable = GetBadCharTable(pattern.Data(), M);
	vector<int> GoodCharTable = GetGoodSuffixTable(pattern.Data(), M);

	for (int j = 0; j <= Length() - M;) {//扫描
		int last = M - 1;
		while (pattern[last] == m_data[last + j])
			last--;//不断比较
		if (last < 0) //如果成功直接返回
			return j;
		j += max(GoodCharTable[last], last - BadCharTable[(int)m_data[last+j]]);//没有成功 last停留在坏字符上
	   //好后缀直接返回移动的单位,坏字符用当前位置-字符在其右边中最右边的位置即移动的单位
	}
	return -1;
}
