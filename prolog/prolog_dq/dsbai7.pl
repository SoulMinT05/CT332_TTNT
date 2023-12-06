delete(_, [], []).
delete(X, [X|T], R) :- delete(X, T, R).
delete(X, [H|T], [H|R]) :- delete(X, T, R).
unique([],[]).
unique([H|T], [H|R]) :- member(H,T), !, delete(H,T,R1), unique(R1,R).
unique([H|T],[H|R]) :- unique(T,R).