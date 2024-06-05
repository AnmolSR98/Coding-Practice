package Section2;

public class Event {
	String name;
	int startTime; // Start time of the event, in minutes since midnight - to be used as the key to sort events in the BST
	int duration; // Duration of the event, in minutes
	public Event(String name, int startTime, int duration) {
		this.name = name;
		this.startTime = startTime;
		this.duration = duration;
	}

	@Override
	public String toString() {
		return name + " starts at " + startTime + " for " + duration + " minutes.";
	}
}
