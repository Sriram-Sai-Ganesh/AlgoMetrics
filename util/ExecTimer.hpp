#pragma once
#include <cstdlib>
#include <array>
#include <functional>
#include <typeinfo>
#include <chrono>

using namespace std;

typedef chrono::high_resolution_clock Clock;

// forward declaration
template<class R, class... args> struct ExecTimer;

/// @brief struct for generic FunctionTimers
/// @tparam R function return type
/// @tparam ...args types of params
template<class R, class... args> 
struct ExecTimer<R(args ...)>{
	private:
		// member variables
		function<R(args...)> myFunc;
		float elapsed;
	public:

		/// @brief constructor for ExecTimer object
		/// @param func function using which ExecTimer object will be created.
		ExecTimer(function<R(args...)> func){
			elapsed=-1;
			myFunc=func;
		}
	
		/// @brief overloaded operator: parantheses
		/// @param ...params arguments for the function to be called. Listed in order. 
		/// @return float execution duration in microseconds
		float operator()(args ... params){
			auto begin = Clock::now();
			// not using return value
			// R result=myFunc(arguments...);	
			myFunc(params...);	
			elapsed=chrono::duration_cast<chrono::microseconds>(Clock::now()-begin).count();
			return elapsed;
		}

		/// @brief returns value of execution time variable
		/// @return time taken to execute function. -1 if uninitialized.
		float Count(){
			return elapsed;
		}
};

/// @brief wrapper to ExecTimer constructor
/// @tparam R return type of @param func 
/// @tparam ...args parameters of @param func. Listed in order.
/// @param func function using which an ExecTimer will be created
/// @return time taken to execute @param func with @param ...args
template<class R, class... args> 
ExecTimer<R(args ...)> CreateTimer(R (*func)(args ...)) {
    return ExecTimer<R(args...)>(function<R(args...)>(func));    
}