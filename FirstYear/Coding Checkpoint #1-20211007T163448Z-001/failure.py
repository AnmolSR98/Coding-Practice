#creating a playable version of pong
import pygame

#defining a main function
def main():
    pygame.init()
    pygame.display.set_mode((500, 400))
    pygame.display.set_caption('Pong Game')
    w_surface = pygame.display.get_surface()
    game = Game(w_surface)
    game.play()
    pygame.quit()
    
#creating a game class
class Game:
    
    def __init__(self, surface):
        # === objects that are part of every game that we will discuss
        self.surface = surface
        self.bg_color = pygame.Color('black')
        
        self.FPS = 60
        self.game_Clock = pygame.time.Clock()
        self.close_clicked = False
        self.continue_game = True
        
        #getting keys 
        keys = pygame.key.get_pressed()  
        
        p1_down = keys[pygame.K_a]
        p1_up = keys[pygame.K_q]
        p2_down = keys[pygame.K_l]
        p2_up = keys[pygame.K_p]
        
        
        # creating objects specific for this game
        self.ball = Ball()
        self.Federer = Paddle()
        self.Hewitt = Paddle()
        self.scores = [0,0]
        self.increment = 10 # number of steps to move per key click
       
    def play(self):
        
        # Play the game until the player presses the close box.
        # - self is the Game that should be continued or not.
  
        while not self.close_clicked:  # until player clicks close box
           # play frame
           self.handle_events()
           self.draw()            
           if self.continue_game:
              self.update()
              self.decide_continue()
           self.game_Clock.tick(self.FPS) # run at most with FPS Frames Per Second
           
    def handle_events(self):
        # Handle each user event by changing the game state appropriately.
        # - self is the Game whose events will be handled
  
        events = pygame.event.get()
        for event in events:
           if event.type == pygame.QUIT:
              self.close_clicked = True
              
        keys = pygame.key.get_pressed()    
        
        if keys[p1_down] and rect.y < (bbound-200):
            rect.move_ip(0, 10)
            
        if keys[p1_up] and rect.y > 0: 
            rect.move_ip(0, -10)
            
        if keys[p2_down] and rect2.y < (bbound-200):
            rect2.move_ip(0, 10)
                
        if keys[p2_up] and rect2.y > 0:
            rect2.move_ip(0, -10)          
    
              
    def draw(self):
        # Draw all game objects.
        # - self is the Game to draw
        
        self.surface.fill(self.bg_color) # clear the display surface first
        self.small_dot.draw()
        self.big_dot.draw()
        pygame.display.update() # make the updated surface appear on the display
        
    def handle_key_up(self, event):
        
        #qa
        #pl
        keys = pygame.key.get_pressed():
        if key[pygame.K_q]:
                center += 1
        if key[pygame.K_a]:
                center += -1        
        
    def handle_key_down(self, event):
        
        if keys[p1_down] and rect.y < (bbound-200):
            rect.move_ip(0, 10)
            
            if keys[p2_down] and rect2.y < (bbound-200):
                rect2.move_ip(0, 10)        
            
    def update(self):
        # Update the game objects for the next frame.
        # - self is the Game to update
        
        self.small_dot.move()
        self.big_dot.move()
        self.frame_counter = self.frame_counter + 1
        
    def decide_continue(self):
        # if a player scores then end the game
        if max(self.scores) > 0:
            self.continue_game = False
    def score_counter(self):
        #defining cases where players score
        if ball_center == 500:
            self.scores[0] = self.score[0] + 1
        elif ball_center == 0:
            self.scores[1] = self.scores[1] + 1

#creating a ball class
class Ball:
    def __init__(self, color, radius, center, velocity, surface):
        
        self.color = pygame.Color(dot_color)
        self.radius = dot_radius
        self.center = dot_center
        self.velocity = [1, 0]
        self.surface = surface
        
    def move(self):
        
        for i in range(0,2):
           self.center[i] = (self.center[i] + self.velocity[i])        
        
    def draw(self):
        
        pygame.draw.circle(self.surface, self.color, self.center, self.radius)
        
#creating a paddle class
class Paddle:
    def __init__(self, colour, length, width):
        
        self.colour = colour
        self.length = length
        self.width = width
        
    def handle_events(self):
        #qa
        #pl
        keys = pygame.key.get_pressed():
        if key[pygame.K_q]:
                center += 1
        if key[pygame.K_a]:
                center += -1
        
    def set_vertical_velocity(self):
        #setting vertical velocity
        vertical_velocity = 1
        
        
    def draw(self):
    