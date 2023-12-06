list_delete(X,[X|L1], L1).
list_delete(X, [Y|L2], [Y|L1]) :- list_delete(X,L2,L1).
swap([],[]).
swap(L,[X|P]) :- list_delete(X,L,L1),swap(L1,P).