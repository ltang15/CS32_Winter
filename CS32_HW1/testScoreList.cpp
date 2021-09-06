#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {

	ScoreList list;

	assert(list.add(34));
	assert(list.add(20));
	assert(list.add(5));
	assert(list.add(100));
	assert(list.add(25));
	assert(!list.add(500));
	assert(!list.add(-5));


	cout << "Min is: " << list.minimum() << endl;
	cout << "Max is: " << list.maximum() << endl;
	cout << "Size is: " << list.size() << endl;

	assert(list.remove(5));
	assert(!list.remove(8));

	cout << "After removing 5. Min is: " << list.minimum() << endl;
	cout << "Max is: " << list.maximum() << endl;


	

}