/*
 * =====================================================================================
 *
 *       Filename:  array_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/08/2020 12:49:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "maxArea.h"
#include <iostream>
#include <vector>
using namespace std;


int main() {

    cout << "********************array test*****************"<< endl;
    cout << "test 1 - max area between array index" << endl;
    vector<int> data = {1,8,6,2,5,4,8,3,7};
    cout << MaxArea().maxArea(data) << endl;
    return 0;
}


