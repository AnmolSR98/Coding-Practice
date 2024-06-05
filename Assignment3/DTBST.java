package Section2;

import java.util.List;

public class DTBST {
	// remember to change back to PRIVATE before submission
	public TreeNode root = null;
	
	public DTBST() {
	// Implement this constructor
	}
	
	/**
	* Adds an event to the tree. Returns true if successful, false if unsuccessful.
	*
	* Precondition:
	* - event is not null.
	* - event.startTime >= 0 (valid start time in minutes since midnight).
	* - event.duration > 0 (valid duration in minutes).
	*
	* Postcondition:
	* - The event has been added to the tree sorted by start time if no conflict
	exists.
	* - Returns true if the event was successfully added.
	* - Returns false if there was a conflict or the event was not added for any
	reason.
	 * @throws Exception 
	*/
	public boolean addEvent(Event event) throws Exception {
		
		// ie checking that the event is valid
		if (event == null) {
			throw new Exception("Event is null!");
		}
		
		if (event.startTime < 0) {
			throw new Exception("Event start time cannot be negative!");
		}
		
		if (event.duration < 0) {
			throw new Exception("Event duration cannot be negative!");
		}
		
		//System.out.println(checkEventConflict(event) + "|||" + event);
		// if there are no conflicts, then add and return true;
		if (!checkEventConflict(event)) {
			root = recAdd(event, root);
			return true;
		}
		
		return false;
	}
	
	private TreeNode recAdd(Event event, TreeNode root) {
		
		if (root == null) {
			root = new TreeNode(event);
		}
		
		else if (event.startTime + event.duration <= root.event.startTime) {
			root.left = recAdd(event, root.left);
		}
		
		// definitely an issue with inserting it on the very right, resulting in some kind of error
		// else if (event.startTime >= root.event.startTime + root.event.duration) {
		else {
			root.right = recAdd(event, root.right);
		}
		
		return root;
	}

	
	/**
	* Deletes the event occurring at the provided time. The time could point to the
	start or middle of an event.
	* Returns true if successful, false if unsuccessful.
	*
	* Precondition:
	* - time >= 0 (valid time in minutes since midnight).
	*
	* Postcondition:
	* - If an event starting or ongoing at the given time is found, it is removed
	from the tree.
	* - Returns true if the event was successfully deleted.
	* - Returns false if no event was found at the given time.
	 * @throws Exception 
	*/
	public boolean deleteEvent(int time) throws Exception {
		return false;
		
	}
	/**
	* Deletes the event named "eventName". Returns true if successful, false if
	unsuccessful.
	*
	* Precondition:
	* - eventName is not null and not empty.
	*
	* Postcondition:
	* - If an event with the given name is found, it is removed from the tree.
	* - Returns true if the event was successfully deleted.
	* - Returns false if no event with the given name was found.
	*/
	// GOING TO HAVE TO DO THIS WITH SOME SORT OF INORDER TRAVERSAL THING
	public boolean deleteEvent(String eventName) {
		return false;
	}
	/**
	* Returns the event occurring at the specified time. Returns null if no event is
	found at this time.
	*
	* Precondition:
	* - time >= 0 (valid time in minutes since midnight).
	*
	* Postcondition:
	* - Returns the event that is occurring at the specified time.
	* - Returns null if no event is occurring at the specified time.
	 * @throws Exception 
	*/
	public Event findEventAtTime(int time) throws Exception {
		
		if (time < 0) {
			throw new Exception("Time must be greater than zero!");
		}
		
		TreeNode eventNode = recSearch(time, root);
		
		
		if (eventNode == null) {
			return null;
		}
		
		return eventNode.event;
		
	}
	
	private TreeNode recSearch(int time, TreeNode root) {
		
		if (root == null) {
			return null;
		}
		
		else if ((time >= root.event.startTime) && (time <= root.event.startTime + root.event.duration)) {
			return root;
		}
		
		else if (time < root.event.startTime) {
			return recSearch(time, root.left);
		}
		
		else {
			return recSearch(time, root.right);
		}
	}
	/**
	* Returns the first event that starts after the specified time. Returns null if
	no such event is found.
	*
	* Precondition:
	* - time >= 0 (valid time in minutes since midnight).
	*
	* Postcondition:
	* - Returns the first event that starts after the specified time.
	* - Returns null if no such event is found.
	*/
	public Event findNextEvent(int time) {
		return null;
	}
	/**
	* Returns the first event that starts after the event with the specified name.
	Returns null if no such event is found.
	*
	* Precondition:
	* - eventName is not null and not empty.
	*
	* Postcondition:
	* - Returns the first event that starts after the event with the specified name.
	* - Returns null if no such event is found.if (root.left != null) {
			System.out.println(root.left.event);
			if (root.left.right != null) {
				System.out.println(root.left.right.event);
			}
		}
	*/
	public Event findNextEvent(String eventName) {
		return null;
	}
	/**
	* Returns the event that occurred (started and finished) immediately before the
	specified time. Returns null if no such event is found.
	*
	* Precondition:
	* - time >= 0 (valid time in minutes since midnight).
	*
	* Postcondition:
	* Returns the event that occurred (started and finished) immediately before the
	specified time. Returns null if no such event is found.
	* - Returns null if no such event is found.
	*/
	public Event findPreviousEvent(int time) {
		return null;
	}
	/**
	* Returns the event that occurred immediately before the event with the specified
	name. Returns null if no such event is found.
	*
	* Precondition:
	* - eventName is not null and not empty.
	*
	* Postcondition:
	* - Returns the event that occurred immediately before the event with the
	specified name.
	* - Returns null if no such event is found.
	*/
	public Event findPreviousEvent(String eventName) {
		return null;
	}
	/**
	* Returns true if a conflict is found between event e and the events in the tree.
	Returns false otherwise.
	*
	* Precondition:
	* - e is not null.
	* - e.startTime >= 0 (valid start time in minutes since midnight).
	* - e.duration > 0 (valid duration in minutes).
	*
	* Postcondition:
	* - Returns true if there is a conflict between event e and any event in the tree.
	* - Returns false if no conflict is found.
	*/
	public boolean checkEventConflict(Event e) {
		
		return recCheckConflict(e.startTime, root);
	}
	
	private boolean recCheckConflict(int time, TreeNode root) {
		
		// if there is a null slot, then false
		if (root == null) {
			return false;
		}
		
		// if there is some overlap, then return true, where the end points are not included
		else if ((time > root.event.startTime) && (time < root.event.startTime + root.event.duration)) {
			return true;
		}
		
		else if (time <= root.event.startTime) {
			return recCheckConflict(time, root.left);
		}
		
		else  {
			return recCheckConflict(time, root.right);
		}
	}
	
	/**
	* Returns a list of events occurring between startTimeRange and endTimeRange,
	inclusive. If endTimeRange is negative, returns all events starting from
	startTimeRange onwards.
	*
	* Precondition:false
	* - startTimeRange >= 0 (valid time in minutes since midnight).
	* - endTimeRange >= startTimeRange or endTimeRange < 0 (indicating no upper
	bound).
	*
	* Postcondition:
	* - Returns a list of events occurring between startTimeRange and endTimeRange,
	inclusive.
	* - If endTimeRange is negative, returns all events starting from startTimeRange
	onwards.
	*/
	public List<Event> getEventsInRange(int startTimeRange, int endTimeRange) {
		// ASK TA ABOUT THIS
		// Do not change this
		//List<Event> events = new ArrayList<>();
		//collectEventsInRange(root, startTimeRange, endTimeRange, events);
		//return events;
		return null;
	}
	/**
	* Returns a list of events occurring between the "start" and "end" times in
	chronological order. Includes the event that is already happening at the
	"start". If the "end" time is negative, all events from the "start" time
	onwards are included.
	*
	* Precondition:
	* - node is either null or a valid TreeNode.
	* - start >= 0 (valid start time in minutes since midnight).
	* - end >= start or end < 0 (indicating no upper bound).
	* - events is not null.
	*
	* Postcondition:
	* - Events in the specified time range are added to the list ’events’ in
	chronological order.
	* - If end is negative, all events from start time onwards are included.
	*/
	private void collectEventsInRange(TreeNode node, int start, int end, List<Event>
	events) {
	// Implement this method
	}
}
