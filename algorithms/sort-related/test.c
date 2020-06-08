/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2020 12:53:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "sort.h"
#include <stdio.h>

#define TEST_QSORT 0
#define TEST_BUBBLESORT 1

void print(int*data, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", data[i]);

    printf("\n");

}
int main()
{
    int data[10] = {11, 3, 9, 14, 20, 33,50,14,99, 100};

#if TEST_QSORT
    printf("qsort test\n");
    qsort(data, 10);
#endif

#ifdef TEST_BUBBLESORT
    printf("bubble sort test\n");
    buble_sort(data, 10);
    print(data, 10);
    int target = 33;
    printf("data:%d at %d in sort\n", target, binsearch(data, target, 10));
#endif

    return 0;
}