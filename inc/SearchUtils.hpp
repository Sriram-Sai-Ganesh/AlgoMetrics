#include <cstdlib>
#include <array>


using namespace std;

namespace SearchUtils{

// returns T index of target, or -1 if absent.
template <class T, size_t len> int IterativeSearch(array<T, len> ar, T target)
{
	for(int i=0;i<len;i++)
		if(ar[i]==target)return i;
	return -1;
}


template <class T, size_t len> int BinarySearch(array<T, len> ar, T target)
{
	// TODO
	return 0;
}

// private helper to BinarySearch
template <class T, size_t len> int binaryFind(array<T, len> ar, int start, int end, T target)
{
	// TODO
	return 0;
}

}		// end namespace