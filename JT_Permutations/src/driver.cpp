#include <iterator> //ostream_iterator
#include <algorithm>
#include <iostream>

#include "perm-jt.h"
#include <rawJT.h>

struct Print
{
	Print()
		:	lineNumber(0)
	{
	}

	void operator() (const std::vector<int>& vector)
	{
		++lineNumber;

		std::cout << lineNumber << ":\t";
		std::copy(vector.begin(), vector.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}

private:
	int lineNumber;
};

int main()
{
	PermJohnsonTrotter pjt(5);
	Print printer;

	do
	{
		printer(pjt.Get());
	} while (pjt.Next());

	return 0;
}
