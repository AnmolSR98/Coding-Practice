% CPSC 449 - Programming Paradigms
% Assignment 4
% Anmol Ratol
% 30231177

% Problem 1 - interleave
interleave(Xs, Ys, Zs) :-
    % Your code here

% Problem 2 - Smart Home Automation Challenge
% Part A: Knowledge Base
room(roomName).
device(someDevice, someRoom).

% Part B: Initial State
state(Lights, Temperature, SecurityMode).

% Part C: State Transition Rules
turn_on_lights(CurrentState, Room, NewState) :-
    % Your code here

adjust_temperature(CurrentState, NewTemp, NewState) :-
    % Your code here

change_security_mode(CurrentState, Mode, NewState) :-
    % Your code here

% Part D: Goal State
reach_goal_state(InitialState, GoalState, Actions) :-
    % Your code here

% Problem 3 - ColorTree
colortree_list(Tree, List) :-
    % Your code here

% Problem 4 - Recipe System
% Part A: Knowledge Base
ingredient(Name, Category) :-
    % Your code here

recipe(Name, IngredientList) :-
    % Your code here

dietary_restriction(RestrictionName) :-
    % Your code here

% Part B: Rules
compatible_ingredient(Ingredient, Restriction) :-
    % Your code here

recipe_compatible(Recipe, Restriction) :-
    % Your code here

recommend_recipe(AvailableIngredients, Restriction, RecommendedRecipe) :-
    % Your code here

% Problem 5 - Ternary to Natural Number Conversion
tern_nat(Tern, Nat) :-
    % Your code here