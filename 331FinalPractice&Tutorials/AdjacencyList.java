package mygraph;

import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.Stack;

public class AdjacencyList {
	
	int size;
	LinkedList<Integer[]>[] list;
	
	public AdjacencyList(int dim1) {
		size = dim1;
		list = new LinkedList[dim1];
		for (int i = 0; i < dim1; i++) {
			list[i] = new LinkedList<Integer[]>();
		}
	}
	
	public void addConnection(int node, int nodeToConnectTo, int weight) {
		Integer[] listToAdd = new Integer[2];
		listToAdd[0] = nodeToConnectTo; listToAdd[1] = weight;
		list[node].add(listToAdd);
	}
	
	public boolean removeConnection(int node, int connection) {
		LinkedList<Integer[]> Location = list[node];
		for (int i = 0;  i < Location.size(); i++) {
			if (Location.get(i)[0] == connection) {
				Location.remove(i);
				return true;
			}
		}
		
		return false;
	}
	
	// needed to add termination condition for the 
	public List<Integer> DFS(int startNode) {
		
		
		List<Integer> vertices = new ArrayList<Integer>();
		Stack<Integer> verticesStack = new Stack<Integer>();
		
	
		
		verticesStack.push(startNode);
		
		boolean loop = true;
		
		while (loop) {
			
			int currentVertex = verticesStack.pop();
			if (!vertices.contains(currentVertex)) {
				vertices.add(currentVertex);
			}
			LinkedList<Integer[]> currentList = list[currentVertex]; 
			
			for (int i = 0; i < currentList.size(); i++) {
				int node = currentList.get(i)[0];
				
				verticesStack.push(node);
			}
			
			loop = (!verticesStack.isEmpty() && (verticesStack.peek() != startNode));
		}
		
		return vertices;
	}
	
	public List<Integer> BFS(int startNode) {
		
		List<Integer> vertices = new ArrayList<Integer>();
		LinkedQueue verticesQueue = new LinkedQueue<Integer>();
	
		
		verticesQueue.enqueue(startNode);
		
		while (!verticesQueue.isEmpty()) {
			
			int currentVertex = (int) verticesQueue.dequeue();
			if (!vertices.contains(currentVertex)) {
				vertices.add(currentVertex);
			}
			LinkedList<Integer[]> currentList = list[currentVertex]; 
			
			for (int i = 0; i < currentList.size(); i++) {
				int node = currentList.get(i)[0];
				verticesQueue.enqueue(node);
			}
		
		}

		return vertices;
	}
	
	// exercises to do for these
	public boolean hasCycle() {
		List<List<Integer>> allNodesReach = new ArrayList<List<Integer>>();
		
		for (int i = 0; i < size; i++) {
			allNodesReach.add(DFS(i));
		}
		
		for (int i = 0; i < size; i++) {
			
			List<Integer> currentReachable = allNodesReach.get(i);
			
			for (int j = 0; j < size; j++) {
				
				if (currentReachable.contains(j) && allNodesReach.get(j).contains(i) && (i != j)) {
					return true;
				}
				
			}
		}
		
		return false;
	}
	
	private boolean visitedAll(boolean[] vertices) {
		
		for (int i = 0; i < vertices.length; i++) {
			if (!vertices[i]) {
				return false;
			}
		}
		
		return true;
	}
	
	// done using DFS
	public List<Integer> TopologicalSort() {
		
		boolean[] hasVisited = new boolean[size];
		Stack<Integer> topologicalStack = new Stack<Integer>();
		int currentNode = 0;
		
		while(!visitedAll(hasVisited)) {
			
			
			List<Integer> currentNodeDFS = DFS(currentNode);
			
			for (int j = currentNodeDFS.size() - 1; j > -1; j--) {
				if (!hasVisited[currentNodeDFS.get(j)]) {
					topologicalStack.push(currentNodeDFS.get(j));
					hasVisited[currentNodeDFS.get(j)] = true;
				}
			}
			
			currentNode++;
		}
		
		List<Integer> sortedList = new ArrayList<Integer>();
		while (!topologicalStack.isEmpty()) {
			sortedList.add(topologicalStack.pop());
		}
		
		return sortedList;
		
	}
	
	// just the dijkstra's algorithm
	public int[] shortestPath(int source) {
		
		int[] vertices = new int[size];
		int[] distances = new int[size];
		int[] prev = new int[size];
		List<Integer[]> edges = new ArrayList<Integer[]>();
		
		// assembling a list of all edges
		for (int a = 0; a < size; a++) {
			LinkedList<Integer[]> edgesOfA = list[a];
			for (int b = 0; b < edgesOfA.size(); b++) {
				Integer[] listToAdd = new Integer[3];
				listToAdd[0] = a;
				listToAdd[1] = edgesOfA.get(b)[0];
				listToAdd[2] = edgesOfA.get(b)[1];
				edges.add(listToAdd);
			}
		}
		
		for (int i = 0; i < edges.size(); i++) {
			System.out.print("[" + edges.get(i)[0] + ", " + edges.get(i)[1] + ", " + edges.get(i)[2] + "], ");
		}
		System.out.println();
		
		for (int i = 0; i < size; i++) {
			vertices[i] = i;
			distances[i] = 1000000000;
			prev[i] = -1;
		}
		
		distances[source] = 0;
		
		for (int k = 0; k < vertices.length - 1; k++) {
			// for each edge/pathway, get the minimum value of the distance to the destination
			// whether that be the distance of the destination from the hq, or the distance from the source
			// from the hq plus the weight of the edge that leads to the destination
			for (int l = 0; l < edges.size(); l++) {
				
				int distance_src = distances[edges.get(l)[0]];
				int distance_dest = distances[edges.get(l)[1]];
				int weight = edges.get(l)[2];
				
				// if the distance from the source plus the weight of the edge is less than the distance to the destination
				// then update the value
				if (distance_src + weight < distance_dest) {
					
					// update the distances, and then update the predecessor
					distances[edges.get(l)[1]] = distance_src + weight;
				}
			}
			
		}
		
		return distances;
		
		
	}
	
	public boolean isStronglyConnected() {
		
		for (int i = 0; i < size; i++) {
			if (DFS(i).size() != size) {
				return false;
			}
		}
		
		return true;
	}
	
	
	// Exercise 4 is just BFS again
	
	public String toString() {
		String returnString = "";
		for (int i = 0; i < size; i++) {
			returnString += (i + ": ") ;
			for (int j = 0; j < list[i].size(); j++) {
				returnString += ("["+list[i].get(j)[0] + ", "+list[i].get(j)[1]+"]"+", ") ;
			}
			returnString += "\n";
		}
		
		return returnString;
	}

}
