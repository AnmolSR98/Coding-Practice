# actual path finding functions
import math

# dijsktra algorithm
def dijkstra(adjMatrix, source):
    vertices, dist, prev = [] , [] , []

    for i in range(len(adjMatrix[0])):
        prev.append(-1)
        dist.append(math.inf)
        vertices.append(i)
    dist[source] = 0

    while len(vertices) != 0:

        minDistVertex = -1
        minDist = math.inf

        for vertex in vertices:
            if dist[vertex] < minDist:
                minDist = dist[vertex]
                minDistVertex = vertex

        vertices.remove(minDistVertex)

        # now getting the values for all the neighbours
        neighbours = []
        adjMatrix[minDistVertex]
        for i in range(len(adjMatrix[minDistVertex])):
            if adjMatrix[minDistVertex][i] != 0:
                neighbours.append(i)

        for neighbour in neighbours:
            alt = dist[minDistVertex] + adjMatrix[minDistVertex][neighbour]
            if alt < dist[neighbour]:
                dist[neighbour] = alt
                prev[neighbour] = minDistVertex

    return dist, prev

def bellmanFord(adjMatrix, source):

    dist = [math.inf] * len(adjMatrix)
    prev = [-1] * len(adjMatrix)
    dist[source] = 0

    # check through all edges FIX
    for i in range(len(adjMatrix) - 1):
        for j in range(len(adjMatrix)):
            for k in range(len(adjMatrix[source])):
                if adjMatrix[j][k] != 0:
                    if dist[j] + adjMatrix[j][k] < dist[k]:
                        dist[k] = dist[j] + adjMatrix[j][k]
                        prev[k] = j

    # check for negative weight cycles
    for j in range(len(adjMatrix)):
        for k in range(len(adjMatrix[source])):
            if adjMatrix[j][k] != 0:
                if dist[j] + adjMatrix[j][k] < dist[k]:
                        prev[k] = j
                        # keeping track of visited nodes
                        visited = [False] * len(adjMatrix)
                        visited[k] = True
                        while not visited[j]:
                            visited[j] = True
                            j = prev[j]
                        negativeCycle = [j]
                        k = prev[j]
                        while k != j:
                            negativeCycle = [k] + negativeCycle
                            k = prev[k]        

    return dist, prev

def getPath(prev, source, dest):
    if source == dest:
        return [source]
    
    path = []
    currentNode = dest
    while currentNode != source:
        path = [currentNode] + path
        currentNode = prev[currentNode]

    path = [source] + path

    return path