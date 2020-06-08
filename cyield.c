/*
 * =====================================================================================
 *
 *       Filename:  cyield.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/02/2020 07:19:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#define Begin() static int state=0; switch(state) { case 0:
#define Yield(x) do { state=__LINE__; printf("%d ", x); return x; case __LINE__:; } while (0)
#define End() }
int function(void) {
  static int i;
  Begin();
  for (i = 0; i < 10; i++)
    Yield(i);
  End();
}

int main()
{
    function();
    function();
    return 0;
}
