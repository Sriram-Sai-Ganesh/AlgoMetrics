#include <cstdlib>
#include <array>
#include <typeinfo>

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

namespace TimerUtils{

// function to time any ArrayUtil::Sort algorithm
template <class T, size_t len, class F> 
double SortTimer(F sorter, array<T, len>& ar, ostream &out=std::cout){

    auto begin = Clock::now();
	// call function
	sorter(ar);
	// double sum = 0;
	// for(int i=0, lim=1000*1000;i<lim;i++) sum += 1;
	auto elapsed = (Clock::now()- begin);
	double micro = chrono::duration_cast<chrono::microseconds>(elapsed).count();
    out<<"wall time measured: "<< micro<<" microseconds.\n";
	return micro;
}

// function to time any ArrayUtil::Search algorithm
template <class T, size_t len, class F> 
void SearchTimer(F searcher, array<T, len>& ar, T target, ostream &out=std::cout){
    auto begin = Clock::now();
	// call function
	searcher(ar);
	auto elapsed = (Clock::now()- begin);
	double micro = chrono::duration_cast<chrono::microseconds>(elapsed).count();
    out<<"wall time measured: "<< micro<<" microseconds.\n";
}

}		// end namespace