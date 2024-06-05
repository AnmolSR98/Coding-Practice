package Section2;

public class Main {
	
	public static void main(String[] args) throws Exception {
		DTBST testTree = new DTBST();
		
		// For 1 through to 8 in the assignment
		testTree.addEvent(new Event("Project Kickoff", 480, 60));
		TreeNode root = testTree.root;
		testTree.addEvent(new Event("Team Meeting", 600, 30));
		testTree.addEvent(new Event("Client Call", 630, 45));
	
		testTree.addEvent(new Event("Lunch Break", 400, 60));
		// Issue here, doesn't get added, seems to be an issue with the conflict checker
		// Never mind, seems to be an issue with the adder
		testTree.addEvent(new Event("Code Review", 465, 480));
		
		testTree.addEvent(new Event("Stand Up", 550, 10));
		testTree.addEvent(new Event("Design Discussion", 960, 60));
		printTree(root.right.right);
		
	}
	
	private static void printTree(TreeNode root) {
		inOrderPrint(root);
		System.out.println();
	}
	
	private static void inOrderPrint(TreeNode root) {
		if (root != null) {
			System.out.println(root.event);
			inOrderPrint(root.left);
			inOrderPrint(root.right);
		}
	}

}
