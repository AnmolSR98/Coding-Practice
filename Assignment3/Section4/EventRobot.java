package Section4;

public class EventRobot {
	
	private int getVertex(int n) {
		return n-1;
	}
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
		// filling the predecessors array with -1s and the distances with maxes 
		for (int vertex: vertices) {
			distances[getVertex(vertex)] = 1000000;
			predecessors[getVertex(vertex)] = -1;
		}
		
		// set the distances from the source to the source as 0, since no edges need be traversed
		distances[getVertex(headquarters)] = 0;
		
		// repeating the following process for each vertex
		for (int k = 0; k < vertices.length - 1; k++) {
			// for each edge/pathway, get the minimum value of the distance to the destination
			// whether that be the distance of the destination from the hq, or the distance from the source
			// from the hq plus the weight of the edge that leads to the destination
			for (int l = 0; l < pathways.length; l++) {
				
				int distance_src = distances[getVertex(pathways[l][0])];
				int distance_dest = distances[getVertex(pathways[l][1])];
				int weight = pathways[l][2];
				
				// if the distance from the source plus the weight of the edge is less than the distance to the destination
				// then update the value
				if (distance_src + weight < distance_dest) {
					
					// update the distances, and then update the predecessor
					distances[getVertex(pathways[l][1])] = distance_src + weight;
					predecessors[getVertex(pathways[l][1])] = vertices[getVertex(pathways[l][0])];
				}
			}
		}
		
		// Need to insert code to filter out negative cycles here, then finished
		
		for (int i = 0; i< distances.length; i++) {
			System.out.print(distances[i] + ",");
		}
		
		System.out.println();
		
		for (int i = 0; i< distances.length; i++) {
			System.out.print(predecessors[i] + ",");
		}
		
		System.out.println();

		// checking for the maximum distance in the distance array
		int maxDistance = -10000000;
		for (int distance: distances) {
			if (maxDistance < distance){
				maxDistance = distance;
			}
			
		}
		
		return maxDistance;
	}
	
}