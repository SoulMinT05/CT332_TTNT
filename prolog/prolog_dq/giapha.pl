parent('James I', 'Charles I').
parent('James I', 'Elizabeth').

parent('Charles I', 'Catherine').
parent('Charles I', 'Charles II').
parent('Charles I', 'James II').

parent('Elizabeth', 'Sophia').
parent('Sophia', 'Geogre I').

male('James I').
male('Charle I').
male('Charle II').
male('Jame II').
male('Geogre I').

female('Catherine').
female('Elizabeth').
female('Sophia').


mother(M, X) :- parent(M,X), female(M).
father(F,X) :- parent(F,X), male(F).
sibling(X,Y) :- parent(Z,X), parent(Z,Y).
