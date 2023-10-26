#include "mergesort.h"

void merge(int* arr, unsigned start, unsigned mid, unsigned end)
{
    int* temp = new int[end - start];

    for (unsigned i = 0; i < mid - start; i++)
        temp[i] = arr[i + start];
    for (unsigned j = 0; j < end - mid; j++)
        temp[mid - start + j] = arr[j + mid];

    unsigned i = 0;
    unsigned j = 0;
    unsigned k = start;
    while (i < mid - start && j < end - mid) 
    {
        if (temp[i] <= temp[mid - start + j])
        {
            arr[k++] = temp[i++];
        }
        else
        {
            arr[k++] = temp[mid - start + j++];
        }
    }

    while (i < mid - start)
    {
        arr[k++] = temp[i++];
    }
    while (j < end - mid)
    {
        arr[k++] = temp[mid - start + j++];
    }

    delete[] temp;
}

void mergesort(int* a, unsigned p, unsigned r)
{
	if (p + 1 < r)
	{
        unsigned m = p + (r - p) / 2;

        mergesort(a, p, m);
        mergesort(a, m, r);
 
        merge(a, p, m, r);
	}
}