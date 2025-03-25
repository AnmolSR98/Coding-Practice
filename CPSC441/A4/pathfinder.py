provNums = {"BritishColumbia": 0,
            "Alberta": 1,
            "Saskwatchewan": 2,
            "Ontario": 3,
            "Quebec": 4,
            "NovaScotia" : 5,
            "NewfoundlandandLabrador": 6}

index = {"hops" : 2, 
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

def convertToAdjacencyMatrix(data, pathType):
    
    pathValIndex = index[pathType]

    # assembling an as of yet empty adjacency matrix
    adjMatrix = []
    for i in range(len(provNums.keys())):
        newRow = []
        for j in range(len(provNums.keys())):
            newRow.append(0)
        adjMatrix.append(newRow)

    for i in range(data):
        if 
            
    print(adjMatrix)
        

if __name__ == "__main__":

    data = getData("paths.txt")

    print(data)

    convertToAdjacencyMatrix(data, "hops")
