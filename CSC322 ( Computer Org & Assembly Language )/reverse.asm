; NAME
; Assignment
; Date
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
array1: dd      1,2,3,4,5
len1:   EQU     ($-array1)


array2: dd      -10, -9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9
len2:   EQU     ($-array2)


array3: dd  0,10,20,30,40,50,60,70,80,90
  dd  100,110,120,130,140,150,160,170,180,190
  dd  200,210,220,230,240,250,260,270,280,290
  dd  300,310,320,330,340,350,360,370,380,390
  dd  400,410,420,430,440,450,460,470,480,490,500
len3:   EQU     ($-array3)

SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; parameter passing for reverse
	mov ebx, array1
	mov ecx, len1
	shr ecx, 2 ; divides ecx by 4, each shr divides it by 2
	call rev

	mov ebx, array2
	mov ecx, len2
	shr ecx, 2
	call rev

	mov ebx, array3
	mov ecx, len3
	shr ecx, 2
	call rev

lastBreak:
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h


;;reverse array function is passed ebx pointing to array and ecx having the number of elements in the array
rev:
	pusha
	mov edi, ebx
	mov eax, ecx

	pushLoop:
		push dword[ebx]
		add ebx, 4
	loop pushLoop

	mov ecx, eax
	mov ebx, edi
	
	popLoop:
		pop dword[ebx]
		add ebx, 4
	loop popLoop
		
	popa
ret
