#include "newSequence.h"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

int main()
{
    Sequence s(0);
    assert(s.insert(5) == -1);
    s.dump();
    Sequence a(5);
    assert(a.insert(1) == 0);
    assert(a.insert(3) == 1);
    assert(a.insert(2) == 1);
    assert(a.insert(4) == 3);
    assert(a.insert(5) == 4);
    assert(a.insert(6) == -1);
    cout << "assigning a to s..." << endl;
    s = a;
    cout << "dump s:" << endl;
    s.dump();
    cout << "a: " << endl;
    a.dump();
    Sequence b(a);
    cout << "b is a copy of a: " << endl;
    b.dump();
    Sequence c(3);
    assert(c.insert(2, 100) == -1);
    assert(c.insert(0, 100) == 0);
    assert(c.insert(98) == 0);
    assert(c.insert(97) == 0);
    cout << "dump c:" << endl;
    c.dump();
    test();
    cout << "All tests passed." << endl;
}