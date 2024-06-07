package Section3;

import java.lang.reflect.Array;
import java.util.LinkedList;

public class ParkingLot <T extends Comparable> {
	
	private LinkedList[] parkingLotArray;
	private int size;
	private int arrayLength = 20;
	
	private class Car{
		String licencePlate;
		String parkingSpot;
		
		@Override
		public String toString() {
			return licencePlate + ":" + parkingSpot;
		}
	}
	
	public ParkingLot() {
		parkingLotArray = new LinkedList[arrayLength];
		for (int i = 0; i < arrayLength; i++) {
			parkingLotArray[i] = new LinkedList();
		}
	}
	
	public int Hash(String licencePlate) {
		return licencePlate.hashCode() % arrayLength;
	}
	
	
	public boolean Search(String licencePlate) {
		return false;
	}
	
	public void Insert(String licencePlate, String parkingSpot) {
		
	}
	
	public Car Retrieve(String licencePlate) {
		return null;
	}
	
	public void Delete(String licencePlate) {
		
	}
	
	public void ToString() {
		for (int i = 0; i < arrayLength; i++) {
			String thisLevel = String.format("%d: ", i);
			LinkedList tmp = parkingLotArray[i];
			thisLevel += tmp;
			System.out.println(thisLevel);
		}
	}
	
	
	
	
	

}
