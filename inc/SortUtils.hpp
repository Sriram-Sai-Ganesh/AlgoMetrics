#include <cstdlib>
#include <array>

using namespace std;
namespace SortUtils{

template <class T, size_t length> void BubbleSort(array<T, length> ar)
{
	for (int i = 0; i < length- 1; i++)
        for (int j = length- 1; i < j; j--)
            if (ar[j] < ar[j - 1])
                swap(ar[j], ar[j - 1]);
}

}		// end namespace
