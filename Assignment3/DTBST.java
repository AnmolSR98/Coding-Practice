package Section2;

import java.util.List;

public class DTBST {
	private TreeNode root = null;
	
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
		
		if (event == null) {
			throw new Exception("Event is null!");
			
		}
		
		if (event.startTime < 0) {
			throw new Exception("Event start time cannot be negative!");
		}
		
		if (event.duration < 0) {
			throw new Exception("Event duration cannot be negative!");
		}
		
		TreeNode tmp = root;
		TreeNode parent = root;
		boolean loop = true;
		boolean added = false;
		
		// remember how to update parent, maybe that would be better
		while (loop) {
			
			// if a spot is found, then add the event (ALSO COVERS IF THE TREE IS EMPTY)
			if (tmp == null) {
				TreeNode newNode = new TreeNode(event);
				// if the parent ie. root is null, make it equal to the newNode
				if (parent == null) {
					root = newNode;
				}
				
				// if the parent event starts after, set the new event to the left
				else if	(parent.event.startTime > event.startTime) {
					parent.left = newNode;
				}
				
				// if the parent event starts before, set the new event to the right
				else {
					parent.right = newNode;
				}
				
				loop = false;
				added = true;
				
			}
			
			// if the root event finishes before the new event starts, move along to the right
			else if (root.event.startTime + root.event.duration < event.startTime) {
				parent = tmp;
				tmp = tmp.right;
			}
			
			// if the root event starts after the new event finished, move it to the left
			else if (root.event.startTime > event.startTime + event.duration) {
				parent = tmp;
				tmp = tmp.left;
			}
			
			// if the root event has some overlap with the new event's time, kill the loop
			else {
				loop = false;
			}
		}
		
		return added;
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
	// NEED TO FIX THIS SOON
	public boolean deleteEvent(int time) throws Exception {
		
		if (time < 0) {
			throw new Exception("Time cannot be negative!");
		}
		
		TreeNode tmp = root; 
		TreeNode parent = root;
		boolean deleted = false;
		boolean loop = true;
		
		while (loop) {
			
			// if an event is found that is going on at that time
			if (tmp == null) {
				return false;
			}
			
			
			else if ((tmp.event.startTime <= time) && (tmp.event.startTime + tmp.event.duration >= time)) {
				
				// if the event occurs before the parent, set the left to null, else set the right to null
				if (parent.event.startTime > time) {
					parent.left = null;
					
				}
				
				else {
					parent.right = null;
				}
				
				return true;
			}
			
			// if the root event finishes before the new event starts, move along to the right
			else if (root.event.startTime + root.event.duration < time) {
				parent = tmp;
				tmp = tmp.right;
			}
			
			// if the root event starts after the new event finished, move it to the left
			else {
				parent = tmp;
				tmp = tmp.left;
			}
						
		}
		
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
	*/
	public Event findEventAtTime(int time) {
		return null;
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
	* - Returns null if no such event is found.
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
		return false;
	}
	
	/**
	* Returns a list of events occurring between startTimeRange and endTimeRange,
	inclusive. If endTimeRange is negative, returns all events starting from
	startTimeRange onwards.
	*
	* Precondition:
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
