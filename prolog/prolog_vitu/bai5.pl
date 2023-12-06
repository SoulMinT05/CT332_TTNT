hanhphuc(X) :- kongheo(X), thongminh(X).
thongminh(X) :- docsach(X).
docsach('An'). 
kongheo('An').
soidong(X) :- hanhphuc(X).