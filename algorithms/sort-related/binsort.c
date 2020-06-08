/*
 * =====================================================================================
 *
 *       Filename:  binsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2020 05:11:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "sort.h"

static void helper(int* data, int low, int high)
{
    if (low >= high) return;

    if (data[low] > data[low+1])
    {
        int tmp = data[low];
        data[low]=data[low+1];
        data[low+1] = tmp;
    }
    helper(data, low+1, high);
}

void buble_sort(int* data, int len)
{
    if (len <= 1) return;
    for (int i = 0; i < len-1; i++)
        helper(data, i, len-i-1);
}

