package hash;

import java.util.LinkedList;

public class ProbingTable <T extends Comparable>{
	LinkedList[] list;
	int size;
	
	
	public ProbingTable(int size) {
		list = new LinkedList[size];
		this.size = size;
		for (int i = 0; i < size; i++) {
			list[i] = new LinkedList<T>();
		}
		
	}
	
	public int Hash(T data) {
		return (int) (data) % list.length;
	}
	
	public boolean add(T data) {
		
		int i = 0;
		int hash = 0;
		while (i < size) {
			hash = Hash(data) + (i % size);
			
			if ((list[i].size() == 0)) {
				list[i].add(data);
				return true;
			}
			
			else if (((Comparable) list[i].get(0)).compareTo("DEL") == 0) {
				list[i].add(data);
				return true;
			}
			i++;
		}
		
		return false;
		
	}
	
	public void remove(T data) {
		
		int i = 0;
		int hash = 0;
		while (i < size) {
			hash = Hash(data) + (i % size);
			
			if ((list[i].size() == 0)) {
				i++;
			}
			
			else if (((Comparable) list[i].get(0)).compareTo(data) == 0) {
				i = size + 1;
				list[i].remove(data);
			}
		}
		
	}
	
	public int search(T data) {
		
		int i = 0;
		int hash = 0;
		while (i < size) {
			hash = Hash(data) + (i % size);
			
			if ((list[i].size() == 0)) {
				i = size + 1;
			}
			
			else if (((Comparable) list[i].get(0)).compareTo(data) == 0) {
				i = size + 1;
				list[i].remove(data);
				return i;
			}
			
			else {
				i++;
			}
		}
		
		return -1;
	}
}
