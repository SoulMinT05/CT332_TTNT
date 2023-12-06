ptvtle([], []).
ptvtle([X], [X]).
ptvtle([H, _|T], [H|R]) :- ptvtle(T, R).
