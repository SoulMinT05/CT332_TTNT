add_list([], L2, L2).    
add_list([X | L1], L2, [X | R]) :- add_list(L1, L2, R).