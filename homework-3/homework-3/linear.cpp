/**
 * CS 32, Homework 3, linear.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/8/2023
*/

/*
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
bool somePredicate(string s) { return s.empty(); }
*/


// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n <= 0)
        return true;
    if (!somePredicate(*a))
        return false;
    return allTrue(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    if (n <= 0)
        return 0;
    if (somePredicate(*a))
        return 1 + countTrue(a + 1, n - 1);
    return countTrue(a + 1, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if (n <= 0)
        return -1;
    if (somePredicate(*a))
        return 0;
    int res = firstTrue(a + 1, n - 1);
    if (res == -1)
        return -1;
    return res + 1;
}

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if (n > 1) {
        int posMax = positionOfMax(a, n - 1);
        if (a[n - 1] > a[posMax])
            posMax = n - 1;
        return posMax;
    }
    if (n == 1)
        return 0;
    return -1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1 > 0) {
        if (a1[n1 - 1] == a2[n2 - 1])
            return contains(a1, n1 - 1, a2, n2 - 1);
        else
            return contains(a1, n1 - 1, a2, n2);
    }
    return false;
}

/*
int main() {
    // test allTrue
    string s1[] = { "","","","","" };
    string s2[] = { "","","x","x","" };
    string s3[] = { "x", "x", "", "x", "x" };
    string s4[] = { "a", "b", "e", "e", "d" };
    assert(allTrue(s1, 5));
    assert(!allTrue(s2, 5));
    assert(allTrue(s2, 2));
    
    // test countTrue
    assert(countTrue(s2, 5) == 3);
    assert(countTrue(s2, 3) == 2);
    
    // test firstTrue
    assert(firstTrue(s3, 5) == 2);
    assert(firstTrue(s3, 2) == -1);
    
    // test positionOfMax
    assert(positionOfMax(s4, 5) == 2);
    
    // test contains
    string s5[] = { "john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel" };
    string s6[] = { "sonia", "ketanji", "samuel" };
    string s7[] = { "sonia", "elena", "elena" };
    string s8[] = { "sonia", "samuel", "ketanji" };
    string s9[] = { "john", "ketanji", "ketanji" };
    assert(contains(s5, 7, s6, 3));
    assert(contains(s5, 7, s7, 3));
    assert(!contains(s5, 7, s8, 3));
    assert(!contains(s5, 7, s9, 3));

    cout << "All tests passed." << endl;
    return 0;
}
*/