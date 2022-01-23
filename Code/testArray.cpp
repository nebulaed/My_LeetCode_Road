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
		// qsort的输入：数组起始地址c.data()，数组元素数量ASIZE，元素类型long，怎么比较大小，compareLongs
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
				// 曾经最高i=58389486 then std::bad_alloc
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
		// forward_list无back()和size()
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
				// multimap不可使用[]做insertion
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
		// 如果元素的数量大于等于篮子数量，那么篮子数量就要扩充为(G++) 2倍或(MSVC) 1.5倍。
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
				// unordered_multimap不可使用[]做insertion
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

// 应该使用容器，而非直接使用分配器，因为分配器在allocate和deallocate时都需要给出数量，如果allocate的数量和deallocate不一致，会带来问题
// list没有随机访问迭代器，由于std::sort()中涉及到*(first + (last - first)/2)，所以传进来的迭代器必须是随机访问迭代器，因此list不能用std::sort()排序，只有自带的list.sort()。
// algorithm中比较string大小，默认是字典比较，即逐个比较字符在ASCII码表哪个更大；我们可以把比较函数自定义为比较string长度
// 对于模版template <class T, class Alloc = alloc> class vector{ ... };，写下template<class Alloc> class vector<bool, Alloc>{ ... };就表示偏特化(partial specialization)或者局部特化，表示指定对第一个参数为bool类型，第二个参数为任意类型的情况，重写该class
// 而全特化表示模版中的所有参数都被指定为某一类型下的特殊情况
// 对于templace<class Iterator> struct iterator_traits {...};，写下template<class T> struct iterator_traits<T*> {...}; 也是一种偏特化，表示针对参数为指向任意类型的指针时的情况
// 同样对于template<class T> struct iterator_traits<const T*>，也是一种偏特化
// 也就是说偏特化有参数个数的偏特化，也有参数范围的偏特化
// __pool_alloc就是GCC2.9的alloc，效率比默认allocator高
// 用法：vector<string, __gnu_cxx::__pool_alloc<string>> vec;

using std::allocator;

namespace jjmy {
	void testAllocator() {
		// 第一个参数表示传入的个数，第二个参数传入什么值函数并不关心，它只是要知道你传入的是什么类型，因此可以第二参数传入一个int*的任意值即可
		int* p = allocator<int>().allocate(512, (int*)0);
		allocator<int>().deallocate(p, 512);
	}
}

// 序列式容器中：
// heap衍生自vector，priority_queue衍生自heap，这里的衍生是复合(composition)，或者说privete继承，而不是public继承关系。
// stack和queue衍生自deque，set、map、multiset、multimap都衍生自rb_tree。 
// 所有容器中除了vector的迭代器之外，其他容器的迭代器都应该是一个class，一个智能指针，才能实现像list的迭代器必须读取当前节点的next指针，指向后面的节点这样复杂的功能
// 迭代器中会有大量的操作符重载，如*，->，前置++，后置++
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