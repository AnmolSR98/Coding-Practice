// Anmol Ratol 30231177
// A main class to test the double threaded binary search tree

package Section1;

public class Main {
	
	// the main method
	public static void main(String[] args) throws Exception {
		DTBST testTree = new DTBST();
		
		// 1. through 7. are just adding a bunch of events
		// 1. 
		testTree.addEvent(new Event("Project Kickoff", 480, 60));
		// 2.
		testTree.addEvent(new Event("Team Meeting", 600, 30));
		// 3.
		testTree.addEvent(new Event("Client Call", 630, 45));
		// 4.
		testTree.addEvent(new Event("Lunch Break", 400, 60));
		// 5.
		testTree.addEvent(new Event("Code Review", 465, 480));
		// 6.
		testTree.addEvent(new Event("Stand Up", 550, 10));
		// 7.
		testTree.addEvent(new Event("Design Discussion", 960, 60));
		
		// 8. Adding an event emergency meeting, and printing conflict if add fails
		if (!testTree.addEvent(new Event("Emergency Meeting", 610, 15))) {
			System.out.println("Conflict!");
		}
		
		// 9. Getting the event at 645
		System.out.println(testTree.findEventAtTime(645));
		
		// 10. Getting the event immediately after lunch break
		Event afterLunch = testTree.findNextEvent("Lunch Break");
		if (afterLunch != null) {
			System.out.println(afterLunch);
		}
		
		else {
			System.out.println("No Such Event");
		}
		
		// 11. Getting the event immediately after client call
		Event beforeClient = testTree.findPreviousEvent("Client Call");
		if (beforeClient != null) {
			System.out.println(beforeClient);
		}
		
		else {
			System.out.println("No Such Event");
		}
		
		// 12.
		System.out.println(testTree.findPreviousEvent(410));
		
		// 13.
		System.out.println(testTree.findPreviousEvent(490));
		
		// 14.
		System.out.println(testTree.findEventAtTime(490));
		
		// 15.
		if (!testTree.deleteEvent("Design Discussion")) {
			System.out.println("No Such Event!");
		}
		
		// 16.
		if (!testTree.deleteEvent(565)) {
			System.out.println("No Such Event!");
		}
		
		// 17.
		if (!testTree.deleteEvent(625)) {
			System.out.println("No Such Event!");
		}
		
		// 18.
		if(!testTree.addEvent(new Event("Wrap Up Meeting", 1010, 15))) {
			System.out.println("Conflict");
		}
		
		// 19.
		System.out.println(testTree.getEventsInRange(480, 1020));
		
		// 20.
		System.out.println(testTree.getEventsInRange(0, 720));
	}

}