#pragma once
#include <iostream>
#include "IGraph.hpp"
using namespace std;

template<class T>
class ITree : IGraph<T>{
	// Pure virtual functions (= 0;).
	// Derived classes *must* override these.
	// If they don't, they're automatically considered 
	// abstract classes.
	virtual size_t Height() = 0;
	virtual size_t Size() = 0;
	virtual void Insert(T arg) = 0;
	virtual void Delete(T arg) = 0;
	virtual bool Contains(T arg) = 0;
};