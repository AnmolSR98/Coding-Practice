package search;

import sort.HeapSortPractice;

public class SearchPractice {
	
	public static int LinearSearch(int[] array, int elem) {
		int i = 0;
		for (int num: array) {
			if (num == elem) {
				return i;
			}
			i++;
		}
		
		return -1;
	}
	
	public static int BinarySearch(int[] array, int elem, int low, int high) {
		
		if (low > high) {
			return -1;
		}
		
		else {
			
			int mid = (low + high) / 2;
			
			if (array[mid] == elem) {
				return mid;
			}
		
			else if (elem < array[mid]) {
				return BinarySearch(array, elem, low, mid-1);
			}
				
			else {
				return BinarySearch(array, elem, mid+1, high);
			}
		}
		
	}
	
	public static void main(String[] args) throws Exception {
		int[] testArray = new int[5];
		testArray[0] = 9;
		testArray[1] = 1;
		testArray[2] = 3;
		testArray[3] = 7;
		testArray[4] = 5;
		
		System.out.println(LinearSearch(testArray, 9));
		
		HeapSortPractice.HeapSort(testArray);
		
		System.out.println(BinarySearch(testArray, 5, 0, testArray.length));
		
		
	}

}
