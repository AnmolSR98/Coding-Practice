package llbst;

public class LLBST <T extends Comparable> {
	
	private class Node{
		private Node right;
		private Node left;
		private T data;
		
		public Node(T dataToStore) {data = dataToStore;}
		
		public Node getRight() { return right;}
		public Node getLeft() { return left;}
		
		public void setRight(Node newRight) {right = newRight;}
		public void setLeft(Node newLeft) {right = newLeft;}
		
		public T getData(){return data;}
		public void setData(T newData) {data = newData;}  
	}
	Node root;
	
	public boolean isFull() {return false;}
	public boolean isEmpty() {return (root == null);}
	public void clear() {root = null;}
	
	public boolean contains(T value) {
		return recContains(value, root);
	}
	
	private boolean recContains(T value, Node root) {
		if (root.getData() == value) { return true; }
		
		else if (root == null) { return false; }
		
		else if(value.compareTo(root.getData()) < 0) {
			return recContains(value, root.getLeft());
		}
		
		else {
			return recContains(value, root.getLeft());
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
	
	public void remove(T value) {
		root = recRemove(value, root);
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
		
		else if (root.getLeft() == null) {
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
	}
	
	public void inOrderPrint(Node root) {
		if (root != null) {
			inOrderPrint(root.getLeft());
			inOrderPrint(root);
			inOrderPrint(root.getRight());
		}
	}
	
}
