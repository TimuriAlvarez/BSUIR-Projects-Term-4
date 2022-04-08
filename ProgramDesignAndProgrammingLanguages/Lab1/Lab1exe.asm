; Lab 1 (EXE)
	.model	small				; Small model supports one data segment and one code segment. 
	.stack	100h				; stack 100h reserves 100h bytes for stack. org 100h sets the current address to 100h,
								; that is the address the assembler is assuming

	.code						; The .CODE directive in your program instructs the assembler to start a code segment.
start:
	mov	AX,	DGROUP				; Copies the value of DGROUP into the AX register
	mov	DS,	AX					; Copies the value from AX register into the DS register

	lea	DX,	message				; Puts the offset of message into the DX register
	mov	AH,	09h					; Copies the value 9 into the AH register
	int	21h						; Generates a software interrupt 21h - output the string

	mov	AX,	4C00h				; Copies the value 4C00h into the AH register
	int	21h						; Generates a software interrupt 21h - exit from the programm

	.data						; The .CODE directive in your program instructs the assembler to start a data segment.
message	db	"Hello World!", 0Dh, 0Ah, '$'		; Message db = BYTE
	end start					; The END directive at the end of your program closes remaining segments.
