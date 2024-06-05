package Section2;

public class TreeNode {
	Event event;
	TreeNode left, right;
	boolean leftThread, rightThread;
	
	public TreeNode(Event event) {
		this.event = event;
		this.left = null;
		this.right = null;
		this.leftThread = true;
		this.rightThread = true;
	}
}
