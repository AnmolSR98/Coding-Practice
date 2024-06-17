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
	
	public List<Integer> DFS(int startNode) {
		
		List<Integer> vertices = new ArrayList<Integer>();
		Stack<Integer> verticesStack = new Stack<Integer>();
	
		
		verticesStack.push(startNode);
		
		while (!verticesStack.isEmpty()) {
			
			int currentVertex = verticesStack.pop();
			if (!vertices.contains(currentVertex)) {
				vertices.add(currentVertex);
			}
			LinkedList<Integer[]> currentList = list[currentVertex]; 
			
			for (int i = 0; i < currentList.size(); i++) {
				int node = currentList.get(i)[0];
				verticesStack.push(node);
			}
		
		}

		return vertices;
	}
	
	public List<Integer> BFS(int startNode) {
		
		List<Integer> vertices = new ArrayList<Integer>();
		LinkedQueue verticesQueue = new LinkedQueue();
	
		
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
		return false;
	}
	
	public void TopologicalSort() {
		
	}
	
	public int[] shortestPath() {
		return new int[5];
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
