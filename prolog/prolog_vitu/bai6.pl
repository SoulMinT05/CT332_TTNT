thanhvien(long).
thanhvien(trinh).
thanhvien(hung).
thanhvien(anh).

thanhvien(X) :- cuoi(Y, X), thanhvien(Y).
cuoi(long, trinh).
vo(X, Y) :- cuoi(Y, X).

anhtrai(hung, anh).

hopclbnha(long).
hopclbnha(X) :- cuoi(X, Y), hopclbnha(Y).
hopclbnha(Y) :- cuoi(X, Y), hopclbnha(X).
