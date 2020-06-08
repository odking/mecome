/*
 * =====================================================================================
 *
 *       Filename:  zconvert.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/03/2020 01:03:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (s.length() == 0 || s.length() == 1 || numRows <= 1) return s;
        int len = s.length();
        int mod = numRows - 1;
        int med = numRows - 2;

        int lop = med + numRows;

        vector<string> v;
        int i;
        for (i = 0; i < numRows; i++)
            v.push_back("");

        for (i = 0;  i <= len/lop; i++) {
            for (int j = i * lop; j < i * lop + lop && j < len; j++)
                if (j % lop < numRows)
                    v[j%lop].push_back(s[j]);
                else
                    v[mod - j % mod].push_back(s[j]);
        }

        string r;
        for (i = 0; i < numRows; i++) {
            r.append(v[i]);
        }
        return r;
    }
};

int main()
{
    string s = "PAYPALISHIRING";
    cout << Solution().convert(s, 3) << endl;

    return 0;
}
