#include <cstdlib>
#include <array>
#include <functional>
#include <typeinfo>
#include <chrono>

#pragma once

using namespace std;

typedef chrono::high_resolution_clock Clock;

// forward declaration
template<class R, class... args> class ExecTimer;

// struct for generic FunctionTimers
template<class R, class... args> 
struct ExecTimer<R(args ...)>{
	private:
		// member variables
		function<R(args...)> myFunc;
		int elapsed;
	public:

		// constructor
		ExecTimer(function<R(args...)> func){
			elapsed=-1;
			myFunc=func;
		}
	
		// overload () operator
		float operator()(args ... arguments){
			auto begin = Clock::now();
			// ignore return value
			// R result=myFunc(arguments...);	
			myFunc(arguments...);	
			elapsed=chrono::duration_cast<chrono::microseconds>(Clock::now()-begin).count();
			return elapsed;
		}

		// return timer result in microseconds
		// -1 if function has not been run.
		float Count(){
			return elapsed;
		}
};

// wrapper function to constructor
template<class R, class... args> 
ExecTimer<R(args ...)> CreateTimer(R (*func)(args ...)) {
    return ExecTimer<R(args...)>(function<R(args...)>(func));
}