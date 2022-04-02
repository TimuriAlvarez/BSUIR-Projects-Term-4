; Lab3

; Notes for the lab 3
; Arythm+Logic operations
; Shifts: <- | ->
; Big nums -> abs and left

; Command [operand]
    ret
    ret 00h
; Can be placed:
; MEMORY
; REGS
; In command

; MUL: only 1 operand
; res -> AX or DX (leftover)
    mul 05h
    div 05h
; CALL:
    call label
    ; push CS - far
    push IP
; Interruptions:
    int 00h ; [CODE]
; Table of interruption vectors - 1st KB of memory
; Each one is 4bytes - LOGICAL ADDRESS
; 2b - segm, 2b - effective
; x4 - vect 21h = 84h : H - Segm
; int 100h: dword CS; int dword effective address
    push CS, IP, flags
    jmp far [N*4+2]:[N*4]
    ; BODY
    iret
     ; auto:
     pop flags, IP, CS
; In protected mode: will change table of interruption's vectors
; CHAR -> SYMBOLS (-30h) also negative
; NUM OUTPUT
; OVERFLOWS!!! DON'T CHECK IF NOT ASKED TO
; USE DIRECTIVE
; use macro end equ
.386
; Gistogramms:
; '1'-||||||x15
; '2'-||||x3
;
; '10'-||||||||||x55

; REQUIRED REPORTS OF LABS
; GDRIVE ^ ALL LABS ^

; Title
; TOR
; Screens
; Listing
; No result