#include "perm-jt.h"
#include <iterator> //ostream_iterator
#include <algorithm>
#include <iostream>
#include <set>

struct Print
{
	void operator() (std::vector<int> const& v) const
	{
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}
};

void PrintVectorWithDirection(const std::vector<int>& array, const std::vector<int>& dir)
{
	for (size_t i = 0; i < array.size(); ++i)
	{
		std::string dirSymbol;
		if (dir[i] > 0)
			dirSymbol = ">";
		else
			dirSymbol = "<";


		std::cout << dirSymbol << array[i] << " ";
	}
	std::cout << "\n";
}

void PrintVector(const std::vector<int>& array)
{
	for (const int element : array)
	{
		std::cout << element << " ";
	}
	std::cout << "\n";
}

int factorial(int value)
{
	if (value == 0 || value == 1)
		return 1;

	return value * factorial(value - 1);
}

int main()
{
	// decleration
	std::vector<int> myArr;
	std::vector<int> dir;

	// Total size
	constexpr int size = 5;

	// Initialization
	myArr.reserve(size);
	dir.reserve(size);

	for (int i = 0; i < size; ++i)
	{
		myArr.emplace_back(i + 1);
		dir.emplace_back(-1);
	}

	// Printing Vector
	//PrintVectorWithDirection(myArr, dir);
	PrintVector(myArr);

	// Implementation of JT Algorithm
	for (int i = 0; i < factorial(size); ++i)
	{
		// find the largest element index
		int largestIndex = static_cast<int>(std::distance(myArr.begin(), std::max_element(myArr.begin(), myArr.end())));
		//std::cout << "Largest Index: " << largestIndex << "\n";

		// swap the largest element in the direction by size - 1 times
		do
		{
			const int swapIndex = largestIndex + dir[largestIndex];
			if (swapIndex >= 0 && swapIndex < size)
			{
				std::swap(myArr[largestIndex], myArr[swapIndex]);
				std::swap(dir[largestIndex], dir[swapIndex]);
				largestIndex = swapIndex;
				//PrintVectorWithDirection(myArr, dir);
				PrintVector(myArr);
			}
		} while (largestIndex > 0 && largestIndex < size - 1);

		// Find the largest mobile element
		int mobileElementIndex = -1;
		for (int j = 0; j < static_cast<int>(myArr.size()); ++j)
		{
			if (j == largestIndex)
				continue;

			const int nextIndex = j + dir[j];
			if (nextIndex >= 0 && nextIndex <= static_cast<int>(myArr.size() - 1) && // checking validity of nextIndex
				myArr[j] > myArr[nextIndex])
			{
				mobileElementIndex = j;
			}
		}

		if (mobileElementIndex == -1)
			break;

		// Swap what mobile index is pointing towards
		const int swapIndex = mobileElementIndex + dir[mobileElementIndex];
		if (swapIndex >= 0 && swapIndex <= size - 1)	// checking validity of swapIndex
		{
			// Change the direction of all greater elements
			for (int j = 0; j < static_cast<int>(myArr.size()); ++j)
			{
				if (myArr[j] > myArr[mobileElementIndex])
					dir[j] *= -1;
			}

			std::swap(myArr[mobileElementIndex], myArr[swapIndex]);
			std::swap(dir[mobileElementIndex], dir[swapIndex]);
			
			//PrintVectorWithDirection(myArr, dir);
			PrintVector(myArr);
		}
	}

	return 0;

	////// Driver Code ////////////////////
	//PermJohnsonTrotter pjt(5);
	//Print printer;

	//do
	//{
	//	printer(pjt.Get());
	//	//pjt.Print();
	//} while (pjt.Next());
	///////////////////////////////////////
}
