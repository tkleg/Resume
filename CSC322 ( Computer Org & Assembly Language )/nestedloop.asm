; Bob Allen
; Fall 2023
; Playing with nested loops
;   A loop going N times inside a loop going M times
;   executes the inner loop code M*N times.
;   So, we can 'multiply' M*N by just incrementing 
;   a variable inside the nested loops.

M EQU 20
N EQU 7

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ

SECTION .bss
; define uninitialized data here
saveECX:	RESD 1
product:	RESW 1

SECTION .text
global _main
_main:

;;;;  'multiply' M times N through nested loop and increment
	xor ax,ax	;; hold product in ax
	mov ecx,M	;; Outer loop counter is M
outer:
	mov [saveECX],ecx  ;; save outer loop counter
	mov ecx,N	   ;; Inner loop counter is N
inner:
	inc ax		;; This line gets executed M*N times
	loop inner

	mov ecx,[saveECX]	;; restore the outer loop count
	loop outer

	mov [product],ax	;; save the product

lastBreak:

; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
