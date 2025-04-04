# actual path finding functions
import math

# dijsktra algorithm
def dijkstra(adjMatrix, source):
    vertices, dist, prev = [] , [] , []

    # set up the vertices, dist, and prev arrays
    for i in range(len(adjMatrix[0])):
        prev.append(-1)
        dist.append(math.inf)
        vertices.append(i)
    dist[source] = 0

    # while all vertices have yet to be checked
    while len(vertices) != 0:

        # get the vertex with the min distance from the source
        minDistVertex = -1
        minDist = math.inf

        for vertex in vertices:
            if dist[vertex] < minDist:
                minDist = dist[vertex]
                minDistVertex = vertex

        vertices.remove(minDistVertex)

        # get all of its neighbours
        neighbours = []
        adjMatrix[minDistVertex]
        for i in range(len(adjMatrix[minDistVertex])):
            if adjMatrix[minDistVertex][i] != 0:
                neighbours.append(i)

        # check if the path from this node to the neighbour is the best so far, and update it if it is
        for neighbour in neighbours:
            alt = dist[minDistVertex] + adjMatrix[minDistVertex][neighbour]
            if alt < dist[neighbour]:
                dist[neighbour] = alt
                prev[neighbour] = minDistVertex

    # return the distances and previous arrays
    return dist, prev

def bellmanFord(adjMatrix, source):

    dist = [math.inf] * len(adjMatrix)
    prev = [-1] * len(adjMatrix)
    dist[source] = 0

    # check through n - 1 times (n = number of nodes)
    for i in range(len(adjMatrix) - 1):
        # for each node, check its neighbours and update if it is the best path found thus far
        for j in range(len(adjMatrix)):
            for k in range(len(adjMatrix[source])):
                if adjMatrix[j][k] != 0:
                    if dist[j] + adjMatrix[j][k] < dist[k]:
                        dist[k] = dist[j] + adjMatrix[j][k]
                        prev[k] = j

    # check for negative weight cycles
    for j in range(len(adjMatrix)):
        for k in range(len(adjMatrix[source])):
            # for each node, check through its edgees
            if adjMatrix[j][k] != 0:
                # if a negative cycle exists
                if dist[j] + adjMatrix[j][k] < dist[k]:
                        # mark it as the previous node 
                        prev[k] = j
                        # keeping track of visited nodes
                        visited = [False] * len(adjMatrix)
                        # mark the node itself as visited
                        visited[k] = True
                        # go through all the previous nodes
                        while not visited[j]:
                            visited[j] = True
                            j = prev[j]
                        # now add these to the negative cycle and return it
                        negativeCycle = [j]
                        k = prev[j]
                        while k != j:
                            negativeCycle = [k] + negativeCycle
                            k = prev[k]     
                        return negativeCycle

    return dist, prev

def getPath(prev, source, dest):
    # base case
    if source == dest:
        return [source]
    
    # otherwise, start at the destination
    path = []
    currentNode = dest
    # move continuously backwards using the prev array to update
    while currentNode != source:
        path = [currentNode] + path
        currentNode = prev[currentNode]

    # now add the source as the final addition and return
    path = [source] + path
    return path