/*
 * =====================================================================================
 *
 *       Filename:  qsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2020 12:32:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "sort.h"

int iterator_index(int* data, int start, int end)
{
    int p = data[start];
    while (start < end) {
        while (start < end && data[end] >= p)
            end--;

        data[start]=data[end];
        while (start < end && data[start] <= p)
            start++;

        data[end]=data[start];
    }
    data[start]=p;
    return start;
}

int qsort_helper(int*data, int start, int end)
{
    if (start >= end) return 0;

    int it = iterator_index(data, start, end);
    qsort_helper(data, 0, it-1);
    qsort_helper(data, it+1, end);
    return 0;
}

int qsort(int *data, int len)
{
    return qsort_helper(data, 0, len-1);
}
