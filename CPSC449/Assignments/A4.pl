% CPSC 449 - Programming Paradigms
% Assignment 4
% Anmol Ratol
% 30231177

% Problem 1 - interleave
% just a modified version of the append code from the tutorials
append_list([], List, List, Index).
append_list(List, [Head|Tail], [Head|Result], 1):- append_list(List, Tail, Result, 0).
append_list([Head|Tail], List, [Head|Result], 0):- append_list(Tail, List, Result, 1).

interleave(Xs, Ys, Zs) :-
    append_list(Xs, Ys, Zs, 0), !.

% Problem 2 - Smart Home Automation Challenge
% Part A: Knowledge Base
room(roomName).
device(someDevice, someRoom).

room(living_room).
room(bedroom).
room(kitchen).

device(light, bedroom).
device(light, kitchen).
device(light, living_room).

device(thermostat, kitchen).
device(thermostat, bedroom).
device(thermostat, living_room).

device(security_camera, kitchen).
device(security_camera, bedroom).
device(security_camera, living_room).

% Part B: Initial State
state(Lights, Temperature, SecurityMode).

initial_state(state([], 20, disarmed)).
goal_state(state([living_room], 22, armed)).

% Part C: State Transition Rules
turn_on_lights(CurrentState, Room, NewState) :-
    CurrentState = state(RoomList, Temp, Mode),
    NewState = state([Room|RoomList], Temp, Mode).

adjust_temperature(CurrentState, NewTemp, NewState) :-
    CurrentState = state(RoomList, Temp, Mode),
    NewState = state(RoomList, NewTemp, Mode).

change_security_mode(CurrentState, Mode, NewState) :-
    CurrentState = state(RoomList, Temp, OldMode),
    NewState = state(RoomList, Temp, Mode).

% Part D: Goal State
reach_goal_state(InitialState, GoalState, Actions) :-
    InitialState = state(OldRooms, OldTemp, OldMode),
    GoalState = state([NewRoom|OldRooms], NewTemp, NewMode), 
    Actions =  [turn_on_lights(NewRoom),
                adjust_temperature(NewTemp),
                change_security_mode(NewMode)].

% Problem 3 - ColorTree STILL NEED TO FILL IN THIS ONE

leaf(_, _).
cnode(red, []).
cnode(green, []).
cnode(blue, []).
cnode(red, [T|Ts]) :- colortree(T), cnode(red, Ts).
cnode(green, [T|Ts]) :- colortree(T), cnode(green, Ts).
cnode(blue, [T|Ts]) :- colortree(T), cnode(blue, Ts).
colortree(leaf(_, _)).
colortree(cnode(_, _)).

% base cases consisting of a tree with only one cnode or only one leaf
colortree_list(cnode(Color, []), [Color, []]).
colortree_list(leaf(X, Y), [X, Y]).

% end of the list with a leaf or cnode
colortree_list([leaf(X, Y)], [[X, Y]]).
colortree_list([cnode(Color, RestTree)], [[Color|RestList]]) :-
    colortree_list(RestTree, RestList).

% processing a list that has either a cnode or a leaf at the start
colortree_list([leaf(X, Y)|Remainder], [[X, Y]|RemList]) :-
    colortree_list(Remainder, RemList).
colortree_list([cnode(Color, RestTree)|Remainder], [[Color|RestList]|RemList]) :-
    colortree_list(RestTree, RestList),
    colortree_list(Remainder, RemList).

% tree that starts with a cnode that has more elements
colortree_list(cnode(Color, RestTree), [Color|RestList]) :-
    colortree_list(RestTree, RestList).


% Problem 4 - Recipe System
% Part A: Knowledge Base
ingredient(chicken, meat).
ingredient(tofu, vegetarian).
ingredient(lettuce, vegetable).
ingredient(tomato, vegetable).
ingredient(cheese, dairy).

recipe(chicken_salad, [chicken, lettuce, tomato]).
recipe(veggie_salad, [tofu, lettuce, tomato]).
recipe(cheese_salad, [cheese, lettuce, tomato]).

dietary_restriction(vegetarian).
dietary_restriction(vegan).

% Part B: Rules
compatible_ingredient(Ingredient, vegetarian) :-
    ingredient(Ingredient, Category), Category \= meat.
compatible_ingredient(Ingredient, vegan) :-
    ingredient(Ingredient, Category), Category \= meat, Category \= dairy.

% own custom defined function
check_ingredient_list(Restriction, []).
check_ingredient_list(Restriction, [Head|Tail]) :-
    compatible_ingredient(Head, Restriction), check_ingredient_list(Restriction, Tail).
recipe_compatible(Recipe, Restriction) :-
    recipe(Recipe, RecipeList), check_ingredient_list(Restriction, RecipeList).

% make something that gets all compatible recipes
% check each ingredient is part of the available ingredient
check_ingredients_match(AvailableIngredients, []).
check_ingredients_match(AvailableIngredients, [Head|Tail]):-
    member(Head, AvailableIngredients), check_ingredients_match(AvailableIngredients, Tail).

recommend_recipe(AvailableIngredients, Restriction, RecommendedRecipe) :-
    recipe(RecommendedRecipe, RecipeList), recipe_compatible(RecommendedRecipe, Restriction), check_ingredients_match(AvailableIngredients, RecipeList).

% Problem 5 - Ternary to Natural Number Conversion

succ(succ(X)) :- succ(X).
succ(nat_zero).
nat_zero.

tern(zero).
tern(one).
tern(two).
tern(tern(X)):- 
    tern(X).
tern(tern(X, Y)):- 
    tern(X), tern(Y).
tern(tern(X), tern(Y)) :-
    tern(X), tern(Y).

tern_nat( tern(zero), nat_zero).
tern_nat( tern(one), succ(Nat)) :- tern_nat(tern(zero), Nat).
tern_nat( tern(two), succ(Nat)) :- tern_nat(tern(one),  Nat).

tern_nat( tern(tern(zero), tern(X)), Nat) :- tern_nat(tern(X),  Nat).

tern_nat( tern(tern(zero), tern(zero)), Nat) :- tern_nat(tern(zero),  Nat).
tern_nat( tern(tern(one),  tern(zero)), succ(succ(succ(Nat)))) :- tern_nat(tern(tern(zero), tern(zero)),  Nat).
tern_nat( tern(tern(two),  tern(zero)), succ(succ(succ(Nat)))) :- tern_nat(tern(tern(one), tern(zero)),  Nat).

%tern_nat( tern(zero), tern_nat(tern(tern(X), tern(zero)), Nat) ),


tern_nat( tern(tern(X), tern(Y)), Nat ) :-
    tern_nat( tern(tern(X), tern(zero)), Nat), tern_nat( tern(Y), Nat ).
