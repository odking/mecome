/*
 * =====================================================================================
 *
 *       Filename:  threesum.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2020 02:56:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class ThreeSum {
public:
    vector<vector<int>> threesum(vector<int> &nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        for (int i = 0; i < n; i++)
        {
            if (i != 0 && nums[i] == nums[i-1])
                continue;

            int third = n -1;
            target -= i;
            for (int j = i + 1; j < n; j++)
            {
                if (j > i +1 && nums[j] == nums[j-1])
                {
                    while (j <= third && nums[j ] + nums[third] > target)
                        third--;

                    if (j == third)
                        break;

                    if (nums[j] + nums[third] == target)
                    {
                        vector<int> v = {nums[i], nums[j], nums[third]};
                        ans.push_back(v);
                    }
                }
            }

        }

        return ans;
    }
};

int main() {
    vector<int> input = { 1,2,3,-1, 0, -3, 4 ,5, 2,4,3,6,0, -2, -1 };
    int target = 0;

    vector<vector<int>> v = ThreeSum().threesum(input, target);
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
            cout << v[i][j] << " " ;
        cout << endl;
    }

    return 0;

}


