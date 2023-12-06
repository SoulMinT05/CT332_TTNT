push_back(X, [], X).
push_back(X, [H|T], R) :- push_back(X, T, R1), R = [H|R1].
push_back(X, [H|T], [H|R1]) :- push_back(X, T, R1).