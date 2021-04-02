;;=============================================================
;; CS 2110 - Spring 2020
;; Homework 6 - Reverse Linked List
;;=============================================================
;; Name: Sahit Kavukuntla
;;============================================================

;; In this file, you must implement the 'reverseLL' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'reverseLL' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; Arguments of reverseLL: Node head
;;
;; reverseLL(Node head) {
;;     // note that a NULL address is the same thing as the value 0
;;     if (head == NULL) {
;;         return NULL;
;;     }
;;     if (head.next == NULL) {
;;         return head;
;;     }
;;     Node tail = head.next;
;;     Node newHead = reverseLL(tail);
;;     tail.next = head;
;;     head.next = NULL;
;;     return newHead;
;; }
reverseLL

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

LDR R0, R5, 4   ; R0 = head = x4000
BRnp SKIPRETURNNULL

AND R0, R0, 0
STR R0, R5, 3
BR TEARDOWN

SKIPRETURNNULL

LDR R1, R0, 0   ; R1 = head.next = x4008
BRnp SKIPRETURNHEAD

STR R0, R5, 3
BR TEARDOWN

SKIPRETURNHEAD

STR R1, R5, 0	;localvar1 = tail = head.next

ADD R6, R6, -1	;allocate space on stack for arg1
STR R1, R6, 0	;store arg1

JSR reverseLL

LDR R3, R6, 0	;R3 = newHead = reverseLL(tail)
ADD R6, R6, 2	;pop rv and arg1

STR R0, R1, 0	;tail.next = head


AND R0, R0, 0
STR R0, R1, 0	;head.next = NULL

STR R3, R5, 3

TEARDOWN
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

;; YOUR CODE HERE

RET

;; used by the autograder
STACK .fill xF000
.end

;; The following is an example of a small linked list that starts at x4000.
;;
;; The first number (offset 0) contains the address of the next node in the
;; linked list, or zero if this is the final node.
;;
;; The second number (offset 1) contains the data of this node.
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill x4010
.fill 12
.end

.orig x4010
.fill 0
.fill -7
.end
