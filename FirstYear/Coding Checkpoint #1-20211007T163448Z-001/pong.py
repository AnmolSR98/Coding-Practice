# Anmol Ratol, 1587571
# Project 2, creating Pong in pygame
# virtually all of this code ended up using information from https://www.pygame.org/docs/

import pygame as pg
import random as rand

def main():

    # setting up the game to run, creating the variables for the surface and setting caption, calling the play function and then getting the to quit after play ends
    pg.init()
    pg.display.set_caption("Pong")
    rgt_bound = 1200
    bot_bound = 800
    game = Game((rgt_bound, bot_bound))
    game.play()
    pg.quit()
    
    
class Game:
    
    # initialize the values needed to create the game
    def __init__(self, bounds):
        
        self.surface = pg.display.set_mode(bounds) # initializing surface
        self.color = (0, 0, 0)# the surface color set to black
        self.clock = pg.time.Clock()# creating a clock
        self.score = [0, 0]# initializing player scores
        self.bounds = bounds# initializing the board boundaries
        self.FPS = 60# initializing frames per second
        
    def play(self):
        
        # just defining some variables to use later
        white = (255, 255, 255)
        # setting paddle and dimensions
        paddle_size = (40, 200)
        ball_size = (40, 40)
        # paddles and ball start position
        paddle1_SP = (paddle_size[0], 0.5*(self.bounds[1]-paddle_size[1]))
        paddle2_SP = (self.bounds[0] - 2*paddle_size[0], 0.5*(self.bounds[1]-paddle_size[1]))
        ball_SP = (0.5*(self.bounds[0]-ball_size[0]),0.5*(self.bounds[1]-ball_size[1]))
        # ball starting velocity
        ball_v = (7,7)        
        # the top and bottom of the board
        ybound = (100, self.bounds[1]-100)
        
        # initializing the paddles and ball
        paddle1 = Paddle(paddle_size, white, paddle1_SP, ybound)
        paddle2 = Paddle(paddle_size, white, paddle2_SP, ybound)
        ball = Ball(ball_size, white, ball_SP, ball_v)
        
        # play condition
        self.play = True
        
        while self.play:
            
            # check if the player has clicked out of the window
            self.decide_continue()
            
            # move the paddles and ball
            paddle1.move( pg.K_a, pg.K_q)
            paddle2.move( pg.K_l, pg.K_p)
            ball.move()
            
            # handle any events that may occur, ie. collisions between the walls, paddles and ball
            self.handle_events(self.bounds[1]-100, ball, paddle1, paddle2)
            
            # draw a black screen first
            self.surface.fill(self.color)
            # draw other stuff on top of the black surface
            
            # the boundary lines
            pg.draw.line(self.surface, white, (-2000, 94), (2000, 94), 10)
            pg.draw.line(self.surface, white, (-2000, self.bounds[1]-96), (2000, self.bounds[1]-96), 10)
            
            # the paddles and ball
            paddle1.draw(self.surface)
            paddle2.draw(self.surface)
            ball.draw(self.surface)
            
            # the score being drawn
            # the following three lines were written using some resources from https://pygame.readthedocs.io/en/latest/4_text/text.html
            font = pg.font.Font(None, 74)
            text = font.render((str(self.score[0]) + " : " + str(self.score[1])), True, white)
            self.surface.blit(text, (550, 20))  
            
            # display the frame
            pg.display.flip()
            
            # move along at 60 frames a second, can also be used to speed up the game as it does calculations frame by frame
            self.clock.tick(self.FPS) 
            
    def decide_continue(self):
        
        # if player quits the game, set the loop to end 
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.play = False    
                
    def handle_events(self, ybound, ball, paddle1, paddle2):
        
        # initializing the various variables used later on
        ball_velocity_x = 15
        ball_velocity_y = 15
        ball_reset_x = 10
        x_directions = [-1, 1]
        ball_size = (40, 40)
        ball_SP = (0.5*(self.bounds[0]-ball_size[0]),0.5*(self.bounds[1]-ball_size[1]))
        goal_bounds = (-0.5*self.bounds[0], 1.5*self.bounds[0])
                      
        # checking for collisions along y bounds, reversing the velocity if they collide along this point
        if ball.rect.y < 100:
            
            ball.vv = ball_velocity_y
            
        if ball.rect.y > (ybound - ball.dimensions[1]):
            
            ball.vv = -1*ball_velocity_y
            
        #checking if collided with a part of specific paddle, and changing ball velocity accordingly
        
        # if ball collides with either paddle 
        if ball.rect.collidelist([paddle1, paddle2]) != -1:
                
            #if collides with middle, increase ball horizontal velocity to the maximum of 15, and dampen the vertical velocity
            if ball.rect.colliderect(paddle1.midrect):
                ball.vv = 0.66*ball.vv
                ball.hv = ball_velocity_x
                
            elif ball.rect.colliderect(paddle2.midrect):
                ball.vv = 0.66*ball.vv
                ball.hv = -ball_velocity_x
                
            # if collides with top or bottom, set ball vertical velocity to maximum of 15
            elif ball.rect.colliderect(paddle1.toprect):
                ball.hv = -ball.hv
                ball.vv = -ball_velocity_y
                
            elif ball.rect.colliderect(paddle2.toprect):
                ball.hv = -ball.hv
                ball.vv = -ball_velocity_y 
                
            elif ball.rect.colliderect(paddle1.botrect):
                ball.hv = -ball.hv
                ball.vv = ball_velocity_y              
                
            elif ball.rect.colliderect(paddle2.botrect):
                ball.hv = -ball.hv
                ball.vv = ball_velocity_y
            
        # checking if collided with the end of the x bounds
        if ball.rect.x <= goal_bounds[0] or ball.rect.x >= goal_bounds[1]:
            
            #find a way to space the "serves" a little bit
            if ball.rect.x <= goal_bounds[0]:
                self.score_counter(1)
            if ball.rect.x >= goal_bounds[1]:
                self.score_counter(0)            
            ball.rect.x = ball_SP[0]
            ball.rect.y = ball_SP[1]
            ball.vv = ball_velocity_y
            ball.hv = x_directions[rand.randint(0,1)]*ball_reset_x
    
    # increase the score for a certain player
    def score_counter(self, player_id):
        self.score[player_id] += 1
        
            

class Paddle:
    
    # initializing a paddle
    def __init__(self, dimensions, color, start_position, board):
        
        # initialize the paddle and its hitboxes, along with its color and dimensions
        self.rect = pg.rect.Rect(start_position, dimensions)
        self.toprect = pg.rect.Rect(start_position, (dimensions[0], 0.2*dimensions[1]))
        self.midrect = pg.rect.Rect([start_position[0], start_position[1] + 0.2*dimensions[1]], (dimensions[0], 0.6*dimensions[1]))
        self.botrect = pg.rect.Rect([start_position[0], start_position[1] + 0.8*dimensions[1]], (dimensions[0], 0.2*dimensions[1]))        
        self.color = color
        self.dimensions = dimensions
        self.board = board
        
    def draw(self, surface):
        
        # draw the paddle 
        pg.draw.rect(surface, self.color, self.rect)       
    
    def move(self, down_key, up_key):
        
        # index 0 as the down key
        # index 1 as the up key
        keys = pg.key.get_pressed()
        
        # key pressed to move paddle up, then move the paddle and the hitboxes
        if keys[down_key] and self.rect.y < (self.board[1] - self.dimensions[1]):
            
            # the following lines were written using the help of resources from https://stackoverflow.com/questions/32061507/moving-a-rectangle-in-pygame
            self.rect.move_ip(0, 10)
            self.toprect.move_ip(0, 10)
            self.midrect.move_ip(0, 10)
            self.botrect.move_ip(0, 10)            
            
        # same thing for key pressed to move paddle down,
        if keys[up_key] and self.rect.y > self.board[0]:
            self.rect.move_ip(0, -10)
            self.toprect.move_ip(0, -10)
            self.midrect.move_ip(0, -10)
            self.botrect.move_ip(0, -10)

class Ball:
    
    # initialize the ball
    def __init__(self, dimensions, color, start_position, velocities):
        
        # create a little ball, setting its color, initial velocities, along with its dimensions 
        self.rect = pg.rect.Rect(start_position, dimensions)
        self.color = color
        self.hv = velocities[0]
        self.vv = velocities[1]
        self.dimensions = dimensions
        
    def draw(self, surface):
        
        # draw the ball
        pg.draw.rect(surface, self.color, self.rect)
            
    def move(self):
        
        # move the ball at its velocity
        self.rect.move_ip(self.hv, self.vv)        

# calling the main function
main()
        
        