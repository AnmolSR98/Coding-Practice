package sortingstack;
// Anmol Ratol, 30231177
// Creating an algorithm to simulate using a queue to sort values from a stack


import java.util.Random;

public class Stack_To_Queue_To_Stack {

	// simulating the use of queues and stacks with these integer arrays
	static int[] queue;
	static int[] stack;
	
	// code to copy the contents of one array to another
	private static void clone(int[] array, int[] array2) {
		for (int i = 0; i < array.length; i++){
			array[i] = array2[i];
		}
	}
	
	// moving the values of the list into a stack, with the bottom being the end of the stack array and the top being the front
	public static void Unsorted_Stack(int[] array) {
		
		stack = new int[array.length];
		
		for (int i = 0; i < array.length; i++){
			stack[array.length-i-1] = array[i];
		}
		
		clone(array, stack);
	}

	// simulating popping the values into the queue, with the back being the front
	public static void Stack_To_Queue(int[] array) {
		
		queue = new int[array.length];
		
		for (int i = 0; i < array.length; i++){
			queue[array.length-i-1] = array[i];
		}
		
		clone(array, queue);
		
	}
	
	// sorting the queue from smallest to largest, with the largest values going at the back of the queue (front of the array)
	public static void Sorting_Queue(int[] array) {
		
		// standard insertion sort code
		for (int i = 0; i < array.length; i++){
			int j = i;
			while ((j > 0) && (array[j] > array[j - 1])){
				int tmp = array[j];
				array[j] = array[j-1];
				array[j-1] = tmp;
				j--;
			}
		}
		
		
	}

	// dequeuing the values into the stack
	public static void Sorted_Stack(int[] array) {
				
		for (int i = 0; i < array.length; i++){
			stack[array.length-i-1] = array[i];
		}
		
		clone(array, stack);
		
	}
	
	// remainder is code copied from the template
	public static void main ( String [ ] args ) {
		Random random = new Random ( ) ;
		int [ ] randomNumbers = new int [ 10 ] ; // Array t o s t o r e 10 random numbers
		// Generate random numbers and s t o r e them i n t h e a r r a y
		for ( int i = 0 ; i < randomNumbers.length ; i ++) {
			randomNumbers [ i ] = random.nextInt( 100 ) + 1 ;
		}
		// P r i n t t h e g e n e r a t e d random numbers
		System.out.println ( "Unsorted Numbers numbers:" ) ;
		for ( int number : randomNumbers ) {
			System.out.println ( number ) ;
		}
		// C a l l t h e f u n c t i o n s t o e x e c u t e t h e s t e p s
		Unsorted_Stack ( randomNumbers ) ;
		System.out.println ( "Unsorted numbers in Stack:" ) ;
		printArray ( randomNumbers ) ;
		
		Stack_To_Queue ( randomNumbers ) ;
		System.out.println ( "Unsorted numbers in Queue:" ) ;
		printArray ( randomNumbers ) ;
		
		Sorting_Queue ( randomNumbers ) ;
		System.out.println ( "Sorted numbers in Queue :" ) ;
		printArray ( randomNumbers ) ;
		
		Sorted_Stack ( randomNumbers ) ;
		System.out.println( "Sorted numbers in Stack :" ) ;
		printArray ( randomNumbers ) ;
	}
	
	// U t i l i t y method t o p r i n t an a r r a y
	public static void printArray ( int [ ] array ) {
		for ( int num : array ) {
		System.out.print (num + " " ) ;
		}
		System.out.println( ) ;
	}
	
	
}
