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
		searchTree.RoLR(searchTree.root);
		System.out.println();
		searchTree.LRRo(searchTree.root);
		System.out.println();
		// bug with remove function 
	}
	
}
