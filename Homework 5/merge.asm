;;=============================================================
;; CS 2110 - Spring 2020
;; Homework 5 - Array Merge
;;=============================================================
;; Name: Sahit Kavukuntla
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; x = 0;
;; y = 0;
;; z = 0;
;; while (x < LENGTH_X && y < LENGTH_Y) {
;;   if (ARR_X[x] <= ARR_Y[y]) {
;;     ARR_RES[z] = ARR_X[x];
;;     z++;
;;     x++;
;;   } else {
;;     ARR_RES[z] = ARR_Y[y];
;;     z++;
;;     y++;
;;   }
;; }
;; while(x < ARRX.length) {
;;   ARR_RES[z] = ARR_X[x];
;;   z++;
;;   x++;
;; }
;; while (y < ARRY.length) {
;;   ARR_RES[z] = ARR_Y[y];
;;   z++;
;;   y++;
;; }

;; ld, add, ldr


.orig x3000

;; put your code here

AND R0, R0, #0 ; R0 = x = 0
AND R1, R1, #0 ; R1 = y = 0
AND R2, R2, #0 ; R2 = z = 0

WHILE1


; set ARR_X[x]
LD R7, ARR_X ; R7 = x4000
ADD R3, R7, R0 ; R3 = address of ARR_X[x]
LDR R3, R3, #0 ; R3 = ARR_X[x]

; set ARR_Y[y]
LD R7, ARR_Y ; R7 = x4100
ADD R4, R7, R1 ; R4 = address of ARR_Y[y]
LDR R4, R4, #0 ; R4 = ARR_Y[y]

; check x < LENGTH_X
LD R7, LENGTH_X ; R7 = LENGTH_X
NOT R7, R7
ADD R7, R7, #1 ; R7 = -R7
ADD R5, R0, R7 ; R5 = x - LENGTH_X
	BRzp ENDWHILE1

; check y < LENGTH_Y
LD R7, LENGTH_Y ; R7 = LENGTH_Y
NOT R7, R7
ADD R7, R7, #1 ; R7 = -R7
ADD R6, R1, R7 ; R6 = y - LENGTH_Y
	BRzp ENDWHILE1

NOT R5, R4
ADD R5, R5, #1
ADD R5, R3, R5 ; R5 = ARR_X[x] - ARR_Y[y]

LD R7, ARR_RES ; R7 = x4200
ADD R7, R7, R2 ; R7 = address of ARR_RES[z]
LDR R6, R7, #0 ; R6 = ARR_RES[z]

ADD R5, R5, #0 ; set cc for ARR_X[x] <= ARR_Y[y]
BRp ELSE

STR R3, R7, #0 ; ARR_RES[z] = ARR_X[x]
ADD R2, R2, #1 ; z++
ADD R0, R0, #1 ; x++

BRnzp ENDIF
ELSE

STR R4, R7, #0 ; ARR_RES[z] = ARR_Y[y]
ADD R2, R2, #1 ; z++
ADD R1, R1, #1 ; y++

ENDIF

BRnzp WHILE1
ENDWHILE1 ; line 23 of pseudocode

LD R7, LENGTH_X ; R7 = LENGTH_X
NOT R7, R7
ADD R7, R7, #1 ; R7 = -R7
ADD R5, R0, R7 ; R5 = x - LENGTH_X

WHILE2
	ADD R5, R5, #0 ; SET CC FOR x < LENGTH_X
	BRzp ENDWHILE2

	LD R7, ARR_X ; R7 = x4000
	ADD R3, R7, R0 ; R3 = address of ARR_X[x]
	LDR R3, R3, #0 ; R3 = ARR_X[x]

	LD R7, ARR_RES ; R7 = x4200
	ADD R7, R7, R2 ; R7 = address of ARR_RES[z]
	LDR R6, R7, #0 ; R6 = ARR_RES[z]

	STR R3, R7, #0 ; ARR_RES[z] = ARR_X[x]
	ADD R2, R2, #1 ; z++
	ADD R0, R0, #1 ; x++

	LD R7, LENGTH_X ; R7 = LENGTH_X
	NOT R7, R7
	ADD R7, R7, #1 ; R7 = -R7
	ADD R5, R0, R7 ; R5 = x - LENGTH_X

	BRnzp WHILE2
ENDWHILE2


WHILE3
	LD R7, LENGTH_Y ; R7 = LENGTH_Y
	NOT R7, R7
	ADD R7, R7, #1 ; R7 = -R7
	ADD R6, R1, R7 ; R6 = y - LENGTH_Y
	BRzp ENDWHILE3

	LD R7, ARR_Y ; R7 = x4100
	ADD R4, R7, R1 ; R4 = address of ARR_Y[y]
	LDR R4, R4, #0 ; R4 = ARR_Y[y]

	LD R7, ARR_RES ; R7 = x4200
	ADD R7, R7, R2 ; R7 = address of ARR_RES[z]
	LDR R6, R7, #0 ; R6 = ARR_RES[z]

	STR R4, R7, #0 ; ARR_RES[z] = ARR_Y[y]
	ADD R2, R2, #1 ; z++
	ADD R1, R1, #1 ; y++

	BRnzp WHILE3
ENDWHILE3


HALT

ARR_X      .fill x4000
ARR_Y      .fill x4100
ARR_RES    .fill x4200

LENGTH_X   .fill 5
LENGTH_Y   .fill 7
LENGTH_RES .fill 12

.end

.orig x4000
.fill 1
.fill 5
.fill 10
.fill 11
.fill 12
.end

.orig x4100
.fill 3
.fill 4
.fill 6
.fill 9
.fill 15
.fill 16
.fill 17
.end