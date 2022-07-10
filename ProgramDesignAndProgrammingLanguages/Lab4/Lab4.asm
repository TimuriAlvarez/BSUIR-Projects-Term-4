; Lab 4
	.model small
	.stack 100h
	.386
; [Name] area (template)
	; Declarations
		.const
		;[NAME]		EQU	[HEX_VAL]	; [Description] {Comment position: 37}
	; Constants
		.const
		;[NAME]		d?	...													; [Description] {Comment position: 77}
	; Variables
		.data
		;[NAME]		d?	...													; [Description] {Comment position: 77}
	; Macro
		.const
		; [Description]
			;m_[name] macro mp_[arg1], mp_[arg2], ...
				;...
			;endm
		; {next}
	; Procedures
		.code
		; [Description]
			;p_[name] proc near
				; Start
					;push BP
					;mov BP, SP
				; Save registers
					;push USED_REGS_ALPHA
				; Load parameters
					;mov REG, ARG?_$
					;mov REG, ARG?_$
				; Procedure
					;...
				; Upload results
					;...
				; Restore registers
					;pop USED_REGS_REVERSED
				; Return
					;pop BP
					;ret ARG$
			;p_[name] endp
		; {next}
; Common area
	; Declarations
		.const
		CR			EQU	0Dh			; Carrige return character
		NL			EQU	0Ah			; New line charecter
		NUL			EQU	00h			; Null character
		BCKSPC		EQU	08h			; Backspace character
		SPC			EQU	20h			; Space character
		SCP			EQU	1Bh			; Escape character
		TAB			EQU	09h			; Tab character
	; Constants
		.const
	; Variables
		.data
	; Macro
		.const
		; Initialize registers
			m_init_regs macro
				mov AX, DGROUP
				mov DS, AX
				mov ES, AX
			endm
		; Initialize flags
			m_init_flag macro
				cli
			endm
		; Initialize before main
			m_init macro
				m_init_regs
				m_init_flag
			endm
		; Return from main procedure
			m_return macro mp_code
				mov	AH,	4Ch
				mov AL, mp_code
				int	21h
			endm
		; Clear register
			m_clear macro mp_register
				xor mp_register, mp_register
			endm
		; Send data from one place to another
			m_send macro mp_to, mp_from
				push AX
				mov AX, mp_from
				mov mp_to, AX
				pop AX
			endm
		; Call any procedure with 1 stack argument represented as an offset
			m_call_proc macro mp_proc, mp_arg
				push offset mp_arg
				call mp_proc
			endm
		; From to loop
			m_from_to_loop macro mp_loop_name, mp_from, mp_to, mp_index
				mov mp_index, mp_from
				mov CX, mp_to
				sub CX, mp_index
				inc CX
				dec mp_index
				mp_loop_name:
					inc mp_index
			endm
		; To from loop (reversed)
			m_to_from_loop macro mp_loop_name, mp_to, mp_from, mp_index
				mov mp_index, mp_to
				mov CX, mp_index
				sub CX, mp_from
				inc CX
				inc mp_index
				mp_loop_name:
					dec mp_index
			endm
		; Switch-case construction
			; Swich part
				m_switch macro mp_value
					SWITCH_VALUE EQU mp_value
				endm
			; Case part
				m_case macro mp_value, mp_label
					cmp SWITCH_VALUE, mp_value
					je mp_label
				endm
			; Default case part
				m_default_case macro mp_label
					jmp mp_label
				endm
	; Procedures
		.code
; Strings area
	; Declarations
		.const
		ARG1		EQU	02h			; 'Ret' value for		1 procedure argument
		ARG1_1		EQU	[BP+04h]	; Procedure argument		1 out of 1 value
		ARG2		EQU	04h			; 'Ret' value for		2 procedure arguments
		ARG1_2		EQU	[BP+06h]	; Procedure argument		1 out of 2 value
		ARG2_2		EQU	[BP+04h]	; Procedure argument		2 out of 2 value
		ARG3		EQU	06h			; 'Ret' value for		3 procedure arguments
		ARG1_3		EQU	[BP+08h]	; Procedure argument		1 out of 3 value
		ARG2_3		EQU	[BP+06h]	; Procedure argument		2 out of 3 value
		ARG3_3		EQU	[BP+04h]	; Procedure argument		3 out of 3 value
		ENDL		EQU	CR, NL		; 'Enter' key equivalent: "\r\n" characters
	; Constants
		.const
		cs_start	db	"Programm has started...", ENDL, NUL				; Start message
		cs_end		db	"Programm has ended...", ENDL, NUL					; End message
	; Variables
		.data
		vi_temp_4_s	dw	?													; Temp word for strings' procedures
		vs_bufsize	dw	256													; Very important hidden procedures' parameter!
																			; It shold be equal to size of string buffer - 1 (for NUL character).
		;
	; Macro
		; Print char
			m_print_c macro mp_arg
				push mp_arg
				call p_print_c
			endm
		; Print string
			m_print_s macro mp_arg
				m_call_proc p_print_s, mp_arg
			endm
		; Print int
			m_print_i macro mp_arg
				m_call_proc p_print_i, mp_arg
			endm
		; Get size of string (to vi_temp_4_s)
			m_size_s macro mp_arg
				m_call_proc p_size_s, mp_arg
			endm
		; Get char
			m_get_c macro mp_arg
				call p_get_c
				mov mp_arg, vi_temp_4_s
			endm
		; Get string
			m_get_s macro pm_str, pm_size
				mov vs_bufsize, pm_size
				m_call_proc p_get_s, pm_str
			endm
		; Get int
			m_get_i macro mp_arg
				m_call_proc p_get_i, mp_arg
			endm
	; Procedures
		.code
		; Print char
			p_print_c proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX
				; Load parameters
					mov DX, ARG1_1
				; Procedure
					mov AH, 02h
					int 21h
				; Restore registers
					pop DX AX
				; Return
					pop BP
					ret ARG1
			p_print_c endp
		; Print string
			p_print_s proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX SI
				; Load parameters
					mov SI, ARG1_1
				; Procedure
					l_print_c_loop:
						lodsb
						cmp AL, NUL
						je l_print_s_end
						m_print_c AX
						jmp l_print_c_loop
				; Restore registers
					l_print_s_end:
					pop SI DX AX
				; Return
					pop BP
					ret ARG1
			p_print_s endp
		; Print int
			p_print_i proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX BX CX DX
				; Load parameters
					mov AX, ARG1_1
					mov BL, NL
					m_clear CX
				; Procedure
					cmp AX, NUL
					jge l_print_i_pushing_loop ; is greater or equal 0
					; is negative
					mov DL, '-'
					m_print_c DX
					neg AX
					; now it's positive
					l_print_i_pushing_loop:
						div BL
						push AX
						inc CX
						m_clear AH
						cmp AL, NUL
						jne l_print_i_pushing_loop
					l_print_i_popping_loop:
						pop AX
						mov DL, AH
						add DL, '0'
						m_print_c DX
						loop l_print_i_popping_loop
				; Restore registers
					pop DX CX BX AX
				; Return
					pop BP
					ret ARG1
			p_print_i endp
		; Get size of string (to vi_temp_4_s)
			p_size_s proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DI
				; Load parameters
					mov DI, ARG1_1
					mov AL, NUL
				; Procedure
					repne scasb
					sub DI, ARG1_1
					dec DI
				; Upload results
					mov vi_temp_4_s, DI
				; Restore registers
					pop DI AX
				; Return
					pop BP
					ret ARG1
			p_size_s endp
		; Get char
			p_get_c proc near
				; Start
				; Save registers
					push AX DX
				; Load parameters
				; Procedure
					mov AH, 01h
					int 21h
				; Upload results
					mov vi_temp_4_s, AX
				; Restore registers
					pop DX AX
				; Return
					ret
			p_get_c endp
		; Get string
			p_get_s proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX CX DI
				; Load parameters
					mov DI, ARG1_1
					mov	CX,	vs_bufsize
				; Procedure
					l_get_s_loop:
						m_get_c AX
						cmp AL, BCKSPC
						je l_get_s_backspace_route
						cmp AL, CR
						je l_get_s_end
						stosb
						loop l_get_s_loop
						cmp CX, NUL
						jne l_get_s_end
						m_print_c CR
						m_print_c NL
					l_get_s_end:
						mov AL, NUL
						stosb
				; Restore registers
					pop DI CX DX AX
				; Return
					pop BP
					ret ARG1
				; Carrige return action
					l_get_s_backspace_route:
					cmp CX, vs_bufsize
					m_print_c SPC
					je l_get_s_loop
					dec DI
					inc CX
					m_print_c BCKSPC
					jmp l_get_s_loop
			p_get_s endp
		; Get int
			p_get_i proc near
				; ???????????????????????????????????????????????????????????????????????????????????????????????????????/
			p_get_i endp
		; Proc...
; Main area
	; Declarations
		.const
		STRSIZE		EQU	0Fh
		VM_ADDR		EQU	0B800h
		; Attributes:
			; Colours
				CLR_BLK	EQU	00h		; Black		colour
				CLR_BLU	EQU	01h		; Blue		colour
				CLR_GRN	EQU	02h		; Green		colour
				CLR_CYA	EQU	03h		; Cyan		colour
				CLR_RED	EQU	04h		; Red		colour
				CLR_PUR	EQU	05h		; Purple	colour
				CLR_BRW	EQU	06h		; Brown		colour
				CLR_GRA	EQU	07h		; Gray		colour
				CLR_BRG	EQU	08h		; Is		bright
				CLR_BLN	EQU	08h		; or		blinking
				CLR_NOT	EQU	00h		; Neither	bright
									; nor		blinking
		; Video modes
			;VM_STN	EQU	00h			; 40*25 черно-белый;
			;VM_STC	EQU	01h			; 40*25 16-цветный (стандартный);
			VM_BW	EQU	02h			; 80*25 черно-белый;
			VM_CL	EQU	03h			; 80*25 16-цветный (стандартный);
			VM_MN	EQU	07h			; 80*25 черно-белый монохромный (стандартный).
		; Box elements ...
			BX_TL	EQU	00C9h		; top angle				left
			BX_TR	EQU	00BBh		; top angle				right
			BX_ML	EQU	00CCh		; middle connector		left 
			BX_MR	EQU	00B9h		; middle connector		right
			BX_TB	EQU	00CBh		; top connector to		bottomn
			BX_BT	EQU	00CAh		; bottomn connector to	top
			BX_BL	EQU	00C8h		; bottomn angle			left
			BX_BR	EQU	00BCh		; bottomn angle			right
			BX_H	EQU	00CDh		; plain line			horizontal
			BX_V	EQU	00BAh		; plain line			vertical
		; Special characters
			SCH_I	EQU	'l'			; Character		'I'		representation
			SCH_XCL	EQU	'!'			; Character		'!'		representation
			SCH_ARU	EQU	001Eh		; Arrow up		'^'		representation
			SCH_ARD	EQU	001Fh		; Arrow down	'v'		representation
			SCH_ARL	EQU	0011h		; Arrow left	'<'		representation
			SCH_ARR	EQU	0010h		; Arrow right	'>'		representation
			SCH_QOP	EQU	00B5h		; Quotation		open	representation
			SCH_QCL	EQU	00C6h		; Quotation		close	representation
		; Game actions
			A_START	EQU	0000h		; Start	game
			A_QUIT	EQU	0000h		; Quit	game
			A_PAUSE	EQU	0000h		; Pause	game
			A_UP	EQU	0000h		; Move	up
			A_DOWN	EQU	0000h		; Move	down
			A_LEFT	EQU	0000h		; Move	left
			A_RIGHT	EQU	0000h		; Move	right
		; Game conditions
			COND_WA	EQU	1			; Launching (waiting)
			COND_RU	EQU	2			; Running (launched)
			COND_PA	EQU	3			; Paused
			COND_GO	EQU	4			; Game over
	; Constants
		.const
		ci_lim_x_r	dw	79													; Real limit of X-axis
		ci_lim_y_r	dw	24													; Real limit of Y-axis
		ci_lim_x_g	dw	39													; Game limit of X-axis
		ci_lim_y_g	dw	14													; Game limit of Y-axis
		; Messages
			cs_cnt1	db	"~  Welcome to          ~", NUL
			cs_snak	db	"SNAK E", NUL
			cs_cnt2	db	"~   Score:             ~", NUL
			cs_lft1	db	"Move, eat, grow and", NUL
			cs_lft2	db	"try to beat the score.", NUL
			cs_rgh1	db	"The author:", NUL
			cs_rgh2	db	"Thanks to :", NUL
			cs_tmur	db	"T MUR", NUL
			cs_rakx	db	"RA K 99X", NUL
			cs_bt0t	db	"[ENTER]    ", NUL
			cs_bt0b	db	"Start    ", NUL
			cs_bt1t	db	"[SPACE TAB]", NUL
			cs_bt1b	db	"Pause    ", NUL
			cs_bt2t	db	"[", SCH_ARU," W]", NUL
			cs_bt2b	db	"Up", NUL
			cs_bt3t	db	"[", SCH_ARD," S]", NUL
			cs_bt3b	db	"Down", NUL
			cs_bt4t	db	"[", SCH_ARL," A]", NUL
			cs_bt4b	db	"Left", NUL
			cs_bt5t	db	"[", SCH_ARR," D]", NUL
			cs_bt5b	db	"Right", NUL
			cs_bt6t	db	"[ESCAPE Q]", NUL
			cs_bt6b	db	"Quit", NUL
			cs_bt00	db	"Restart ", NUL
			cs_bt11	db	"Continue", NUL
			cs_st_w	db	SCH_QOP, " Status:              ", SCH_QCL, NUL
			cs_st_k	db	SCH_QOP, " Key logger:          ", SCH_QCL, NUL
		; Status
			stat_wa	db	"Waiting... ", NUL
			stat_ru	db	"Running... ", NUL
			stat_pa	db	"Paused.    ", NUL
			stat_go	db	"Game over. ", NUL
			stat_tp	db	"Teleported.", NUL
			stat_ap	db	"+ Apple... ", NUL
			stat_ns	db	"New score! ", NUL
	; Variables
		.data
		vi_loc		dw	?													; Location of character in video memory
		;vi_x_real	dw	?
		;vi_y_real	dw	?
		;vi_x_game	dw	?
		;vi_y_game	dw	?
		; Styles (attributes)
			style_frame	dw	?
			style_simpl	dw	?
			style_title	dw	?
			style_i_stl	dw	?
			style_timur	dw	?
			style_activ	dw	?
			style_blink	dw	?
			style_gmbox	dw	?
			style_snake	dw	?
			style_apple	dw	?
		; Game variables
			vi_key		dw	?
			vi_cond		dw	?
	; Macro
		; Change video mode
			m_vmode macro mp_mode
				push AX
				m_clear AH
				mov AL, mp_mode
				int 10h
				pop AX
			endm
		; Convert coordinates to location
			m_conv_xy2loc macro mp_x, mp_y
				push mp_x
				push mp_y
				call p_conv_xy2loc
			endm
		; Place character with attributes in video memory using location
			m_place_c_by_loc macro mp_char, mp_style, mp_location
				push mp_char
				push mp_style
				push mp_location
				call p_place_c_by_loc
			endm
		; Place character with attributes in video memory using coordinates
			m_place_c_by_xy macro mp_char, mp_style, mp_x, mp_y
				m_conv_xy2loc mp_x, mp_y
				m_place_c_by_loc mp_char, mp_style, vi_loc
			endm
		; Place string with attributes in video memory starting from location
			m_place_s_by_loc macro mp_string, mp_style, mp_location
				push offset mp_string
				push mp_style
				push mp_location
				call p_place_s_by_loc
			endm
		; Place string with attributes in video memory starting from coordinates
			m_place_s_by_xy macro mp_string, mp_style, mp_x, mp_y
				m_conv_xy2loc mp_x, mp_y
				m_place_s_by_loc mp_string, mp_style, vi_loc
			endm
		; Calculate attribute
			m_style_calc macro mp_fg_clr, mp_fg_br, mp_bg_clr, mp_bg_br, mp_attr_loc
				push DX
				mov DX, mp_bg_clr	; Load background colour		(DL)
				or DX, mp_bg_br		; Load background brightness	(DL)
				shl DX, 4
				or DX, mp_fg_clr	; Load foreground colour		(DL)
				or DX, mp_fg_br		; Load foreground brightness	(DL)
				mov mp_attr_loc, DX	; Save attributes
				pop DX
			endm
		; Set status
			m_set_status macro mp_status
				m_place_s_by_xy mp_status, style_simpl,	12,	24
			endm
		; Place character in the game
			m_place_in_game macro mp_char, mp_style, mp_game_x, mp_game_y
				push AX DX
				mov AX, mp_game_x
				mov DL, 02h
				mul DL
				mov DX, mp_game_y
				add DX, 06h
				xor AH, AH
				xor DH, DH
				m_place_c_by_xy mp_char, mp_style, AX, DX
				inc AX
				m_place_c_by_xy mp_char, mp_style, AX, DX
				pop DX AX
			endm
	; Procedures
		.code
		start:
		; Main
			; Start
				m_init
				m_print_s cs_start
			; Load parameters
			; Procedure
				; Set video mode
					m_vmode VM_CL
				; Calculate attributes
					m_style_calc CLR_GRA, CLR_BRG, CLR_BLK, CLR_NOT, style_frame
					m_style_calc CLR_GRA, CLR_NOT, CLR_BLK, CLR_NOT, style_simpl
					m_style_calc CLR_GRN, CLR_NOT, CLR_BLK, CLR_NOT, style_title
					m_style_calc CLR_RED, CLR_NOT, CLR_BLK, CLR_NOT, style_i_stl
					m_style_calc CLR_BRW, CLR_NOT, CLR_BLK, CLR_NOT, style_timur
					m_style_calc CLR_GRA, CLR_BRG, CLR_BLK, CLR_NOT, style_activ
					m_style_calc CLR_GRA, CLR_BRG, CLR_BLK, CLR_BLN, style_blink
					m_style_calc CLR_BLK, CLR_NOT, CLR_BRW, CLR_NOT, style_gmbox
					m_style_calc CLR_BLK, CLR_NOT, CLR_GRN, CLR_NOT, style_snake
					m_style_calc CLR_RED, CLR_BRG, CLR_BLK, CLR_NOT, style_apple
				; Print the frameboox
					; Printing lines macro
						; Print horisontal lines macro
							m_print_horizontal_line macro mp_loop_name, mp_from_x, mp_to_x, mp_const_y
								m_from_to_loop mp_loop_name, mp_from_x, mp_to_x, DI
									m_place_c_by_xy BX_H, style_frame, DI, mp_const_y
								loop mp_loop_name
							endm
						; Print vertical lines macro
							m_print_vertical_line macro mp_loop_name, mp_from_y, mp_to_y, mp_const_x
								m_from_to_loop mp_loop_name, mp_from_y, mp_to_y, DI
									m_place_c_by_xy BX_V, style_frame, mp_const_x, DI
								loop mp_loop_name
							endm
					; Print horisontal lines
						m_print_horizontal_line	l_y__0_loop,	0,	ci_lim_x_r,	0
						m_print_horizontal_line	l_y__5_loop,	0,	ci_lim_x_r,	5
						m_print_horizontal_line	l_y_21_loop,	0,	ci_lim_x_r,	21
						m_print_horizontal_line	l_y_24_loop,	0,	ci_lim_x_r,	24
					; Print vertical lines
						m_print_vertical_line	l_x__0_loop,	0,	ci_lim_y_r,	0
						m_print_vertical_line	l_x_25_loop,	0,	5,			25
						m_print_vertical_line	l_x_54_loop,	0,	5,			54
						m_print_vertical_line	l_x_79_loop,	0,	ci_lim_y_r,	79
					; Print unique characters
						m_place_c_by_xy BX_TL, style_frame,		0,	0
						m_place_c_by_xy BX_TR, style_frame,		79,	0
						m_place_c_by_xy BX_BL, style_frame,		0,	5
						m_place_c_by_xy BX_BR, style_frame,		79,	5
						m_place_c_by_xy BX_TL, style_frame,		0,	21
						m_place_c_by_xy BX_TR, style_frame,		79,	21
						m_place_c_by_xy BX_BL, style_frame,		0,	24
						m_place_c_by_xy BX_BR, style_frame,		79,	24
						m_place_c_by_xy BX_TB, style_frame,		25,	0
						m_place_c_by_xy BX_TB, style_frame,		54,	0
						m_place_c_by_xy BX_BT, style_frame,		25,	5
						m_place_c_by_xy BX_BT, style_frame,		54,	5
				; Print the messages:
					; Central box
						m_place_s_by_xy cs_cnt1, style_simpl	28,	2
						m_place_s_by_xy cs_snak, style_title	42,	2
						m_place_c_by_xy SCH_I,   style_i_stl	46,	2
						m_place_c_by_xy SCH_XCL, style_i_stl	48,	2
						m_place_s_by_xy cs_cnt2, style_simpl	28,	3
					; Left box
						m_place_s_by_xy cs_lft1, style_simpl,	2,	2
						m_place_s_by_xy cs_lft2, style_simpl,	2,	3
					; Right boox
						m_place_s_by_xy cs_rgh1, style_simpl,	57,	2
						m_place_s_by_xy cs_rgh2, style_simpl,	57,	3
						m_place_s_by_xy cs_tmur, style_timur,	69,	2
						m_place_c_by_xy SCH_I,   style_i_stl,	70,	2
						m_place_c_by_xy SCH_I,   style_i_stl,	74,	2
						m_place_s_by_xy cs_rakx, style_title,	69,	3
						m_place_c_by_xy SCH_I,   style_i_stl,	71,	3
						m_place_c_by_xy SCH_I,   style_i_stl,	73,	3
					; Bottomn box
						; Start
							m_place_s_by_xy cs_bt0t, style_activ,	2,	22
							;m_place_c_by_xy '/',    style_simpl,	8,	22
							m_place_s_by_xy cs_bt0b, style_simpl,	2,	23
						; Up
							m_place_s_by_xy cs_bt2t, style_activ,	15,	22
							m_place_c_by_xy '/',     style_simpl,	17,	22
							m_place_s_by_xy cs_bt2b, style_simpl,	15,	23
						; Down
							m_place_s_by_xy cs_bt3t, style_activ,	28,	22
							m_place_c_by_xy '/',     style_simpl,	30,	22
							m_place_s_by_xy cs_bt3b, style_simpl,	28,	23
						; Left
							m_place_s_by_xy cs_bt4t, style_activ,	41,	22
							m_place_c_by_xy '/',     style_simpl,	43,	22
							m_place_s_by_xy cs_bt4b, style_simpl,	41,	23
						; Right
							m_place_s_by_xy cs_bt5t, style_activ,	54,	22
							m_place_c_by_xy '/',     style_simpl,	56,	22
							m_place_s_by_xy cs_bt5b, style_simpl,	54,	23
						; Quit
							m_place_s_by_xy cs_bt6t, style_activ,	67,	22
							m_place_c_by_xy '/',     style_simpl,	74,	22
							m_place_s_by_xy cs_bt6b, style_simpl,	67,	23
					; Status bar
						; Status
							m_place_s_by_xy cs_st_w, style_frame,	2,	24
						; Key
							m_place_s_by_xy cs_st_k, style_frame,	54,	24
				; Print the game:
					; Game box
						; Printing lines macro
							; Print horisontal lines macro
							m_print_horizontal_line macro mp_loop_name, mp_from_x, mp_to_x, mp_const_y
								m_from_to_loop mp_loop_name, mp_from_x, mp_to_x, DI
									m_place_c_by_xy ' ', style_snake, DI, mp_const_y
								loop mp_loop_name
							endm
							; Print vertical lines macro
							m_print_vertical_line macro mp_loop_name, mp_from_y, mp_to_y, mp_const_x
								m_from_to_loop mp_loop_name, mp_from_y, mp_to_y, DI
									m_place_c_by_xy ' ', style_snake, mp_const_x, DI
								loop mp_loop_name
							endm
						; Printing lines
							m_print_horizontal_line	l_y__6_loop,	1,	78,	6
							m_print_horizontal_line	l_y_20_loop,	1,	78,	20
							m_print_vertical_line	l_x__0_loop2,	6,	20,	0
							m_print_vertical_line	l_x__1_loop,	6,	20,	1
							m_print_vertical_line	l_x_78_loop,	6,	20,	78
							m_print_vertical_line	l_x_79_loop2,	6,	20,	79
						; REMOVE BEFORE
						; Printing lines macro
							; Print horisontal lines macro
							m_print_horizontal_line macro mp_loop_name, mp_from_x, mp_to_x, mp_const_y
								m_from_to_loop mp_loop_name, mp_from_x, mp_to_x, DI
									m_place_in_game ' ', style_gmbox, DI, mp_const_y
								loop mp_loop_name
							endm
							; Print vertical lines macro
							m_print_vertical_line macro mp_loop_name, mp_from_y, mp_to_y, mp_const_x
								m_from_to_loop mp_loop_name, mp_from_y, mp_to_y, DI
									m_place_in_game ' ', style_gmbox, mp_const_x, DI
								loop mp_loop_name
							endm
						; Printing lines
							;m_print_horizontal_line	l_game_y__0_loop,	0,	39,	0
							;m_print_horizontal_line	l_game_y_14_loop,	0,	39,	14
							;m_print_vertical_line	l_game_x__0_loop,	0,	14,	0
							;m_print_vertical_line	l_game_x_39_loop,	0,	14,	39
					; Game
				; Launch the game
					; Set starting condition
						mov vi_cond, COND_WA
						m_set_status stat_wa
					; Infinite loop
						l_game_loop:
							; Get key
								call p_get_key
							; Process key (switch-case)
								m_switch vi_key
									cmp vi_cond, COND_RU
									je l_skip_enter
									cmp vi_cond, COND_PA
									je l_skip_enter
								m_case CR, l_enter_label
									l_skip_enter:
									cmp vi_cond, COND_RU
									jne l_skip_pause
								m_case SPC, l_pause_label
								m_case TAB, l_pause_label
									l_skip_pause:
									cmp vi_cond, COND_PA
									jne l_skip_continue
								m_case SPC, l_continue_label
								m_case TAB, l_continue_label
									l_skip_continue:
								m_case SCP, l_pre_esc_label
								m_case 'Q', l_pre_esc_label
								m_case 'q', l_pre_esc_label
									cmp vi_cond, COND_RU
									jne l_skip_controls
								m_case SCH_ARU, l_w_key_label
								m_case 'W', l_w_key_label
								m_case 'w', l_w_key_label
								m_case SCH_ARD, l_w_key_label
								m_case 'S', l_s_key_label
								m_case 's', l_s_key_label
								m_case SCH_ARL, l_w_key_label
								m_case 'A', l_a_key_label
								m_case 'a', l_a_key_label
								m_case SCH_ARD, l_w_key_label
								m_case 'D', l_d_key_label
								m_case 'd', l_d_key_label
									l_skip_controls:
								m_default_case l_game_loop
					; Cases
						; Controls
							l_w_key_label:
							l_s_key_label:
							l_a_key_label:
							l_d_key_label:
								jmp l_game_loop
						; Enter trigger
							l_enter_label:
								mov vi_cond, COND_RU
								m_set_status stat_ru
								; Print "pause"
									m_place_s_by_xy cs_bt1t, style_activ,	2,	22
									m_place_c_by_xy '/',     style_simpl,	8,	22
									m_place_s_by_xy cs_bt1b, style_simpl,	2,	23
								jmp l_game_loop
						; Pause-continue trigger
							l_pause_label:
								mov vi_cond, COND_PA
								m_set_status stat_pa
								; Print "continue"
									m_place_s_by_xy cs_bt1t, style_activ,	2,	22
									m_place_c_by_xy '/',     style_simpl,	8,	22
									m_place_s_by_xy cs_bt11, style_simpl,	2,	23
								jmp l_game_loop
							l_continue_label:
								mov vi_cond, COND_RU
								m_set_status stat_ru
								; Print "pause"
									m_place_s_by_xy cs_bt1t, style_activ,	2,	22
									m_place_c_by_xy '/',     style_simpl,	8,	22
									m_place_s_by_xy cs_bt1b, style_simpl,	2,	23
								jmp l_game_loop
						; Escape trigger
							l_pre_esc_label:
								mov AX, vi_cond
								; Print "restart"
									m_place_s_by_xy cs_bt0t, style_activ,	2,	22
									;m_place_c_by_xy '/',    style_simpl,	8,	22
									m_place_s_by_xy cs_bt00, style_simpl,	2,	23
								mov vi_cond, COND_GO
								m_set_status stat_go
								cmp AX, COND_WA
								je l_quit_label
								cmp AX, COND_GO
								je l_quit_label
								jmp l_game_loop
				; Quit the game
					l_quit_label:
						; Set video mode
							m_vmode VM_CL
						; Return
							m_print_s cs_end
							m_return NUL
		; Convert coordinates to location
			p_conv_xy2loc proc near
					push BP
					mov BP, SP
				; Save registers
					push AX BX DX CX
				; Load parameters
					mov AX, ARG2_2
					mov BX, ARG1_2
				; Procedure
					mov DL, 80
					mul DL
					add AX, BX
					mov DX, 2
					mul DX
				; Upload results
					mov vi_loc, AX
				; Restore registers
					pop CX DX BX AX
				; Return
					pop BP
					ret ARG2
			p_conv_xy2loc endp
		; Coonvert location to coordinates
			p_conv_loc2xy proc near
			p_conv_loc2xy endp
		; Place character with attributes in video memory using location
			p_place_c_by_loc proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push DX DI ES
				; Load parameters
					mov DX, ARG2_3	; Load attribute	(DL)
					mov DH, DL		; Move it to DH		(DH)
					xor DL, DL		; Clear DL			(  )
					or DX,  ARG1_3	; Load character	(DL)
					mov DI, ARG3_3	; Load location		(DI)
				; Procedure (place 'attr + character' in video memory using location)
					push 0B800h
					pop ES
					mov ES:DI, DX
				; Upload results
				; Restore registers
					pop ES DI DX
				; Return
					pop BP
					ret ARG3
			p_place_c_by_loc endp
		; Place string with attributes in video memory starting from location
			p_place_s_by_loc proc near
				; Start
					push BP
					mov BP, SP
				; Save registers
					push AX DX SI DI
				; Load parameters
					mov SI, ARG1_3	; Load string's offset
					mov DI, ARG3_3	; Load video memory location
				; Procedure
					l_place_c_loop:
						lodsb
						cmp AL, NUL
						je l_place_s_end
						m_place_c_by_loc AX, ARG2_3, DI
						add DI, 02h
						jmp l_place_c_loop
				; Restore registers
					l_place_s_end:
					pop DI SI DX AX
				; Return
					pop BP
					ret ARG3
			p_place_s_by_loc endp
		; Get key from the keyboard buffer
			p_get_key proc near
				; Start
				; Save registers
					push AX
				; Load parameters
				; Procedure
					; Check if there is a key available in buffer
						mov AH, 01h
						mov AL, 00h
						int 16h
						m_clear AL
						jnz l_get_key_end
					; Get the key if available
						mov AH, 00h
						mov AL, 00h
						int 16h
				; Upload results
					l_get_key_end:
						m_clear AH
						mov vi_key, AX
						m_place_c_by_xy vi_key, style_simpl, 68, 24
				; Restore registers
					pop AX
				; Return
					ret
			p_get_key endp
		; [Description]
			;p_[name] proc near
				; Start
					;push BP
					;mov BP, SP
				; Save registers
					;push USED_REGS_ALPHA
				; Load parameters
					;mov REG, ARG?_$
					;mov REG, ARG?_$
				; Procedure
					;...
				; Upload results
					;...
				; Restore registers
					;pop USED_REGS_REVERSED
				; Return
					;pop BP
					;ret ARG$
			;p_[name] endp
		end start
; End of Lab
