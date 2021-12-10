#include "Mystring.h"
Mystring::Mystring()//������ַ���
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
void Mystring::Reset()//����˽�г�Ա
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
{//�����Ѵ��ڵ�Mystringlei����ĸ�ֵ
	if (*this == other) return *this;//���
	if (m_data) delete[]m_data;//����������ԭ��Ԫ��
	if (other.IsEmpty()) {//otherΪ�գ�ֱ������
		Reset(); 
	}
	if (m_capacity < other.m_size)//��ֵ����������޷�������ֵ
		Reserve(other.m_capacity);//����
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
	assert(!str.IsEmpty());//Ҫ�ӵ��ַ���Ϊ��
	if (str.Length() + m_size > m_capacity)
		Reserve(m_capacity << 1);//����
	int L = m_size;//��¼ԭ����
	m_size +=str.Length();//��
	for (int i = L; i < m_size; ++i)
		m_data[i] = str[i - L];//ת�ƽ�m_data
	return *this;
}
Mystring& Mystring::operator+=(const Mystring& str)
{
	assert(str.IsEmpty());//Ҫ�ӵ��ַ�Ϊ��
	if (str.Length() + m_size > m_capacity)
		Reserve(m_capacity << 1);//����
	int L = m_size;//��¼ԭ����
	m_size += str.Length();//��
	for (int i = L; i < m_size; ++i)
		m_data[i] = str[i - L];//ת�ƽ�m_data
	return *this;
}
int Mystring::operator==(const Mystring& rhs) const
{
	if (m_size != rhs.m_size) return 0;//base case���Ȳ����
	for (int i = 0; i < m_size; i++)
		if (m_data[i] != rhs.m_data[i])//����Ƚ�
			return 0;
	return 1;
}
Mystring Mystring::operator+(const Mystring& rhs)//����һ�����ַ���
{
	Mystring str;//����һ���¶���
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
		if (sz < m_size) {//��Ҫ����Ԫ��
			char* ptr = new char[m_capacity];
			for (int i = 0; i < sz; ++i)
				ptr[i] = m_data[i];//�������µ�Ԫ��
			delete[] m_data; 
			m_data = ptr;
		}
		else {//����Ҫ����Ԫ��
			Reserve(sz);//sz����capacity�����ݣ�����ʲô������
			for (int i = m_size; i < sz; ++i)
				m_data[i] = c;
		}
		m_size = sz;//���ȷ��sz
	}
}
void Mystring::Reserve(int cap)//����
{
	if (cap > m_capacity) {//ָ������������ԭ����
		char* ptr = new char[cap];
		int sz = m_size;
		for (int i = 0; i < m_size; ++i)//��ת�Ƶ����ַ���
			ptr[i] = m_data[i];
		Reset();//����
		m_data = ptr; m_size = sz; m_capacity = cap;
	}
}
bool Mystring::Insert(int idx, const char* szStr)
{
	if (idx > m_size) return false;//base case 1
	if (szStr == nullptr) return false;//base case 2
	Mystring str;//�¶��󱣴�idx�����Ԫ��
	str.m_size = m_size-idx; 
	str.m_capacity = m_size;
	str.m_data = new char[str.m_capacity];
	int L = strlen(szStr);
	for (int i = idx; i < m_size; ++i)//����idx�ĺ�벿��
		str.m_data[i] = m_data[i];
	Reserve(m_size + L);//����ܳ��ȴ���m_capicity������
	Resize(idx);//ֻʣǰidx��Ԫ��
	for (int i = idx; i < idx + L; ++i)//��ʽ����
		m_data[i] = szStr[i - idx];
	Append(str);//�ټ���ԭ�ȵĺ�벿��
	m_size += L;//����m_size
}
void Mystring::Remove(int idx, int len)
{
	if (idx < 0 || idx >= m_size) return;
	if (len <= 0) return;
    char* ptr = new char[m_size];
	if (len >= m_size - idx - 1) {//�������� 
		//ɾ��idx���������ֵ
		len = m_size - idx - 1;//��len>���ֵʱ �������len
		for (int i = 0; i <= idx; ++i)
			ptr[i] = m_data[i];//����ptr
		delete[] m_data;//�������Ԫ��
		m_data = ptr;//�ٴ���
	}
	else {
		for (int i = 0; i <= idx; ++i)
			ptr[i] = m_data[i];
		for (int i = idx + len + 1 + idx; i < m_size + idx; ++i)//�����ϸ�ѭ����������
			ptr[i] = m_data[i - idx];
		delete[] m_data;
		m_data = ptr;//�ٴ���
	}
	m_size -= len;//����m_size
}
ostream& operator<<(ostream& out, const Mystring& str)
{//�����
	char* p = str.m_data;
	int m = str.Length();
	if (m == 0 || p == nullptr) return out;
	for (int i = 0; i < m; ++i)
		out << p[i];
	return out;
}
Mystring& operator>>(istream& in, Mystring& str)
{//������ strΪ���ַ���
	
	int i = 0;
	while (in) 
		in >> str.m_data[i++];
	str.m_size = i; str.m_capacity = 2 * i;
	return str;
}
Mystring& Mystring::Inverse()
{//��ת���ʴ���
	Mystring result;//���ַ���
	result.m_data = new char[m_capacity];//Ԥ������ռ�
	result.m_capacity = m_capacity;
	result.m_size = m_size;
	Mystring s;//�մ�
	int m = Length()-1;
	int i = m; int j = i;
	while (j >= 0) {
		while (j >= 0 && m_data[j] != ' ')
			j--;//�˳�ѭ��ʱ��i���ǿո�λ��
		result.Append(Substring(j + 1, i)+s);//���ʣ�' \0'
		while (j >= 0 && m_data[j] == ' ')
			j--;//�����ո�(�����ж���ո�)
		//��ʱjΪ�����ڶ������ʵ����һ����ĸ��λ��
		i = j;//����i
	}
	return result;
}
Mystring& Mystring::MaxPalindromePre()
{//Ѱ�������ǰ׺
	Mystring Inversestr = Inverse();//�����ַ���
	Mystring mid; mid.m_data[0] = '#';
	Append(mid+Inversestr);
	int L = 1 + 2 * Length();
	vector<int> Next = GetNext(Data(), L);
	int m = Next.back();//ȡ��Next�������һ��ֵ
	return Substring(0, m-1);
}
int Mystring::FindBasic(const Mystring& pattern) const
{
	int M = pattern.Length();//ƥ�䴮�ĳ���
	if (M > Length()) return 0;
	for (int i = 0; i <= Length() - M; ++i) {//���ƥ��λ����length()-M
		int j = 0;//ÿ����λ�������¿�ʼ
		while (j < M && pattern[j] == m_data[i + j])
			j++;
		if (j == M) return i;//����ƥ��λ��
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
	int M = pattern.Length();//ƥ�䴮�ĳ���
	if (M > Length()) return -1;
	
	long patHash = pattern.Hashing(M);
	long txtHsah = Hashing(M);//����ָ��ֵ

	if(patHash == txtHsah)//��һ�αȶԾ�ָ��ֵ��Ƚ�����һ���ȶ�
		if(Check(m_data,pattern.Data(),M))//ƥ��ɹ�
			return 0;//����ƥ��λ ��Ϊ��0λ
	
	for (int i = M; i < Length(); ++i) {//���л���
		txtHsah = ReHashing(txtHsah, m_data[i - M], m_data[i], M - 1);
		if (patHash == txtHsah)
			if (Check(m_data + i - M + 1, pattern.Data(), M))//���뻬������ַ���
				return i - M + 1;
	}
	return -1;
}
bool Mystring::Check(const char* data, const char* pdata, int M) const
{//�Ƚ�������ͬ���ȵ��ַ���
	for (int i = 0; i <= M; ++i) {
		if (data[i] != pdata[i])
			return false;
	}
	return true;
}
vector<int> Mystring::GetNext(const char* szpattern, int M) const
{
	vector<int> next;
	next.push_back(-1);//next[0]=-1 ��Ϊ�ڱ�
	int j = 0; int i = -1;

	while (j < M) {//Mλp������
		while (i >= 0 && szpattern[j] != szpattern[i])
			i = next[i];//����
		//��������-1��i = next[0] = -1����󳤶�λ0 ��next[j+1] = 0  ++i��i=0���Ժ�Ƚ�p[0]��p[j]
		//��������0 ��p[0] = p[j] next[j+1] = 1  �Ժ�Ƚ�p[1] �� p[j]
		next.push_back(++i);//++iλ��ǰ����󳤶ȣ����ϸ�ѭ�������������������ϸ�ѭ������󳤶�ֱ������
		++j;
	}
	return next;
}
int Mystring::FindKMP(const Mystring& pattern) const
{
	int M = pattern.Length();//ƥ�䴮�ĳ���
	if (M > Length()) return -1;  

	vector<int> vecNext = GetNext(pattern.Data(), M);//��patterm��Ӧ��next��
	
	int i = 0; int j = 0;
	while (i < Length() && j < M)//�ڷ�Χ��
	{
		if (j < 0 || m_data[i] == pattern[j]) {
			i++; j++;//��ĸƥ��
		}
		else
			j = vecNext[j];//��vecNext[j]=0
	}
	if (j == M) //���ƥ��Ļ��ܻᵽ��M����ʱƥ��λ�þ���i-j
		return i - j;
	return -1;
}
vector<int> Mystring::GetBadCharTable(const char* szPattern, int M) const
{//���ַ���      ���� �����ַ��������� ����
	vector<int> vecBadChars(M, -1);
	for (int i = 0; i < M; ++i)
		vecBadChars[(int)szPattern[i]] = i;//��¼ÿ���ַ��ڴ�����ҵ�λ��
	return vecBadChars;
	//��������Ϊi-b(x)
}
vector<int> Mystring::GetSuffixTable(const char* szPattern, int M) const
{//suffix[i]�Ǵ�i������pattern��׺ƥ�������Ӵ�����
	vector<int> vecSuffixes(M, 0);
	vecSuffixes[M - 1] = M;//��ʼ�������һλ��ʼ��suffix��pattern�غ�
	for (int i = M - 2; i >= 0; --i) {//��������
		int prev = i;
		while(prev >= 0 && szPattern[prev] == szPattern[M - 1 - (i - prev)])
			prev--;//���ʱ�Ϳ��Բ�����ǰ����
		vecSuffixes[i] = i - prev;//�����ľ�����Ǵ�i������ִ�����󳤶�
	}
	return vecSuffixes;
}
vector<int> Mystring::GetGoodSuffixTable(const char* szPattern, int M) const
{//case 3 -> case2 -> case 1 ���ϸ���
	vector<int> Suffix = GetSuffixTable(szPattern, M);//���suffix��

	vector<int> GoodSuffixes(M, M);//case 1,λ��ΪM,û����ͬ���ִ����ַ�

	int j = 0;
	for (int i = M - 1; i >= 0; --i) {
		if (Suffix[i] = i + 1) {//pattern[i]��pattern[0]��preffix  i�����ǰ׺�ͺ�׺��ͬ 
			//��case 2
			for (; j < M - 1 - i; ++j)//�����ǰ׺��ɨ��
				if (GoodSuffixes[j] == M)//�����case 3�͸���
					GoodSuffixes[j] = M - 1 - i;//�����ƶ����� ǰ׺�е��ַ������ƶ�M-1-i������
		}
	}
	for (int i = 0; i < M - 1; ++i) //case 1
		GoodSuffixes[M - 1 - Suffix[i]] = M - 1 - i;//��׺ǰһ��Ԫ�ز�ͬ���ƶ�M-1-i����λ
	return GoodSuffixes;
}
int Mystring::FindBM(const Mystring& pattern) const
{
	int M = pattern.Length();

	vector<int> BadCharTable = GetBadCharTable(pattern.Data(), M);
	vector<int> GoodCharTable = GetGoodSuffixTable(pattern.Data(), M);

	for (int j = 0; j <= Length() - M;) {//ɨ��
		int last = M - 1;
		while (pattern[last] == m_data[last + j])
			last--;//���ϱȽ�
		if (last < 0) //����ɹ�ֱ�ӷ���
			return j;
		j += max(GoodCharTable[last], last - BadCharTable[(int)m_data[last+j]]);//û�гɹ� lastͣ���ڻ��ַ���
	   //�ú�׺ֱ�ӷ����ƶ��ĵ�λ,���ַ��õ�ǰλ��-�ַ������ұ������ұߵ�λ�ü��ƶ��ĵ�λ
	}
	return -1;
}
