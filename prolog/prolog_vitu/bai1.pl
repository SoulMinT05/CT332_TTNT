#cau a
# thich('Xena', 'wine').
# thich('Keera', 'Keera').
thich('Mary', 'food').
thich('Mary', 'wine').
thich('John', 'wine').
thich('John', 'Mary').

thich('John', X) :- thich('Mary', X). #c

#cau c
# thich('John', X) :- thich('Mary', X).

thich('John', X) :- thich(X, 'wine').
thich('John', X) :- thich(X, X).