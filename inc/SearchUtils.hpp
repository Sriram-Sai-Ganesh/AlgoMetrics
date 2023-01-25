#include <cstdlib>

namespace SearchUtils{
template <class T> int IterativeSearch(T ar[], int length, T target)
{
	for(int i=0;i<length;i++)
		if(ar[i]==target)return i;
	return -1;
}

template<class T> int BinarySearch(T ar[], int length, T target)
{
	return 0;
}

template<class T> int binaryFind(T ar[], int start, int end, T target)
{
	return 0;
}

}		// end namespace