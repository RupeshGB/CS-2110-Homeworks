;;=============================================================
;; CS 2110 - Spring 2021
;; Homework 5 - Iterative GCD
;;=============================================================
;; Name: Sahit Kavukuntla
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; a = (argument 1);
;; b = (argument 2);
;; ANSWER = 0;
;;
;; while (a != b) {
;;   if (a > b) {
;;     a = a - b;
;;   } else {
;;     b = b - a;
;;   }
;; }
;; ANSWER = a;


;;  brz for a - b
;;  if else
;; st r to answer

.orig x3000

;; put your code here
LD R0, A ; R0 = A
LD R1, B ; R1 = B
NOT R3, R1
ADD R3, R3, #1 ; R3 = -B
ADD R4, R0, R3 ; R4 = A-B

LOOP ; branch back here
	ADD R4, R4, #0 ; set cc for while
	BRz ENDLOOP
		ADD R4, R4, #0 ; set cc for if
		BRnz ELSE ; if A-B <= 0, skip to else
			NOT R3, R1 
			ADD R3, R3, #1 ; R3 = -B
			ADD R0, R0, R3 ; R0 = A = A-B
		BR ENDIF ; skip else block
		ELSE ; do else
			NOT R3, R0 
			ADD R3, R3, #1 ; R3 = -A
			ADD R1, R1, R3 ; R1 = B = B-A
		ENDIF
		NOT R3, R1
		ADD R3, R3, #1 ; R3 = -B
		ADD R4, R0, R3 ; R4 = A-B
	BR LOOP ; go back to start of loop

ENDLOOP
ST R1, ANSWER ; ANSWER = a

HALT

A .fill 20
B .fill 19

ANSWER .blkw 1

.end

