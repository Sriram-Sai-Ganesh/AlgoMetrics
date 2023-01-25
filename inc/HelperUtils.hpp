#include <cstdlib>
#include "XoshiroCpp.hpp"		// rng header

using namespace std;

namespace HelperUtils{

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
