package sort;

public class SelectionSortPractice {
	
	public static void SelectionSort(int[] array) {

		int n = array.length;
		for (int i = 0; i < n; i++) {
			int[] spliceArray = new int[n - i];
			for (int j = i; j < n; j++) {
				spliceArray[j - i] = array[j];
				System.out.print(spliceArray[j - i] + ", ");
			}
			System.out.println();
			
			int minIndex = findMinIndex(spliceArray);
			
			int tmp = array[i]; 
			array[i] = array[minIndex + i];
			array[minIndex + i] = tmp;
			
		}
	}
	
	private static int findMinIndex(int[] array) {
		// TODO Auto-generated method stub
		int minIndex = 0;
		for (int i = 1; i < array.length; i++) {
			if (array[i] < array[minIndex]) {
				minIndex = i;
			}
		}
		
		return minIndex;
	}

	public static void main (String[] args) {
		
		int[] testArray = new int[5];
		testArray[0] = 9;
		testArray[1] = 1;
		testArray[2] = 3;
		testArray[3] = 7;
		testArray[4] = 5;
		
		SelectionSort(testArray);
		
		for (int stdnt: testArray) {
			System.out.print(stdnt + ", ");
		}
		System.out.println();
	}
}
