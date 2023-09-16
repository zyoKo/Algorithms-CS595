#include "perm-lexicographical.h"
#include <iterator> //ostream_iterator
#include <algorithm>
#include <functional>
#include <iostream>

struct Print
{
	void operator() (std::vector<int> const& v) const
	{
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}
};


void run(int s)
{
	std::vector<int> v(s);

	for (int i = 0; i < s; ++i) 
		v[i] = i + 1;

	Print printer;

	do { printer(v); } while (nextPermLexicographical(v));
}

void test0() { run(5); }
void test1() { run(6); }

//void (*pTests[])(void) = { test0, test1 };
std::vector<std::function<void()>> tests{ test0, test1 };

#include <cstdio> //sscanf
int main(int argc, char** argv)
{
	for (const auto& test : tests)
		test();

	return 0;
}
