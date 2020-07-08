/*
 * =====================================================================================
 *
 *       Filename:  movezero-283.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2020 12:59:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
using namespace std;

class MoveZero {
public:
    int nextj(vector<int> num, int j) {
        while (num[j] == 0 && j < num.size())
            j++;
        return j;
    }

    void moveZero(vector<int> &nums) {
        int i = 0;
        int j = nextj(nums, i+1);

        while (i < j && j < nums.size()){
            if (nums[i] == 0) {
                if (nums[j] != 0) {
                    int tmp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = tmp;
                    i++;
                }
                j = nextj(nums, j);
            }
            else {
                i++;
                j = nextj(nums, i+1);
            }
        }
    }
};


