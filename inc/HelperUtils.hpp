#include <cstdlib>
#include <array>
#include <typeinfo>

#include "randutils.hpp"		// prng header

using namespace std;

namespace HelperUtils{

// returns array populated with random T in range [min, max)
template <class T, size_t len> array<T, len> GetRandomArray(T min, T max)
{
	randutils::mt19937_rng rng;
	array<T, len> result;
	cout<<"Creating array of "<<len<<" (type '"<<typeid(T).name()<<"') randoms range ("<<min<<", "<<max<<"].\n";
	for (size_t i=0; i<result.size(); i++)
        result[i]=rng.uniform(min, max-1);
	return result;
}


// returns array populated with uniform distribution from [min, max]
template <class T, size_t len> array<T, len> GetUniformArray(T min, T max)
{
	cout<<"Creating array of "<<len<<" (type'"<<typeid(T).name()<<"') uniform in  range ["<<min<<", "<<max<<"].\n";
	
	array<T, len> result;
	for (size_t i=0; i<result.size(); i++)
        result[i] = min + ((max-min)*(i*1.0/result.size()));
	return result;	
}

// print array 'a' separated by ' '
template<class T, size_t len> void PrintArray(array<T, len> a)
{
	cout<<"Printing array of "<<len<<" (type'"<<typeid(T).name()<<"').\n\t";
	cout<<"[";
    for(size_t i=0;i<a.size()-1;i++){
        cout << a[i] << ", ";
	}
	cout<<a[a.size()-1]<<"]";
}
}		// end namespace

void endl(int n=1){
	while(n-->0)
	{
		cout<<endl;
	}
}