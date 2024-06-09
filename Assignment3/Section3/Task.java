// Anmol Ratol 30231177
// A class file for the task

package Section3;

public class Task {
	
	// basic attributes
	int id;
	int priority;
	String description;
	
	// constructor
	public Task(int ident, int prior, String descr) {
		id = ident;
		priority = prior;
		description = descr;
	}
	
	// overriden toString method for clean printing
	@Override
	public String toString() {
		return "Task ID: "+id+", Priority: "+priority+", Description: "+description; 
	}
}
