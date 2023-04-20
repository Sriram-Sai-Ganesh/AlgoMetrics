#pragma once
#include <iostream>

using namespace std;

template<class T>
class IGraph{
	virtual size_t NumberOfChildren() = 0;
	virtual void Clear() = 0;
};