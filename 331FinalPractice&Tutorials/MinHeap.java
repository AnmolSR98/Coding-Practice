package heap;


public class MinHeap {
	
	private int[] Heap;
	private int size;
	private int length;
	
	public MinHeap(int length) {
		Heap = new int[length];
		size = 0;
		this.length = length;
	}
	
	public boolean isEmpty() {
		return (size == 0);
	}
	
	public boolean isFull() {
		return (size == length);
	}
	
	public int size() {
		return size;
	}
	
	// int must be greater than zero
	public void enqueue(int elem) throws Exception {
		
		// throw exception if the heap is full
		if (isFull()) {
			throw new Exception("Heap is full!");
		}
		
		// create the newNode in the size location, ie. the first empty spot
		int newNode = size;
		Heap[newNode] = elem;
		
		// shuffle the new value into place
		shuffle(newNode);
		
		
		// increment the size
		size++;
	}
	
	private void shuffle(int node) {
		
		// setting a while loop
		boolean loop = true;
		while (loop){
			
			// if the value of the parent is less than the child, swap them
			if (Heap[node] < Heap[getParent(node)]) {
				swap(node, getParent(node));
				node = getParent(node);
			}
			
			// otherwise, we're done sinking them and can exit the loop
			else {
				loop = false;
			}
			
		}
		
	}
	
	private void nullSink(int node) {
		
		// setting up a loop to sink the null value
		boolean loop = true;
		while (loop) {
			
			// get the left and right child
			int leftChild = getChild(node, 0);
			int rightChild = getChild(node, 1);
			
			// assuming the rightChild exists within the heap
			if (rightChild < size) {
				
				// take the maximum of the left child and right child and swap the 
				// null node with whichever child is larger to preserve heap
				if (Heap[rightChild] < Heap[leftChild]) {
					swap(node, rightChild);
					node = rightChild;
				}
				
				else {
					swap(node, leftChild);
					node = leftChild;
				}
				
			}
			
			// otherwise if the leftChild exists swap it with that
			else if (leftChild < size) {
				swap(node, leftChild);
				node = leftChild;
			}
			
			// if neither child exists
			
			else {
				
				// if the node is not the last element, swap it with the last element in the heap
				if (node != size - 1) {
					swap(node, size - 1);
				}
				
				// kill the loop
				loop = false;
			}
			
		}
		
		
	}
	
	
	private void swap(int a, int b) {
		int tmp = Heap[a];
		Heap[a] = Heap[b];
		Heap[b] = tmp;
	}
	
	private int getParent(int node) {
		return (node - 1)/2;
	}
	
	private int getChild(int parent, int direction) {
		
		if (direction == 0) {
			return 2*parent + 1;
		}
		
		else if (direction == 1) {
			return 2*parent + 2; 
		}
		
		// returns a minus one if a wrong direction is inputed
		return -1;
	}
	
	public int dequeue() throws Exception {
		
		if (isEmpty()) {
			throw new Exception("Heap is empty!");
		}
		
		// get the root as a placeholder
		int nodeToReturn = Heap[0];
		
		nullSink(0);
		
		// decrement the size
		size--;
		return nodeToReturn;
		
	}
	
	public void print() {
		for (int i = 0; i < size; i ++) {
			System.out.print(Heap[i] + ",");
		}
		System.out.println();
	}

}
