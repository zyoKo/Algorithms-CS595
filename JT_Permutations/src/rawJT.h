/// NOTE: Don't need to run this file, it's a raw implementation (for personal reference)
///	Go to driver.cpp and perm-jt.h ////////////

#pragma once

#include <iostream>
#include <vector>

namespace RawJohnsonTrotter
{
	class JohnsonTrotter
	{
	public:
		JohnsonTrotter(int size = 5)
		{
			// Initialization
			array.reserve(size);
			direction.reserve(size);

			for (int i = 0; i < size; ++i)
			{
				array.emplace_back(i + 1);
				direction.emplace_back(-1);
			}
		}

		void Run(bool withDirectionSymbols = false)
		{
			// Printing Vector
			PrintVector(withDirectionSymbols);

			// Implementation of JT Algorithm
			for (int i = 0; i < Factorial(static_cast<int>(array.size())); ++i)
			{
				// find the largest element index
				int largestIndex = static_cast<int>(std::distance(array.begin(), std::max_element(array.begin(), array.end())));

				// swap the largest element in the direction by size - 1 times
				do
				{
					const int swapIndex = largestIndex + direction[largestIndex];
					if (swapIndex >= 0 && swapIndex < static_cast<int>(array.size()))
					{
						std::swap(array[largestIndex], array[swapIndex]);
						std::swap(direction[largestIndex], direction[swapIndex]);
						largestIndex = swapIndex;

						PrintVector(withDirectionSymbols);
					}
				} while (largestIndex > 0 && largestIndex < static_cast<int>(array.size()) - 1);

				// Find the largest mobile element
				int mobileElementIndex = -1;
				for (int j = 0; j < static_cast<int>(array.size()); ++j)
				{
					if (j == largestIndex)
						continue;

					const int nextIndex = j + direction[j];
					if (nextIndex >= 0 && nextIndex <= static_cast<int>(array.size() - 1) && // checking validity of nextIndex
						array[j] > array[nextIndex])
					{
						mobileElementIndex = j;
					}
				}

				if (mobileElementIndex == -1)
					break;

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

					PrintVector(withDirectionSymbols);
				}
			}
		}

	private:
		std::vector<int> array, direction;

		static int Factorial(int value)
		{
			if (value == 0 || value == 1)
				return 1;

			return value * Factorial(value - 1);
		}

		void PrintVector(bool withDirectionSymbols) const
		{
			for (size_t i = 0; i < array.size(); ++i)
			{
				std::string dirSymbol;
				if (withDirectionSymbols)
				{
					if (direction[i] > 0)
						dirSymbol = ">";
					else
						dirSymbol = "<";
				}

				std::cout << (withDirectionSymbols ? dirSymbol : "") << array[i] << " ";
			}
			std::cout << "\n";
		}
	};
}
