

count([],_,0). 
count([X|T],X,C):- count(T,X,C1), C is C1+1. 
count([H|T],X,C):- count(T,X,C).
