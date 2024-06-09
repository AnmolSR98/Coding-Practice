// Anmol Ratol 30231177
// A java file for the parkingLotManager class, essentially a driver for the parkingLot class
package Section2;


public class ParkingLotManager {
	
	// main method
	public static void main(String[] args) {
		
		// instantiating the testLot, being size 20 
		ParkingLot testLot = new ParkingLot(20);
		
		// 1. Adding the various cars using the park function to quickly split the strings  
		park(testLot, "AB1234:1-23");
		park(testLot, "CD5678:2-45");
		park(testLot, "EF9012:3-12");
		park(testLot, "GH3456:1-34");
		
		// 2. Printing the initial state of the lot
		System.out.println(testLot);
		
		// 3. Inserting a car that was already there, which should do nothing more than update its lot number
		testLot.Insert("AB1234", "2-50");
		
		// 4. Search for the value of AB1234
		testLot.Search("AB1234");
		
		// 5. Trying out the retrieve function for CD5678, expected output should be 2-45 with no exceptions raised
		try {
			System.out.println(testLot.Retrieve("CD5678"));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 6. Deleting CD5678, no exceptions should be raised
		try {
			testLot.Delete("CD5678");
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 7. Attempting to delete it a second time, an exception should be raised and then printed
		try {
			testLot.Delete("CD5678");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 8. Attempting to retrieve CD5678, an exception should be raised and then printed
		try {
			testLot.Retrieve("CD5678");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println(e);
		}
		
		// 9. Print the final status of the lot
		System.out.println(testLot);
		
		
	}
	
	// quick function to insert the cars that splits the strings for me
	public static void park(ParkingLot lot, String licenceAndLot) {
		lot.Insert(licenceAndLot.split(":")[0], licenceAndLot.split(":")[1]);
	}
	
}
