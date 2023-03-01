#include <iostream>

#include "../util/TestRunner.hpp"

using namespace std;

int main()
{
	TestRunner::RunSorterTests();
	TestRunner::RunSinglyLinkedList();
	TestRunner::RunDoublyLinkedList();
	TestRunner::RunQueue();
	TestRunner::RunStack();

	return 0;
}