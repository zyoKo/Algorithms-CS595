#include "lis.h"

int Lis_Recursive(const std::vector<int>& arr, int n, int& max_ref, std::vector<int>& memo)
{
	if (memo[n - 1] != -1)
		return memo[n - 1];

	// Base case
	if (n == 1)
		return 1;

	int max_ending_here = 1;

	for (int i = 1; i < n; i++)
	{
		const int res = Lis_Recursive(arr, i, max_ref, memo);
		if (arr[i - 1] < arr[n - 1] && res + 1 > max_ending_here)
			max_ending_here = res + 1;
	}

	if (max_ref < max_ending_here)
		max_ref = max_ending_here;

	memo[n - 1] = max_ending_here;

	return max_ending_here;
}

int longest_increasing_subsequence(const std::vector<int>& sequence)
{
	if (sequence.empty())
		return 0;

	int length = 1;
	std::vector<int> memo(sequence.size(), -1);  // -1 means not yet calculated
	Lis_Recursive(sequence, static_cast<int>(sequence.size()), length, memo);

	return length;
}
