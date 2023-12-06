nguoi(marcus).
pompeian(marcus).
# lama(pompeian(X)).
lama(X) :- pompeian(X).
ruler(caesar).
amsat(X, Y) :- lama(X), ruler(Y), noloyalto(X, Y).
noloyalto(marcus, caesar).
