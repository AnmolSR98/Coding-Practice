package Section4;

public class Task {
	int id;
	int priority;
	String description;
	
	public Task() {
	}
	
	@Override
	public String toString() {
		return "Task ID: "+id+", Priority: "+priority+", Description: "+description; 
	}
}
