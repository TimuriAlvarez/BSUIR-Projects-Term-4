; Lab 1 (COM)
	.model	tiny				; Tiny-model programs run only under MS-DOS.
								; Tiny model places all data and code in a single segment.
								; Therefore, the total program file size can occupy no more than 64K. 

	.code						; The .CODE directive in your program instructs the assembler to start a code segment.
	org	100h					; В MS DOS при запуске com файла первые 100H байт перед запущенным кодом резервируется под
								; управляющие структуры. Потому вся адресация внутри кода должна начинаться со смещением
								; 100H байт. Директива org 100H как раз и говорит компилятору что всю адресацию внутри кода
								; нужно сместить именно на эти 100H байт.
start:
	mov	AH,	09h					; Copies the value 9 into the AH register
	lea	DX,	message				; Puts the offset of message into the DX register
	int	21h						; Generates a software interrupt 21h - output the string
	ret							; Returns from the Procedure

message	db	"Hello World!", 0Dh, 0Ah, '$'
	end start					; The END directive at the end of your program closes remaining segments.
