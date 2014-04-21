Copyright (c) 2014 Godly T.Alias

square(ANS,X) :- ANS is X*X.

mul(ANS,X,Y) :- ANS is X*Y.

sub(ANS,X,Y) :- ANS is X-Y.

pos_discriminant(A,B,C) :- !,square(X,B),mul(Z,A,C),mul(Y,4,Z), K is X-Y, K >= 0.
