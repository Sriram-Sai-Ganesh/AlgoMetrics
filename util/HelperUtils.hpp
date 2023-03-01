#include <iostream>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <typeinfo>
#include <random>

#include "../util/ExecTimer.hpp"

#include "../class/SinglyLinkedList.hpp"
#include "../class/DoublyLinkedList.hpp"

using namespace std;

const unsigned seed=chrono::system_clock::now().time_since_epoch().count();		// prng seed
random_device rd;
mt19937 engine(rd());

namespace HelperUtils{

// print array 'arr' separated by ', '
template<class T, size_t len> 
void PrintArray(array<T, len> arr, ostream &out=cout)
{
	out<<"Printing array of "<<len<<" (type'"<<typeid(T).name()<<"').\n\t";
	out<<"[";
    for(size_t i=0;i<len-1;i++){
        out << arr[i] << ", ";
	}
	out<<arr[len-1]<<"]";
}


// print singly linked list 'link'
template<class T> 
void PrintSinglyLinkedList(SinglyLinkedList<T> link, ostream &out=cout){
	out<<"Printing SinglyLinkedList of length "<<link.Size()<<" (type'"<<typeid(T).name()<<"'):\n";
	out<<"[  ";
	for(auto h:link)
	{
		out<<h<<"  ";
	}
	out<<"]\n";
}


// print doubly linked list 'link'
template<class T> 
void PrintDoublyLinkedList(DoublyLinkedList<T> link, ostream &out=cout){
	
	out<<"Printing DoublyLinkedList of length "<<link.Size()<<" (type'"<<typeid(T).name()<<"'):\n";
	out<<"[  ";
	for(auto h:link)
	{
		out<<h<<"  ";
	}
	out<<"]\n";
}

// returns array populated with random T in range [min, max)
template <class T, size_t len> 
array<T, len> GetRandomArray(T min=-len, T max=len)
{
	array<T, len> result;
	uniform_real_distribution<T> distr(min, max);
	for (size_t i=0; i<result.size(); i++)
        result[i]=distr(engine);
	return result;
}

// return random T number in range [min,max]
template<class T> 
T GetRandomNumber(T min, T max){
	uniform_real_distribution<T> distr(min, max);
	return distr(engine);
}

// returns std::array populated with uniform distribution from [min, max]
template <class T, size_t len> 
array<T, len> GetUniformArray(T min=0, T max=len)
{
	array<T, len> result;
	for (size_t i=0; i<result.size(); i++)
        result[i] = min + ((max-min)*(i*1.0/result.size()));
	return result;	
}

// returns std::array with values uniform in [min, max) in random order.
template <class T, size_t len>
array<T, len> GetUniformRandomArray(T min=0, T max=len){
	auto result = GetUniformArray<T, len>(min, max);
	
	shuffle (begin(result), end(result), default_random_engine(seed));
	return result;
}

template<class T, size_t len>
decltype(auto) CreateSorterVector(){
	// create vector of (string,ExecTimers)
	vector<pair<string, ExecTimer<void (array<T, len> &)>>> result;
	result.push_back(make_pair("QuickSort", CreateTimer(ArrayUtils::QuickSort<T, len>)));
	result.push_back(make_pair("Tail Recursive QuickSort", CreateTimer(ArrayUtils::TailRecursiveQuickSort<T, len>)));
	result.push_back(make_pair("MergeSort", CreateTimer(ArrayUtils::MergeSort<T, len>)));
	return result;
}
}		// end namespace

// print 'n' blank lines
void endl(ostream &out=cout, int n=1){
	while(n--)
	{
		out<<"\n";
	}
}