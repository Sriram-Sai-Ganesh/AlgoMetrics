#include <cstdlib>
#include <array>

using namespace std;

namespace ArrayUtils{

// sequential search iteratively in 'ar' for 'target'
template <class T, size_t len> int IterativeSearch(array<T, len> ar, T target)
{
	int length = len;
	for(int i=0;i<length;i++)
		if(ar[i]==target)return i;
	return -1;
}

// private helper to BinarySearch
template <class T, size_t len> int binaryFind(array<T, len> ar, int start, int end, T target)
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

// Binary Search recursively in 'ar' for 'target'
template <class T, size_t len> int RecursiveBinarySearch(array<T, len> ar, T target)
{
	int length = len;
	int result = ArrayUtils::binaryFind<T, len>(ar, 0, length-1, target);
	return result;
}

// Binary Search iteratively in 'ar' for 'target'
template <class T, size_t len> int IterativeBinarySearch(array<T, len> ar, T target)
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