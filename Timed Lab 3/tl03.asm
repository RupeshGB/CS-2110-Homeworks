;; Timed Lab 3
;; Student Name: Sahit Kavukuntlaclear


;; Please read the PDF for full directions.
;; The pseudocode for the program you must implement is listed below; it is also listed in the PDF.
;; If there are any discrepancies between the PDF's pseudocode and the pseudocode below, notify a TA on Piazza quickly.
;; However, in the end, the pseudocode is just an example of a program that would fulfill the requirements specified in the PDF.

;; Pseudocode:
;;
;; ABS(x) {
;;     if (x < 0) {
;;         return -x;
;;     } else {
;;         return x;
;;     }
;; }
;;
;;
;;
;; POW3(x) {
;;     if (x == 0) {
;;         return 1;
;;     } else {
;;         return 3 * POW3(x - 1);
;;     }
;; }
;;
;;
;; MAP(array, length) {
;;     i = 0;
;;     while (i < length) {
;;         element = arr[i];
;;         if (i & 1 == 0) {
;;             result = ABS(element);
;;         } else {
;;             result = POW3(element);
;;         }
;;         arr[i] = result;
;;         i++;
;;     }
;; }

.orig x3000
HALT

STACK .fill xF000

; DO NOT MODIFY ABOVE


; START ABS SUBROUTINE
ABS



ADD R6, R6, -4
STR R7, R6, 2   ;save return address
STR R5, R6, 1   ;saves old frame pointer
ADD R5, R6, 0   ;position R5 right above oldFP
ADD R6, R6, -5  ;move R6 up to allow space for registers

;;save registers
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
STR R3, R6, 3
STR R4, R6, 4

LDR R0, R5, 4   ;R0 = n

BRzp SKIPIF
NOT R0, R0
ADD R0, R0, 1

SKIPIF

STR R0, R5, 3

;;restore registers
LDR R0, R6, 0
LDR R1, R6, 1
LDR R2, R6, 2
LDR R3, R6, 3
LDR R4, R6, 4

;;restore return address, frame pointer and move R6 to RV
ADD R6, R6, 6
LDR R5, R6, 0
LDR R7, R6, 1
ADD R6, R6, 2


RET
; END ABS SUBROUTINE




; START POW3 SUBROUTINE
POW3



ADD R6, R6, -4
STR R7, R6, 2   ;save return address
STR R5, R6, 1   ;saves old frame pointer
ADD R5, R6, 0   ;position R5 right above oldFP
ADD R6, R6, -5  ;move R6 up to allow space for registers

;;save registers
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
STR R3, R6, 3
STR R4, R6, 4

LDR R0, R5, 4   ;R0 = n
BRz RETURN1     ;if  n == 1 return 1

;;call POW3(n-1)
ADD R6, R6, -1
ADD R0, R0, -1
STR R0, R6, 0  ;;pass the parameter for the callee (CALLER BUILDUP)
JSR POW3
LDR R1, R6, 0  ;;return value in R1 (CALLER TEARDOWN)
ADD R6, R6, 2  ;;R6 back to the top of the stack

ADD R0, R1, R1
ADD R0, R0, R1
BR TEARDOWN

RETURN1
AND R0, R0, 0
ADD R0, R0, 1

;;CALLEE TEARDOWN CODE
TEARDOWN
;;save result at return address
STR R0, R5, 3

;;restore registers
LDR R0, R6, 0
LDR R1, R6, 1
LDR R2, R6, 2
LDR R3, R6, 3
LDR R4, R6, 4

;;restore return address, frame pointer and move R6 to RV
ADD R6, R6, 6
LDR R5, R6, 0
LDR R7, R6, 1
ADD R6, R6, 2



RET
; END POW3 SUBROUTINE




; START MAP SUBROUTINE
MAP



ADD R6, R6, -4
STR R7, R6, 2   ;save return address
STR R5, R6, 1   ;saves old frame pointer
ADD R5, R6, 0   ;position R5 right above oldFP
ADD R6, R6, -5  ;move R6 up to allow space for registers

;;save registers
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
STR R3, R6, 3
STR R4, R6, 4


AND R0, R0, 0   ;R0 = i = 0 SAVE

WHILE

LDR R1, R5, 5   ;R1 = length

NOT R1, R1
ADD R1, R1, 1
ADD R1, R0, R1  ;R1 = i - length CAN USE
BRzp ENDWHILE

ADD R6, R6, -1
LDR R2, R5, 4   ;R2 = array pointer
ADD R2, R2, R0  
LDR R2, R2, 0   ;R2 = ARRAY[i] SAVE

AND R1, R0, 1

BRnp ELSE
STR R2, R6, 0  ;;pass the parameter for the callee (CALLER BUILDUP)
JSR ABS
LDR R2, R6, 0  ;;return value in R2 (CALLER TEARDOWN)
ADD R6, R6, 2  ;;R6 back to the top of the stack

BR SKIPELSE

ELSE
STR R2, R6, 0  ;;pass the parameter for the callee (CALLER BUILDUP)
JSR POW3
LDR R2, R6, 0  ;;return value in R2 (CALLER TEARDOWN)
ADD R6, R6, 2  ;;R6 back to the top of the stack

SKIPELSE
LDR R3, R5, 4
ADD R3, R3, R0  ;R2 = &ARRAY + i
STR R2, R3, 0

ADD R0, R0, 1

BR WHILE

ENDWHILE

LDR R0, R6, 0
LDR R1, R6, 1
LDR R2, R6, 2
LDR R3, R6, 3
LDR R4, R6, 4

;;restore return address, frame pointer and move R6 to RV
ADD R6, R6, 6
LDR R5, R6, 0
LDR R7, R6, 1
ADD R6, R6, 2


RET
; END MAP SUBROUTINE


; ARRAY FOR TESTING
ARRAY .fill x4000
.end

.orig x4000
.fill -2
.fill 5
.fill 3
.fill 2
.fill -6
.fill 0
.end
