/*
 * =====================================================================================
 *
 *       Filename:  singleton.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/2020 01:13:06 AM
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

class Singleton {
private:
    static Singleton *m_inst;
private:
    Singleton() { cout  << "singleton instance" << endl; }

public:
    static Singleton* GetInstance() {
        if (m_inst == nullptr)
            return new Singleton();
        return m_inst;
    }
};

Singleton* Singleton::m_inst = nullptr;

int main() {
    Singleton* s = Singleton::GetInstance();
    return 0;
}
