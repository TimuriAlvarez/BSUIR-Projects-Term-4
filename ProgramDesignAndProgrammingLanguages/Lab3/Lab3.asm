; Lab 3
	.model small
	.stack 100h
	.386
; Macro
	ARR_SIZE EQU 5
	; Sender macro
		macro_send macro macro_param_to, macro_param_from
			push AX
			mov AX, macro_param_from
			mov macro_param_to, AX
			pop AX
		endm
	; DS ES configuration macro
		macro_ds_es_config macro
			macro_send DS, DGROUP
			macro_send ES, DGROUP
		endm
;Data
	.data
	var_array_of_numbers		dw ARR_SIZE dup(0)
	var_min						dw ?
	var_max						dw ?
	message_enter_number		db 0Ah,0Dh, "Enter num ", '$'
	message_min_val				db 0Ah,0Dh, "Minimum value: ", '$'
	message_max_val				db 0Ah,0Dh, "Maximum value: ", '$'
	warning_message_overflow	db 0Ah,0Dh, "Overflow detected, number changed to default value (0)", 0Ah,0Dh,'$'
; Functions
	.code
	; Procepure that warns about overflow
		procedure_overflow proc
			mov AH, 09h
			lea DX, warning_message_overflow
			int 21h
			ret
		procedure_overflow endp
	;function to write nums
		procedure_get_number proc
			xor DI,DI
			xor ax,ax		 ;
			xor BX,BX		 ;		 clearing
			xor CX,CX		 ;
			mov BX,10		 ;use for dividing by 10
			StartLoopEnter:
				mov AH,1
				int 21h
				xor AH,AH
				;checker 'enter' and letters+
				cmp al,0Dh
				je OutFunWrite
				cmp al,'-'
				je MinusTrue
				cmp al, '0'
				jl OutFunWrite
				cmp al,'9'
				jg OutFunWrite
				jmp ContLoopEnter
				MinusTrue:
				cmp DX,1	;if minus was already written we leave function as letter error
				je RetFunWrite
				mov DX,1	;otherwise we set flag to make number negative in future
				jmp StartLoopEnter
				ContLoopEnter:
				;checker 'enter' and letters-
					;additional check of overflow
					cmp DI,4
					jne ContinueAddingNum
					sub al,30h
					cmp DX,1
					je NegativeChecker
					cmp al,7
					jg CallBuffOverflow
					add al,30h
					jmp ContinueAddingNum
					NegativeChecker:
					cmp al,8
					jg CallBuffOverflow
					add al,30h
					jmp ContinueAddingNum
				ContinueAddingNum:
				xchg ax,CX	 ;because mul command multiply number in ax, we swap two atributes
				push DX	 ;remember number in DX (negative flag)
				imul BX	 ;multiply by 10 (actually there is no need in imul, we could use just mul)
				pop DX		 ;returning negative flag
				jo	 CallBuffOverflow
				xchg ax,CX	 ;returning normal number in CX
				sub al,30h	 
				add CX,ax		 ;adding number to CX
				inc DI
				jmp StartLoopEnter
			OutFunWrite:
				cmp DX,1		;if negative flag was set
				jne RetFunWrite
				xor DX,DX
				neg CX			 ;we make negative num
			RetFunWrite:
				ret
			CallBuffOverflow:
				call procedure_overflow
				mov CX,0
				ret
		procedure_get_number endp
	;output num located in CX
		procedure_print_number proc
			cmp CX,0		;for 0 in CX we have alternative way to output	
			je OutputZero
			xor BX,BX		 ;
			mov ax,CX		 ;		 clearing mess
			xor CX,CX		 ;
			StartDivOutput:
			cmp ax,0	;if FOR SOME REASON in ax will be 0, we should leave
			je OutFunOutput
			xor DX,DX		 ;we also FOR SOME F*****G reason should clear DX befor div
			mov BX,10		 ;divide by 10
			div BX
			add DX,30h	 ;make it become a letter
			push DX	 ;remember what num we've got
			inc CX		 ;increasing number of nums that we should get from stack
			jmp StartDivOutput
			;simple output nums
			OutFunOutput:
				mov AH,2
				pop DX
				int 21h
			loop OutFunOutput
				ret
			OutputZero:
				mov AH,2
				mov DX,CX
				add DX,30h
				int 21h
				ret
		procedure_print_number endp
	; Print char (DL -> stdout) >DL<
		proc_char_print proc near
			; Start
				push AX
				mov AH, 02h
				int 21h
				pop AX
			; Return
				ret
			proc_char_print endp
	; Print number (CX -> stdout) > <
		proc_number_print proc near
			; Start
			; Save registers
				push AX BX CX DX
			; Load parameters
				mov AX, CX
				mov BL, 10
				xor CX, CX
			; Procedure
				cmp AX, 00h
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
					xor AH, AH
					cmp AL, 00h
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
				ret
			proc_number_print endp
; Main function
	start:
		; DS ES
			macro_ds_es_config
		; Clear DI, SI
			mov SI, 0
			mov DI, 1
		;++++++++++++++++++++++Enter array++++++++++++++++++++++++
		loop_enter_array:
			mov AH, 09h
			lea DX, message_enter_number
			int 21h

			mov CX, DI
			call procedure_print_number

			mov DX, ':'
			int 21h

			mov DX, 32
			int 21h

			push DI
			call procedure_get_number
			pop DI
			
			mov var_array_of_numbers[SI],CX
			inc SI
			inc SI
			inc DI
			
			cmp DI,ARR_SIZE
			jle loop_enter_array
		;----------------------Enter array------------------------
		;+++++++++++++++++++++++Logic+++++++++++++++++++++++++++++
			xor SI, SI
			xor DI, DI
			mov DX, var_array_of_numbers[00h]
			mov var_min, DX
			mov var_max, DX
			label_min_max_seek:
				cmp DI, ARR_SIZE
				je label_main_procedure_end
				mov DX, var_array_of_numbers[SI]
				inc SI
				inc SI
				inc DI
				cmp DX, var_min
				jl label_update_min
				label_update_min_return:
				cmp DX, var_max
				jg label_update_max
				label_update_max_return:
				jmp label_min_max_seek
			label_update_min:
				mov var_min, DX
				jmp label_update_min_return
			label_update_max:
				mov var_max, DX
				jmp label_update_max_return
		;-----------------------Logic-----------------------------
	label_main_procedure_end:
		mov AH, 09h
		lea DX, message_min_val
		int 21h
		mov CX, var_min
		call proc_number_print

		mov AH, 09h
		lea DX, message_max_val
		int 21h
		mov CX, var_max
		call proc_number_print

		mov ax, 4C00h
		int 21h
	end start
;End of main function
