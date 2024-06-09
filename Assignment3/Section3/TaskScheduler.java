// Anmol Ratol 30231177
// creating a task scheduler class to manage the tasks by placing them in a maxHeap sorted by priority
package Section3;

public class TaskScheduler {
	
	// creating a static class maxHeap within TaskScheduler to house the heap and its operations
	static class maxHeap {
		
		// the array that contains the tasks
		private Task[] taskHeap;
		// the size
		private int size = 0;
		
		// simple constructor method
		public maxHeap(int maxSize){
			taskHeap = new Task[maxSize];
		}
		
		// is full
		private boolean isFull() {
			return (size == taskHeap.length);
		}
		
		// is empty
		private boolean isEmpty() {
			return (size == 0);
		}
		
		// sinking the node, assuming its value is not null
		private void shuffle(int node) {
			
			// setting a while loop
			boolean loop = true;
			while (loop){
				
				// if the value of the parent is less than the child, swap them
				if (taskHeap[node].priority > taskHeap[getParent(node)].priority) {
					swap(node, getParent(node));
					node = getParent(node);
				}
				
				// otherwise, we're done sinking them and can exit the loop
				else {
					loop = false;
				}
				
			}
			
		}
		
		// add task, which is just a modified version of the add algorithm for maxHeap
		public void AddTask(Task task) throws Exception {
			
			// throw exception if the heap is full
			if (isFull()) {
				throw new Exception("Heap is full!");
			}
			
			// create the newNode in the size location, ie. the first empty spot
			int newNode = size;
			taskHeap[newNode] = task;
			
			// shuffle the new value into place
			shuffle(newNode);
			
			
			// increment the size
			size++;
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
					if (taskHeap[rightChild].priority > taskHeap[leftChild].priority) {
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
		
		// modified remove function of heap
		public Task RemoveTask(int taskID) throws Exception {
			
			// check it if it is empty
			if (isEmpty()) {
				throw new Exception("Heap is empty!");
			}
			
			// get the root as a placeholder
			int taskPosition = 0;
			Task taskToReturn = taskHeap[0];
			boolean loop = true;
			
			// scan through the loop to get the actual position of the task, and place the value in placeholder variable while making the task null
			for (int i = 0; i < size; i++) {
				if (taskHeap[i].id == taskID) {
					taskPosition = i;
					taskToReturn = taskHeap[i];
					taskHeap[i] = null;
				}
			}
			
			// sink the null task 
			nullSink(taskPosition);
			
			// decrement the size
			size--;
			return taskToReturn;
		}
		
		// return the root of the whole heap
		public Task getNextTask() throws Exception {
			
			return RemoveTask(taskHeap[0].id);
			
		}
		
		public void PrintAllTasks() {
			
			// cloning the value of taskHeap
			Task[] printTasks = taskHeap.clone();
			
			// running a quick insertion sort of the heap array to sort in descending order by priority
			int i = 1;
			int j = 0;
			
			while (i < size) {
				j = i;
				while ((j > 0) && (printTasks[j-1].priority < printTasks[j].priority)){
					Task tmp = printTasks[j-1];
					printTasks[j-1] = printTasks[j];
					printTasks[j] = tmp;
					j--;
				}
				i++;
			}
			
			// printing the sorted array
			for (int k = 0; k < size; k++) {
				System.out.println(printTasks[k]);
			}
		}
		
		// basic swap code
		private void swap(int a, int b) {
			Task tmp = taskHeap[a];
			taskHeap[a] = taskHeap[b];
			taskHeap[b] = tmp;
		}
		
		// get parent code
		private int getParent(int a) {
			return (a - 1)/2;
		}
		
		// 0 for left, 1 for right to get index of child depending on direction entered
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
		
	}
	
	
	// main method 
	public static void main(String[] args) throws Exception {
		
		// initializing a heap of size 32
		int testSize = 32;
		maxHeap testHeap = new maxHeap(testSize);
		
		// 1. Adding the tasks into place 
		try {
			testHeap.AddTask(new Task(101, 5, "Complete project report"));
			testHeap.AddTask(new Task(102, 1, "Organize meeting"));
			testHeap.AddTask(new Task(103, 3, "Review code"));
			testHeap.AddTask(new Task(104, 4, "Test new feature"));
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 2. printing out all of the tasks
		testHeap.PrintAllTasks();
		System.out.println();
		
		// 3. adding a new task, update documentation
		try {
			testHeap.AddTask(new Task(105, 2, "Update documentation"));
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 4. printing the next task
		try {
			System.out.println(testHeap.getNextTask());
			System.out.println();
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 5. remove the task with id 103
		try {
			testHeap.RemoveTask(103);
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		
		// 6. print the updated heap
		testHeap.PrintAllTasks();
		System.out.println();
		
		// 7. cycle through getNextTask until the heap is empty
		boolean loop = true;
		while(loop) {
			
			Task taskToPrint;
			
			try {
				taskToPrint = testHeap.getNextTask();
				System.out.println(taskToPrint);
			}
			
			catch (Exception e){
				loop = false;
			}
	
		}
		
		
		
	}
}
