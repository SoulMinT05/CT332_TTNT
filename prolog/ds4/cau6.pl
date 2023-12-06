smaller([], P, R) :- R = [] .
smaller([H|T], P, R) :- H < P, smaller(T,P,R2), R = [H|R2], !.
smaller([H|T], P, R) :- smaller(T,P,R).