package LLRBT;

public class LLRBT<T extends Comparable>{
	
	public class Node{
		private Node right;
		private Node left;
		private T data;
		private Node parent;
		private String colour = "r"; // all nodes start off red
		
		
		public Node(T dataToStore) {data = dataToStore;}
		
		public Node getRight() { return right;}
		public Node getLeft() { return left;}
		public Node getParent() {return parent;}
		public String getColour() {return colour;}
		
		public void setRight(Node newRight) {right = newRight;}
		public void setLeft(Node newLeft) {left = newLeft;}
		public void setParent(Node newParent) {parent = newParent;}
		public void setColour() {
			if (colour.compareTo("r") == 0){
				colour = "b";
			}
			
			else {
				colour = "r";
			}
		}
		
		public T getData(){return data;}
		public void setData(T newData) {data = newData;}  
	}
	public Node root;
	
	public LLRBT() {}
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

		// case 1, empty tree
		if (root == null) {
			Node newNode = new Node(value);
			newNode.setColour(); // changing colour to black
			root = newNode;
		}
		
		else {
			Node newNode = new Node(value);
			Node parent = getParent(value);
			Node pibling = getSibling(parent);
			
			// case 2, parent and pibling are red
			if ((parent.getColour().compareTo("r") == 0) && (pibling.getColour().compareTo("r") == 0)) {
				parent.setColour();
				pibling.setColour();
				Node grandParent = parent.getParent();
				grandParent.setColour();
				
			}
			
			else {
				if (pibling == null) {
					
				}
			}
			
			
		}
	}
	
	private void Case2(Node parent) {
		
	}
	
	private Node getParent(T value) {
		Node tmp = root;
		Node parent = tmp;
		
		while (tmp != null) {
			if (tmp.getData().compareTo(value) < 0) {
				parent = tmp;
				tmp = tmp.getLeft();
			}
			
			else {
				parent = tmp;
				tmp = tmp.getRight();
			}
		}
		
		return parent;
	}
	
	private Node getSibling(Node node) {
		if (node.getParent() == null)  {
			return null;
		}
		
		else {
			// if the parent is the right child
			if (node.getParent().getData().compareTo(node.getData()) < 0) {
				return node.getParent().getLeft();
			}
			
			else {
				return node.getParent().getRight();
			}
		}
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
	
	// INSERT NEW CODE HERE
	public void remove(T value){
		
	}
	private T getPredecessor() {
		
		Node tmp = root.getLeft();
		while (tmp.getRight() != null) {
			tmp = tmp.getRight();
		}
		
		tmp.getParent().setRight(null);
		
		return tmp.getData();
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

}
