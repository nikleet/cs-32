/*

#include "RainfallList.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	RainfallList r = RainfallList();
	assert(r.add(0) == true);
	assert(r.add(400) == true);
	assert(r.add(-23459) == false);
	assert(r.add(401) == false);
	assert(r.add(150) == true);
	r.add(300);
	assert(r.remove(0) == true);
	assert(r.remove(6) == false);
	assert(r.minimum() == 150);
	assert(r.maximum() == 400);
	cout << "All tests passed! (problem 4)" << endl;
	return 0;
}
*/
