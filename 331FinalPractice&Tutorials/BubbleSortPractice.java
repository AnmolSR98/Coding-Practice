package sort;

public class BubbleSortPractice {

	public static void BubbleSort(int[] array) {

		int n = array.length;
		for (int i = 0; i < n; i++) {
			for (int j = n-1; j > i; j--) {
				if (array[j] < array[j - 1]) {
					int tmp = array[j];
					array[j] = array[j-1];
					array[j-1] = tmp;
				}
			}
		}
	}
	
	public static void main (String[] args) {
		
		int[] testArray = new int[5];
		testArray[0] = 9;
		testArray[1] = 1;
		testArray[2] = 3;
		testArray[3] = 7;
		testArray[4] = 5;
		
		BubbleSort(testArray);
		
		for (int stdnt: testArray) {
			System.out.print(stdnt + ", ");
		}
		System.out.println();
	}
}
