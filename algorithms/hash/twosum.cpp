/*
 * =====================================================================================
 *
 *       Filename:  twosum.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/30/2020 12:17:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twosum(vector<int>& nums, int target) {
        vector<int> result;
        unordered_map<int, int> hm;
        for (int i = 0; i < nums.size(); i++) {
            int an = target - nums[i];
            if (hm.find(an) != hm.end()) {
                result.push_back(i);
                result.push_back(hm[an]);
                break;
            }
            else {
                hm.insert(make_pair(nums[i], i));
                cout << "inset" <<nums[i] << " " << i << endl;
            }
        }

        return result;
    }
};

int main()
{
    vector<int> v;
    v.push_back(15);
    v.push_back(2);
    v.push_back(7);
    v.push_back(11);

    Solution s;
    vector<int> r = s.twosum(v, 9);
    cout << r[0] << " " << r[1] << endl;

    return 0;
}


