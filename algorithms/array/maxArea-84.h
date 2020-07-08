/*
 * =====================================================================================
 *
 *       Filename:  maxArea-84.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2020 07:15:26 AM
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
using namespace std;

class MaxArea84 {
public:

    int getHeight(vector<int> hs, int cur, int start, int end) {
        int height = cur;
        for (int i = start+1; i < end; i++)
        {
            if (hs[i] < height) height=hs[i];
        }
        return height;
    }
    int largestRectangleArea(vector<int>& heights) {
        if (heights.size() == 0) return 0;
        if (heights.size() ==1) return heights[0];
        int i;
        int max = heights[0];
        for ( i = 0; i < heights.size(); i++) {
            if (heights[i] == 0) continue;

            max = max < heights[i] ? heights[i] : max;

            for (int j = i + 1; j < heights.size(); j++)
            {
                if (heights[j] == 0) break;
                int wide = j - i + 1;
                int height = getHeight(heights, heights[i] < heights[j] ? heights[i]: heights[j], i, j);
                int area = wide * height;
                max = max < area ? area: max;

            }
        }
        return max;
    }
};
