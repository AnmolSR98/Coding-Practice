% CPSC 449 - Programming Paradigms
% Assignment 4
% Anmol Ratol
% 30231177

% Problem 1 - interleave
% just a modified version of the append code from the tutorials
% uses index variable to switch between lists.

% base cases for when a list empties out
append_list([], List, List, Index).
append_list(List, [], List, Index).

% cases where both lists still have variables
append_list(List, [Head|Tail], [Head|Result], 1):- append_list(List, Tail, Result, 0).
append_list([Head|Tail], List, [Head|Result], 0):- append_list(Tail, List, Result, 1).

% actual interleave function just redirects to append list with signal to start with variable from X first
interleave(Xs, Ys, Zs) :-
    append_list(Xs, Ys, Zs, 0), !.

% Problem 2 - Smart Home Automation Challenge
% Part A: Knowledge Base

% copied directly from assignment description
room(roomName).
device(someDevice, someRoom).

% added on my own
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
% defining two possible states
state(Lights, Temperature, SecurityMode).

initial_state(state([], 20, disarmed)).
goal_state(state([living_room], 22, armed)).

% Part C: State Transition Rules
% add a room onto the roomlist that have lights currently turned on.
turn_on_lights(CurrentState, Room, NewState) :-
    CurrentState = state(RoomList, Temp, Mode),
    NewState = state([Room|RoomList], Temp, Mode).

% simply replace temp with new temp
adjust_temperature(CurrentState, NewTemp, NewState) :-
    CurrentState = state(RoomList, Temp, Mode),
    NewState = state(RoomList, NewTemp, Mode).

% replace mode with new mode
change_security_mode(CurrentState, Mode, NewState) :-
    CurrentState = state(RoomList, Temp, OldMode),
    NewState = state(RoomList, Temp, Mode).

% Part D: Goal State
% see if there is any newRoom to be added, return the adjust_temperature(newTemp), and likewise for newMode
reach_goal_state(InitialState, GoalState, Actions) :-
    InitialState = state(OldRooms, OldTemp, OldMode),
    GoalState = state([NewRoom|OldRooms], NewTemp, NewMode), 
    Actions =  [turn_on_lights(NewRoom),
                adjust_temperature(NewTemp),
                change_security_mode(NewMode)].

% Problem 3 - ColorTree 

% knowledge base copied directly from assignment
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
% simply writing that foods are vegetarian if they aren't meat, and vegan if they also aren't dairy
compatible_ingredient(Ingredient, vegetarian) :-
    ingredient(Ingredient, Category), Category \= meat.
compatible_ingredient(Ingredient, vegan) :-
    ingredient(Ingredient, Category), Category \= meat, Category \= dairy.

% check ingredient list checks that each ingredient is compatible
check_ingredient_list(Restriction, []).
check_ingredient_list(Restriction, [Head|Tail]) :-
    compatible_ingredient(Head, Restriction), check_ingredient_list(Restriction, Tail).
% recipe compatible just passes on a recipe list to check_ingredient_list.
recipe_compatible(Recipe, Restriction) :-
    recipe(Recipe, RecipeList), check_ingredient_list(Restriction, RecipeList).

% check each ingredient is part of the available ingredients
check_ingredients_match(AvailableIngredients, []).
check_ingredients_match(AvailableIngredients, [Head|Tail]):-
    member(Head, AvailableIngredients), check_ingredients_match(AvailableIngredients, Tail).

% find a recipe, check that it is compatible with the restriction, and check that the available ingredients contains what is needed.
recommend_recipe(AvailableIngredients, Restriction, RecommendedRecipe) :-
    recipe(RecommendedRecipe, RecipeList), recipe_compatible(RecommendedRecipe, Restriction), check_ingredients_match(AvailableIngredients, RecipeList).

% Problem 5 - Ternary to Natural Number Conversion

% definition of succ
succ(succ(X)) :- succ(X).
succ(nat_zero).
nat_zero.

% basic definition of ternary numbers
tern(tern(X), tern(Y)) :- tern(X), tern(Y).
tern(zero).
tern(one).
tern(two).

% addition function
sum_nat( nat_zero, N2, N2 ).
sum_nat( N1, nat_zero, N1 ).
sum_nat( succ(N1), N2, succ(Result) ) :- sum_nat( N1, N2, Result ).

% basic conversion rules
tern_nat( tern(zero), nat_zero).
tern_nat( tern(one), succ(nat_zero)).
tern_nat( tern(two), succ(succ(nat_zero))).

% helper for tern_nat that triples existing total and then adds it to the lastest result from tern_nat of X
tern_helper( tern(X), CurrentTotal, Total) :- 
    sum_nat(NewResult, TripTotal, Total), % add it on the new total to get the overall value
    times_three(CurrentTotal, TripTotal), % multiply the existing total by three
    tern_nat(tern(X), NewResult), !.  % get the read from the "head"

% helper function simply splits in case of multiple terns
tern_helper( tern(X, Y), CurrentTotal, Total) :- 
    tern_helper(X, CurrentTotal, UpdatedTotal), % get the value of the total thus far
    tern_helper(Y, UpdatedTotal, Total). % feed it to the next iteration 

% tern_nat for multiple terns just redirects to tern helper
tern_nat( tern(X, Y), Nat) :-
    tern_helper( X, nat_zero, First), % start with the current total at zero, add head value on
    tern_helper( Y, First, Nat).    % pass it onto next iteration

% function to multiply a natural number by three
times_three( nat_zero, nat_zero ).
times_three( succ(Nat), succ(succ(succ(Result))) ) :- times_three( Nat, Result ).