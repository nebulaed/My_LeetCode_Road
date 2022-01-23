#include<array>
#include<iostream>
#include<ctime>
#include<cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::string;

long get_a_target_long()
{
	long target = 0;
	cout << "target (0~" << RAND_MAX << "):";
	cin >> target;
	return target;
}

string get_a_target_string()
{
	long target = 0;
	char buf[10];

	cout << "target (0~" << RAND_MAX << "):";
	cin >> target;
	snprintf(buf, 10, "%d", target);
	return string(buf);
}

int compareLongs(const void* a, const void* b)
{
	return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b)
{
	if (*(string*)a > * (string*)b)
	{
		return 1;
	}
	else if (*(string*)a < *(string*)b)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
namespace jj01
{
	void test_array()
	{
		cout << "\ntest_array()......\n";
		const long ASIZE = 200000L;
		array<long, ASIZE> c;

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			c[i] = rand();
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "array.size()= " << c.size() << endl;
		cout << "array.front()= " << c.front() << endl;
		cout << "array.back()= " << c.back() << endl;
		cout << "array.data()= " << c.data() << endl;

		long target = get_a_target_long();

		timeStart = clock();
		// qsort�����룺������ʼ��ַc.data()������Ԫ������ASIZE��Ԫ������long����ô�Ƚϴ�С��compareLongs
		qsort(c.data(), ASIZE, sizeof(long), compareLongs);
		long* pItem = (long*)bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
		cout << "qsort() + bsearch(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != NULL)
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

#include<vector>
#include<stdexcept>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<ctime>
#include<algorithm>

using std::vector;
using std::exception;
using std::find;

namespace jj02
{
	void test_vector(const long& value)
	{
		cout << "\ntest_vector()......\n";

		vector<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception & p)
			{
				// �������i=58389486 then std::bad_alloc
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "vector.size()= " << c.size() << endl;
		cout << "vector.front()= " << c.front() << endl;
		cout << "vector.back()= " << c.back() << endl;
		cout << "vector.data()= " << c.data() << endl;
		cout << "vector.capacity()= " << c.capacity() << endl;

		string target = get_a_target_string();
		

		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds: " << clock() - timeStart << endl;

		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}

		timeStart = clock();
		sort(c.begin(), c.end());
		string* pItem2 = (string*)bsearch(&target, (c.data()), c.size(), sizeof(string), compareStrings);
		cout << "sort() + bsearch(), milli-seconds: " << clock() - timeStart << endl;

		if (pItem2 != NULL)
		{
			cout << "found, " << *pItem2 << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

#include<list>

using std::list;

namespace jj03
{
	void test_list(const long& value)
	{
		cout << "\ntest_list()......\n";

		list<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch(exception &p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "list.size()= " << c.size() << endl;
		cout << "list.max_size()= " << c.max_size() << endl;
		cout << "list.front()= " << c.front() << endl;
		cout << "list.back()= " << c.back() << endl;

		string target = get_a_target_string();
		timeStart = clock();

		auto pItem = find(c.begin(), c.end(), target);
		cout << "find(), milli-seconds: " << clock() - timeStart << endl;

		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}

		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds:" << clock() - timeStart << endl;
	}
}

#include<forward_list>

using std::forward_list;

namespace jj04
{
	void test_forward_list(const long& value)
	{
		cout << "\ntest_forward_list()......\n";

		forward_list<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push_front(string(buf));
			}
			catch (exception & p)
			{
				cout << "i = " << i << " " << p.what() << endl;
				abort();
			}
		}
		// forward_list��back()��size()
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "forward_list.max_size()= " << c.max_size() << endl;
		cout << "forward_list.front()= " << c.front() << endl;

		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "find(), milli-seconds: " << clock() - timeStart << endl;

		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
		
		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds: " << (clock() - timeStart) << endl;
	}
}

#include<deque>

using std::deque;

namespace jj05
{
	void test_deque(const long& value)
	{
		cout << "\ntest_deque()......\n";

		deque<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception & p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "deque.size()= " << c.size() << endl;
		cout << "deque.front()= " << c.front() << endl;
		cout << "deque.back()= " << c.back() << endl;
		cout << "deque.max_size()= " << c.max_size() << endl;

		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "find(), milli-seconds: " << (clock() - timeStart) << endl;

		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}

		timeStart = clock();
		sort(c.begin(), c.end());
		cout << "sort(), milli-seconds: " << (clock() - timeStart) << endl;
	}
}

#include<stack>

using std::stack;

namespace jj17
{
	void test_stack(const long& value)
	{
		cout << "\ntest_stack()......\n";
		
		stack<string> c;
		char buf[10];
		
		clock_t timeStart = clock();

		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			catch(exception & p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "stack.size()= " << c.size() << endl;
		cout << "stack.top()= " << c.top() << endl;
		c.pop();
		cout << "stack.size()= " << c.size() << endl;
		cout << "stack.top()= " << c.top() << endl;

	}
}

#include<queue>

using std::queue;

namespace jj18
{
	void test_queue(const long& value)
	{
		cout << "\ntest_queue()......\n";
		queue<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			catch (exception & p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "queue.size()= " << c.size() << endl;
		cout << "queue.front()= " << c.front() << endl;
		cout << "queue.back()= " << c.back() << endl;
		c.pop();
		cout << "queue.size()= " << c.size() << endl;
		cout << "queue.front()= " << c.front() << endl;
		cout << "queue.back()= " << c.back() << endl;
	}
}

#include<set>

using std::multiset;

namespace jj06
{
	void test_multiset(const long& value)
	{
		cout << "\ntest_multiset()......\n";

		multiset<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception & p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "multiset.size()=" << c.size() << endl;
		cout << "multiset.max_size()=" << c.max_size() << endl;

		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}

		timeStart = clock();
		pItem = c.find(target);
		cout << "c.find(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

#include<map>

using std::multimap;
using std::pair;

namespace jj07
{
	void test_multimap(const long& value)
	{
		cout << "\ntest_multimap()......\n";

		multimap<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				// multimap����ʹ��[]��insertion
				c.insert(pair<long, string>(i, buf));
			}
			catch (exception & p)
			{
				cout << "i =" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "multimap.size()=" << c.size() << endl;
		cout << "multimap.max_size()=" << c.max_size() << endl;

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds: " << clock() - timeStart << endl;
		if (pItem != c.end())
		{
			cout << "found, value=" << (*pItem).second << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

#include<unordered_set>

using std::unordered_multiset;

namespace jj08
{
	void test_unordered_multiset(const long& value)
	{
		cout << "\ntest_unordered_multiset......\n";

		unordered_multiset<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception & p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		// ���Ԫ�ص��������ڵ���������������ô����������Ҫ����Ϊ(G++) 2����(MSVC) 1.5����
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "unordered_multiset.size()= " << c.size() << endl;
		cout << "unordered_multiset.max_size()= " << c.max_size() << endl;
		cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
		cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
		cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;
		cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;
		for (unsigned i = 0; i < 40; ++i) {
			cout << "bucket #" << i << " has " << c.bucket_size(i) << "elements.\n";
		}

		string target = get_a_target_string();
		timeStart = clock();

		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}

		timeStart = clock();
		pItem = c.find(target);
		cout << "c.find(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found! " << endl;
		}
		//c.clear();
		//test_moveable(unordered_multisetM<MyString>)
	}
}

#include<unordered_map>

using std::unordered_multimap;

namespace jj09
{
	void test_unordered_multimap(const long& value)
	{
		cout << "\ntest_unordered_multimap()......\n";

		unordered_multimap<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				// unordered_multimap����ʹ��[]��insertion
				c.insert(pair<long, string>(i, buf));
			}
			catch (exception & p)
			{
				cout << "i =" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "unordered_multimap.size()=" << c.size() << endl;
		cout << "unordered_multimap.max_size()=" << c.max_size() << endl;

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds: " << clock() - timeStart << endl;
		if (pItem != c.end())
		{
			cout << "found, value=" << (*pItem).second << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

using std::set;

namespace jj13
{
	void test_set(const long& value)
	{
		cout << "\ntest_set()......\n";

		set<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception & p)
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "set.size()=" << c.size() << endl;

		cout << "set.max_size()=" << c.max_size() << endl;

		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}

		timeStart = clock();
		pItem = c.find(target);
		cout << "c.find(), milli-seconds: " << (clock() - timeStart) << endl;
		if (pItem != c.end())
		{
			cout << "found, " << *pItem << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

using std::map;

namespace jj14
{
	void test_map(const long& value)
	{
		cout << "\ntest_map()......\n";

		map<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c[i] = string(buf);
			}
			catch (exception & p)
			{
				cout << "i =" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds: " << (clock() - timeStart) << endl;
		cout << "map.size()=" << c.size() << endl;
		cout << "map.max_size()=" << c.max_size() << endl;

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds: " << clock() - timeStart << endl;
		if (pItem != c.end())
		{
			cout << "found, value=" << (*pItem).second << endl;
		}
		else
		{
			cout << "not found!" << endl;
		}
	}
}

// Ӧ��ʹ������������ֱ��ʹ�÷���������Ϊ��������allocate��deallocateʱ����Ҫ�������������allocate��������deallocate��һ�£����������
// listû��������ʵ�����������std::sort()���漰��*(first + (last - first)/2)�����Դ������ĵ�����������������ʵ����������list������std::sort()����ֻ���Դ���list.sort()��
// algorithm�бȽ�string��С��Ĭ�����ֵ�Ƚϣ�������Ƚ��ַ���ASCII����ĸ��������ǿ��԰ѱȽϺ����Զ���Ϊ�Ƚ�string����
// ����ģ��template <class T, class Alloc = alloc> class vector{ ... };��д��template<class Alloc> class vector<bool, Alloc>{ ... };�ͱ�ʾƫ�ػ�(partial specialization)���߾ֲ��ػ�����ʾָ���Ե�һ������Ϊbool���ͣ��ڶ�������Ϊ�������͵��������д��class
// ��ȫ�ػ���ʾģ���е����в�������ָ��Ϊĳһ�����µ��������
// ����templace<class Iterator> struct iterator_traits {...};��д��template<class T> struct iterator_traits<T*> {...}; Ҳ��һ��ƫ�ػ�����ʾ��Բ���Ϊָ���������͵�ָ��ʱ�����
// ͬ������template<class T> struct iterator_traits<const T*>��Ҳ��һ��ƫ�ػ�
// Ҳ����˵ƫ�ػ��в���������ƫ�ػ���Ҳ�в�����Χ��ƫ�ػ�
// __pool_alloc����GCC2.9��alloc��Ч�ʱ�Ĭ��allocator��
// �÷���vector<string, __gnu_cxx::__pool_alloc<string>> vec;

using std::allocator;

namespace jjmy {
	void testAllocator() {
		// ��һ��������ʾ����ĸ������ڶ�����������ʲôֵ�����������ģ���ֻ��Ҫ֪���㴫�����ʲô���ͣ���˿��Եڶ���������һ��int*������ֵ����
		int* p = allocator<int>().allocate(512, (int*)0);
		allocator<int>().deallocate(p, 512);
	}
}

// ����ʽ�����У�
// heap������vector��priority_queue������heap������������Ǹ���(composition)������˵privete�̳У�������public�̳й�ϵ��
// stack��queue������deque��set��map��multiset��multimap��������rb_tree�� 
// ���������г���vector�ĵ�����֮�⣬���������ĵ�������Ӧ����һ��class��һ������ָ�룬����ʵ����list�ĵ����������ȡ��ǰ�ڵ��nextָ�룬ָ�����Ľڵ��������ӵĹ���
// �������л��д����Ĳ��������أ���*��->��ǰ��++������++
int main()
{
	//jj01::test_array();

	//jj02::test_vector(1000000);

	//jj03::test_list(1000000);

	//jj04::test_forward_list(1000000);

	//jj05::test_deque(1000000);

	//jj06::test_multiset(1000000);

	//jj07::test_multimap(1000000);

	//jj08::test_unordered_multiset(1000000);

	//jj09::test_unordered_multimap(1000000);

	//jj13::test_set(1000000);

	//jj14::test_map(1000000);

	//jj17::test_stack(1000000);

	//jj18::test_queue(1000000);

	jjmy::testAllocator();

	system("pause");
	return 0;
}