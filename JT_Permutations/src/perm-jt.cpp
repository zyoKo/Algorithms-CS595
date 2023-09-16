#include "perm-jt.h"

#include <algorithm>

PermJohnsonTrotter::PermJohnsonTrotter(int size)
	:	array(),
		direction(),
		largestIndex(0),
		mobileIndexFound(true),
		mobileElementIndex(-1)
{
	//array.reserve(size);
	for (int i = 0; i < size; ++i)
		array.push_back(i + 1);

	//direction.reserve(size);
	for (int i = 0; i < size; ++i)
		direction.push_back(-1);	// -1 for left (init all direction to left)
}

bool PermJohnsonTrotter::Next()
{
	largestIndex = static_cast<int>(std::distance(array.begin(), std::max_element(array.begin(), array.end())));

	if (mobileIndexFound || (largestIndex > 0 && largestIndex < static_cast<int>(array.size()) - 1))
	{
		const int swapIndex = largestIndex + direction[largestIndex];
		if (swapIndex >= 0 && swapIndex < static_cast<int>(array.size()))
		{
			std::swap(array[largestIndex], array[swapIndex]);
			std::swap(direction[largestIndex], direction[swapIndex]);
			largestIndex = swapIndex;
		}

		if (mobileIndexFound)
			mobileIndexFound = false;
	}
	else
	{
		// Find the largest mobile element
		mobileElementIndex = -1;
		//int mobileElementIndexPrev = mobileElementIndex;
		for (int j = 0; j < static_cast<int>(array.size()); ++j)
		{
			if (j == largestIndex)
				continue;

			const int nextIndex = j + direction[j];
			if (nextIndex >= 0 && nextIndex <= static_cast<int>(array.size() - 1) && // checking validity of nextIndex
				array[j] > array[nextIndex])
			{
				if (mobileElementIndex > 0)
				{
					if (array[j] > array[mobileElementIndex])
						mobileElementIndex = j;
				}
				else
				{
					mobileElementIndex = j;
				}
			}
		}

		// no mobile index found, stop execution
		if (mobileElementIndex == -1)
			return false;

		mobileIndexFound = true;

		// Swap what mobile index is pointing towards
		const int swapIndex = mobileElementIndex + direction[mobileElementIndex];
		if (swapIndex >= 0 && swapIndex <= static_cast<int>(array.size()) - 1)	// checking validity of swapIndex
		{
			// Change the direction of all greater elements
			for (int j = 0; j < static_cast<int>(array.size()); ++j)
			{
				if (array[j] > array[mobileElementIndex])
					direction[j] *= -1;
			}

			std::swap(array[mobileElementIndex], array[swapIndex]);
			std::swap(direction[mobileElementIndex], direction[swapIndex]);
		}
	}

	return true;
}

std::vector<int> const& PermJohnsonTrotter::Get() const
{
	return array;
}
