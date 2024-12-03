% -------------------
% Why Does Prolog Wait for Results?
% -------------------
% Prolog uses a mechanism called "backtracking" to explore all possible solutions to a query.
% By default, Prolog does not stop after finding the first solution; instead, it waits for your input to decide the next action:
%
% - If you press **Enter**, Prolog accepts the current result and terminates the search.
% - If you press **;**, Prolog backtracks to search for additional solutions.
%
% How Backtracking Works:
% 1. Prolog searches through the rules and facts in the knowledge base to find solutions.
% 2. If a solution is found, Prolog returns it but keeps track of alternative paths (if any exist).
% 3. If Prolog finds no further solutions, it outputs `false`, indicating no other answers satisfy the query.
%
% Example:
% ?- member(X, [1, 2, 3]).
% Output:
% X = 1 ;
% X = 2 ;
% X = 3 ;
% false.
% - Prolog iterates through the list `[1, 2, 3]` and finds all possible values for `X`.
% - After `X = 3`, no other solutions exist, so Prolog outputs `false`.
%
% Stopping Prolog from Waiting:
% 1. **Cut operator (`!`)**: Add a "cut" to terminate the search once a solution is found. For example:
%    first_member(X, List) :- member(X, List), !.
%    Query:
%    ?- first_member(X, [1, 2, 3]).
%    Output:
%    X = 1.
%    Explanation: Prolog stops after finding the first solution.
%
% 2. **Press Enter**: When Prolog finds a solution and waits, pressing **Enter** terminates the search.
%
% 3. **Use constraints**: Define rules with conditions that make other solutions impossible.
%
% Debugging Infinite Waits:
% If Prolog appears to wait indefinitely, it may be stuck in an infinite recursive loop.
% To debug, use tracing (`trace.`) to see how Prolog evaluates the query.


% Example 1: Check if a list is empty.

% Usage:
% ?- is_empty([]).


% Example 2: Find the head and tail of a list.
% Usage:
% ?- head_tail([1, 2, 3], Head, Tail).
% Head = 1, Tail = [2, 3].


% Example 3: Append two lists.

% Usage:
% ?- append_list([1, 2], [3, 4], Result).
% Result = [1, 2, 3, 4].


% Example 4: Reverse a list using recursion.

% Usage:
% ?- reverse_list([1, 2, 3], Result).
% Result = [3, 2, 1].



% Example 5: Check if a list is a palindrome.
% Usage:
% ?- is_palindrome([1, 2, 1]).
% true.


% Example 6: Find the nth element of a list.
% Usage:
% ?- nth_element(2, [a, b, c], Element).
% Element = b.


% Example 7: Remove duplicates from a list.
% Usage:
% ?- remove_duplicates([1, 2, 2, 3, 1], Result).
% Result = [3, 2, 1].


% Example 8: Flatten a nested list.
% Usage:
% ?- flatten_list([1, [2, [3, 4]], 5], Result).
% Result = [1, 2, 3, 4, 5].

