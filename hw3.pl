/*** 1 ***/

append([], L, L).

append([Head | Tail], L2, [Head | L3]) 
	:- append(Tail, L2, L3).

query1a(L, X) :-
	append(_, [_, _, _, _, X, _ | T], L).
	
query1b(L, X) :- 
	append(_, [X, _, _], L).


/*** 2 ***/

/* facts */
enjoys(Person,Object_name).
objectKind(Object_name,Type).


/* rules */
bookReader(Person) :-
	enjoys(Person,A), enjoys(Person,B), enjoys(Person,C), 
	A \= B, B \= C, A \= C,
	objectKind(A,book), objectKind(B,book), objectKind(C,book).


/* automated creation of facts */
enjoys(mary,mrToad).
enjoys(mary,mrBird).
enjoys(mary,mrDog).
enjoys(john,joconda).

objectKind(mrDog,book).
objectKind(mrBird,book).
objectKind(mrToad,book).
objectKind(joconda,painting).

/*** 3 ***/

/* facts */
digit(9). digit(8). digit(7). digit(6). digit(5).
digit(4). digit(3). digit(2). digit(1). digit(0).


/* rules */
crypto(W,A,I,T,L,G,F,S) :-
	digit(W), digit(A), digit(I), digit(T), digit(L), digit(G), digit(F), digit(S),
	W \= 0, A \= 0, G \= 0,
	W \= A, W \= I, W \= T, W \= L, W \= G, W \= F, W \= S,
	A \= I, A \= T, A \= L, A \= G, A \= F, A \= S,
	I \= T, I \= L, I \= G, I \= F, I \= S,
	T \= L, T \= G, T \= F, T \= S,
	L \= G, L \= F, L \= S,
	G \= F, G \= S,
	F \= S,

	WAIT is W*1000 + A*100 + I*10 + T,
	ALL is A*100 + L*10 + L,
	SUM is WAIT + ALL,
	GIFTS is G*10000 + I*1000 + F*100 + T*10 + S,
	SUM = GIFTS.


/*** 4 ***/

/* facts */
rev([], Y, Y).

/* rules */
reverse(X,Z) :- 
	rev(X, [], Z).

rev([A | X], Y, Z) :- 
	rev(X, [A | Y], Z).

/* Trace 

example:
	reverse([a,b,c,d], Z).

	rev([a,b,c,d], [], Z) => rev([b,c,d], [a], Z) => rev([c,d], [b,a], Z) => rev([d], [c,b,a], Z) =>
	rev([], [d,c,b,a], Z) => Z = [d,c,b,a] END 

	reverse takes a list and a result variable. It passes the list and result variable to rev function.
	We set a base fact for rev where the input list is empty.
	As each time the rev function is called, it takes the head of the input list and places it in front of the
	the second list. When there is a blank list in the input, the process stops and returns the saved second list.

*?
