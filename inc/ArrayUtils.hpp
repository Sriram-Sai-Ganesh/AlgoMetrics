#include <cstdlib>
#include <functional>
#include <array>

using namespace std;
namespace ArrayUtils{

/// @brief anonymous local namespace to hold private helper functions
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

	/// @brief helper to MergeSort. Merges sorted sub-arrays of 1 array.
	/// @tparam T Type of array element.
	/// @tparam len Length of array.
	/// @param ar array to be sorted.
	/// @param start first index of sub-array to be merged.
	/// @param mid middle index of sub-array to be merged.
	/// @param end last index of sub-array to be merged.
	template<class T, size_t len>
	void merge(array<T, len>& ar, int start, int mid, int end)
	{
		int leftSize = mid - start + 1, rightSize = end - mid;
		// allocate memory for temporary arrays
		T *tempLeft  = (T*) (malloc(sizeof(T)*(leftSize)));
    	T *tempRight = (T*) (malloc(sizeof(T)*(rightSize)));

		for (int i = 0; i < leftSize; i++)
			tempLeft[i] = ar[start + i];
		for (int j = 0; j < rightSize; j++)
			tempRight[j] = ar[mid + 1 + j];

		// iterate over temp and main arrays
		int i=0, j=0, k=start;

		// pick smaller of the pair from the two temp arrays
		while (i < leftSize && j < rightSize) {
			if (tempLeft[i] <= tempRight[j]) {
				ar[k++] = tempLeft[i++];
			} else {
				ar[k++] = tempRight[j++];
			}
		}

		// if we exhaust 1 temp array, fill in the main 
		// array with remaining elements from the other.
		while (i < leftSize) {
			ar[k++] = tempLeft[i++];
		}

		while (j < rightSize) {
			ar[k++] = tempRight[j++];
		}
	}

	/// @brief helper to ArrayUtils::MergeSort.
	/// @tparam T type of array element.
	/// @tparam len length of array.
	/// @param ar array to be sorted.
	/// @param start start index of sub-array to be sorted.
	/// @param end last index of sub-array to be sorted.
	template<class T, size_t len>
	void mergesort(array<T, len>& ar, int start, int end)
	{
		if(start>=end)return;
		int mid = start + (end - start) / 2;
		mergesort(ar, start, mid);
		mergesort(ar, mid + 1, end);
		merge(ar, start, mid, end);
	}



	/// @brief helper to RecursiveInsertionSort.
	/// @tparam T type of array element.
	/// @tparam len length of array to be sorted.
	/// @param ar array to be sorted.
	/// @param size size of sub-array to be sorted.
	template<class T, size_t len>
	void insertionsort(array<T, len>& ar, int size) {
		if (size <= 1)return;
		// sort the first size-1 elements
		insertionsort(ar, size-1);
		// SortedInsert the last element
		T last = ar[size-1];
		int index = size-2;
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (index >= 0 && ar[index] > last)
		{
			ar[index+1] = ar[index];
			index--;
		}
		ar[index+1] = last;
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

	// helper to QuickSort
	template<class T, size_t len>
	void quicksort(array<T, len>& ar, int low, int high) {
		if (low < high) {
			
			// partition around 
			int prt = partition(ar, low, high);

			// Separately sort elements before and after partition
			quicksort<T, len>(ar, low, prt - 1);
			quicksort<T, len>(ar, prt + 1, high);
		}
	}

	// helper to TailRecursiveQuickSort
	template<class T, size_t len>
	void tailquicksort(array<T, len>& ar, int low, int high) {
		while (low < high) {
			
			// partition around 
			int prt = partition(ar, low, high);

			// Separately sort elements before and after partition
			tailquicksort<T, len>(ar, low, prt - 1);
			low=prt+1;
		}
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
	// define bounds
	int start=0, end=len-1, mid=-1;
	// interval halve until we pass ourselves
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

// BubbleSort iteratively
template <class T, size_t len> 
void BubbleSort(array<T, len>& ar)
{
	// number of swaps
	int length = len;
	// swap 1 fewer element each time
	for (int i = 0; i < length - 1; i++)
        for (int j = length - 1; j > i ; j--)
            if (ar[j] < ar[j - 1])
				// smallest element bubbles to the bottom
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

// iteratively perform InsertionSort on ar
template <class T, size_t len> 
void IterativeInsertionSort(array<T, len>& ar)
{
	int j, current, lim=len;
    for (int i = 1; i < lim; i++){
        current = ar[i];
        j = i - 1;

        // swap current with left neighbor
		// until it is in sorted order
        while (j >= 0 && ar[j] > current){
            ar[j + 1] = ar[j];
            j--;
        }
        ar[j + 1] = current;
    }
}


// recursively perform InsertionSort on ar
template <class T, size_t len> 
void RecursiveInsertionSort(array<T, len>& ar)
{
	insertionsort<T, len>(ar, len);
}

// QuickSort ar
template <class T, size_t len> 
void MergeSort(array<T, len>& ar)
{
	// calls private function
    mergesort(ar, 0, len-1);
}

// QuickSort ar
template <class T, size_t len> 
void QuickSort(array<T, len> &ar)
{
    quicksort(ar, 0, len-1);
}
// QuickSort ar
template <class T, size_t len> 
void TailRecursiveQuickSort(array<T, len> &ar)
{
    tailquicksort(ar, 0, len-1);
}

// BogoSort ar in O(n!) time
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