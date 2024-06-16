package sort;

public class MergeSortPractice {

	public static void MergeSort(int[] array, int low, int high) {
		
		if (low < high) {
			int mid = (low+high)/2;
			MergeSort(array, low, mid);
			MergeSort(array, mid+1, high);
			Merge(array, low, high, mid);
		}
		
	}
	
	public static void Merge(int[] array, int low, int high, int mid) {
		
		int n1 = mid - low + 1;
		int n2 = high - mid;
		
		int[] left = new int[n1];
		for (int i = 0; i < n1; i++) {
			left[i] = array[low + i];
		}
		
		int[] right = new int[n2];
		for (int i = 0; i < n2; i++) {
			right[i] = array[mid + 1 + i];
		}
		
		int i = 0;
		int j = 0;
		int k = low;
		
		while ((i < n1) && (j < n2)) {
			if (left[i] <= right[j]) {
				array[k] = left[i];
				i++;
			}
			
			else {
				array[k] = right[j];
				j++;
			}
			
			k++;
		}
		
		while (i < n1) {
			array[k] = left[i];
			i++;
			k++;
		}
		
		while (j < n2) {
			array[k] = right[j];
			j++;
			k++;
		}
		
	}
	
	public static void main(String[] args) {
		int[] testArray = new int[5];
		testArray[0] = 9;
		testArray[1] = 1;
		testArray[2] = 3;
		testArray[3] = 7;
		testArray[4] = 5;
		MergeSort(testArray, 0, testArray.length - 1);
		
		for (int stdnt: testArray) {
			System.out.print(stdnt + ", ");
		}
		System.out.println();
		
	}
	
}
