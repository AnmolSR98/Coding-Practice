package mygraph;

import java.util.LinkedList;

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
	
	public void getSpanningTree() {
		
	}
	
	public String toString() {
		String returnString = "";
		for (int i = 0; i < size; i++) {
			returnString += (i + ": ") ;
			for (int j = 0; j < list[i].size(); j++) {
				returnString += ("["+list[i].get(i)[0] + ", "+list[i].get(i)[1]+"]"+", ") ;
			}
			returnString += "\n";
		}
		
		return returnString;
	}

}
