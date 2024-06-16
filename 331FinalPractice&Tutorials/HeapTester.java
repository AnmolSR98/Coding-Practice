package heap;

public class HeapTester {
	
	public static void main(String[] args) throws Exception {
		MinHeap testHeap = new MinHeap(16);
		testHeap.enqueue(5);
		testHeap.enqueue(7);
		testHeap.enqueue(3);
		testHeap.enqueue(2);
		testHeap.enqueue(-2);
		testHeap.enqueue(-1);
		testHeap.print();
		while (!testHeap.isEmpty()) {
			System.out.print(testHeap.dequeue()+", ");
		}
		
	}
	
	

}
