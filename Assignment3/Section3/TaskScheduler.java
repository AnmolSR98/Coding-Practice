package Section4;

public class TaskScheduler {
	// I think this is supposed to be the max priority heap
	static class maxHeap {
		
		private Task[] taskHeap;
		private int size = 0;
		
		public maxHeap(int maxSize){
			taskHeap = new Task[maxSize]; // creates an array of nulls
		}
		
		public void AddTask(Task task) {
			int newNode = size;
			taskHeap[newNode] = task;
			boolean loop = true;
			
			while (loop){
				
				if (taskHeap[newNode].priority > taskHeap[getParent(newNode)].priority) {
					swap(newNode, getParent(newNode));
					newNode = getParent(newNode);
				}
				
				else {
					loop = false;
				}
				
			}
			
			size++;
		}
		
		public Task RemoveTask(int taskID) {
			
			int taskPosition = 0;
			Task taskToReturn = taskHeap[0];
			boolean loop = true;
			
			for (int i = 0; i < size; i++) {
				if (taskHeap[i].id == taskID) {
					taskPosition = i;
					taskToReturn = taskHeap[i];
					taskHeap[i] = null;
				}
			}
			
			
			// sinking the null value
			while (loop) {
				
				int leftChild = getChild(taskPosition, 0);
				int rightChild = getChild(taskPosition, 1);
				
				if (rightChild < size) {
					
					if (taskHeap[rightChild].priority > taskHeap[leftChild].priority) {
						swap(taskPosition, rightChild);
						taskPosition = rightChild;
					}
					
					else {
						swap(taskPosition, leftChild);
						taskPosition = leftChild;
					}
					
				}
				
				else if (leftChild < size) {
					swap(taskPosition, leftChild);
					taskPosition = leftChild;
				}
				
				else {
					
					if (taskPosition != size - 1) {
						swap(taskPosition, size - 1);
					}
					
					loop = false;
				}
				
			}
			
			size--;
			return taskToReturn;
		}
		
		public Task getNextTask() {
			
			if (size == 0) {
				return null;
			}
			
			return RemoveTask(taskHeap[0].id);
			
		}
		
		public void PrintAllTasks() {
			
			Task[] printTasks = taskHeap.clone();
			
			int i = 1;
			int j = 0;
			
			// running a quick insertion sort of the entire heap
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
			
			
			for (int k = 0; k < size; k++) {
				System.out.println(printTasks[k]);
			}
		}
		
		private void swap(int a, int b) {
			Task tmp = taskHeap[a];
			taskHeap[a] = taskHeap[b];
			taskHeap[b] = tmp;
		}
		
		private int getParent(int a) {
			return (a - 1)/2;
		}
		
		// 0 for left, 1 for right
		private int getChild(int parent, int direction) {
			
			if (direction == 0) {
				return 2*parent + 1;
			}
			
			else if (direction == 1) {
				return 2*parent + 2; 
			}
			
			return -1;
		}
		
	}
	
	
	// then I can put the main method here for driving
	public static void main(String[] args) {
		
		int testSize = 32;
		maxHeap testHeap = new maxHeap(testSize);
		
		// 1.
		testHeap.AddTask(new Task(101, 5, "Complete project report"));
		testHeap.AddTask(new Task(102, 1, "Organize meeting"));
		testHeap.AddTask(new Task(103, 3, "Review code"));
		testHeap.AddTask(new Task(104, 4, "Test new feature"));
		
		// 2.
		testHeap.PrintAllTasks();
		System.out.println();
		
		// 3. Up to here everything is working fine
		testHeap.AddTask(new Task(105, 2, "Update documentation"));
		
		// 4. 
		System.out.println(testHeap.getNextTask());
		System.out.println();
		
		// 5. Running into a bug here where null is left in the positions for some reason [FIXED]
		testHeap.RemoveTask(103);
		
		
		// 6. 
		testHeap.PrintAllTasks();
		System.out.println();
		
		// 7. Need to fix in terms of priority 
		boolean loop = true;
		while(loop) {
			Task taskToPrint = testHeap.getNextTask();
			if (taskToPrint != null) {
				System.out.println(taskToPrint);
			}
			
			else {
				loop = false;
			}
		}
		
		
		
	}
}
