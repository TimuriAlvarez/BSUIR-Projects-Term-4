; Lab 3
	.model small
	.stack 100h
	.386

; Macro declarations
	BUF_SIZE	EQU	200			; Size of the string buffer
	ARR_SIZE	EQU 5			; Size of the array of numbers REPLACE with 30
	CR			EQU	0Dh			; Carrige return character
	NL			EQU 0Ah			; New line charecter
	NUL			EQU 00h			; Null character
	BCKSPC		EQU	08h			; Backspace character
	SPC			EQU	' '			; Space character
	ESCP		EQU 
	MINUS		EQU	'-'			; Minus character
	PLUS		EQU	'+'			; Plus character
	ENDL		EQU	CR, NL		; End of line: "\r\n" characters
; Common macros
	macro_set_ds macro
		mov EAX, DGROUP
		mov DS, EAX
		mov ES, EAX
		endm
	macro_return macro macro_param_code
		mov	AH,	4Ch
		mov AL, macro_param_code
		int	21h
		endm
	macro_string_function_call macro macro_param_function, macro_param_string
		push offset macro_param_string
		call macro_param_function
		endm
	macro_string_print macro macro_param_string
		macro_string_function_call proc_string_print, macro_param_string
		endm
	macro_string_scan macro macro_param_string
		macro_string_function_call proc_string_scan, macro_param_string
		endm
	macro_print_num macro macro_param_message, macro_param_number
		macro_string_print macro_param_message
		push macro_param_number
		call proc_number_print
		endm
	clear macro macro_param_register
		xor macro_param_register, macro_param_register
		endm
	send macro macro_param_destination, macro_param_sourse
		push AX
		mov AX, macro_param_sourse
		mov macro_param_destination, AX
		pop AX
		endm
	;macro_offset_to_index macro macro_param_string, macro_param_offset
		;mov AX, macro_param_offset
		;sub AX, offset macro_param_string
		;endm
; Specific macros
	macro_num_validator macro macro_param_label_validation_failed
		macro_string_function_call proc_num_to_string_validate, var_temp_string
		push AX
		mov AX, var_temp
		cmp AX, 00h
		pop AX
		jne macro_param_label_validation_failed
		endm
.data
	; Variables
		arr_num					dw	ARR_SIZE dup(0)
		var_min					dw	?
		var_max					dw	?
		var_result				dw	?
		var_temp				dw	?
		;var_temp1				dw	?
		;var_temp2				dw	?
		;var_offset_word_start	dw	?
		;var_offset_word_end		dw	?
		;var_offset_string_start	dw	?
		;var_offset_string_end	dw	?
	; Strings
		var_temp_string			db	BUF_SIZE+01h	dup(?)
	; Messages
		message_start			db	ENDL, "Process started...", ENDL, NUL
		message_enter_number	db	"Enter the number: ", NUL
		message_print_number0	db	ENDL, "Array[ ", NUL
		message_print_number1	db	" ]: ", NUL
		
		message_min_number		db	"Min number: ", NUL
		message_max_number		db	"Max number: ", NUL
		message_minmax_number	db	"Max - min = ", NUL
		message_result_print	db	ENDL, "The result: ", NUL
		message_end				db	ENDL, "Process ended...", ENDL, NUL
	; Warnings (exceptions)
		warning_string_is_empty	db	"The input is empty! Try  again: ", NUL
		warning_invalid_char	db	"Invalid character's detected! Try again: ", NUL
		;warning_multiple_words	db	ENDL, "You provided more than one word! Enter the one and only word.", ENDL, NUL
		;warning_no_changes		db	ENDL, "No changes can be applied to this string.", ENDL, "Leaving it untouched as it is.", ENDL, NUL
; End of .data segment

.code
	;;
	;; Common procedures:
	;;
		; Get char (stdin -> AL) >AX<
			proc_char_scan proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
				; Procedure
					mov AH, 01h
					int 21h
				; Restore registers
				; Return
					pop BP
					ret
			proc_char_scan endp
		; Get string (stdin -> MEMORY) > <
			proc_string_scan proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX CX DI
				; Load parameters
					mov DI, [BP+04h]
					mov	CX,	BUF_SIZE
				; Procedure (loop)
					proc_string_scan_loop:
						call proc_char_scan ; >AX<
						;cmp AH, 0Eh
						;je proc_string_scan_backspace
						cmp AL, BCKSPC
						je proc_string_scan_backspace
						cmp AL, CR
						je proc_string_scan_end
						stosb
						loop proc_string_scan_loop
						cmp CX, NUL
						jne proc_string_scan_end
						mov DL, CR
						call proc_char_print
						mov DL, NL
						call proc_char_print
					proc_string_scan_end:
						mov AL, NUL
						stosb
				; Restore registers
					pop DI CX DX AX
				; Return
					pop BP
					ret 02h
				; Carrige return action
					proc_string_scan_backspace:
					cmp CX, BUF_SIZE
					mov DL, SPC
					call proc_char_print
					je proc_string_scan_loop
					dec DI
					inc CX
					mov DL, BCKSPC
					call proc_char_print
					jmp proc_string_scan_loop
			proc_string_scan endp
		; Print char (DL -> stdout) >DL<
			proc_char_print proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX
				; Procedure
					mov AH, 02h
					int 21h
				; Restore registers
					pop AX
				; Return
					pop BP
					ret
			proc_char_print endp
		; Print string (MEMORY -> stdout) > <
			proc_string_print proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX SI
				; Load parameters
					mov SI, [BP+4h]
				; Procedure
					proc_string_print_loop:
					lodsb
					cmp AL, NUL
					je proc_string_print_end
					mov DL, AL
					call proc_char_print
					jmp proc_string_print_loop
				; Restore registers
					proc_string_print_end:
					pop SI DX AX
				; Return
					pop BP
					ret 02h
			proc_string_print endp
		; Size of string (MEMORY -> var_temp) > <
			proc_string_size proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DI
				; Load parameters
					mov DI, [BP+04h]
					mov AL, NUL
				; Procedure
					repne scasb
					sub DI, [BP+04h]
					dec DI
					mov var_temp, DI
				; Restore registers
					pop DI AX
				; Return
					pop BP
					ret 02h
			proc_string_size endp
		; Print number (MEMORY -> stdout) > <
			proc_number_print proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX BX CX DX
				; Load parameters
					mov AX, [BP+04h]
					mov BL, NL
					clear CX
				; Procedure
					cmp AX, NUL
					jge proc_number_print_loop_1 ; is greater or equal 0
					; is negative
					mov DL, '-'
					call proc_char_print
					neg AX
					; now it's positive
					proc_number_print_loop_1:
						div BL
						push AX
						inc CX
						clear AH
						cmp AL, NUL
						jne proc_number_print_loop_1
					proc_number_print_loop_2:
						pop AX
						mov DL, AH
						add DL, '0'
						call proc_char_print
						loop proc_number_print_loop_2
				; Restore registers
					pop DX CX BX AX
				; Return
					pop BP
					ret 02h
			proc_number_print endp
	;;
	;; Specific procedures:
	;;
		; String Validation
			proc_num_to_string_validate proc
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX SI
					clear AX
					clear DX
				; Load parameters
					mov SI, [BP+4h]
					send var_temp 00h
				; Procedure
					; First character
						lodsb
					; Is null
						cmp AL, NUL
						je proc_num_to_string_empty_label
					; Is minus or plus
						cmp AL, MINUS
						je proc_num_to_string_plus_minus_label
						cmp AL, PLUS
						je proc_num_to_string_plus_minus_label
					proc_num_to_string_validate_loop:
						cmp AL, NUL
						je proc_num_to_string_validate_end
						cmp AL, '0'
						jnge proc_num_to_string_invalid_label
						cmp AL, '9'
						jnle proc_num_to_string_invalid_label
						lodsb
						jmp proc_num_to_string_validate_loop
				; Restore registers
					proc_num_to_string_validate_end:
						pop SI DX AX
				; Return
					pop BP
					ret 02h
				; Minus or plus
					proc_num_to_string_plus_minus_label:
					; Second character
						lodsb
					; Is null
						cmp AL, NUL
						je proc_num_to_string_empty_label
					jmp proc_num_to_string_validate_loop
				; Failes
					; Empty
						proc_num_to_string_empty_label:
						macro_string_print warning_string_is_empty
						send var_temp 01h
						jmp proc_num_to_string_validate_end
					; Invalid character
						proc_num_to_string_invalid_label:
							send var_temp 02h
							mov DL, AL
							call proc_char_print
							mov DL, ':'
							call proc_char_print
							macro_string_print warning_invalid_char
							jmp proc_num_to_string_validate_end
			proc_num_to_string_validate endp
		; String -> number (temp_var)
			proc_num_to_string proc
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX SI
				; Load parameters
					mov SI, [BP+4h]
				; Procedure
					mov AX, 1
					mov var_temp, AX
				; Restore registers
						pop SI DX AX
				; Return
					pop BP
					ret 02h
			proc_num_to_string endp
		; Find min
			proc_find_min proc
			proc_find_min endp
		; Find max
			proc_find_max proc
			proc_find_max endp
		; Get result
			proc_get_result proc
			proc_get_result endp
	;;
	;; Main Code:
	;;
	start:
		; Move DGROP address to the DS ES. Clear Direction Flag
			macro_set_ds
			cld
		; Message start
			macro_string_print message_start
		; Number entering
			mov CX, ARR_SIZE
			entering_loop:
				macro_string_print message_enter_number
				macro_string_scan var_temp_string
				macro_num_validator entering_loop
				macro_string_function_call proc_num_to_string, var_temp_string
				mov arr_num[6], 9
				loop entering_loop
		; Array printing:
			mov CX, ARR_SIZE
			clear DI
			printing_loop:
				inc DI
				macro_print_num message_print_number0, DI
				macro_print_num message_print_number1, arr_num[DI]
				loop printing_loop
		; Quit
			label_main_process_end:
				macro_string_print message_end
				macro_return NUL
		;;
		;; Exceptions:
		;;
			;exception_word_is_empty:
				;macro_string_print warning_word_is_empty
				;jmp label_initialize_word
			;exception_multiple_words:
				;macro_string_print warning_multiple_words
				;jmp label_initialize_word
			;exception_string_is_empty:
				;macro_string_print warning_string_is_empty
				;jmp label_initialize_string
			;exception_no_changes:
				;macro_string_print warning_no_changes
				;jmp label_main_process_end
	end start
; End of .code Segment
