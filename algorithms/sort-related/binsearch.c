/*
 * =====================================================================================
 *
 *       Filename:  binsearch.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2020 05:27:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "sort.h"

static int helper(int* array, int start, int end, int data)
{
    if (start > end) return -1;

    int mid = (start + end) / 2;
    if (array[mid] == data) return mid;
    if (array[mid] < data) return helper(array, mid+1, end, data);
    else return helper(array, start, mid - 1, data);
}

int binsearch(int* array, int data, int len)
{
    return helper(array, 0, len-1, data);
}
