#include <cstdlib>
#include <array>

#include "randutils.hpp"		// prng header

using namespace std;



namespace HelperUtils{

// returns array populated with random T in range [min, max)
template <class T, size_t len> array<T, len> GetRandomArray(T min, T max)
{
	randutils::mt19937_rng rng;
	array<T, len> result;

	for (size_t i=0; i<result.size(); i++)
        result[i]=rng.uniform(min, max-1);

	return result;
}


// returns array populated with uniform distribution from [min, max]
template <class T, size_t len> array<T, len> GetUniformArray(T min, T max)
{
	array<T, len> result;
	for (size_t i=0; i<result.size(); i++)
        result[i] = min + ((max-min)*(i*1.0/result.size()));
	return result;	
}

template<class T, size_t len> void PrintArray(array<T, len> a)
{
    for (auto num : a)
        cout << num << " ";
}


}		// end namespace
