package sort;

public class QuickSortPractice {
	
	private static class Student{
		String name;
		double GPA;
		
		public Student(String setName, double setGPA) {
			name = setName;
			GPA = setGPA;
		}
		
		@Override
		public String toString() {
			return name+": "+GPA;
		}
	}
	
	// develop using lomuto partition
	private static void QuickSort(Student[] studentArray, int low, int high) {
		
		
		if (low < high) {
			int pi = studentPartition(studentArray, low, high);
			QuickSort(studentArray, low, pi - 1);
			QuickSort(studentArray, pi + 1, high);
		}
	}
	
	// lomuto partition implementation
	private static int studentPartition(Student[] inArray, int low, int high) {
		
		Student pivot = inArray[high];
		int i = low - 1;
		
		for (int j = low; j < high; j++) {
			if (inArray[j].GPA < pivot.GPA) {
				i++;
				Student tmp = inArray[i];
				inArray[i] = inArray[j];
				inArray[j] = tmp;
			}
			
			else if ((inArray[j].GPA == pivot.GPA) && (inArray[j].name.compareTo(pivot.name) < 0)){
				i++;
				Student tmp = inArray[i];
				inArray[i] = inArray[j];
				inArray[j] = tmp;
			}
		}
		
		Student tmp = inArray[high];
		inArray[high] = inArray[i + 1];
		inArray[i + 1] = tmp;
		
		return (i + 1);
	}
	
	public static void main(String[] args) {
		
		Student[] testArray = new Student[5];
		testArray[0] = new Student("Ashley", 3.9);
		testArray[1] = new Student("Robert", 3.9);
		testArray[2] = new Student("James", 3.2);
		testArray[3] = new Student("Jewgeni", 1.9);
		testArray[4] = new Student("Dr. Dre", 0.9);

		QuickSort(testArray, 0, 4);
		
		for (Student stdnt: testArray) {
			System.out.print(stdnt + ", ");
		}
		System.out.println();
		
	}
}
