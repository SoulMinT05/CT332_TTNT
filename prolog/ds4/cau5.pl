# sum([],[0,0]).
# sum([H|T],[N1,N2]):- sum(T,[N3,N2]), iseven(H), N1 is N3+H.
# sum([H|T],[N1,N2]):- sum(T,[N1,N3]), \+ iseven(H), N2 is N3+H.

sum_odd(L, S) :-
  member(X, L),
  odd(X),
  sum_odd(L', S1),
  S is S1 + X.

sum_odd([], 0).