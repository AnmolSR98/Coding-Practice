package sort;

public class QuickSortPractice {
	
	private class Movie {
		String name;
		int releaseYear;
		
		public Movie(String setName, int setReleaseYear) {
			name = setName;
			releaseYear = setReleaseYear;
		}
	}
	
	private class Student{
		String name;
		int GPA;
		
		public Student(String setName, int setGPA) {
			name = setName;
			GPA = setGPA;
		}
	}
	
	
	// develop using hoares partition
	private void QuickSort(Movie[] movieArray, int low, int high) {
		
	}
	
	private int moviePartition(Movie[] inArray, int low, int high) {
		return -1;
	}
	
	// develop using lomuto partition
	private void QuickSort(Student[] studentArray, int low, int high) {
		
		if (low < high) {
			int pi = studentPartition(studentArray, low, high);
			QuickSort(studentArray, low, pi - 1);
			QuickSort(studentArray, pi + 1, high);
		}
		
	}
	
	private int studentPartition(Student[] inArray, int low, int high) {
		Student pivot = inArray[high];
		int i = low - 1;
		
		for (int j = low; j < high - 1; j++) {
			if (inArray[j].GPA <= pivot.GPA) {
				Student tmp = pivot;
				pivot = inArray[j];
				inArray[j] = tmp;
				i++;
			}
			
			else if ((inArray[j].GPA == pivot.GPA) && (inArray[j].name.compareTo(pivot.name) < 0)) {
				Student tmp = pivot;
				pivot = inArray[j];
				inArray[j] = tmp;
				i++;
			}
		}
		
		Student tmp = inArray[high];
		inArray[high] = inArray[i + 1];
		inArray[i + 1] = tmp;
		
		return (i + 1);
	}
	
	public static void main(String[] args) {
		
	}
}
