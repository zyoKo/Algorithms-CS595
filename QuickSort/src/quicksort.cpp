#include "quicksort.h"

#include <algorithm>

unsigned Partition(int* a, unsigned begin, unsigned end)
{
	const int pivot = a[end - 1];
    auto b = begin;

    for (unsigned i = begin; i < end - 1; ++i) {
        if (a[i] < pivot) { // swap
            const int temp = a[b];
            a[b] = a[i];
            a[i] = temp;

            ++b;
        }
    }

    // swap last element
    const int temp = a[b];
    a[b] = a[end - 1];
    a[end - 1] = temp;

    return b;  
}

void quicksort(int* a, unsigned begin, unsigned end) {
	if (begin + 1 < end) {
        const unsigned pivotIndex = Partition(a, begin, end);
        quicksort(a, begin, pivotIndex);
        quicksort(a, pivotIndex + 1, end);
    }
}