; Lab4

; use in/out
; not int 21.h 10h or 16h

; Interface:
; Video Memory

; B800:0000 - char
; B800:0001 - attributes
	send ES, B800h ; mov command won't work use AX
	mov  DS, 0000h
	send ES, B800h ; mov command won't work use AX
	mov  DS, FFFFh
; Clear the screen and set graphical mode
	mov AL, 3h
	int 10h

; N of variants = 8 my variant := 1

; Use timer (int) or from Lab4
; interruption handler must be as small as it possible
; should be handeled quiqly

; common parts with other labs
; After the exit - restore all vectors
