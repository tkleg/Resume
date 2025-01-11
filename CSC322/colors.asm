; Bob Allen
; Printing colors
; Fall 2023

SECTION .data
; Clear Screen control characters 
cls	db	1bh, '[2J' 
clsLen	dd $-cls

; Reset console colors
reset 	db	1bh,'[0m'
resetLen dd $-reset

; Set cursor position control characters
pos1	db	1bh, '[' 
row	db	'05'
	db	';'
col	db	'05'
	db	'H'

; Set cursor position control characters
pos2	db	1bh, '[' 
	db	'10'
	db	';'
	db	'10'
	db	'H'

; Set cursor position control characters
pos3	db	1bh, '[' 
	db	'15'
	db	';'
	db	'15'
	db	'H'

; Set cursor position control characters
pos4	db	1bh, '[' 
	db	'20'
	db	';'
	db	'20'
	db	'H'

; Set cursor position control characters
pos5	db	1bh, '[' 
	db	'25'
	db	';'
	db	'25'
	db	'H'

; Some messages with their lengths
msg1    db "No Shave November."
msg1Len dd $-msg1
msg2    db "Eat Chili!!."
msg2Len dd $-msg2
msg3    db "Go Mercer Bears!!!!!!!"
msg3Len dd $-msg3
msg4    db "Trick or Treat?"
msg4Len dd $-msg4

; Color sequences ** NOTE:  all color sequences have a length of 5
colorLen: dd 5

black:	db 1bh, "[30m"  ;;; black foreground
red:	db 1bh, "[31m"  ;;; red foreground
green:	db 1bh, "[32m" 	;;; green foreground
yellow:	db 1bh, "[33m" 	;;; yellow foreground
blue:	db 1bh, "[34m" 	;;; blue foreground
magenta:db 1bh, "[35m" 	;;; magenta foreground
cyan:	db 1bh, "[36m" 	;;; cyan foreground
white:	db 1bh, "[37m" 	;;; white foreground


SECTION .text
global _main
_main:

;;;;;  Print Clear the screen
	mov	eax,4
	mov	ebx,1
	mov 	ecx,cls
	mov	edx,[clsLen]
	int 	80h

;;;;;  Set the cursor to position 1
	mov	eax,4
	mov	ebx,1
	mov	ecx,pos1
	mov	edx,8
	int	80h

;;;   set color to red
	mov	eax,4
	mov	ebx,1
	mov 	ecx,red
	mov	edx,[colorLen]
	int	80h

;;;; 	print first message
	mov	eax,4
	mov	ebx,1
	mov 	ecx,msg1
	mov	edx,[msg1Len]
	int 	80h


;;;;;  Set the cursor to position 2
	mov	eax,4
	mov	ebx,1
	mov	ecx,pos2
	mov	edx,8
	int	80h

;;;   set color to blue
	mov	eax,4
	mov	ebx,1
	mov 	ecx,blue
	mov	edx,[colorLen]
	int	80h

;;;; 	print second message
	mov	eax,4
	mov	ebx,1
	mov 	ecx,msg2
	mov	edx,[msg2Len]
	int 	80h

;;;   set color to green
	mov	eax,4
	mov	ebx,1
	mov 	ecx,green
	mov	edx,[colorLen]
	int	80h


;;;;;  Set the cursor to position 3
	mov	eax,4
	mov	ebx,1
	mov	ecx,pos3
	mov	edx,8
	int	80h

;;;; 	print third  message
	mov	eax,4
	mov	ebx,1
	mov 	ecx,msg3
	mov	edx,[msg3Len]
	int 	80h

;;;   set color to magenta
	mov	eax,4
	mov	ebx,1
	mov 	ecx,magenta
	mov	edx,[colorLen]
	int	80h


;;;;;  Set the cursor to position 4
	mov	eax,4
	mov	ebx,1
	mov	ecx,pos4
	mov	edx,8
	int	80h

;;;; 	print fourth  message
	mov	eax,4
	mov	ebx,1
	mov 	ecx,msg4
	mov	edx,[msg4Len]
	int 	80h


; Normal termination code
	mov eax, 1
	mov ebx, 0
	int 80h
