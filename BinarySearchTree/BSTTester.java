package llbst;

public class BSTTester {
	
	public static void main(String[] args) throws Exception {
		LLBST searchTree = new LLBST();
		
		searchTree.add(5);
		searchTree.add(7);
		searchTree.add(4);
		searchTree.add(9);
		searchTree.add(1);
		searchTree.add(6);
		System.out.println(searchTree.contains(5));
		System.out.println(searchTree.contains(7));
		System.out.println(searchTree.contains(4));
		System.out.println(searchTree.contains(9));
		System.out.println(searchTree.contains(1));
		System.out.println(searchTree.contains(200));
		searchTree.printTree();
		System.out.println();
		searchTree.remove(1);
		searchTree.remove(5);
		System.out.println(searchTree.root.getData());
		System.out.println(searchTree.contains(1));
		searchTree.printTree();
		searchTree.add(2);
		searchTree.add(1);
		searchTree.add(3);
		searchTree.printTree();
		searchTree.rotate(1, 4);
		searchTree.printTree();
		System.out.println(searchTree.root.getData());
		System.out.println(searchTree.root.getRight().getData());
		System.out.println(searchTree.root.getLeft().getData());
		searchTree.rotate(1, 2);
		searchTree.printTree();
		System.out.println(searchTree.root.getData());
		System.out.println(searchTree.root.getRight().getLeft().getData());
		System.out.println(searchTree.root.getLeft().getData());
		searchTree.rotate(0, 4);
		searchTree.printTree();
		System.out.println(searchTree.root.getData());
		System.out.println(searchTree.root.getRight().getData());
		System.out.println(searchTree.root.getLeft().getData());
	
		// bug with remove function [FIXED]
	}
	
}
