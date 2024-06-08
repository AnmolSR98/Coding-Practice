package Section3;

public class ParkingLotManager {
	
	public static void main(String[] args) {
		
		ParkingLot testLot = new ParkingLot();
		
		// 1.
		park(testLot, "AB1234:1-23");
		park(testLot, "CD5678:2-45");
		park(testLot, "EF9012:3-12");
		park(testLot, "GH3456:1-34");
		
		// 2.
		System.out.println(testLot);
		
		// 3.
		testLot.Insert("AB1234", "2-50");
		
		// 4.
		testLot.Search("AB1234");
		
		// 5.
		System.out.println(testLot.Retrieve("CD5678"));
		
		// 6.
		testLot.Delete("CD5678");
		
		// 7.
		testLot.Delete("CD5678");
		
		// 8.
		testLot.Retrieve("CD5678");
		
		// 9.
		System.out.println(testLot);
		
		
	}
	
	public static void park(ParkingLot lot, String licenceAndLot) {
		lot.Insert(licenceAndLot.split(":")[0], licenceAndLot.split(":")[1]);
	}
	
}
