#include <cstdlib>
#include <array>

using namespace std;
namespace SortUtils{

template <class T, size_t len> array<T, len> BubbleSort(array<T, len> ar)
{
	for (int i = 0; i < len - 1; i++)
        for (int j = len - 1; i < j; j--)
            if (ar[j] < ar[j - 1])
                swap(ar[j], ar[j - 1]);
	return ar;
}

}		// end namespace
