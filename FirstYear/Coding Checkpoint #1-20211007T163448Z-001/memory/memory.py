# Anmol Ratol, 1587571
# Project 3, creating memory in pygame, a game that basically the equivalent of the memory match card game where you have tiles flipped down, you flip one up
# and try to find its complement, if successful, keep the cards up, else flip them both back down, objective is to match all the cards

import random
import pygame as pg


def main():

    # setting up the game to run, creating the variables for the surface and setting caption, calling the play function and then getting the to quit after play ends
    pg.init()
    pg.display.set_caption("Memory")
    rgt_bound = 500
    bot_bound = 400
    game = Game((rgt_bound, bot_bound))
    game.play()
    pg.quit()

   
class Game:
    
    # initialize the values needed to create the game
    def __init__(self, bounds):
        
        self.surface = pg.display.set_mode(bounds)  
        self.clock = pg.time.Clock()
        self.FPS = 60
        self.score = 0
        self.frame_counter = 0
        self.clicked_images = 0
        
        # setting up the default cover image and scaling it
        self.image_raw = pg.image.load(r'image0.bmp')
        self.cover_image = pg.transform.scale(self.image_raw, (100, 100))
        
        # the actual image to use for the covering
        self.default = Tile([100, 100], [-1, -1], self.cover_image, self.surface, self.cover_image)
        
        # the two tiles the player can select at any moment
        self.tile = self.default
        self.tile2 = self.default  
        
        # non interactive tiles
        self.completed_tiles = []
        
        # the size of the tiles
        self.tile_dimensions = (100, 100)
        
        # setting up images to use, replace later and make these attributes of the game class
        self.raw_image1 = pg.image.load(r'image1.bmp')
        self.raw_image2 = pg.image.load(r'image2.bmp')
        self.raw_image3 = pg.image.load(r'image3.bmp')
        self.raw_image4 = pg.image.load(r'image4.bmp')
        self.raw_image5 = pg.image.load(r'image5.bmp')
        self.raw_image6 = pg.image.load(r'image6.bmp')
        self.raw_image7 = pg.image.load(r'image7.bmp')
        self.raw_image8 = pg.image.load(r'image8.bmp')                     
        
        # scaling them properly
        self.image1 = pg.transform.scale(self.raw_image1, (100, 100))
        self.image2 = pg.transform.scale(self.raw_image2, (100, 100))
        self.image3 = pg.transform.scale(self.raw_image3, (100, 100))
        self.image4 = pg.transform.scale(self.raw_image4, (100, 100))  
        self.image5 = pg.transform.scale(self.raw_image5, (100, 100))
        self.image6 = pg.transform.scale(self.raw_image6, (100, 100))  
        self.image7 = pg.transform.scale(self.raw_image7, (100, 100))
        self.image8 = pg.transform.scale(self.raw_image8, (100, 100))          
        
        # making them into a proper image array
        self.images = [self.image1, self.image2, self.image3, self.image4, self.image5, self.image6, self.image7, self.image8]
        
        # creating a variable for delaying if the player selects two tiles that dont match
        self.delay = False
    
    def play(self):
        
        # dimensions of the grid, x times y must be even for this to work, up to max of 4 by 4
        self.x = 4
        self.y = 4
        
        # generate the unsolved tiles and the covering
        self.unsolved_tiles = self.tile_generate(self.x, self.y, self.tile_dimensions, self.surface)
        
        # set the loop to run
        self.play = True  
        
        while self.play:           
            
            # handle the events of the frame
            self.handle_events()            
            
            # update the events of the frame
            self.update()  
            
            # draw the frame
            self.draw()
            
            # move along at 60 frames a second, can also be used to speed up the game as it does calculations frame by frame
            self.clock.tick(self.FPS)           
        
    # a tile generating function   
    def tile_generate(self, a, b, dimensions, surface):
        
        images = []
        tiles = []
        
        # double up the images to ensure each tile has a compliment
        for i in range(2):
            for j in range(int(a*b*0.5)):
                images.append(self.images[j])
                
        random.shuffle(images)
        
        # generate an array of tiles, a by b
        for i in range(a):
            for j in range(b):
                tiles.append(Tile(dimensions, [i, j], images[len(images)-1], surface, self.cover_image))
                images.pop(len(images)-1)
        
        self.interactive_space = [100*a, 100*b]               
         
        return tiles    
    
      
    def update(self):
        
        # increase by one every frame
        self.frame_counter += 1
        
        # every 60 frames is a second
        if self.frame_counter % self.FPS == 0:
            self.score_counter()
                        
    def handle_events(self):
        
        events = pg.event.get()
        pos = 0
        
        for event in events:
            
            if event.type == pg.MOUSEBUTTONUP:
                
                # if player clicks on frame, find where they clicked 
                pos = pg.mouse.get_pos()
                
                # checking the player has clicked somewhere in the interactive space, if so, add 1
                if self.good_click(pos):
                    self.clicked_images += 1
                
            # decided to smush the decide continue function here
            self.decide_continue(event)           
        
        # ie. if the mouse has been clicked
        if pos != 0:
            
            # rounding the mouse coordinates in term of the coordinates generated for the tile array
            new_pos = [int(pos[0]/100), int(pos[1]/100)]
            
            # if the player has clicked on one image, use first click function
            if self.clicked_images == 1:
                
                self.first_click(new_pos)
            
            # otherwise assume a second click and use second click function    
            else:
                
                self.second_click(new_pos)
                
    # for the first good click                   
    def first_click(self, pos):
        
        #check which tile you have clicked
        for tile in self.unsolved_tiles:
            if tile.same_position(pos):
                self.tile = tile
                #flip over the tile
                tile.flip()
    
    # for the second good click
    def second_click(self, pos):
        for tile in self.unsolved_tiles:
            # check which tile you have clicked
            if tile.same_position(pos):
                self.tile2 = tile
                
                #flip the second tile over
                tile.flip()
                
                # if the player has clicked a tile that is a good match (same image, different location), move them into completed tiles, and remove them from the unsolved tiles, 
                # reset clicked images to zero
                if self.tile2.good_match(self.tile):
                    
                    for comp_tile in self.unsolved_tiles:
                        if comp_tile.same_position(self.tile2):
                            tile.is_matched(comp_tile)
                    
                    self.unsolved_tiles.remove(self.tile)
                    self.unsolved_tiles.remove(self.tile2)
                    self.completed_tiles.append(self.tile)
                    self.completed_tiles.append(self.tile2)
                    self.clicked_images = 0
                
                # if the player clicks on the same tile twice, don't count it as a proper second click and keep that tile visible
                elif self.tile2.check_same(self.tile): 
                    
                    tile.flip()
                    self.clicked_images = 1
                
                # if not a good match and two different tiles, draw the tiles, wait for a bit, and set self.clicked_images to 0   
                else:
                    
                    self.delay = True
                    self.clicked_images = 0    
                
    # check if the player has clicked out of the windows            
    def decide_continue(self, event):
        if event.type == pg.QUIT:
            self.play = False     
            
    # creating a draw function
    def draw(self):
        
        # the screen drawing function, starting with filling it black, drawing the tile covering, the tiles the player has selected, the ones that have been matched, 
        # update the frame counter and score, draw the text, and then display the frame
        self.surface.fill("black")
        
        for tile in self.completed_tiles:
            tile.draw()
        
        for tile in self.unsolved_tiles:
            tile.draw()
            
        font = pg.font.Font(None, 74)
        text = font.render(str(self.score), True, (255, 255, 255))
        self.surface.blit(text, (500-font.size("000")[0], 0))             
        pg.display.flip() 
        
        # delay the game to linger on this frame if the player didnt pick a match, then reset the tiles and the delay variable, plus the players picked tiles
        if self.delay:
            pg.time.delay(500)
            self.delay = False
            
            for tile in self.unsolved_tiles:
                if tile.check_same(self.tile) or tile.check_same(self.tile2):
                    tile.flip()
                    
            self.tile = self.default
            self.tile2 = self.default        
        
    # if the player hasnt solved all the tiles, keep the score moving up
    def score_counter(self):
        if len(self.completed_tiles) < self.x*self.y:
            self.score += 1
            
    # check that player has clicked in the proper space (the interactive space)
    def good_click(self, pos):
        return (pos[0] <= self.interactive_space[0] and pos[1] <= self.interactive_space[1])




# the class Tile for the tiles to be matched
class Tile:
    
    # initialize the tile's image, position, and surface to be drawn on
    def __init__(self, dimensions, start_position, image, surface, cover):
        
        self.image = image
        self.start = start_position
        self.surface = surface
        self.cover = cover
        self.flipped = False
        
    # draw the image at it's starting position
    def draw(self):
        if self.flipped:
            self.surface.blit(self.image, (self.start[0]*100, self.start[1]*100))
        else:
            self.surface.blit(self.cover, (self.start[0]*100, self.start[1]*100))
    
    # if the tiles are the same image, with different starts, they must be matching, return true
    def good_match(self, other_tile):
        return (self.image == other_tile.image and self.start != other_tile.start)
    
    # checking that the copordinates match the start position of the tile
    def same_position(self, pos):
        return (self.start == pos)
    
    # checking if they are the same tile
    def check_same(self, other_tile):
        return (self.start == other_tile.start)
    
    # flip the tile
    def flip(self):
        self.flipped = not self.flipped

# calling the main function
main()