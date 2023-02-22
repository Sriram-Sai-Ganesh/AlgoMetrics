#include <cstdlib>
#include <array>
#include <algorithm>
#include <typeinfo>
#include <random>
#include "randutils.hpp"
#include "SinglyLinkedList.hpp"
#include "ExecTimer.hpp"
#include "DoublyLinkedList.hpp"

const uint64_t seed=33489857205;		// prng seed, unused
randutils::mt19937_rng rng;
using namespace std;

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
	auto *current = link.GetHeadPtr();
	out<<"Printing singly linked list of "<<link.length()<<" (type'"<<typeid(T).name()<<"').\n";
	out<<"First : "<<link.head->data<<"\t";
	out<<"Last : "<<link.last->data<<"\n";
	out<<"[  ";
	while(current!=NULL){
		out<<current->data<<"-("<<current->next->data<<")  ";
		current=current->next;
	}
	out<<"]";
}


// print doubly linked list 'link'
template<class T> 
void PrintDoublyLinkedList(DoublyLinkedList<T> link, ostream &out=cout){
	auto current = link.head;
	out<<"Printing doubly linked list of "<<link.length()<<" (type'"<<typeid(T).name()<<"').\n";
	out<<"First : "<<link.head->data<<"\t";
	out<<"Last : "<<link.last->data<<"\n";
	out<<"[ ";
	while(current!=NULL){
		out<<current->data<<"-("<<current->prev->data<<","<<current->next->data<<")  ";
		current=current->next;
	}
	out<<"]";
}

// returns array populated with random T in range [min, max)
template <class T, size_t len> 
array<T, len> GetRandomArray(T min=-len, T max=len)
{
	array<T, len> result;
	for (size_t i=0; i<result.size(); i++)
        result[i]=rng.uniform(min, max-1);
	return result;
}

// return random T number in range [min,max]
template<class T> 
T GetRandomNumber(T min, T max){
	return rng.uniform(min, max);
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
	random_shuffle(begin(result), end(result));
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
void endl(ostream &out, int n=1){
	while(n--)
	{
		out<<"\n";
	}
}