package Section4;

public class EventRobot {
/**
* Calculates minimum required charge for robots.
*
* - 1 <= pathways.length < 1000
* - pathways[i].length == 3
* - pathways[i] = [x, y, c] - where 1 <= x,y <= n, -1000 <= c <= 1000
* - n (number of buildings) >= 1
* - 1 <= headquarters <= n
* Pairs of (x,y) in pathways are unique. (i.e., no multiple edges.)
*/
	public int minimumCharge(int[][] pathways, int n, int headquarters) {
		// Implement this method
		// listing out all of the vertices
		int[] vertices = new int[n];
		int[] distances = new int[n];
		int[] predecessors = new int[n];
		
		for (int i = 1; i <= n; i++) {
			vertices[i - 1] = i;
		}
		
		// now comes the implementation of the bellman ford algorithm
		// initializing the graph
		for (int vertex: vertices) {
			distances[vertex - 1] = 1001;
			predecessors[vertex - 1] = -1;
		}
		
		distances[headquarters - 1] = 0;
		
		// checking the distances for each vertex
		for (int k = 0; k < vertices.length - 1; k++) {
			for (int l = 0; l < pathways.length; l++) {
				if (distances[pathways[l][0] - 1] + pathways[l][2] < distances[pathways[l][1] - 1]) {
					 distances[pathways[l][1] - 1]  = distances[pathways[l][0] - 1] + pathways[l][2];
					 predecessors[pathways[l][1] - 1] = distances[pathways[l][0] - 1];
				}
			}
		}
		
		// checking for negative weight cycles
		for (int m = 0; m < pathways.length; m++) {
			if (distances[pathways[m][0] - 1] + pathways[m][2] < distances[pathways[m][1] - 1]) {
				predecessors[pathways[m][1] - 1] = distances[pathways[m][0] - 1];
				
				boolean[] nodesVisited = new boolean[n];
				nodesVisited[pathways[m][1] - 1] = true;
				int immPred = pathways[m][0] - 1;
				while (nodesVisited[immPred]) {
					nodesVisited[immPred] = true;
					immPred = predecessors[immPred];
				}
				
				// ncycle := u
				vertices[pathways[m][1] - 1] = predecessors[pathways[m][0] -1];
				while (vertices[pathways[m][1] - 1] != predecessors[pathways[m][0] -1]) {
					//ncycle := concatenate([v], ncycle)
					vertices[pathways[m][1] - 1]  = predecessors[vertices[pathways[m][1] - 1]];
				}
				
				// error "graph contains a negative weight cycle, ncycle"
				
			}
		}
		
		// checking for the maximum distance in the distance array
		int maxDistance = -1000;
		for (int distance: distances) {
			if (maxDistance < distance) {
				maxDistance = distance;
			}
			
		}
		
		return maxDistance;
	}
	
	public static void main() {
		
		int[][] testPaths1 = {{1, 2, 4}};
		int n1 = 2;
		int h1 = 1;
		
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