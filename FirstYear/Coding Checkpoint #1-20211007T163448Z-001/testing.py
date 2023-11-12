#stationary set up
import pygame
pygame.init()

#for caption of window
pygame.display.set_caption('Pong')   

rbound = 1200
bbound = 600

surface = pygame.display.set_mode((rbound,bbound))

color = (255, 255, 255)

top = 200

rect = pygame.rect.Rect((20, top), (40, 200))
rect2 = pygame.rect.Rect((1140, top), (40, 200))
rect3 = pygame.rect.Rect((580, 280), (40, 40))

score1 = 0
score2 = 0


play = True

hv = 10
vv = 10

clock = pygame.time.Clock()

while play:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            play = False    
    
    #collision and movement for the respective paddles
    
    keys = pygame.key.get_pressed()
    
    if keys[pygame.K_a] and rect.y < (bbound-200):
        rect.move_ip(0, 10)
        
    if keys[pygame.K_q] and rect.y > 0: 
        rect.move_ip(0, -10)
        
    if keys[pygame.K_l] and rect2.y < (bbound-200):
        rect2.move_ip(0, 10)
            
    if keys[pygame.K_p] and rect2.y > 0:
        rect2.move_ip(0, -10)            
        
        
    #collision and movement for the ball    
    rect3.move_ip(hv, vv)   
    
    if rect3.collidelist((rect, rect2)) != -1:
        
        vv = -vv
        hv = -hv
        
    if rect3.y == 0 or rect3.y == (600-40):
        
        vv = -vv        
        
    surface.fill((0, 0, 0))    

    pygame.draw.rect(surface, color, rect)
    pygame.draw.rect(surface, color, rect2)
    pygame.draw.rect(surface, color, rect3)
    
    font = pygame.font.Font(None, 74)
    text = font.render(str(score1), 1, (255, 255, 255))
    surface.blit(text, (40, 550))
    
    pygame.display.flip()
    
    clock.tick(60)    
        
pygame.quit()



