#building the game from the ground up

import pygame as pg

def main():
    
    pg.init()
    pg.display.set_caption("Pong")
    rbound = 1200
    bbound = 600
    surface = pg.display.set_mode((rbound,bbound))  
    game = Game(surface)
    game.play()
    pygame.quit()
    
    
class Game:
    
    def __init__(self, surface):
        self.surface = surface
        self.color = (0, 0, 0)
        self.clock = pg.time.Clock()
        self.play = True
    
    def play(self):
        
        keys = pg.key.get_pressed()
        
        key1 = [keys[pygame.K_a], keys[pygame.K_q]]
        key2 = [keys[pygame.K_l], keys[pygame.K_p]]
        
        paddle1 = Paddle((40, 200), (255, 255, 255), (20, 200), key1)
        
        paddle2 = Paddle((40, 200), (255, 255, 255), (1140, 200), key2)
        
        ball = Ball((40, 40), (255, 255, 255), (580, 280))
        
        while self.play:
            
            self.check_exit()
            paddle1.move(600)
            paddle2.move(600)
            handle_events(600, paddle1, paddle1)
            
            self.surface.fill((0,0,0))
            paddle1.draw(self.surface)
            paddle2.draw(self.surface)
            ball.draw()
            pg.display.flip()
            clock.tick(60)  
            
    def check_exit(self):
        
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.play = False        

class Paddle:
    
    def __init__(self, dimensions, color, start_position, keys):
        
        self.rect = pg.rect.Rect(start_position, dimensions)
        self.color = color
        self.keys = keys
        
    def draw(self, surface):
        
        pg.draw.rect(surface, self.color, self.rect)
    
    def move(self, ybound):
        #defining 0 as the down key
        #defining 1 as the up key
        
        if keys[0] and rect.y > 0:
            self.rect.move_ip(0, 10)
        if keys[1] and rect.y < (ybound - self.dimensions[1]):
            self.rect.move_ip(0, -10)

class Ball:
    
    def __init__(self, dimensions, color, start_position, velocities):
        
        self.rect = pg.rect.Rect(start_position, dimensions)
        self.color = color
        self.hv = velocities[0]
        self.vv = velocities[1]
        
    def draw(self, surface):
        
        pg.draw.rect(surface, self.color, self.rect)
        
    def handle_events(self, ybound, paddle1, paddle2):
        
        if self.rect.y == 0 or self.rect.y == (ybound - dimensions[1]):
            
            vv = -vv
            
        if self.rect.collidelist((paddle1, paddle2)) != -1:
                
            vv = -vv
            hv = -hv
        

main()
        
        