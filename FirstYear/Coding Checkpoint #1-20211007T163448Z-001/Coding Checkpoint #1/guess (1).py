# -*- coding: utf-8 -*-
"""Guess.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1BaBreGIYhFvdAbsX3aGPgl4YuoxPGDEw
"""

#program for guess the number game 

#import the random module of python for use
import random as rand

#creating the input prompt for the number to ask the user for their guess
guess = input("I am thinking of a number from 1 to 10. Which number am I thinking of? ")

#RN = Random Number that the program is thinking of
RN = rand.randint(1, 10)

#if the two are equal, correct
if guess == RN:
  print("Correctomundo!")

#if the two aren't equal, wrong
else:
  print("No Bueno!")

#help taken from https://stackoverflow.com/questions/28669459/how-to-print-variables-without-spaces-between-values, first comment
#as I had forgotten how to remove the unnecessary space between the number and period.
#printing the random number the machine had in mind
print("The correct answer was " + str(RN) + ".")