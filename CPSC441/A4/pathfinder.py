# importing both search and visual, search is for dijsktra + bellman ford, visual is for creating graphs with networkx
import search
import visual

# dicitonaries for the indexes used throughout the code, along with the provinces
provNums = {"BritishColumbia": 0,
            "Alberta": 1,
            "Saskatchewan": 2,
            "Ontario": 3,
            "Ottawa": 4,
            "Quebec": 5,
            "NovaScotia" : 6,
            "NewfoundlandandLabrador": 7}

index = {  "sour" : 0,
           "dest" : 1,
           "hops" : 2, 
           "dist" : 3, 
           "time" : 4, 
           "deme" : 5}

def getData(path):

    # opening and reading the file, then closing it
    file = open(path, 'r')
    fileLines = file.readlines()
    file.close()
    data = []

    # processing each line into its own list in the data array
    for line in fileLines:
        data.append(line.split())

    return data

# converting the input data into adjacency matrixes depending on input
def convertToAdjacencyMatrix(data, pathType):
    
    pathValIndex = index[pathType]

    # assembling an as of yet empty adjacency matrix
    adjMatrix = []
    for i in range(len(provNums.keys())):
        newRow = []
        for j in range(len(provNums.keys())):
            newRow.append(0)
        adjMatrix.append(newRow)

    # for each line, update the data if no path exists there or if this path is cheaper than the other one
    for line in data:
        sour = provNums[ line[index["sour"]] ] # plug the source into the provNums dictionary and do the same for the destination
        dest = provNums[ line[index["dest"]] ]

        if adjMatrix[sour][dest] == 0:
            adjMatrix[sour][dest] = int( line[pathValIndex] )
            
        else:
            if int( line[pathValIndex] ) < adjMatrix[sour][dest]:
                adjMatrix[sour][dest] = int( line[pathValIndex] )

    # making the matrix symmetric
    for i in range(len(provNums.keys())):
        for j in range(len(provNums.keys())):
            if adjMatrix[i][j] == 0:
                adjMatrix[i][j] = adjMatrix[j][i]

            elif adjMatrix[i][j] < adjMatrix[j][i]:
                adjMatrix[i][j] = adjMatrix[j][i]

    return adjMatrix

# converts the raw input of numbers into the appropriate province 3 letter strins
def convertPathToProvinces(path):

    newPath = []
    for prov in path:
        newPath.append(list(provNums.keys())[prov][0:3].upper())

    return newPath

def main():

    # get the data as an input
    data = getData("paths.txt")

    # getting all of the various adjacency matrixes by each metric
    hopsMatrix = convertToAdjacencyMatrix(data, "hops")
    distMatrix = convertToAdjacencyMatrix(data, "dist")
    timeMatrix = convertToAdjacencyMatrix(data, "time")
    demeMatrix = convertToAdjacencyMatrix(data, "deme")

    # getting the shortest hops between provinces 
    f = open("hops.txt", mode = 'w')
    for prov in provNums.values():
        dest = provNums["Ottawa"]
        provHops, provPrev = search.bellmanFord(hopsMatrix, prov)
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, dest))
        f.write(f"{list(provNums.keys())[prov][0:3].upper()} : {provHops[dest]} : {provPath}\n")

    f.close()

    # getting the shortest dist between provinces 
    f = open("dist.txt", mode = 'w')
    for prov in provNums.values():
        dest = provNums["Ottawa"]
        provDist, provPrev = search.dijkstra(distMatrix, prov)
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, dest))
        f.write(f"{list(provNums.keys())[prov][0:3].upper()} : {provDist[dest]} : {provPath}\n")
    f.close()

    # getting the shortest time between provinces 
    f = open("time.txt", mode = 'w')
    for prov in provNums.values():
        dest = provNums["Ottawa"]
        provTime, provPrev = search.bellmanFord(timeMatrix, prov)
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, dest))
        f.write(f"{list(provNums.keys())[prov][0:3].upper()} : {provTime[dest]} : {provPath}\n")
    f.close()

    # getting the shortest dementors between provinces 
    f = open("deme.txt", mode = 'w')
    for prov in provNums.values():
        dest = provNums["Ottawa"]
        provDeme, provPrev = search.dijkstra(demeMatrix, prov)
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, dest))
        f.write(f"{list(provNums.keys())[prov][0:3].upper()} : {provDeme[dest]} : {provPath}\n")
    f.close()

    # now assembling the graphs
    for prov in provNums.values():
        paths = []
        # adding the hopsMatrix
        provPrev = search.dijkstra(hopsMatrix, prov)[1]
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, provNums["Ottawa"]))
        paths.append(provPath)
        # adding the distMatrix
        provPrev = search.dijkstra(distMatrix, prov)[1]
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, provNums["Ottawa"]))
        paths.append(provPath)
        # adding the timeMatrix
        provPrev = search.dijkstra(timeMatrix, prov)[1]
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, provNums["Ottawa"]))
        paths.append(provPath)
        # adding the demeMatrix
        provPrev = search.dijkstra(demeMatrix, prov)[1]
        provPath = convertPathToProvinces(search.getPath(provPrev, prov, provNums["Ottawa"]))
        paths.append(provPath)
        visual.getNodeGraph(paths, list(provNums.keys())[prov], list(provNums.keys())[prov][0:3].upper())
        

if __name__ == "__main__":
    main()
