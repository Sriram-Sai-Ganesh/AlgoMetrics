#include <cstdlib>
#include <array>
#include <algorithm> 

using namespace std;

namespace ArrayUtils{

// anonymous local namespace to hold private helper functions
namespace{
	// helper to BinarySearch
	template <class T, size_t len> 
	int binaryFind(array<T, len> ar, int start, int end, T target)
	{
		int mid = (end+start)/2;
		if(end<start){
			return -1;
		}
		else if(target==ar[mid]){
			return mid;
		}
		else if(target>ar[mid]){
			return binaryFind(ar, mid+1, end, target);
		}
		else {
			return binaryFind(ar, start, mid-1, target);
		}
	}

	// helper to QuickSort
	template<class T, size_t len>
	int partition(array<T, len>& ar, int low, int high) {
		int pivot = ar[high]; // pivot around high
		int i = (low - 1);
		for (int j = low; j <= high - 1; j++) {
			if (ar[j] < pivot) {
				i++;
				swap(ar[i], ar[j]);
			}
		}
		swap(ar[i + 1], ar[high]);
		return (i + 1);
	}
}

// Sequential search iteratively
template <class T, size_t len> 
int IterativeSearch(array<T, len> ar, T target)
{
	int length = len;
	for(int i=0;i<length;i++){
		if(ar[i]==target)return i;
	}
	return -1;
}
// Binary Search recursively
template <class T, size_t len> 
int RecursiveBinarySearch(array<T, len> ar, T target)
{
	int length = len;
	int result = binaryFind<T, len>(ar, 0, length-1, target);
	return result;
}

// Binary Search iteratively
template <class T, size_t len> 
int IterativeBinarySearch(array<T, len> ar, T target)
{
	int start=0, end=len-1;
	int mid=-1;
	while(start<=end){
		mid=start+(end-start)/2;
		if(ar[mid]>target){
			end=mid-1;
		}
		else if(ar[mid]<target){
			start=mid+1;
		}
		else return mid;
	}
	return -1;
}

// BubbleSort ar
template <class T, size_t len> 
void BubbleSort(array<T, len>& ar)
{
	int length = len;
	for (int i = 0; i < length - 1; i++)
        for (int j = length - 1; i < j; j--)
            if (ar[j] < ar[j - 1])
                swap(ar[j], ar[j - 1]);
}

// SelectionSort ar
template <class T, size_t len> 
void SelectionSort(array<T, len>& ar)
{
	int lim = len, boundary=0;
	int min, minIndex;
	// until entire array is within the 'sorted' range
	for(boundary=0;boundary<lim;boundary++)
	{
		min=ar[boundary];
		minIndex=boundary;
		// find min in array
		for(int i=boundary+1;i<lim;i++){
			if(ar[i]<min){
				min=ar[i];
				minIndex=i;
			}
		}
		// swap min value with last index of sorted region
		swap(ar[boundary], ar[minIndex]);
		// temp=ar[boundary];
		// ar[boundary]=min;
		// ar[minIndex]=temp;
	}
}

// InsertionSort ar
template <class T, size_t len> 
void InsertionSort(array<T, len>& ar)
{
	int j, current, lim=len;
    for (int i = 1; i < lim; i++)
    {
        current = ar[i];
        j = i - 1;

        // swap current with left neighbor
		// until it is in sorted order
        while (j >= 0 && ar[j] > current)
        {
            ar[j + 1] = ar[j];
            j--;
        }
        ar[j + 1] = current;
    }
}

// QuickSort ar
template <class T, size_t len> 
void QuickSort(array<T, len> &ar, int low=0, int high=len-1)
{
    if (low < high) {
        
		// partition around 
        int prt = partition(ar, low, high);

        // Separately sort elements before and after partition
        QuickSort<T, len>(ar, low, prt - 1);
        QuickSort<T, len>(ar, prt + 1, high);
    }
}

// BogoSort ar
template <class T, size_t len> 
void BogoSort(array<T, len> &ar)
{
	// loop until sorted
	for(int i=0, lim=len-1;i<lim;i++)
	{
		// check if non-decreasing, 
		if(ar[i]>ar[i+1])
		{
			// std::random_shuffle and reset if decreasing
			random_shuffle(begin(ar), end(ar));
			i=-1;
		}
	}
}

}		// end namespace