/*
 * =====================================================================================
 *
 *       Filename:  maxArea.cpp
 *
 *    Description:  the max area of two element in array.
 *
 *        Version:  1.0
 *        Created:  06/08/2020 12:43:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef MAX_AREA_H
#define MAX_AREA_H

#include <vector>

class MaxArea {
public:
    int maxArea(std::vector<int>& height) {
        int j = height.size() - 1;
        int max = 0, i = 0;

        while (i < j) {
            int h = j - i;
            int v = height[j] > height[i] ? height[i] : height[j];
            int m = h * v;
            if (m > max)
                max = m;
            if (height[i] < height[j])
                i++;
            else
                j--;

        }
        return max;
    }
};

#endif
