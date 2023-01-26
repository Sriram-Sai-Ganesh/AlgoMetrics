#include <cstdlib>
#include <array>

using namespace std;
namespace SortUtils{


// bubblesort ar and return copy
template <class T, size_t len> array<T, len> BubbleSort(array<T, len> ar)
{
	int length = len;
	for (int i = 0; i < length - 1; i++)
        for (int j = length - 1; i < j; j--)
            if (ar[j] < ar[j - 1])
                swap(ar[j], ar[j - 1]);
	return ar;
}

}		// end namespace
