package Section3;

import java.util.LinkedList;

public class ParkingLot  {
	
	private LinkedList[] parkingLotArray;
	private int size;
	private int arrayLength = 20;
	
	class Car{
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
			parkingLotArray[i] = new LinkedList<Car>();
		}
	}
	
	public int Hash(String licencePlate) {
		return licencePlate.hashCode() % arrayLength;
	}
	
	
	public boolean Search(String licencePlate) {
		
		LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
		
		for (int i = 0; i < lotLocation.size(); i++) {
			Car immCar = (ParkingLot.Car)lotLocation.get(i);
			if (immCar.licencePlate.compareTo(licencePlate) == 0) {
				return true;
			}
		}
		
		return false;
	}
	
	public void Insert(String licencePlate, String parkingSpot) {
		
		if (!Search(licencePlate)) {
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			Car carToAdd = new Car();
			carToAdd.licencePlate = licencePlate;
			carToAdd.parkingSpot = parkingSpot;
			lotLocation.add(carToAdd);
		}
		
		else {
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			
			for (int i = 0; i < lotLocation.size(); i++) {
				Car immCar = (ParkingLot.Car)lotLocation.get(i);
				if (immCar.licencePlate.compareTo(licencePlate) == 0) {
					immCar.parkingSpot = parkingSpot;
				}
			}
		}
		
	}
	
	public String Retrieve(String licencePlate) {
		
		if (Search(licencePlate)) {
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			
			for (int i = 0; i < lotLocation.size(); i++) {
				Car immCar = (ParkingLot.Car)lotLocation.get(i);
				if  (immCar.licencePlate.compareTo(licencePlate) == 0)  {
					return immCar.parkingSpot;
				}
			}
			
		}
		
		System.out.println("Car is not in the table!");
	
		return null;
	}
	
	public void Delete(String licencePlate) {
		
		if (Search(licencePlate)) {
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			
			for (int i = 0; i < lotLocation.size(); i++) {
				Car immCar = (ParkingLot.Car)lotLocation.get(i);
				if  (immCar.licencePlate.compareTo(licencePlate) == 0)  {
					lotLocation.remove(i);
				}
			}
		}
		
		else {
			System.out.println("Car is not in the table!");
		}
	}
	
	@Override
	public String toString() {
		String thisLevel = "";
		for (int i = 0; i < arrayLength; i++) {
			thisLevel += String.format("%d: ", i);
			LinkedList tmp = parkingLotArray[i];
			thisLevel += tmp + "\n";
		}
		return thisLevel;
	}
	
	
	
	
	

}
