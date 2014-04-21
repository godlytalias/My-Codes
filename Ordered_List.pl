Copyright (c) 2014 Godly T.Alias

ordered_list([X|T]) :- check([X|T]),ordered_list(T).

ordered_list([]).

check([]).

check([A]).

check([A,B|T]) :- A<B.
