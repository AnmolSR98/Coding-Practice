package mygraph;

public class GraphTester {
	
	public static void main(String[] args) {
		
		AdjacencyList testGraph = new AdjacencyList(6);
		testGraph.addConnection(0, 1, 1);
		testGraph.addConnection(0, 2, 1);
		testGraph.addConnection(0, 3, 1);
		testGraph.addConnection(0, 4, 1);
		testGraph.addConnection(1, 3, 1);
		testGraph.addConnection(3, 4, 1);
		testGraph.addConnection(4, 2, 1);
		testGraph.addConnection(4, 5, 1);
		
		System.out.println(testGraph);
		System.out.println(testGraph.DFS(0));
		System.out.println(testGraph.BFS(0));
		
	}

}
