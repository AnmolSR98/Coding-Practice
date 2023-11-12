#Anmol Ratol 1587571, completing a program that would take a list of housing values and return some statistics and display it in a text based grid


# create a new grid that can be display from a list of values and dimensions
def create_grid(filename):
    
    # creating three values of the dimensions of the grid and the housing prices
    length = filename[0]
    width = filename[1]
    values = filename[2]
    
    # initializing a proper grid
    grid = []
    
    # filling that array with one empty array for each row
    for i in range(0, width):
        grid.append([])
        
    # filling each empty arraw with the housing values of that row
    for i in range(0, width):
        for j in range(0, length):
            grid[i].append(values[i*length + j])
        
    return grid


# creating essentially a fancy print function
def display_grid(grid):
    
    display_grid = []
    
    # this nested for loop creates a string for each row
    for i in range(len(grid)):
        
        display_grid.append("|")
        
        for j in range(len(grid[i])):
            
            display_grid[i] = display_grid[i] + " " + str(grid[i][j]) + " |"
            
        print(display_grid[i])
            

# finding adjacent properties function
def find_neighbours(row_index, col_index, grid):
    
    # assemble a potential neighbour array, assuming it has 8 neighbours
    potential = []
    # assemble an array of real neighbours
    neighbours= []
    
    # assuming that (1,1) would refer to the top left corner of the grid
    row_index = row_index -1
    col_index = col_index -1
    
    # assembling an array of the potential neighbour indexes
    for i in [row_index -1, row_index, row_index + 1]:
        for j in [col_index - 1, col_index, col_index + 1]:
            if not [i, j] == [row_index, col_index]:
                potential.append([i, j])
        
    # go through a list of all of the coordinates and add the ones that are already in the potential neighbours list
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if [i, j] in potential:
                neighbours.append(grid[i][j])
                
    return neighbours


# interpolating what the price of a 0 value plot should be 
def fill_gaps(grid):
    
    # creating a nested for loop to find the values equal to 0
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            
            # if a value is 0, then find the average value of the neighbours and then fill that 0 in with that value, rounding it the nearest whole number
            if grid[i][j] == 0:
                grid[i][j] = round(sum(find_neighbours(i+1, j+1, grid))/len(find_neighbours(i+1, j+1, grid)))
                
    return grid
    

# find the maximum value in a grid of housing prices
def find_max(grid):

    maxes = []
    
    # find the value of the maxes in each row
    for i in range(len(grid)):
        maxes.append(max(grid[i]))
    
    # return the maximum value of the maxes of each row
    return max(maxes)


# find the average of all values in the grid
def find_average(grid):
    
    average = 0 
    
    # getting the value of the average of each row 
    for i in range(len(grid)):
        average = average + (sum(grid[i])/len(grid[i]))
    
    # dividing the average by the number of rows and 
    average = round(average/len(grid))
    
    return average
           

# the beloved main function
def main():
    
    # defining the filepath to use for the grid
    filepath  = "data_1.txt"
    
    # opening up that file, reading the lines, and making into an array of strings
    a = open(filepath, mode = "r")
    raw_array = a.readlines()
    a.close()
        
    # creating an array of integers from the raw string array
    filter_array = [int(raw_array[0]), int(raw_array[1]), []]    
    
    # converting the array of strings into the array of integers 
    for i in range(2, len(raw_array)):
        filter_array[2].append(int(raw_array[i]))
        
    # creating a proper grid array, good_array
    good_array = create_grid(filter_array)
    
    # display the grid
    print("This is our grid:")
    display_grid(good_array)
    
    # fill in any potential gaps
    fill_gaps(good_array)
    
    # display the updated array
    print("")
    print("This is our newly calculated grid:")
    display_grid(good_array)
    
    # display some interesting stats, such as average and maximum of the filled in grid
    print("")
    print("STATS")
    
    print("Average housing price in this area is:", find_average(good_array))

    print("Maximum housing price in this area is:", find_max(good_array))

main()