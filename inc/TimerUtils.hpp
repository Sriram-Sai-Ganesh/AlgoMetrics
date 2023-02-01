#include <cstdlib>
#include <array>
#include <typeinfo>

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

namespace TimerUtils{

// function to time any ArrayUtil::Sort algorithm
template <class T, size_t len, class F> 
void SortTimer(F sorter, array<T, len>& ar){

    auto begin = Clock::now();
	// call function
	sorter(ar);
	auto elapsed = (Clock::now()- begin);
    std::cout<<"Steady Time measured: "<< chrono::duration_cast<chrono::microseconds>(elapsed).count()<<" microseconds.\n";
}

}		// end namespace
