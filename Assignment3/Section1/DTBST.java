package Section1;

import java.util.List;
import java.util.ArrayList;

public class DTBST {
	// the root of the tree
	private TreeNode root = null;
	
	// constructor that I ended up leaving empty
	public DTBST() {
		
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
		
		// Checking that the event is valid ie. not null, with positive start time and duration
		if (event == null) {
			throw new Exception("Event is null!");
		}
		
		if (event.startTime < 0) {
			throw new Exception("Event start time cannot be negative!");
		}
		
		if (event.duration < 0) {
			throw new Exception("Event duration cannot be negative!");
		}
		
		// Check first for any potential conflicts and then proceed if none are found
		if (!checkEventConflict(event)) {
			root = recAdd(event, root, -1);
			return true;
		}
		
		// Otherwise, return false
		return false;
	}
	
	// Private function 
	// The following lines (63 through to 100) are heavily based off the code in the notes from CPSC 331 notes on Binary Search Trees, the code 
	// for which was written by Dr.Jalal Kawash
	
	// Code for adding an event to the bst, which also takes argument direction which indicates the location of the node relative to the previous one
	// With 0 indicating the node is a left child, 1 for right child,  and -1 for root
	private TreeNode recAdd(Event event, TreeNode root, int direction) {
		
		// if the root is null, then add the event here
		if (root == null) {
			root = new TreeNode(event);
			
			// if the node is a left child, set leftThread to be true
			if (direction == 0) {
				root.leftThread = true;
				root.rightThread = false;
			}
			
			// if the node is a root, set both as false
			else if (direction == -1){
				root.leftThread = false;
				root.rightThread = false;
			}
			
			// if the node is a right child, set RightThread to be true
			else {
				root.leftThread = false;
				root.rightThread = true;
			}
		}
		
		// if the current node is larger, then traverse left
		else if (event.startTime < root.event.startTime) {
			root.left = recAdd(event, root.left, 0);
		}
		
		// otherwise, traverse right
		else {
			root.right = recAdd(event, root.right, 1);
		}
		
		// return the root after all of the recursions
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
		
		// Checking that a valid time has been entered
		if (time < 0) {
			throw new Exception("Time cannot be negative!");
		}
		
		// Get the event that occurs at that time
		Event event = findEventAtTime(time);
		// If the event is null, ie no event at the time then return false
		if (event == null) {
			return false;
		}
		
		// Otherwise, remove the event by calling recRemove
		root = recRemove(event, root);
		
		// Return true after removing
		return true;
	}
	
	// Once again the code from lines 140 to 164 is from the BinarySearchTree lecture written by Dr. Jalal Kawash
	private TreeNode recRemove(Event event, TreeNode root) {
		
		// if the root is null, return null
		if (root == null) {
			return null;
		}
		
		// if the root is greater than the event, the Node to be deleted will be along the left
		else if (root.event.startTime > event.startTime) {
			root.left = recRemove(event, root.left);
		}
		
		// if the root is less than the event, the Node to be deleted will be along the right
		else if (root.event.startTime < event.startTime) {
			root.right = recRemove(event, root.right);
		}
		
		// otherwise we have found the node to remove
		else {
			root = removeNode(root);
		}
		
		// return the root at the end of the recursions
		return root;
	}
	
	// Again, based heavily on the code from BST lectures written by Dr.Jalal Kawash from lines 167 to 191
	private TreeNode removeNode(TreeNode root) {
		
		// Create a tmp variable
		TreeNode tmp;
		
		// if the left child is null, then return the right child
		if (root.left == null) {
			return root.right;
		}
		
		// if the right child is null, then return the left child
		else if (root.right == null){
			return root.left;
		}
		
		// otherwise, fetch the successor and return it to replace the node being deleted
		else {
			tmp = getSuccessor(root);
			root.event = tmp.event;
			// remove the successor from the right subtree
			root.right = recRemove(tmp.event, root.right);
			// return the successor
			return root;
		}
	}
	
	private TreeNode getSuccessor(TreeNode root) {
		
		// Straightforward getSuccessor function, shift right once and then cycle left until reaching the min in the right subtree
		TreeNode tmp = root.right;
		
		if (tmp == null){
			return null;
		}
		
		while (tmp.left != null) {
			tmp = tmp.left;
		}
		
		return tmp;
	}
	
	private TreeNode getPredecessor(TreeNode root) {
		
		// Straightforward getPredecessor function, shift left once and then cycle right until reaching the max in the left subtree
		TreeNode tmp = root.left;
		
		if (tmp == null){
			return null;
		}
		
		while (tmp.right != null) {
			tmp = tmp.right;
		}
		
		return tmp;
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
	 * @throws Exception 
	*/
	public boolean deleteEvent(String eventName) throws Exception {
		// convert the event and to a startTime and then use the integer input function provided the event exists (ie. event time is not -1)
		int startTime = getEventTime(eventName, root);
		
		if (startTime == -1) {
			throw new Exception("There is no event with this name!");
		}
		
		return deleteEvent(startTime);
	}
	
	// Postorder traversal until the time for an event is found 
	private int getEventTime(String eventName, TreeNode root) {
		
		// if we have reached a null node, then we've exhausted the search of the tree
		if (root == null) {
			return -1;
		}
		
		// if the events match, then return the startTime
		else if (root.event.name.compareTo(eventName) == 0) {
			return root.event.startTime;
		}
		
		else {
			// otherwise try for left and right, if they yield a good result return
			int startTimeLeft = getEventTime(eventName, root.left);
			int startTimeRight = getEventTime(eventName, root.right);
			
			if (startTimeLeft != -1) {
				return startTimeLeft;
			}
			
			else if (startTimeRight != -1) {
				return startTimeRight;
			}
			
		}
		
		// otherwise return a -1 to indicate no event was found with this name
		return -1;
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
		
		// check that a valid time has been entered
		if (time < 0)  {
			throw new Exception("Time cannot be negative!");
		}
		
		// if so, search for it
		TreeNode eventNode = recSearch(time, root);
		
		// if a node with that event has been found return it, otherwise return null
		if (eventNode == null) {
			return null;
		}
		
		return eventNode.event;
		
	}
	
	// Following code section is heavily based on the recSearch provided in the Binary Search Lecture by Dr. Jalal Kawash 
	// Lines 313 - 336
	// This a function to find a node with an event at a specific time
	private TreeNode recSearch(int time, TreeNode root) {
		
		// if the root is null, then it is not in the tree
		if (root == null) {
			return null;
		}
		
		// if the time falls within [startTime, startTime + duration] then return this node
		else if ((time >= root.event.startTime) && (time <= root.event.startTime + root.event.duration)) {
			return root;
		}
		
		// otherwise if the time occurs before the nodes event, traverse left
		else if (time < root.event.startTime) {
			return recSearch(time, root.left);
		}
		
		// otherwise, if the time occurs after the nodes event, traverse right
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
	 * @throws Exception 
	*/
	public Event findNextEvent(int time) throws Exception {
		
		// check that a valid time has been entered
		if (time < 0)  {
			throw new Exception("Time cannot be negative!");
		}
		
		// get the node for the event that is occuring at the time provided
		TreeNode nodeAtTime = recSearch(time, root);
		TreeNode successor = null;
		TreeNode parent = null;
		
		// if there is no node, try to find the larger parent for where the time would be slotted in
		if (nodeAtTime == null) {
			parent = getLargerParent(time, root);
		}
		
		else {
			// if there is a node at the time, then get the successor and the parent
			successor = getSuccessor(nodeAtTime);
			parent = getLargerParent(nodeAtTime.event.startTime, root);
		}
		
		// if the successor is not null, return it
		if (successor != null) {
			return successor.event;
		}
		
		// if the parent is not null, return it
		else if (parent != null) {
			return parent.event;
		}
		
		// otherwise, there is no event after this time
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
	 * @throws Exception 
	*/
	// Have it get the time that the thing starts at first, then go searching
	public Event findNextEvent(String eventName) throws Exception {
		int startTime = getEventTime(eventName, root);
		if (startTime == -1) {
			return null;
		}
	
		return findNextEvent(startTime);
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
	 * @throws Exception 
	*/
	
	public Event findPreviousEvent(int time) throws Exception {
		
		// check that a valid time has been entered
		if (time < 0)  {
			throw new Exception("Time cannot be negative!");
		}
		
		// find the node for the event occurring at the time
		TreeNode nodeAtTime = recSearch(time, root);
		TreeNode predecessor = null;
		TreeNode parent = null;
		
		// if there is no event occuring at the time, get the smaller parent for where the event would be slotted in
		if (nodeAtTime == null) {
			parent = getSmallerParent(time, root);
		}
		
		// if there is an event, get both the parent and the predecessor
		else {
			predecessor = getPredecessor(nodeAtTime);
			parent = getSmallerParent(nodeAtTime.event.startTime, root);
		}
		
		// if the predecessor exists, return it
		if (predecessor != null) {
			return predecessor.event;
		}
		
		// otherwise, return the parent
		else if (parent != null) {
			return parent.event;
		}
		
		// if neither are found, return null
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
	 * @throws Exception 
	*/
	// redirects traffic to the integer input function
	public Event findPreviousEvent(String eventName) throws Exception {
		int startTime = getEventTime(eventName, root);
		if (startTime == -1) {
			return null;
		}
		
		return findPreviousEvent(startTime);
	}
	
	// function to be used in the case that a node doesn't have a left subtree, in which case the next smallest value is its parent
	private TreeNode getSmallerParent(int time, TreeNode root) {
		
		// if the root is null or equal to the time, then we have reached the node we were trying to find the nextSmallest value for, and thus it should terminate
		if ((root == null) || (root.event.startTime == time)) {
			return null;
		}
		
		// if the node is greater than the value for the time, we need to cycle left
		else if (root.event.startTime > time) {
			return getSmallerParent(time, root.left);
		}
		
		// otherwise we need to keep cycling right as long the node is still smaller than and provided the right is not null
		else if ((root.event.startTime < time) && (root.right != null)) {
			
			// if the right node is still smaller, keep cycling right
			if (root.right.event.startTime < time) {
				return getSmallerParent(time, root.right);
			}
			
			// if not, then this is the parent and we should return it
			else {
				return root;
			}
			
		}
		
		// otherwise, we have reached the parent and should return
		else {
			return root;
		}
	}
	
	// virtually identical to the code above, but for finding a larger parent in the case that there is no successor
	private TreeNode getLargerParent(int time, TreeNode root) {
		
		if ((root == null) || (root.event.startTime == time)) {
			return null;
		}
		
		else if (root.event.startTime < time) {
			return getLargerParent(time, root.right);
		}
		
		else if ((root.event.startTime > time) && (root.left != null)) {
			
			if (root.left.event.startTime > time) {
				return getLargerParent(time, root.left);
			}
			
			else {
				return root;
			}
			
		}
		
		else {
			return root;
		}
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
	// Simple function that passes along to recursive event conflict checker
	public boolean checkEventConflict(Event e) {
		return recCheckConflict(e.startTime, root);
	}
	
	// function to recursively check there is a spot for the event in the tree
	private boolean recCheckConflict(int time, TreeNode root) {
		
		// if there is a null slot, then false
		if (root == null) {
			return false;
		}
		
		// if there is some overlap, then return true, where the end points are not included
		else if ((time > root.event.startTime) && (time < root.event.startTime + root.event.duration)) {
			return true;
		}
		
		// otherwise traverse left
		else if (time <= root.event.startTime) {
			return recCheckConflict(time, root.left);
		}
		
		// otherwise go right
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
		// Do not change this
		List<Event> events = new ArrayList<>();
		collectEventsInRange(root, startTimeRange, endTimeRange, events);
		return events;
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
	* - Events in the specified time range are added to the list events in
	chronological order.
	* - If end is negative, all events from start time onwards are included.
	*/
	private void collectEventsInRange(TreeNode node, int start, int end, List<Event> events) {
		// In order traversal method
		if (node != null) {
			
			// check along the left subtree
			collectEventsInRange(node.left, start, end, events);
			
			// if the node's event occurs within the range specified, (with -1 indicating no upper bound) then add it to the list
			if ((node.event.startTime + node.event.duration >= start) && ((node.event.startTime <= end) || (end < 0))) {
				events.add(node.event);
			}
			
			// check along the right subtree
			collectEventsInRange(node.right, start, end, events);
		}
		
	}
}