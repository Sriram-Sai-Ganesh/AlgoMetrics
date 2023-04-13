#pragma once
#include <iostream>
#include "IGraph.hpp"
using namespace std;

template<class T>
class ITree : IGraph<T>{
	// TODO Delete
	// pure virtual functions (= 0;)
	// derived classes *must* override these
	virtual size_t Height() = 0;
	virtual size_t Size() = 0;
	virtual void Insert(T arg) = 0;
	virtual void Delete(T arg) = 0;
	virtual bool Contains(T arg) = 0;
};