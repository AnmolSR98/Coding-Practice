package llbst;

public class LLBST <T extends Comparable> {
	
	class Node{
		private Node right;
		private Node left;
		private T data;
		
		public Node(T dataToStore) {data = dataToStore;}
		
		public Node getRight() { return right;}
		public Node getLeft() { return left;}
		
		public void setRight(Node newRight) {right = newRight;}
		public void setLeft(Node newLeft) {left = newLeft;}
		
		public T getData(){return data;}
		public void setData(T newData) {data = newData;}  
	}
	public Node root;
	
	public LLBST() {}
	public boolean isFull() {return false;}
	public boolean isEmpty() {return (root == null);}
	public void clear() {root = null;}
	
	public int size() {
		return recSize(root);
	}
	
	private int recSize(Node root) {
		
		if (root == null) {
			return 0;
		}
		
		else {
			return recSize(root.getLeft()) + recSize(root.getRight()) + 1;
		}
	}
	
	public boolean contains(T value) {
		return recContains(value, root);
	}
	
	private boolean recContains(T value, Node root) {
		
		if (root == null) { return false; }
		
		else if(root.getData().compareTo(value) == 0) { return true; }
		
		else if(value.compareTo(root.getData()) < 0) {
			return recContains(value, root.getLeft());
		}
		
		else {
			return recContains(value, root.getRight());
		}
	}
	
	public void add(T value) {
		root = recAdd(value, root);
	}
	
	private Node recAdd(T value, Node root) {
		
		if (root == null) {
			root = new Node(value);
		}
		
		else if (value.compareTo(root.getData()) < 0){
			root.setLeft(recAdd(value, root.getLeft()));
		}
		
		else {
			root.setRight(recAdd(value, root.getRight()));
		}
		
		return root;
		
	}
	
	public void remove(T value) throws Exception {
		if (contains(value)) {
			root = recRemove(value, root);
		}
		
		else {
			throw new Exception("The value is not in the tree!");
		}
	}
	
	private Node recRemove(T value, Node root) {
		if (root == null) {
			return null;
		}
		
		else if (value.compareTo(root.getData()) < 0) {
			root.setLeft(recRemove(value, root.getLeft()));
		}
		
		else if (value.compareTo(root.getData()) < 0) {
			root.setRight(recRemove(value, root.getRight()));
		}
		
		else {
			root = removeNode(root);
		}
		
		return root;
	}
	
	private Node removeNode(Node root) {
		T tmp;
		if (root.getLeft() == null) {
			return root.getRight();
		}
		
		else if (root.getRight() == null) {
			return root.getLeft();
		}
		
		else {
			tmp = getSuccessor(root);
			root.setData(tmp);
			root.setRight(recRemove(tmp, root.getRight()));
			return root;
		}
	}
	
	private T getSuccessor(Node node) {
		Node temp = node.getRight();
		while (temp.getLeft() != null) {
			temp = temp.getLeft();
		}
		
		return temp.getData();
	}
	
	public void printTree() {
		inOrderPrint(root);
		System.out.println();
	}
	
	private void inOrderPrint(Node root) {
		if (root != null) {
			inOrderPrint(root.getLeft());
			System.out.print(root.getData() + ",");
			inOrderPrint(root.getRight());
		}
	}
	
	public void LRRo(Node root) {
		if (root != null) {
			LRRo(root.getLeft());
			LRRo(root.getRight());
			System.out.print(root.getData() + ",");
		}
	}
	
	public void RoLR(Node root) {
		if (root != null) {
			System.out.print(root.getData() + ",");
			RoLR(root.getLeft());
			RoLR(root.getRight());
		}
	}
	
	public void rotate(int direction, T value) throws Exception {
		// 0 for left, 1 for right
		if (contains(value) && direction == 1) {
			root = rightRotate(value, root.getLeft(), root);
		}
		
		else if(contains(value) && direction == 0) {
			root = leftRotate(value, root.getRight(), root);
		}
		
		else {
			throw new Exception("Value is not in tree!");
		}
	}
	
	private Node rightRotate(T value, Node a, Node b) {
		
		if (a.getData().compareTo(value) == 0) {
			b.setLeft(a.getRight());
			a.setRight(b);
		}
		
		else if (a.getData().compareTo(value) < 0){
			return rightRotate(value, a.getLeft(), a);
		}
		
		else {
			return rightRotate(value, a.getRight(), a);
		}
		
		return a;
	}
	
	private Node leftRotate(T value, Node a, Node b) {
		
		if (a.getData().compareTo(value) == 0) {
			b.setRight(a.getLeft());
			a.setLeft(b);
		}
		
		else if (a.getData().compareTo(value) < 0){
			return leftRotate(value, a.getLeft(), a);
		}
		
		else {
			return leftRotate(value, a.getRight(), a);
		}
		
		return a;
	}
}
