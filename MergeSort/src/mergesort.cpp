#include "mergesort.h"

#include <thread>

static int* temp;

void merge(int* arr, unsigned begin, unsigned mid, unsigned end) 
{

    for (unsigned i = begin; i < end; i++)
    {
        temp[i] = arr[i];
    }

    // 2 pointer Traversal
    unsigned ptrL = begin; // [begin, mid)
    unsigned ptrR = mid;   // [mid, end)
    unsigned ptr = begin;

    while (ptrL < mid && ptrR < end) 
    {
        if (temp[ptrL] <= temp[ptrR]) 
        {
            arr[ptr] = temp[ptrL];
            ++ptrL;
        }
        else 
        {
            arr[ptr] = temp[ptrR];
            ++ptrR;
        }
        ++ptr;
    }

    // copy remaining of L[]
    // R[] already in correct position
    while (ptrL < mid) 
    {
        arr[ptr] = temp[ptrL];
        ++ptr;
        ++ptrL;
    }

}

void mergesort(int* arr, unsigned p, unsigned r)
 {
    if (r - p < 2)
        return;

    temp = new int[r];  // Only allocate once to save time

    const unsigned mid = p + (r - p) / 2;
    mergesort(arr, p, mid);
    mergesort(arr, mid, r);
    merge(arr, p, mid, r);
    
    delete[] temp;
}