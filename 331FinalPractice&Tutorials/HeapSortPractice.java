package sort;

import heap.MinHeap;

public class HeapSortPractice {

	public static void HeapSort(int[] array) throws Exception {
		MinHeap utilHeap = new MinHeap(array.length);
		for (int elem: array) {
			utilHeap.enqueue(elem);
		}
		
		for (int i = 0; i < array.length; i++) {
			array[i] = utilHeap.dequeue();
		}
	}

	public static void main (String[] args) throws Exception {
		
		int[] testArray = new int[5];
		testArray[0] = 9;
		testArray[1] = 1;
		testArray[2] = 3;
		testArray[3] = 7;
		testArray[4] = 5;
		
		HeapSort(testArray);
		
		for (int stdnt: testArray) {
			System.out.print(stdnt + ", ");
		}
		System.out.println();
	}
	
}
