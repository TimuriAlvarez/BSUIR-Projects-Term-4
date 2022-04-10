; Lab 2
	.model small
	.stack 100h
	.386

; Macro declarations
	BUF_SIZE	EQU	200			; Size of the string buffer
	CR			EQU	0Dh			; Carrige return character
	NL			EQU 0Ah			; New line charecter
	NUL			EQU 00h			; Null character
	BCKSPC		EQU	08h			; Backspace character
	SPC			EQU	' '			; Space character
	ENDL		EQU	CR, NL		; End of line: "\r\n" characters
; Advanced macros
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
	macro_offset_to_index macro macro_param_string, macro_param_offset
		mov AX, macro_param_offset
		sub AX, offset macro_param_string
		endm
	macro_get_offsets macro macro_param_string, macro_param_basic_offset, macro_param_offset_start, macro_param_offset_end
		macro_string_function_call proc_get_offsets, macro_param_basic_offset
		send macro_param_offset_start, var_temp1
		send macro_param_offset_end, var_temp2

		mov macro_param_basic_offset, macro_param_offset_end
		inc macro_param_basic_offset
		endm
	macro_validation macro macro_param_offset_start, macro_param_validation_fail_label
		push AX SI
		mov SI, macro_param_offset_start
		lodsb
		cmp AL, NUL
		pop SI AX
		je macro_param_validation_fail_label
		endm
	macro_set_di macro
		mov DI, var_offset_string_end
		inc DI
		endm
.data
	; Variables
		var_temp				dw	?
		var_temp1				dw	?
		var_temp2				dw	?
		var_offset_word_start	dw	?
		var_offset_word_end		dw	?
		var_offset_string_start	dw	?
		var_offset_string_end	dw	?
	; Strings
		var_string_string		db	BUF_SIZE+02h	dup(?)
		var_string_word			db	BUF_SIZE+02h	dup(?)
	; Messages
		message_start			db	ENDL, "Process started...", ENDL, NUL
		message_string_enter	db	"Enter the string: ", NUL
		message_string_print	db	"The string: ", NUL
		message_word_enter		db	ENDL, "Enter the word: ", NUL
		message_word_print		db	"The word: ", NUL
		message_result_print	db	ENDL, "The result: ", NUL
		message_end				db	ENDL, "Process ended...", ENDL, NUL
	; Warnings (exceptions)
		warning_string_is_empty	db	ENDL, "The string was not provided! Try again.", ENDL, NUL
		warning_word_is_empty	db	ENDL, "The word was not provided! Try again.", ENDL, NUL
		warning_multiple_words	db	ENDL, "You provided more than one word! Enter the one and only word.", ENDL, NUL
		warning_no_changes		db	ENDL, "No changes can be applied to this string.", ENDL, "Leaving it untouched as it is.", ENDL, NUL
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
						mov AL, SPC
						stosb
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
		; Get offsets (MEMORY -> var_temp1-2) > <
			proc_get_offsets proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX CX DI
				; Load parameters
					mov DI, [BP+04h]
					push DI
					call proc_string_size
					mov CX, var_temp
					inc CX
					mov AL, SPC
				; Procedure
					repe scasb
					dec DI
					mov var_temp1, DI
					repne scasb
					cmp DI, var_temp1
					je proc_get_offsets_skip
					dec DI
					cmp DI, var_temp1
					je proc_get_offsets_skip
					dec DI
					proc_get_offsets_skip:
					mov var_temp2, DI
				; Restore registers
					pop DI CX AX
				; Return
					pop BP
					ret 02h
			proc_get_offsets endp
		; Compare strings (words)
			proc_compare_words proc near
				; Start
				; Save registers
					push AX CX SI DI
				; Load parameters
					mov SI, var_offset_string_start
					mov DI, var_offset_word_start
					mov CX, var_offset_string_end
					sub CX, var_offset_string_start
					inc CX
					inc CX
				; Procedure
					repe cmpsb
				; Restore registers
					pop DI SI CX AX
				; Return
					ret
			proc_compare_words endp
		; Shift the string
			proc_string_shift proc near
				; Start
				; Save registers
					push AX SI DI
				; Load parameters
					mov SI, var_temp1
					mov DI, var_offset_string_start
				; Procedure
					proc_string_shift_loop:
					lodsb
					stosb
					cmp AL, NUL
					jne proc_string_shift_loop
				; Restore registers
					pop DI SI AX
				; Return
					ret
			proc_string_shift endp
	;;
	;; Main Code:
	;;
	start:
		; Move DGROP address to the DS ES
			macro_set_ds
		; Clear Direction Flag
			cld
		; Message start
			macro_string_print message_start
		; Initialize string
			label_initialize_string:
				macro_string_print message_string_enter
				macro_string_scan var_string_string
				macro_string_print message_string_print
				macro_string_print var_string_string
		; Get string's offsets
			mov DI, offset var_string_string
			macro_get_offsets var_string_string, DI, var_offset_string_start, var_offset_string_end
		; Validate string
			macro_validation var_offset_string_start, exception_string_is_empty
		; Save DI in SI
			mov SI, DI
		; Initialize word
			label_initialize_word:
				macro_string_print message_word_enter
				macro_string_scan var_string_word
				macro_string_print message_word_print
				macro_string_print var_string_word
		; Get word's offsets
			mov DI, offset var_string_word
			macro_get_offsets var_string_word, DI, var_offset_word_start, var_offset_word_end
		; Validate word
			macro_validation var_offset_word_start, exception_word_is_empty
		; Get next word in the var_strig_word
		; (must be "\0", because only one word is acceptable in input)
			macro_get_offsets var_string_word, DI, var_temp1, var_temp2
		; Check if "\0"
			macro_validation var_temp1, label_word_is_good
			jmp exception_multiple_words
		; Recover DI from SI
			label_word_is_good:
				mov DI, SI
		; "Infinite" loop
			infinite_loop:
				; Comparing selected words
					call proc_compare_words
					pushf
				; Iteration (move to the next word)
					macro_get_offsets var_string_string, DI, var_offset_string_start, var_offset_string_end
				; Validation (isn't it "\0"?)
					macro_validation var_offset_string_start, exception_no_changes
				; Iterate again
					popf
					jne infinite_loop
		; Skipping spaces untill the next word
			macro_get_offsets var_string_string, DI, var_temp1, var_temp2
		; Shift string
			call proc_string_shift
		; Print  result and quit
			label_main_process_end:
				macro_string_print message_result_print
				macro_string_print var_string_string
				macro_string_print message_end
				macro_return NUL
		;;
		;; Exceptions:
		;;
			exception_word_is_empty:
				macro_string_print warning_word_is_empty
				jmp label_initialize_word
			exception_multiple_words:
				macro_string_print warning_multiple_words
				jmp label_initialize_word
			exception_string_is_empty:
				macro_string_print warning_string_is_empty
				jmp label_initialize_string
			exception_no_changes:
				macro_string_print warning_no_changes
				jmp label_main_process_end
	end start
; End of .code Segment
