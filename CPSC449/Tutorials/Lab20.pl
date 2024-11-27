% Exercises:
% Facts:

likes(susan, pasta).
likes(susan, ice_cream).
likes(susan, sushi).
likes(jane, chocolate).
likes(jane, cookie).
likes(john, pizza).
likes(john, pasta).
likes(mary, salad).
likes(mary, pasta).
likes(tom, pizza).
likes(tom, sushi).
likes(tom, cookie).

% Using the facts above, write queries for questoins below:

% Who likes pasta?

% likes(Person, pasta)
% can use ; to get the rest of the answers

% What does Susan like?

% likes(susan, X)
% can use ; to get the rest of the answers


% Attributes of foods
healthy(salad).
healthy(sushi).
healthy(pasta).
unhealthy(pizza).
unhealthy(cookie).

sweet(ice_cream).
sweet(cookie).

% Write the following queries:
% List all people who like unhealthy food:

% likes(X, Y), unhealthy(Y)
% can use ; to get the rest of the answers

% List all people who like unhealthy food:

% Who likes at least one healthy and one unhealthy food?:

% likes(X, Y), unhealthy(Y), likes(X, Z), healthy(Z).

% Conjuction (AND)
% Write a rule that determines if someone likes healthy food or not.

likes_healthy_food(X) :-
    likes(X, Y), healthy(Y).

% Disjunction (OR)
% Write a rule that determines if someone likes unhealthy or swee food.

likes_unhealthyORsweet_food(X) :-
    likes(X, Y), (unhealthy(Y);sweet(Y)).

% Define a rule to find people who like varied foods, meaning that they like more than one type (healthy or unhealthy) of food

likes_varied_food(Person) :-
    likes(Person, Food1), 
    likes(Person, Food2),
    Food1 \= Food2,
    (healthy(Food1);unhealthy(Food2)),
    (healthy(Food2);unhealthy(Food1)).

% Define a rule to find people who like only healthy foods
%  The \+ operator is used for negation, meaning "not". 

likes_only_healthy_food(Person) :-
    likes(Person, Food),
    healthy(Food),
    \+ (likes(Person, Food2), unhealthy(Food2)).

% Define a rule that finds people who like more than one type of food but don’t like both healthy and unhealthy.

likes_more_than_one(Person) :-
    likes (Person, Food1),
    likes (Person, Food2),
    Food1 \= Food2,
    \+ (likes_varied_food(Person)).
