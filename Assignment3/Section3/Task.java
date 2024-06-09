package Section4;

public class Task {
	int id;
	int priority;
	String description;
	
	public Task(int ident, int prior, String descr) {
		id = ident;
		priority = prior;
		description = descr;
	}
	
	@Override
	public String toString() {
		return "Task ID: "+id+", Priority: "+priority+", Description: "+description; 
	}
}
