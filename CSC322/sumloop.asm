; Bob Allen
; Playing with Loops and summing
; Fall 2023

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
array:	dw	1,2,3,4,5,6,-1,-2,-3,-4,-5,-7


SECTION .bss
; define uninitialized data here
sum:	RESW 1

SECTION .text
global _main
_main:

;;;; Init sum to zero (just a nice first step)
	mov word [sum],0

;;;; Sum the array in ax (first) so zero it out
	xor ax,ax

;;;; Loop ecx times, adding the next array element into ax
	mov ebx,array	;; ebx points to the next element in array
	mov ecx,12	;; ecx is our loop counter (i.e. len of array)

top:
	add  ax,[ebx]	;; add next array element to 'sum'
	add  ebx,2	;; point to the next element in array
	loop top

;;;; Write ax sum into sum variable
	mov [sum],ax

lastBreak:

; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
