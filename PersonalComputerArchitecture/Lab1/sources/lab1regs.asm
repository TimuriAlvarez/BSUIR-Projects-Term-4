; Lab1 - using Registers
	.model	small
	.stack	100h

.code
	start:
		mov	DX,	03F8h
		mov	AL,	'r'
		out	DX,	AL
		mov	AL,	'a'
		mov	DX,	02F8h
		in	AL,	DX
		mov	AH,	2
		mov	DL,	AL
		int	21h
		mov	AX,	4C00h
		int	21h
	end	start
; end .code
