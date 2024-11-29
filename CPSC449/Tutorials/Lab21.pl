
% In Prolog, constants represent fixed values that cannot be changed during program execution.
% They are used to define facts, relationships, and data within a Prolog knowledge base.
% Types of Constants:
% 1. Atoms: Atoms are symbolic names that represent specific entities.
% Syntax:
% Lowercase letters: apple, john, likes.
% Enclosed in single quotes for special characters or starting with uppercase: 'New York', '123abc'.
% Special predefined constants: true, false, [] (empty list).

% Numbers:
% Numerical constants represent numeric values.
% Can be integers (5, 42) or floating-point numbers (3.14, -0.5)

% Strings:
% Strings are sequences of characters enclosed in double quotes like "John Doe"
% Represented as lists of ASCII codes or characters in some implementations.


% Variables in Prolog
% In Prolog, variables are placeholders that can match with values during the resolution process. 
% They are not like variables in imperative languages, where they represent fixed memory locations. 
% Instead, Prolog variables are logical placeholders used to express relationships and constraints.
% Syntax:
% Variable names must start with an uppercase letter or an underscore (_), e.g., X, Y, _Temp.
% Variables starting with an underscore (_) are often used as anonymous variables, meaning their value is irrelevant and not saved.

%Exercises:
%Using the knowledge base below, answer the questions:
% Authors
author(george_orwell).
author(jk_rowling).
author(jane_austen).
author(agatha_christie).
author(jrr_tolkien).

% Books and their authors
book('1984', george_orwell).
book(animal_farm, george_orwell).
book(harry_potter_and_the_sorcerers_stone, jk_rowling).
book(harry_potter_and_the_chamber_of_secrets, jk_rowling).
book(murder_on_the_orient_express, agatha_christie).
book(the_hobbit, jrr_tolkien).
book(pride_and_prejudice, jane_austen).


% Books available in the library
available('1984').
available(animal_farm).
available(harry_potter_and_the_sorcerers_stone).
available(harry_potter_and_the_chamber_of_secrets).
available(murder_on_the_orient_express).
available(the_hobbit).

% Borrowing behavior
borrowed('1984', alice).
borrowed(harry_potter_and_the_sorcerers_stone, bob).
borrowed(the_hobbit, charlie).
borrowed(murder_on_the_orient_express, dave).

% Write a query to find out the books that jk rowling has written

% book (X, jk_rowling)

% Define a rule finds all books written by a specific author.

from_author(X, SomeBook) :-
    book(SomeBook, X).

% Define a rule checks if a book is currently available in the library (i.e., not borrowed).

is_available(Book) :-
    available(Book), \+ borrowed(Book, Person).

%Define a rule that identifies people who have borrowed more than one book.

has_borrowed_mult(Person) :-
    borrowed(Book1, Person), borrowed(Book2, Person), Book1 \= Book2.






