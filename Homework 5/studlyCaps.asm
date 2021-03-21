;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Studly Caps!
;;=============================================================
;; Name: Sahit Kavukuntla
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;; string = "TWENTY 1 ten";
;; i = 0;
;; while (string[i] != 0) {
;;   if (i % 2 == 0) {
;;   // should be lowercase
;;     if ('A' <= string[i] <= 'Z') {
;;       string[i] = string[i] | 32;
;;     }
;;   } else {
;;   // should be uppercase
;;     if ('a' <= string[i] <= 'z') {
;;       string[i] = string[i] & ~32;
;;     }
;;   }
;;   i++;
;; }

.orig x3000

AND R0, R0, #0 ; R0 = i = 0
WHILE
	LD R7, STRING ; R7 = x4000
	ADD R1, R0, R7 ; R1 = address of string[i]
	LDR R2, R1, #0 ; R2 = string[i]

	BRz ENDWHILE

	AND R3, R0, #1 ; R3 = i % 2 == 0
	BRnp ELSE
		LD R7, UPPERA
		NOT R7, R7
		ADD R7, R7, #1 ; R7 = -A
		ADD R3, R2, R7 ; R3 = string[i] - A
		BRn SKIPIF1

		LD R7, UPPERZ
		NOT R7, R7
		ADD R7, R7, #1 ; R7 = -Z
		ADD R3, R2, R7 ; R3 = string[i] - Z
		BRp SKIPIF1

			LD R7, NOT32 ; make char lowercase
			NOT R4, R2 ; R4 = ~string[i]
			AND R4, R4, R7 ; R4 = ~string[i] & ~32
			NOT R2, R4 ; R2 = string[i] | 32
			STR R2, R1, #0 
	SKIPIF1
	BRnzp ENDIFELSE
	ELSE
		LD R7, LOWERA
		NOT R7, R7
		ADD R7, R7, #1 ; R7 = -a
		ADD R3, R2, R7 ; R3 = string[i] - a
		BRn SKIPIF2

		LD R7, LOWERZ
		NOT R7, R7
		ADD R7, R7, #1 ; R7 = -z
		ADD R3, R2, R7 ; R3 = string[i] - z
		BRp SKIPIF2

			LD R7, NOT32 ; make char uppercase
			AND R2, R2, R7 ; R2 = string[i] & ~32
			STR R2, R1, #0

		SKIPIF2

	ENDIFELSE

	ADD R0, R0, #1 ; i++

	BRnzp WHILE

ENDWHILE

HALT

NOT32 .fill -33 ;; ~32

UPPERA .fill x41    ;; A in ASCII
UPPERZ .fill x5A	;; Z in ASCII
LOWERA .fill x61	;; a in ASCII
LOWERZ .fill x7A	;; z in ASCII

STRING .fill x4000
.end

.orig x4000
.stringz "TWENTY 1 ten"
.end