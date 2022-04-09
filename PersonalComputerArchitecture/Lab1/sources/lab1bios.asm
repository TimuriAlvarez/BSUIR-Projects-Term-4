; Lab1 - using Bios 14h
	.model	small
	.stack	100h

ENDL	EQU	0Dh, 0Ah, '$'

.data
	writing_error_message	db	"Writing to COM-port error!",	ENDL
	reading_error_message	db	"Reading from COM-port error!",	ENDL
; end .data
.code
	; Print Message from DX Procedure
		message_proc	PROC
			mov	AH,	9h
			int	21h
			ret
		message_proc	ENDP
	; Main Procedure
		start:
			; Set Data Segment Address
				mov	AX,	DGROUP
				mov	DS,	AX
			; Write to COM_0
				mov	DX,	0h			; Port's numberh -> 0h
				mov	AH,	1h			; Communication status (1h -> input)
				mov	AL,	'r'			; Data for port 0h
				int	14h				; calling bios interruption 14h
				; mov	AL,	'a'
			; Errors-Check for Writing
				and AH, 10000000b	; 7th bit error check
				cmp	AH,	10000000b
				je	error_branch0
			; Read from COM_1
				mov	DX,	1h
				mov	AH,	2h
				int	14h
			; Errors-Check for Reading
				cmp	AH,	0h
				jne	error_branch1
			; Nornmal Finish
				mov	AH,	2h
				mov	DL,	AL
				int	21h
				mov	AL,	0h
			; Exit from Main Procedure (end-point)
				exit_poc:
					mov	AH,	4Ch
					int	21h
			; Writing Errors
				error_branch0:
					lea	DX,	writing_error_message
					call	message_proc
					mov	AL,	1h
					jmp	exit_poc
			; Reading Errors
				error_branch1:
					lea	DX,	reading_error_message
					call	message_proc
					mov	AL,	2h
					jmp	exit_poc
		end	start
; end .code
