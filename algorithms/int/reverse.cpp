/*
 * =====================================================================================
 *
 *       Filename:  reverse.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/02/2020 08:23:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;
#define INT_MAX 32767
#define INT_MIN -32768

class Solution {
public:
    int reverse(int n) {
        int r = 0;
        while (n % 10 != 0){
            int x = n % 10;
            n /= 10;

            if (r > INT_MAX/10 || ( r == INT_MAX/10 && x > 7 )) return 0;
            if (r < INT_MIN/10 || (r == INT_MIN/10 && r < -8)) return 0;

            r = r*10 + x;
        }
        return r;
    }
};

int main()
{
    int i = -32723;
    cout << Solution().reverse(i) << endl;
    return 0;

}


