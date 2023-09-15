#include "perm-jt.h"

PermJohnsonTrotter::PermJohnsonTrotter(int size)
	:	size(size)
{
	array.reserve(size);
	for (int i = 0; i < size; ++i)
		array.emplace_back(i + 1);

	direction.reserve(size);
	for (int i = 0; i < size; ++i)
		direction.emplace_back(-1);	// -1 for left (init all direction to left)
}

bool PermJohnsonTrotter::Next()
{
	for (int i = 0; i < size; ++i)
	{
		
	}

	return false;
}

std::vector<int> const& PermJohnsonTrotter::Get() const
{
	return std::vector<int>();
}