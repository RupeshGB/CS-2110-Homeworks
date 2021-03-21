;;=============================================================
;; CS 2110 - Fall 2020
;; Homework 5 - Palindrome
;;=============================================================
;; Name: Sahit Kavukuntla
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; string = "racecar";
;; len = 0;
;;
;; // to find the length of the string
;; while (string[len] != '\0') {
;;   len = len + 1;
;; }
;;
;; // to check whether the string is a palindrome
;; result = 1;
;; i = 0;
;; while (i < length) {
;;   if (string[i] != string[length - i - 1]) {
;;     result = 0;
;;     break;
;;   }
;;   i = i + 1;
;; }

.orig x3000

AND R0, R0, #0 ; R0 = len = 0

WHILE1

	LD R7, STRING ; R7 = x4000
	ADD R1, R0, R7 ; R1 = address of string[len]
	LDR R2, R1, #0 ; R2 = string[len]

	BRz ENDWHILE1

	ADD R0, R0, #1 ; len++

	BRnzp WHILE1

ENDWHILE1

AND R1, R1, #0
ADD R1, R1, #1 ; R1 = result = 1
AND R2, R2, #0 ; R2 = i = 0
WHILE2
	NOT R6, R0
	ADD R7, R6, #1 ; R6 = -length
	ADD R3, R2, R7 ; R3 = i - length

	BRzp ENDWHILE2

	LD R7, STRING
	ADD R7, R7, R2 ; R7 = address of string[i]
	LDR R3, R7, #0 ; R3 = data at string[i]

	NOT R4, R2
	ADD R4, R4, #1 ; R4 = -i

	ADD R5, R0, R4 ; R5 = length - i

	ADD R5, R5, #-1 ; R5 = length - i - 1

	LD R7, STRING
	ADD R7, R5, R7
	LDR R4, R7, #0 ; R4 = string[length - i - 1]

	NOT R4, R4
	ADD R4, R4, #1
	ADD R6, R3, R4 ; (string[i]) - (string[length - i - 1])

	BRz ENDIF

		AND R1, R1, #0
		BRnzp ENDWHILE2

	ENDIF

	ADD R2, R2, #1 ; i++
	BR WHILE2

ENDWHILE2

ST R1, ANSWER

HALT

ANSWER .blkw 1
STRING .fill x4000
.end

.orig x4000
.stringz "racecar"
.end
