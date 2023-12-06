tohop(_, 0, 1).
tohop(X, X, 1).
tohop(N, K, X) :- K>0, N>K, K1 is K-1, N1 is N-1, tohop(N1, K, X1),
					tohop(N1, K1, X2), X is X1 + X2.