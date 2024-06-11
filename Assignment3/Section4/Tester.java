package Section4;

public class Tester {


	public static void main(String[] args) { 
		
		EventRobot testRobot = new EventRobot();
		
		int[][] testPaths1 = {{1, 2, 4}};
		int n1 = 2;
		int h1 = 1;
		
		testRobot.minimumCharge(testPaths1, n1, h1);
		
		int[][] testPaths2 = {{1, 2, 4}};
		int n2 = 2;
		int h2 = 2;
		
		
		int[][] testPaths3 = {{2, 1, 3}, {2, 3, 2}, {3, 4, 5}};
		int n3 = 4;
		int h3 = 2;
		
		
		int[][] testPaths4 = {{2, 1, 3}, {2, 3, 2}, {3, 4, -2}, {2, 4, 5}};
		int n4 = 4;
		int h4 = 2;
		
	}
	
}
