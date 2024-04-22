import pygame
import pygame_menu

pygame.init()
screen = pygame.display.set_mode((600,800))

def set_difficulty(value, difficulty):
    # Do the job here !
    pass

def start_the_game():
    # Do the job here !
    pass

menu = pygame_menu.Menu('Welcome',400,300)

menu.add.text_input('Name :', default='Ziang Liu')
menu.add.selector('Difficulty :', [('Hard', 1), ('Easy', 2)], onchange=set_difficulty)
menu.add.button('Play', start_the_game)
menu.add.button('Quit', pygame_menu.events.EXIT)

while 1:
    pygame.init()
    