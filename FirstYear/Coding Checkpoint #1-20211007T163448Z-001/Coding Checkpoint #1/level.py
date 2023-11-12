#Anmol Ratol #1587571
#question 4, checking which level to assign them to

#the two floats for the score that the participant received on the quiz, which we may assume are between 0 and 100, grade 1 = gr1, grade 2 = gr2.

gr1 = float(input("What is the score on quiz #1? "))
gr2 = float(input("What is the score on quiz #2? "))

#creating an array of both values to make finding the values a little bit easier, grade array is shortened to grarr
grarr = [gr1, gr2]

#creating a string st to reduce how much I have to type
st = "You have been selected for level"

#if the lowest quiz score is 80 or more, put them in level 3
if min(grarr) >= 80:
  print(st + " 3.")
  
#if the lowest quiz score is 50 or more, put them in level 2
elif min(grarr) >= 50:
  print(st + " 2.")
  
#if the lowest quiz score is less than 50 but they have one score above fifty they must redo a quiz
elif min(grarr) <= 50 and max(grarr) >= 50:
  print("You will have to redo the quiz on which you received a(n)", min(grarr))

#if all other outcomes are exhausted (they have scored below 50 in both quizzes), they will be put in to level 1
else:
  print(st + " 1.")