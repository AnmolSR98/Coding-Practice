// Anmol Ratol 30231177
// A java file for the parkingLot class, which organizes car parking spots using a hash table
package Section2;

import java.util.LinkedList;

public class ParkingLot  {
	
	// the actual array of linked lists of cars
	private LinkedList[] parkingLotArray;
	
	// the size of the parking lot
	private int listLength;
	
	// nested class for car
	class Car{
		// basic attributes of the car
		String licencePlate;
		String parkingSpot;
		
		// a string method for cleaner printing
		@Override
		public String toString() {
			return licencePlate + ":" + parkingSpot;
		}
	}
	
	// constructor for the parking lot, requires lotSize as an argument, and then fills parkingLotArray with that many empty linkedLists
	public ParkingLot(int lotSize) {
		listLength = lotSize;
		parkingLotArray = new LinkedList[listLength];
		for (int i = 0; i < listLength; i++) {
			parkingLotArray[i] = new LinkedList<>();
		}
	}
	
	// hash function, take the hashCode of the licence plate and mod it by listLength
	public int Hash(String licencePlate) {
		return licencePlate.hashCode() % listLength;
	}
	
	// search function
	public boolean Search(String licencePlate) {
		
		// first get the location using hash function
		LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
		
		// then cycle through the linked list and if the licencePlate is found, return true
		for (int i = 0; i < lotLocation.size(); i++) {

			if (((Car)lotLocation.get(i)).licencePlate.compareTo(licencePlate) == 0) {
				return true;
			}
		}
		
		// otherwise, return false
		return false;
	}
	
	// insert function
	public void Insert(String licencePlate, String parkingSpot) {
		
		// provided that the car is not in the lot already
		if (!Search(licencePlate)) {
			// create a new car and it to ParkingLot.the lot in its calculated hash location
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			Car carToAdd = new Car();
			carToAdd.licencePlate = licencePlate;
			carToAdd.parkingSpot = parkingSpot;
			lotLocation.add(carToAdd);
		}
		
		else {
			// otherwise find the car and update its parkingSpot data
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			
			for (int i = 0; i < lotLocation.size(); i++) {
				Car immCar = (Car)lotLocation.get(i);
				if (immCar.licencePlate.compareTo(licencePlate) == 0) {
					immCar.parkingSpot = parkingSpot;
				}
			}
		}
		
	}
	
	// retrieve function to get the parking spot of a car with this specific licence plate
	public String Retrieve(String licencePlate) throws Exception {
		
		// if it is in the lot
		if (Search(licencePlate)) {
			// find it and return its parking spot
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			
			for (int i = 0; i < lotLocation.size(); i++) {
				Car immCar = (Car)lotLocation.get(i);
				if  (immCar.licencePlate.compareTo(licencePlate) == 0)  {
					return immCar.parkingSpot;
				}
			}
			
		}
		
		// otherwise, raise an exception
		throw new Exception("Car is not in the table!");
	}
	
	public void Delete(String licencePlate) throws Exception {
		
		// if it is in the lot
		if (Search(licencePlate)) {
			
			// find it, and remove the element from the list
			LinkedList lotLocation = parkingLotArray[Hash(licencePlate)];
			
			for (int i = 0; i < lotLocation.size(); i++) {
				Car immCar = (ParkingLot.Car)lotLocation.get(i);
				if  (immCar.licencePlate.compareTo(licencePlate) == 0)  {
					lotLocation.remove(i);
				}
			}
		}
		
		// otherwise, raise an exception
		else {
			throw new Exception("Car is not in the table!");
		}
	}
	
	// a function to get the parking lot as a string 
	@Override
	public String toString() {
		String thisLevel = "";
		// incrementally building up the string with each linked list being put on its own line
		for (int i = 0; i < listLength; i++) {
			thisLevel += String.format("%d: ", i);
			LinkedList tmp = parkingLotArray[i];
			thisLevel += tmp + "\n";
		}
		return thisLevel;
	}
	
	
	
	
	

}
