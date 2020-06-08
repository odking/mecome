/*
 * =====================================================================================
 *
 *       Filename:  huiwen.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/02/2020 01:06:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <iostream>
using namespace std;

class LongestPalidrome {
public:
    pair<int, int> expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }

        return {left + 1, right -1};
    }

    // condition, expand from i or expand from {i,i+1}
    // time O(n*n), space O(1);
    string longestPalidrome(string s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.length(); i++)
        {
            auto [start1, end1] = expand(s, i, i);
            auto [start2, end2] = expand(s, i, i+1);
            if (end1 - start1 > end - start)
            {
                start = start1;
                end = end1;
            }
            if (end2 - start2 > end - start)
            {
                start = start2;
                end = end2;
            }
        }

        return s.substr(start, end - start + 1);
    }
};

int main() {
    string s = "abcbd";
    cout << LongestPalidrome().longestPalidrome(s) << endl;
    return 0;
}
