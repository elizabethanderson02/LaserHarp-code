import pygame
import time
import random
import math
import pygame_menu
import serial

# import os
# from playsound import playsound

# version 8(Playing Mode):  Controling notes falling down in right order.
#
# What next: Sleep for 0.02s to avoid buttons violation? It will happen probably
# Add Menu so player can change songs or pause or quit
# Add different instruments


def display(message):
    font = pygame.font.Font(None, 50)
    text = font.render(message, True, (255, 255, 255))
    screen.blit(text, (0, 0))


def displaykeys(message):
    font = pygame.font.SysFont('arial', 50, bold=True, italic=False)
    text = font.render(message, True, (255, 23, 140), (255, 192, 203))
    screen.blit(text, (width / 2 - 10 * len(message), 500))


# Initialize the parameters


falling_time = 50
width, height = 1920, 1100
FallingSpeed = height / falling_time

number_of_strings = 24
interval = width / number_of_strings -3
Score = 0
strings = [[0, 800]]
sleeptime = 0.02

do = interval
re = 2 * interval
me = 3 * interval
fa = 4 * interval
so = 5 * interval
la = 6 * interval
ti = 7 * interval
do1 = 8 * interval
re1 = 9 * interval
me1 = 10 * interval
fa1 = 11 * interval
so1 = 12 * interval
la1 = 13 * interval
ti1 = 14 * interval
do2 = 15 * interval
re2 = 16 * interval
me2 = 17 * interval
fa2 = 18 * interval
so2 = 19 * interval
la2 = 20 * interval
ti2 = 21 * interval
do3 = 22 * interval
re3 = 23 * interval
me3 = 24 * interval


# Music Pack, 4000 per bar
Doll_And_Dancing_Bear = \
    [[do, 0], [re, -250], [me, -500], [fa, -750], [so, -1000], [so, -1250], [so, -1500], [fa, -1625], [me, -1750],
     [fa, -2000], [fa, -2250], [fa, -2500], [me, -2625], [re, -2750], [do, -3000], [me, -3250], [so, -3500],
     [do, -4000], [re, -4250], [me, -4500], [fa, -4750], [so, -5000], [so, -5250], [so, -5500], [fa, -5625],
     [me, -5750], [fa, -6000], [fa, -6250], [fa, -6500], [me, -6625], [re, -6750], [do, -7000], [me, -7250],
     [do, -7500], [la, -8000], [la, -8250], [la, -8500], [so, -8625], [fa, -8750], [so, -9000], [so, -9250],
     [so, -9500], [fa, -9625], [me, -9750], [fa, -10000], [fa, -10250], [fa, -10500], [me, -10625], [re, -10750],
     [do, -11000], [me, -11250], [so, -11500], [la, -12000], [la, -12250], [la, -12500], [so, -12625], [fa, -12750],
     [so, -13000], [so, -13250], [so, -13500], [fa, -13625], [me, -13750], [fa, -14000], [fa, -14250], [fa, -14500],
     [me, -14625], [re, -14750], [do, -15000], [me, -15250], [do, -15500]]

Twinkle_Twinkle_Little_Star = \
    [[do, 0], [do, -250], [so, -500], [so, -750], [la, -1000], [la, -1250], [so, -1500], [fa, -2000], [fa, -2250],
     [me, -2500], [me, -2750], [re, -3000], [re, -3250], [do, -3500], [so, -4000], [so, -4250], [fa, -4500],
     [fa, -4750], [me, -5000], [me, -5250], [re, -5500], [so, -6000], [so, -6250], [fa, -6500], [fa, -6750],
     [me, -7000], [me, -7250], [re, -7500], [do, -8000], [do, -8250], [so, -8500], [so, -8750], [la, -9000],
     [la, -9250], [so, -9500], [fa, -10000], [fa, -10250], [me, -10500], [me, -10750], [re, -11000], [re, -11250],
     [do, -11500]]

FreePlay = []

Songs = [Doll_And_Dancing_Bear, Twinkle_Twinkle_Little_Star, FreePlay]
FallingNotes = Songs[0]
keys = [False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False,False, False, False, False, False, False, False, False]
clock = pygame.time.Clock()

# Initialize the game


pygame.init()
pygame.mixer.init()
screen = pygame.display.set_mode((width, height))
bg = pygame.image.load('background.jpg')
keysimg = pygame.image.load('laserOff.png')
fallingNote = pygame.image.load('noteLaser.png')
keyspressedimg = pygame.image.load('laser.png')
index = 0
Message = 'Start!'
starttime = endtime = 0
# Main body

def set_difficulty(value, difficulty):
    global FallingSpeed
    if difficulty == 'Insane':
        FallingSpeed = 40
    if difficulty == 'Hard':
        FallingSpeed = 30
    if difficulty == 'Medium':
        FallingSpeed = 20
    if difficulty == 'Easy':
        FallingSpeed = 10
    print(value, difficulty)
    

def start_the_game():
    global index
    index = 2
    menu.disable()

def back_to_menu():
    global index
    index = 1
    menu.enable()



def set_songs(value, number):
    global FallingNotes
 
    FallingNotes = Songs[number]

menu = pygame_menu.Menu('Hello', 1000, 300, enabled=True, onclose=None, theme=pygame_menu.themes.THEME_DARK)
selector1 = menu.add.selector('Difficulty :',
                              [('Easy', 'Easy'), ('Medium', 'Medium'), ('Hard', 'Hard'), ('Insane', 'Insane')],
                              onchange=set_difficulty)
selector2 = menu.add.selector('Songs :',
                              [('Doll and dancing bear', 0), ('Twinkle twinkle little star', 1), ('Free Play', 2)],
                              onchange=set_songs)
menu.add.button('Play', start_the_game)
menu.add.button('Quit', pygame_menu.events.EXIT)

index = 1

ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
ser.reset_input_buffer()
print(ser)
    


while (index == 1):
    menu.mainloop(surface=screen)

while (index == 2):
    
    clock.tick(60)
    screen.fill((0,0,0))
    #screen.blit(bg, (0, 0))
    #screen.blit(bg, (833, 0))
    display('Score:' + str(Score))
    displaykeys(Message)

    screen.blit(keysimg, (do, 0))
    screen.blit(keysimg, (re, 0))
    screen.blit(keysimg, (me, 0))
    screen.blit(keysimg, (fa, 0))
    screen.blit(keysimg, (so, 0))
    screen.blit(keysimg, (la, 0))
    screen.blit(keysimg, (ti, 0))
    screen.blit(keysimg, (do1, 0))
    screen.blit(keysimg, (re1, 0))
    screen.blit(keysimg, (me1, 0))
    screen.blit(keysimg, (fa1, 0))
    screen.blit(keysimg, (so1, 0))
    screen.blit(keysimg, (la1, 0))
    screen.blit(keysimg, (ti1, 0))
    screen.blit(keysimg, (do2, 0))
    screen.blit(keysimg, (re2, 0))
    screen.blit(keysimg, (me2, 0))
    screen.blit(keysimg, (fa2, 0))
    screen.blit(keysimg, (so2, 0))
    screen.blit(keysimg, (la2, 0))
    screen.blit(keysimg, (ti2, 0))
    screen.blit(keysimg, (do3, 0))
    screen.blit(keysimg, (re3, 0))
    screen.blit(keysimg, (me3, 0))
    
    # for FallingNote in FallingNotes:
    for i in range(0, len(FallingNotes)):
        FallingNotes[i][1] += FallingSpeed
        screen.blit(fallingNote, FallingNotes[i])
    # print(FallingNotes[0])
    # print(FallingNotes[i][1])
    tickBefore = pygame.time.get_ticks()
    print("ticks before serial line: " + str(tickBefore))
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
    tickAfter = pygame.time.get_ticks()
    print("ticks after serial line: " + str(tickAfter))
    
    res = any(chr.isdigit() for chr in line)
    if res:
        intLine = float(line)
    else:
        intLine = 0;
    if intLine >= 8388608:
        keys[23] = True
        screen.blit(keyspressedimg, (me3, 0))
        intLine = intLine - 8388608
    elif intLine < 8388608:
        keys[23] = False
    if intLine >= 4194304:
        keys[22] = True
        screen.blit(keyspressedimg, (re3, 0))
        intLine = intLine - 4194304
    elif intLine < 4194304:
        keys[22] = False
    if intLine >= 2097152:
        keys[21] = True
        screen.blit(keyspressedimg, (do3, 0))
        intLine = intLine - 2097152
    elif intLine < 2097152:
        keys[21] = False
    if intLine >= 1048576:
        keys[20] = True
        screen.blit(keyspressedimg, (ti2, 0))
        intLine = intLine - 1048576
    elif intLine < 1048576:
        keys[20] = False
    if intLine >= 524288:
        keys[19] = True
        screen.blit(keyspressedimg, (la2, 0))
        intLine = intLine - 524288
    elif intLine < 524288:
        keys[19] = False
    if intLine >= 262144:
        keys[18] = True
        screen.blit(keyspressedimg, (so2, 0))
        intLine = intLine - 262144
    elif intLine < 262144:
        keys[18] = False
    if intLine >= 131072:
        keys[17] = True
        screen.blit(keyspressedimg, (fa2, 0))
        intLine = intLine - 131072
    elif intLine < 131072:
        keys[17] = False
    if intLine >= 65536:
        keys[16] = True
        screen.blit(keyspressedimg, (me2, 0))
        intLine = intLine - 65536
    elif intLine < 65536:
        keys[16] = False
    if intLine >= 32768:
        keys[15] = True
        screen.blit(keyspressedimg, (re2, 0))
        intLine = intLine - 32768
    elif intLine < 32768:
        keys[15] = False
    if intLine >= 16384:
        keys[14] = True
        screen.blit(keyspressedimg, (do2, 0))
        intLine = intLine - 16384
    elif intLine < 16384:
        keys[14] = False
    if intLine >= 8192:
        keys[13] = True
        screen.blit(keyspressedimg, (ti1, 0))
        intLine = intLine - 8192
    elif intLine < 8192:
        keys[13] = False
    if intLine >= 4096:
        keys[12] = True
        screen.blit(keyspressedimg, (la1, 0))
        intLine = intLine - 4096
    elif intLine < 4096:
        keys[12] = False
    if intLine >= 2048:
        keys[11] = True
        screen.blit(keyspressedimg, (so1, 0))
        intLine = intLine - 2048
    elif intLine < 2048:
        keys[11] = False
    if intLine >= 1024:
        keys[10] = True
        screen.blit(keyspressedimg, (fa1, 0))
        intLine = intLine - 1024
    elif intLine < 1024:
        keys[10] = False
    if intLine >= 512:
        keys[9] = True
        screen.blit(keyspressedimg, (me1, 0))
        intLine = intLine - 512
    elif intLine < 512:
        keys[9] = False
    if intLine >= 256:
        keys[8] = True
        screen.blit(keyspressedimg, (re1, 0))
        intLine = intLine - 256
    elif intLine < 256:
        keys[8] = False
    if intLine >= 128:
        keys[7] = True
        screen.blit(keyspressedimg, (do1, 0))
        intLine = intLine - 128
    elif intLine < 128:
        keys[7] = False
    if intLine >= 64:
        keys[6] = True
        screen.blit(keyspressedimg, (ti, 0))
        intLine = intLine - 64
    elif intLine < 64:
        keys[6] = False
    if intLine >= 32:
        keys[5] = True
        screen.blit(keyspressedimg, (la, 0))
        intLine = intLine - 32
    elif intLine < 32:
        keys[5] = False
    if intLine >= 16:
        keys[4] = True
        screen.blit(keyspressedimg, (so, 0))
        intLine = intLine - 16
    elif intLine < 16:
        keys[4] = False
    if intLine >= 8:
        keys[3] = True
        screen.blit(keyspressedimg, (fa, 0))
        intLine = intLine - 8
    elif intLine < 8:
        keys[3] = False
    if intLine >= 4:
        keys[2] = True
        screen.blit(keyspressedimg, (me, 0))
        intLine = intLine - 4
    elif intLine < 4:
        keys[2] = False
    if intLine >= 2:
        keys[1] = True
        screen.blit(keyspressedimg, (re, 0))
        intLine = intLine - 2
    elif intLine < 2:
        keys[1] = False
    if intLine == 1:
        keys[0] = True
        screen.blit(keyspressedimg, (do, 0))
        intLine = intLine - 1
    elif intLine == 0:
        keys[0] = False
        
    
    for event in pygame.event.get():
        # Quit
        if event.type == pygame.QUIT:
            pygame.quit()
            exit(0)
   
             
    for i, key_pos in enumerate([do, re, me, fa, so, la, ti, do1, re1, me1, fa1, so1, la1, ti1, do2, re2, me2, fa2, so2, la2, ti2, do3, re3, me3]):
        if keys[i]:  # Check if the key is pressed
            screen.blit(keyspressedimg, (key_pos, 0))
        else:
            screen.blit(keysimg, (key_pos, 0))
    
    for i in range(0, len(FallingNotes)):  # count the score, recognize the keys and the pressed time
        if keys[0] and FallingNotes[i][0] == do:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[0][1] < 750 or 900 < FallingNotes[0][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[1] and FallingNotes[i][0] == re:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[2] and FallingNotes[i][0] == me:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[3] and FallingNotes[i][0] == fa:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[4] and FallingNotes[i][0] == so:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[5] and FallingNotes[i][0] == la:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[6] and FallingNotes[i][0] == ti:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
        if keys[7] and FallingNotes[i][0] == do1:
            if 750 < FallingNotes[i][1] < 900:
                Score += 100
                FallingNotes[i][1] = 1200
                Message = 'Perfect!'
            if 600 < FallingNotes[i][1] < 750 or 900 < FallingNotes[i][1] < 1000:
                Score += 50
                FallingNotes[i][1] = 1200
                Message = 'Good!'
    pygame.display.flip()
