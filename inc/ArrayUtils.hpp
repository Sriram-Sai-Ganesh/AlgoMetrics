#include <cstdlib>
#include <random>	// prng for bogosort
#include <functional>
#include <array>

using namespace std;

/// @brief namespace to hold utility functions for arrays
namespace ArrayUtils{

/// @brief anonymous local namespace to hold private helper functions
namespace{

	/// @brief helper to BinarySearch. Use interval halving to find value.
	/// @tparam T type of elements in the array
	/// @tparam len length of the array
	/// @param ar array to be searched
	/// @param start start index of sub-array to be searched
	/// @param end end index of sub-array to be searched
	/// @param target element to search for
	/// @return index of element in sub-array [start, end]
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

	/// @brief helper to QuickSort. Uses last element as pivot.
	/// @tparam T type of array elements.
	/// @tparam len length of array to be sorted.
	/// @param ar array to be sorted.
	/// @param low first index of sub-array to be sorted.
	/// @param high last index of sub-array to be sorted.
	/// @return 
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

	/// @brief helper to QuickSort. Calls Parition.
	/// @tparam T type of array elements.
	/// @tparam len length of array to be sorted.
	/// @param ar array to be sorted.
	/// @param low first index of sub-array to be sorted.
	/// @param high last index of sub-array to be sorted.
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

    /// @brief helper to QuickSort.
	/// @tparam T type of array elements.
	/// @tparam len length of array to be sorted.
	/// @param ar array to be sorted.
	/// @param low first index of sub-array to be sorted.
	/// @param high last index of sub-array to be sorted.
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
/// @brief iteratively search through an array.
/// @tparam T type of array element.
/// @tparam len length of array to search through.
/// @param ar array to be searched.
/// @param target element to search for.
/// @return index of target if found, -1 otherwise.
template <class T, size_t len> 
int IterativeSearch(array<T, len> ar, T target)
{
	int length = len;
	for(int i=0;i<length;i++){
		if(ar[i]==target)return i;
	}
	return -1;
}

/// @brief Recursive implementation of Binary Search. Wrapper to the binaryFind helper function.
/// @tparam T type of array element.
/// @tparam len length of array to search through.
/// @param ar array to be searched.
/// @param target element to search for.
/// @return index of target if found, -1 otherwise.
template <class T, size_t len> 
int RecursiveBinarySearch(array<T, len> ar, T target)
{
	int length = len;
	int result = binaryFind<T, len>(ar, 0, length-1, target);
	return result;
}

/// @brief iterative implementation of Binary Search.
/// @tparam T type of array element.
/// @tparam len length of array to search through.
/// @param ar array to be searched.
/// @param target element to search for.
/// @return index of target if found, -1 otherwise.
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

/// @brief iterative implementation of BubbleSort.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
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

/// @brief iterative implementation of Selection Sort.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
template <class T, size_t len> 
void SelectionSort(array<T, len>& ar)
{
	// tracks location of moving boundary between 
	// sorted/unsorted elements
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
	}
}
/// @brief iterative implementation of Insertion Sort.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
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

/// @brief recursive implementation of Insertion Sort. 
/// Wrapper to the insertion sort helper function.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
template <class T, size_t len> 
void RecursiveInsertionSort(array<T, len>& ar)
{
	insertionsort<T, len>(ar, len);
}

/// @brief recursive implementation of MergeSort. 
/// Wrapper to the merge sort helper function.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
template <class T, size_t len> 
void MergeSort(array<T, len>& ar)
{
	// calls private function
    mergesort(ar, 0, len-1);
}

/// @brief recursive implementation of QuickSort. 
/// Wrapper to the merge sort helper function.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
template <class T, size_t len> 
void QuickSort(array<T, len> &ar)
{
    quicksort(ar, 0, len-1);
}

/// @brief recursive implementation of TailRecursive QuickSort. 
/// Wrapper to the merge sort helper function.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
template <class T, size_t len> 
void TailRecursiveQuickSort(array<T, len> &ar)
{
    tailquicksort(ar, 0, len-1);
}

/// @brief working! implementation of BogoSort. 
/// Wrapper to the merge sort helper function.
/// @tparam T type of array elements.
/// @tparam len length of array to be sorted.
/// @param ar array to be sorted.
template <class T, size_t len> 
void BogoSort(array<T, len> &ar)
{
	auto seed=chrono::system_clock::now().time_since_epoch().count();		
	// loop until sorted
	for(int i=0, lim=len-1;i<lim;i++)
	{
		// check if non-decreasing, 
		if(ar[i]>ar[i+1])
		{
			// std::random_shuffle and reset if decreasing
			shuffle(begin(ar), end(ar), default_random_engine(seed));
			i=-1;
		}
	}
}
}		// end namespace