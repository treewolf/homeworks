; uncomment language module if running in racket
;#lang scheme

; homework 2

(begin

	; 1.
	; a, b,c - positive integers
	; return integer made of:
	;	last two digit of first
	;	first and last digit of second
	;	first two digit of third
	(define (combine3 a b c)
		(if (and (>= (isValid a 0) 2) (>= (isValid b 0) 2) (>= (isValid c 0) 2) )
			(+ (* (+ (* (+ (* (lastTwo a) 10) (firstDigit b)) 10) (lastDigit b)) 100) (firstTwo c))
			0	
		)
	)
	
	; x - integer. Assumes thorugh caller method that input is valid
	; return first two digits
	(define (firstTwo x)
                (if (>= x 100)
                        (firstTwo (- (quotient x 10) (quotient (modulo x 10) 10)))
                        x
                )
        )

	; x - integer. Assumes through caller method that input is valid
	; returns last two digits
	(define (lastTwo x)
		(if (>= x 100)
			(lastTwo (modulo x 100))
                        x
                )
        )

	; x - integer
	; return last digit of integer
	(define (lastDigit x)
		(if (>= x 10)
			(lastDigit (modulo x 10))
			x
		)
	)

	; x - integer
	; return first digit of integer
	(define (firstDigit x)
		(if (>= x 10)
			(firstDigit (- (quotient x 10) (quotient (modulo x 10) 10)))
			x
		)	
	)

	; x - count of digits, initialize with 0
	; returns number of digits
	(define (isValid n x)
		(cond
			((null? n) x)
			((< n 10) (+ x 1))
			(else (isValid (quotient n 10) (+ x 1)))
		)
	)

	; 2.
	; x - integer
	; d - digit
	; return each digit in integer added by digit, or mod 10
	(define (inc-by-n x d)
		(inc x d (len x 0) 0 0)
	)

	; x - integer
	; d - digit
	; lo - original length, set in calling function
	; lp - placement of current digit
	; t - total number, always start as 0
	; returns fully modified number
	(define (inc x d lo lp t)
		(if (= lo lp)
			t
			(inc (quotient x 10) d lo (+ 1 lp) (+ (* (modulo (+ d (modulo x 10)) 10) (powerTen 1 lp)) t))
		) 
	)

	; x - integer
	; n - always start as 0
	; returns number of digits of an integer
	(define (len x n)
		(if (< x 1) n (len (quotient x 10) (+ n 1)))
	)

	; x - integer
	; p - the given power of
	; will add p-1 0's to end
	; returns power of 10 : x * 10^p
	(define (powerTen x p)
		(if (= p 0) x (powerTen (* x 10) (- p 1)))
	)	

	; 3.
	; L - list of integers
	; n - integer
	; return count of n inside of list
	(define (countnumber L n)
		(if (null? L)
			0
			(if (not (list? L))
				(if (= L n) 1 0)
				(+ (countnumber (car L) n) (countnumber (cdr L) n))
			)
		)
	)

	; 4.
	; f - function
	; L - list of arguments
	; return function given the arguments of every other, starting with second
	(define (mapeven f L)
		(cond
			((null? L) '())
			((list? L)
				(cons
					(car L)
					(cons
						(f (car (cdr L)))
						(mapeven f (cdr (cdr L)))
					)
					
				)
			)
		)
	)

	; helper example for mapeven
	(define (square x) (* x x))

	; 5.
	; L - list of integers
	; returns sum of all squares 
	(define (addTheSquares L)
		(if (null? L)
			0
			(+ (* (car L) (car L)) (addTheSquares (cdr L)))
		)
	)

	; 6.
	; L - list of elements
	; x - element to append
	; return list of a function with integer after each element
	(define (makeInsertInList x)
		(lambda (L)
			(inThis L x)
		)
	) 

	; aux for makeinsertinlist
	; L - list
	; x - element
	; return list of function with integer after each element	
	(define (inThis L x)
		(if (null? L) '()
			(append (cons (car L) (list x)) (inThis (cdr L) x))
		)
	)
	
)
