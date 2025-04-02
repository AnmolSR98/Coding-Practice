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

        print(vertices)

        minDistVertex = -1
        minDist = math.inf

        for vertex in vertices:
            if dist[vertex] < minDist:
                minDist = dist[vertex]
                minDistVertex = vertex

        print(minDistVertex)
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

# shortest path algorithm STILL NEED TO MODIFY AGAIN
def breadthFirstSearch(adjMatrix, source, end):
    queue = []
    queue.append(source)
    exploredNodes = [source]
    pathLength = 0

    while len(queue) != 0:
        vertex = queue[0]
        queue.pop(0)
        if vertex == end:
            return pathLength

        # get a list of all the neighbouring nodes
        neighbours = []
        adjMatrix[vertex]
        for i in range(len(adjMatrix[vertex])):
            if adjMatrix[vertex][i] != 0:
                neighbours.append(i)

        for neighbour in neighbours:
            if neighbour not in exploredNodes:
                exploredNodes.append(neighbour)
                queue.append(neighbour)

    return []