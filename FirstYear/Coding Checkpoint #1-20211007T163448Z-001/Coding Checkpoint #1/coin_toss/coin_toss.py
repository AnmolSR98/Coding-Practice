# -*- coding: utf-8 -*-
"""coin_toss.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1pbm63GN6Gpa3Dfb2txuzstdE6ZOU8nYR
"""

#Version #4, Anmol Ratol #1587571, program for a game where a player will enter heads or tails, and the two computer players flip coins in the hopes of matching.

#importing random for the computer players' coins later on
import random as rand

#opening up ins as instructions.txt in read mode, where the proper path is normally in the first argument
ins = open("instructions.txt", mode = 'r')

#creating a string equivalent to what is in the opened text file 
message = ins.read()

#closing said file
ins.close()

#printing the instructions
print(message)

#rds counts what games of the four game set have been completed, starting at one while the other two vars number of rounds players 1/2 have won
rds = 1
p1 = 0
p2 = 0

#number of games(4 round sets) won by each computer player as well as the number of ties, p#ss = player #X number of games won
p1ss = 0
p2ss = 0
ties = 0

#arrays to show guesses, p#a = player #X array of guesses
p1a = []
p2a = []

#Some strings to save time
p1s = "Player 1"
p2s = "Player 2"
endmess = "ROUND STATS"
gameend = "SUMMARY STATS"

# a varaible to keep the while loop running
play = True

#creating a while loop
while play:

  #user input for what side the coin will give a score
  ua = input("Heads or Tails (H or T)?")

  #if the user inputs "H" or "h", then heads, all other inputs result in tails
  if ua == "H" or ua == "h":
    ua = 1
  else:
    ua = 2

  #the computer players tosses
  p1g = rand.randint(1,2)
  p2g = rand.randint(1,2)

  #print out player 1 and 2's tosses, where 1 = heads, all other results(ie. 2) mean tails
  if p1g == 1:
    print(p1s + " has tossed H")
  else:
    print(p1s + " has tossed T")
  if p2g == 1:
    print(p2s + " has tossed H")
  else:
    print(p2s + " has tossed T")

  #give points to the player that tosses correctly
  if p1g == ua:
    print(p1s + " wins")
    p1 = p1 + 1
  elif p2g == ua:
    print(p2s + " wins")
    p2 = p2 + 1

  #building a list of their tosses
  if p1g == 1:
    p1a.append("H")
  else:
    p1a.append("T")
  if p2g == 1:
    p2a.append("H")
  else:
    p2a.append("T")

  #if on the 4th round, print the game summary
  if rds == 4:
    
    #showing who won the game and how many points they each scored
    print(endmess)
    if p1 > p2:
      p1ss = p1ss + 1   #This is tallying up the total set of 4 games player 1 has won
      print(p1s + " wins this round")
    elif p1 == p2:
      ties = ties + 1   #Does the same with ties
      print(p1s +" and " + p2s + " win this round")
    else:
      p2ss = p2ss + 1   #does the same with player 2
      print(p2s + " wins this round")

    #printing overall statistics and the list of coin tosses over the course of the game
    print(p1s + " points", p1)
    print(p2s + " points", p2)
    print(p1s + " tosses", p1a)
    print(p2s + " tosses", p2a)

    #creating variables to record the amount of time hh occurs in the list
    p1hh = 0
    p2hh = 0

    #trying to find the number of times hh occurs in a toss sequence
    for i in range(0, 3):
      if p1a[i+1] == p1a[i] and p1a[i] == 'H':
        p1hh = p1hh+1
      if p2a[i+1] == p2a[i] and p2a[i] == 'H':
        p2hh = p2hh+1

    #printing that number out
    print(p1s + " has", p1hh, "HH sequences")
    print(p2s + " has", p2hh, "HH sequences")

    #asking if the player wants to play again
    pg = input("Do you want to play another round? y/n ")

    #if yes, reset the round number back to 0, clear the lists, and the number of rounds each players has won
    if pg ==  "Y" or pg == "y":
      rds = 0
      p1a = []
      p2a = []
      p1 = 0
      p2 = 0

    #otherwise, ie. no, print the ending messages and set the play bool to false to kill the loop
    else:
      print(gameend)
      print(p1s + " has won", p1ss, "times")
      print(p2s + " has won", p2ss, "times")
      print("There were", ties, "ties")
      play = False

  #count up the number of round at the end of each one
  rds = rds+1