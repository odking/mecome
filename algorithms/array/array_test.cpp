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
#include "maxArea-84.h"
#include "movezero-283.h"
#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int> v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        cout <<  *it << " ";
    cout << endl;
}

int main() {

    cout << "********************array test*****************"<< endl;
    cout << "test 1 - max area between array index" << endl;
    vector<int> data = {0,1,0,3,12};
    cout << MaxArea().maxArea(data) << endl;
    cout << "test 2 - move zeors" << endl;
    cout << "input: " << endl;
    printVector(data);
    MoveZero().moveZero(data);
    printVector(data);
    cout << "test 3 - max area 84" << endl;
    vector<int> v = {5,5,1,7,1,1,5,2,7,6};
    cout << "resut " << MaxArea84().largestRectangleArea(v) << endl;
    return 0;
}


