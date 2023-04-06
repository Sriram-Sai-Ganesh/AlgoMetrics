#pragma once
#include <iostream>
#include "IGraph.hpp"
using namespace std;

template<class T>
class ITree : IGraph<T>{
	// TODO Delete
	virtual size_t Height() = 0;
	virtual size_t Size() = 0;
	virtual void Insert(T arg) = 0;
	virtual bool Contains(T arg) = 0;
};