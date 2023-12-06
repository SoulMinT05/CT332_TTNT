men(john).
men(fred).
men(harry).
women(mary).
women(julie).
women(susan).
women(anne).
blonde(john).
blonde(julie).
blonde(susan).
dark(fred).
dark(harry).
brunette(mary).
brunette(anne).
gold(X) :- rich(X).
rich(fred).
rich(julie).
thich_sub(X, Y) :- men(X), women(Y).
thich_sub(X, Y) :- women(X), men(Y).
thich(john, X) :- thich_sub(john, X), rich(X), blonde(X).
thich(harry, X) :- thich_sub(harry, X), rich(X).
thich(fred, X) :- thich_sub(fred, X), brunette(X).
thich(mary, X) :- thich_sub(mary, X), dark(X).
thich(julie, X) :- thich_sub(julie, X), dark(X), rich(X).
has(anne, house).
has(john, car).
thichlannhau(X, Y) :- thich(X, Y), thich(Y, X).