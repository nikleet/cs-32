/**
 * CS 32, Homework 3, tree.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/8/2023
*/

// #include <string>
// #include <cassert>
// #include <iostream>
// 
// using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "adam"
// then for this value of a2            the function must return
//    "john" "ketanji" "elena"                     1
//    "john" "elena" "adam"                      2
//    "ketanji" "john" "elena"                     0
//    "sonia" "elena" "adam"                     3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
        return 1;
    if (n1 > 0) {
        if (a1[n1 - 1] == a2[n2 - 1])
            return countIncludes(a1, n1 - 1, a2, n2) + countIncludes(a1, n1 - 1, a2, n2 - 1);
        else
            return countIncludes(a1, n1 - 1, a2, n2);
    }
    return 0;
}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
    int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;

    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < separator
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > separator

    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if (n <= 1)
        return;
    int fnl;    // first not less
    int fg;     // first not greater
    separate(a, n, a[n/2], fnl, fg);
    order(a, fnl);
    order(a + fg, n - fg);
}

// void orderPrint(string a[], int n) {
//     order(a, n);
//     for(int i = 0; i < n - 1; i++)
//         cout << a[i] << ", ";
//     cout << a[n-1] << endl;
// }
// 
// int main() {
// 
//     // test countIncludes                                                                       NEED TO TEST EDGE CASES!
//     string a1[] = { "john", "sonia", "elena", "ketanji", "sonia", "elena", "adam" };
//     //    "john" "ketanji" "elena"                      1
//     //    "john" "elena" "adam"                         2
//     //    "ketanji" "john" "elena"                      0
//     //    "sonia" "elena" "adam"                        3
//     string a2[] = { "john", "ketanji", "elena" };
//     string a3[] = { "john", "elena", "adam" };
//     string a4[] = { "ketanji", "john", "elena" };
//     string a5[] = { "sonia", "elena", "adam" };
// 
//     assert(countIncludes(a1, 7, a2, 3) == 1); 
//     assert(countIncludes(a1, 7, a3, 3) == 2);
//     assert(countIncludes(a1, 7, a4, 3) == 0);
//     assert(countIncludes(a1, 7, a5, 3) == 3);
//     assert(countIncludes(a1, 0, a2, 0) == 1);
//     assert(countIncludes(a1, 7, a2, 0) == 1);
//     assert(countIncludes(a1, 0, a2, 3) == 0);
// 
//     // test order
//     string s1[] = { "b", "e", "t", "a", "c", "v", "m", "p", "o", "e", "x", "q" };
//     string s2[] = { "b", "e", "t", "a", "c", "v", "m", "p", "o", "e", "x", "q", "y"};
//     string s3[] = {"x"};
//     string s4[] = {"b", "a"};
//     orderPrint(s1, 12);
//     orderPrint(s2, 13);
//     orderPrint(s3, 1);
//     orderPrint(s4, 2);
//     orderPrint(s1, 1);
// 
//     cout << "All tests passed." << endl;
//     return 0;
// }