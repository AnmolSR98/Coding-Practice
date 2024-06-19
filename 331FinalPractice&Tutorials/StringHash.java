package hash;

import java.util.LinkedList;

public abstract class StringHash<T extends Comparable>{
	LinkedList[] list;
	int size = 100;
	
	
	public StringHash() {
		LinkedList[] list = new LinkedList[size];
		
		for (int i = 0; i < size; i++) {
			list[i] = new LinkedList<T>();
		}
		
	}
	
	public int Hash(String data) {
		return (int) data.hashCode() % size;
	}
	
	public void add(String data) {
		
		list[Hash(data)].add(data);
	}
	
	public void remove(String data) {
		
		LinkedList location = list[Hash(data)];
		location.remove(data);
	}

}
