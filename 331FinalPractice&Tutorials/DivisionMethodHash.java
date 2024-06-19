package hash;

import java.util.LinkedList;

public class DivisionMethodHash<T extends Comparable>{
	LinkedList[] list;
	
	
	public DivisionMethodHash(int size) {
		list = new LinkedList[size];
		
		for (int i = 0; i < size; i++) {
			list[i] = new LinkedList<T>();
		}
		
	}
	
	public int Hash(T data) {
		return (int) (data) % list.length;
	}
	
	public void add(T data) {
		
		list[Hash(data)].add(data);
	}
	
	public void remove(T data) {
		
		LinkedList location = list[Hash(data)];
		location.remove(data);
	}

}
