#include <cstdlib>
#include <array>
#include <typeinfo>

#include "randutils.hpp"		// prng header

const uint64_t seed=33489857205;		// prng seed, unused

using namespace std;

namespace HelperUtils{

randutils::mt19937_rng rng;

// returns array populated with random T in range [min, max)
template <class T, size_t len> array<T, len> GetRandomArray(T min, T max)
{
	array<T, len> result;
	cout<<"Creating array of "<<len<<" (type '"<<typeid(T).name()<<"') randoms range ("<<min<<", "<<max<<"].\n";
	for (size_t i=0; i<result.size(); i++)
        result[i]=rng.uniform(min, max-1);
	return result;
}

// return random T number in range [min,max]
template<class T> T GetRandomNumber(T min, T max){
	return rng.uniform(min, max);
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

// print 'n' blank lines
void endl(int n=1){
	while(n-->0)
	{
		cout<<endl;
	}
}