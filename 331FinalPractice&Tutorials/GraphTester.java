package mygraph;

public class GraphTester {
	
	public static void main(String[] args) {
		
		AdjacencyList testGraph = new AdjacencyList(8);
		testGraph.addConnection(0, 2, 1);
		testGraph.addConnection(2, 6, 1);
		testGraph.addConnection(1, 6, 1);
		testGraph.addConnection(5, 6, 1);
		testGraph.addConnection(4, 6, 1);
		System.out.println(testGraph.TopologicalSort());
		System.out.println(testGraph.isStronglyConnected());
		int[] paths = testGraph.shortestPath(1);
		for (int elem: paths) {
			System.out.print(elem + ", ");
		}
	}

}
