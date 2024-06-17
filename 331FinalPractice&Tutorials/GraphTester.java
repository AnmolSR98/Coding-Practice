package mygraph;

public class GraphTester {
	
	public static void main(String[] args) {
		AdjacencyList testGraph = new AdjacencyList(5);
		testGraph.addConnection(0, 4, 1);
		System.out.println(testGraph);
		System.out.println(testGraph.removeConnection(0, 4));
	}

}
