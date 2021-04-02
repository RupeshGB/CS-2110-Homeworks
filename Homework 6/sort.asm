;;=============================================================
;; CS 2110 - Spring 2021
;; Homework 6 - Bubble Sort with Compare
;;=============================================================
;; Name: Sahit Kavukuntla
;;=============================================================

;; In this file, you must implement the 'SORT' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'sort' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; array: memory address of the first element in the array
;; len: integer value of the number of elements in the array
;; compare: memory address of the subroutine used to compare elements
;;
;; sort(array, len, function compare) {
;;     // last index of the array
;;     y = len - 1;
;;     while(y > 0) {
;;         x = 0;
;;         while(x < y) {
;;             // if compare returns 1, swap
;;             if (compare(ARRAY[x], ARRAY[x+1]) > 0) {
;;                 temp = ARRAY[x];
;;                 ARRAY[x] = ARRAY[x+1];
;;                 ARRAY[x+1] = temp;
;;             }
;;             x++;
;;         }
;;         y--;
;;     }
;; }
;;
;; HINT: compare will be passed as a parameter on the stack. It will be a
;; a pointer to one of the subroutines below. Think about which instruction
;; allows you to call a subroutine with a memory address that is stored in a register

;; pass b to stack then a


SORT

ADD R6, R6, -4
STR R7, R6, 2   ;save return address
STR R5, R6, 1   ;saves old frame pointer
ADD R5, R6, 0   ;position R5 right above oldFP
ADD R6, R6, -6  ;move R6 up to allow space for registers

;;save registers
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
STR R3, R6, 3
STR R4, R6, 4

;LDR R0, R5, 4   ;R0 = compare pointer
LDR R1, R5, 5   ;R1 = len

ADD R3, R1, -1  ;R3 = y = len - 1
WHILE1
ADD R3, R3, 0

BRnz ENDWHILE1

AND R0, R0, 0   ;R0 = x = 0

WHILE2
NOT R2, R3
ADD R2, R2, 1
ADD R2, R2, R0
BRzp ENDWHILE2

;;if statement i think somehow gotta figure this out
;if condition here
LDR R1, R5, 6  ;R1 = compare pointer
ADD R6, R6, -2
LDR R2, R5, 4   ;R2 = array pointer
ADD R2, R2, R0  
LDR R2, R2, 0   ;R2 = ARRAY[X]
STR R2, R6, 0

LDR R2, R5, 4
ADD R2, R2, R0  ;R2 = &ARRAY + x

LDR R4, R2, 1   ;R4 = ARRAY[X+1]
STR R4, R6, 1

JSRR R1
LDR R1, R6, 0
ADD R6, R6, 3
ADD R1, R1, 0
BRnz ENDIF

;do if here, can use R1, R2, R4
LDR R1, R2, 0   ;R1 = ARRAY[x]
STR R1, R5, 0   ;localvar1/temp = ARRAY[x]


LDR R1, R2, 1   ;R1 = ARRAY[x + 1]
STR R1, R2, 0   ;ARRAY[x] = ARRAY[x + 1]

LDR R1, R5, 0   ;R1 = localvar1 = ARRAY[x]_old
STR R1, R2, 1   ;ARRAY[x] = temp

ENDIF
ADD R0, R0, 1   ;x++
BR WHILE2

ENDWHILE2
ADD R3, R3, -1  ;y--
BR WHILE1

ENDWHILE1

;;restore registers
LDR R0, R6, 0
LDR R1, R6, 1
LDR R2, R6, 2
LDR R3, R6, 3
LDR R4, R6, 4

;;restore return address, frame pointer and move R6 to RV
ADD R6, R5, 0
LDR R5, R6, 1
LDR R7, R6, 2
ADD R6, R6, 3
RET

;; used by the autograder
STACK .fill xF000
.end

;; USE FOR DEBUGGING IN COMPLEX
;; load array at x4000 and put the length as 7
;; you can use the memory addresses of the subroutines below for the last parameter

;; ARRAY
.orig x4000
    .fill 4
    .fill -9
    .fill 0
    .fill -2
    .fill 9
    .fill 3
    .fill -10
.end

;; The following subroutines are possible functions that may be passed
;; as the function address parameter into the sorting function.
;; DO NOT edit the code below; it will be used by the autograder.
.orig x5000
;; returns a positive number if a>b
;; compare(a,b) for ascending sort
CMPGT
    .fill   x1DBD
    .fill   x7180
    .fill   x7381
    .fill   x6183
    .fill   x6384
    .fill   x927F
    .fill   x1261
    .fill   x1201
    .fill   x0C03
    .fill   x5020
    .fill   x1021
    .fill   x0E01
    .fill   x5020
    .fill   x7182
    .fill   x6180
    .fill   x6381
    .fill   x1DA2
    .fill   xC1C0
.end

.orig x5100
;; returns a positive number if b>a
;; compare(a,b) for descending sort
CMPLT
    .fill   x1DBD
    .fill   x7180
    .fill   x7381
    .fill   x6183
    .fill   x6384
    .fill   x927F
    .fill   x1261
    .fill   x1201
    .fill   x0603
    .fill   x5020
    .fill   x1021
    .fill   x0E01
    .fill   x5020
    .fill   x7182
    .fill   x6180
    .fill   x6381
    .fill   x1DA2
    .fill   xC1C0
.end

.orig x5200
;; returns a positive number if |a| > |b|
;; compare(a,b) for ascending sort on magnitudes (absolute value)
CMPABS
    .fill   x1DBD
    .fill   x7180
    .fill   x7381
    .fill   x6183
    .fill   x0602
    .fill   x903F
    .fill   x1021
    .fill   x6384
    .fill   x0C02
    .fill   x927F
    .fill   x1261
    .fill   x1240
    .fill   x0C03
    .fill   x5020
    .fill   x1021
    .fill   x0E01
    .fill   x5020
    .fill   x7182
    .fill   x6180
    .fill   x6381
    .fill   x1DA2
    .fill   xC1C0
.end
