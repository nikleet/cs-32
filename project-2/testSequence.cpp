/**
 * CS 32, Project 2, testSequence.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 4/24/2023
*/

#include <iostream>
#include <cassert>
#include "Sequence.h"
#include <iostream>

using namespace std;

bool checkEqual(Sequence& a, Sequence& b) {
    ItemType aa;
    ItemType bb;
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++) {
        a.get(i, aa);
        a.get(i, bb);
        if (aa != bb)
            return false;
    }
    return true;
}

void test()
{
    Sequence s;
    assert(s.insert(0, 10) == 0);   // test insert first item
    assert(s.insert(0, 20) == 0);   // test insert at beginning of list
    assert(s.insert(30) == 2);      // test one-argument insert 
    assert(s.insert(25) == 2);      // ...
    assert(s.insert(21) == 2);      // ...
    assert(s.insert(-2, 10) == -1); // test invalid argument for insert
    assert(s.insert(7, 50) == -1);  // ...
    assert(s.insert(4, 40) == 4);   // test insert at end of list
    assert(s.insert(4, 1000) == 4); // test insert in middle of list
    assert(s.size() == 7);          // test size()
    s.dump();
    ItemType x = 999;
    assert(s.get(1, x) && x == 10); // test get()
    assert(s.get(0, x) && x == 20); // ...
    Sequence t;
    assert(t.empty());              // test empty()
    t = s;                          
    t.dump();
    assert(checkEqual(t, s));       // test assignment operator
    Sequence c(s);                  
    c.dump();
    assert(checkEqual(c, s));       // test copy constructor
    c.insert(20);
    assert(c.remove(20) == 2);      // test remove() for items in list
    assert(c.remove(-10) == 0);     // test remove() for item not in list
    c.dump();
    assert(c.find(1000) == 3);       // test find() for item in list
    assert(c.find(-10) == -1);       // test find() for item not in list
    // s and t are currently the same
    Sequence a(c);
    c.swap(s);
    assert(checkEqual(c, t));       // test swap()
    assert(checkEqual(s, a));       // test swap()
    
    Sequence seq1;
    Sequence seq2;
    seq1.insert(0, 30);
    seq1.insert(1, 21);
    seq1.insert(2, 63);
    seq1.insert(3, 42);
    seq1.insert(4, 17);
    seq1.insert(5, 63);
    seq1.insert(6, 17);
    seq1.insert(7, 29);
    seq1.insert(8, 8);
    seq1.insert(9, 32);
    seq2.insert(0, 63);
    seq2.insert(1, 17);
    seq2.insert(2, 29);
    seq1.dump();
    seq2.dump();
    assert(subsequence(seq1, seq2) == 5);       // test subsequence() found successfully
    Sequence seq3;
    seq3.insert(0, 17);
    seq3.insert(1, 63);
    seq3.insert(2, 29);
    assert(subsequence(seq1, seq3) == -1);      // test subsequence() failed to find
    assert(subsequence(seq1, seq1) == 0);       // test subsequence() with alias
    Sequence empty;
    assert(subsequence(seq1, empty) == -1);     // test subsequence() with empty Sequence
    assert(subsequence(empty, seq1) == -1);     // test subsequence() with empty Sequence (different params)

    Sequence seq4;
    Sequence seq5;
    Sequence r;
    seq4.insert(0, 3);
    seq4.insert(1, 2);
    seq4.insert(2, 1);
    seq5.insert(0, 7);
    seq5.insert(1, 6);
    seq5.insert(2, 5);
    seq5.insert(3, 4);
    r.insert(9999);
    r.insert(10000);
    seq4.dump();
    seq5.dump();
    r.dump();
    concatReverse(seq4, seq5, r);               // test concatReverse() with different Sequences
    r.dump();
    concatReverse(seq4, seq4, seq4);            // test concatReverse() with alias
    seq4.dump();
    concatReverse(empty, empty, r);             // test concatReverse() with two empty params
    r.dump();
    assert(r.size() == 0);
    concatReverse(empty, seq5, r);              // test concatReverse() with one empty param
    r.dump();
    concatReverse(seq5, empty, r);
    r.dump();

}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

/*
#include "Sequence.h"
#include <type_traits>

#define CHECKTYPE(c, f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
             "You did not declare " #c "::" #f " as the Project 2 spec does");  \
         auto p = static_cast<r (c::*)a>(&c::f);  \
         (void) p;  \
        }
#define CHECKTYPENONMEMBER(f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&f), r (*)a>::value, \
             "You did not declare " #f " as the Project 2 spec does");  \
         auto p = static_cast<r (*)a>(f);  \
         (void) p;  \
        }

static_assert(std::is_default_constructible<Sequence>::value,
    "Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
    "Sequence must be copy-constructible.");
static_assert(std::is_copy_assignable<Sequence>::value,
    "Sequence must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(Sequence, empty, bool, () const);
    CHECKTYPE(Sequence, size, int, () const);
    CHECKTYPE(Sequence, erase, bool, (int));
    CHECKTYPE(Sequence, remove, int, (const ItemType&));
    CHECKTYPE(Sequence, get, bool, (int, ItemType&) const);
    CHECKTYPE(Sequence, set, bool, (int, const ItemType&));
    CHECKTYPE(Sequence, find, int, (const ItemType&) const);
    CHECKTYPE(Sequence, swap, void, (Sequence&));
    CHECKTYPENONMEMBER(subsequence, int, (const Sequence&, const Sequence&));
    CHECKTYPENONMEMBER(concatReverse, void, (const Sequence&, const Sequence&, Sequence&));
    { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void)p; }
    { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void)p; }
}

int main()
{}
*/