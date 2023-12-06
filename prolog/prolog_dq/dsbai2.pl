member(X, [X|_]).
member(X, [Y|L]) :- X\=Y, member(X, L).