		public start
start		proc near
		mov	ax, seg	dseg
		mov	ds, ax
		assume ds:dseg
		mov	bx, 9670h
		add	bx, 0Fh
		shr	bx, 1
		shr	bx, 1
		shr	bx, 1
		shr	bx, 1
		add	ax, bx
		mov	word_data_94E8,	ax
		add	ax, 800h
		mov	word_data_94EA,	ax
		add	ax, 800h
		mov	word_data_94EC,	ax
		add	ax, 800h
		mov	word_data_94EE,	ax
		add	ax, 800h
		mov	word_data_94F0,	ax
		add	ax, 800h
		mov	word_data_94F2,	ax
		add	ax, 800h
		mov	word_data_94F4,	ax
		add	ax, 800h
		mov	word_data_94F6,	ax
		int	12h		; MEMORY SIZE -
					; Return: AX = number of contiguous 1K blocks of memory
		cmp	ax, 200h
		jnb	short loc_code_67
		mov	dx, 7
		mov	ah, 9
		int	21h		; DOS -	PRINT STRING
					; DS:DX	-> string terminated by	"$"
		mov	ax, 4C00h
		int	21h		; DOS -	2+ - QUIT WITH EXIT CODE (EXIT)
					; AL = exit code
; ---------------------------------------------------------------------------
		jmp	short loc_code_6E
; ---------------------------------------------------------------------------

loc_code_67:				; CODE XREF: start+47j
		mov	dx, 2Ah	; '*'
		mov	ah, 9
		int	21h		; DOS -	PRINT STRING
					; DS:DX	-> string terminated by	"$"

loc_code_6E:				; CODE XREF: start+55j
		call	sub_code_600
		call	sub_code_333C
		call	sub_code_2762
		call	sub_code_5EC
		call	sub_code_442
		call	sub_code_588
		call	sub_code_591
		call	sub_code_382A
		mov	byte_data_9501,	0

loc_code_8B:				; CODE XREF: start+84j
		call	sub_code_A9
		call	sub_code_CF
		call	sub_code_FD
		jmp	short loc_code_8B
start		endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_code_1C0

loc_code_96:				; CODE XREF: sub_code_1C0+C6j
		call	sub_code_39A3
		call	sub_code_5BC
		call	sub_code_4A5
		mov	ax, 3
		int	10h		; - VIDEO - SET	VIDEO MODE
					; AL = mode
		mov	ax, 4C00h
		int	21h		; DOS -	2+ - QUIT WITH EXIT CODE (EXIT)
; END OF FUNCTION CHUNK	FOR sub_code_1C0 ; AL	= exit code

; =============== S U B	R O U T	I N E =======================================


sub_code_A9	proc near		; CODE XREF: start:loc_code_8Bp
		call	sub_code_103
		mov	byte_data_9500,	0
		mov	byte_data_94FE,	1
		mov	byte ptr word_data_94FC, 10h
		mov	byte_data_94FF,	0
		mov	byte_data_9502,	0
		call	sub_code_DA7
		call	sub_code_3423
		call	sub_code_21DC
		retn
sub_code_A9	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_CF	proc near		; CODE XREF: start+7Ep
					; sub_code_CF+2Bj
		call	sub_code_1C0
		call	sub_code_FDA
		mov	al, byte_data_94FF
		cmp	al, 0
		jnz	short loc_code_E4
		call	sub_code_32FE
		call	sub_code_B8E
		jmp	short loc_code_ED
; ---------------------------------------------------------------------------

loc_code_E4:				; CODE XREF: sub_code_CF+Bj
		call	sub_code_34A8
		call	sub_code_31A4
		call	sub_code_B8E

loc_code_ED:				; CODE XREF: sub_code_CF+13j
		call	sub_code_220D
		call	sub_code_3383
		mov	al, byte_data_9500
		cmp	al, 0
		jnz	short locret_code_FC
		jmp	short sub_code_CF
; ---------------------------------------------------------------------------

locret_code_FC:			; CODE XREF: sub_code_CF+29j
		retn
sub_code_CF	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_FD	proc near		; CODE XREF: start+81p
		mov	byte_data_6, 1
		retn
sub_code_FD	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_103	proc near		; CODE XREF: sub_code_A9p
		mov	al, byte_data_6
		cmp	al, 0
		jz	short loc_code_115
		mov	word_data_8E7E,	0DAh ; 'Ú'
		call	sub_code_279F
		jmp	short loc_code_11E
; ---------------------------------------------------------------------------

loc_code_115:				; CODE XREF: sub_code_103+5j
		mov	word_data_8E7E,	0E9h ; 'é'
		call	sub_code_28DA

loc_code_11E:				; CODE XREF: sub_code_103+10j
		call	sub_code_39B8
		call	sub_code_3472
		mov	byte_data_9503,	1
		mov	word_data_8E80,	0
		call	sub_code_D98

loc_code_132:				; CODE XREF: sub_code_103:loc_code_195j
		call	sub_code_1C0
		call	sub_code_FDA
		call	sub_code_3498
		call	sub_code_B8E
		call	sub_code_3383
		mov	ax, word_data_954C
		test	ax, 80h
		jnz	short loc_code_197
		inc	word_data_8E80
		mov	bx, word_data_8E80
		test	bx, 7
		jnz	short loc_code_195
		shr	bx, 1
		shr	bx, 1
		shr	bx, 1
		add	bx, word_data_8E7E
		mov	al, [bx]
		cmp	al, 0
		jz	short loc_code_195
		cmp	al, 0FFh
		jz	short loc_code_197
		cmp	al, 0FEh ; 'þ'
		jnz	short loc_code_180
		mov	al, byte_data_9546
		cmp	al, 0
		jz	short loc_code_17B
		call	sub_code_29DB
		jmp	short loc_code_17E
; ---------------------------------------------------------------------------

loc_code_17B:				; CODE XREF: sub_code_103+71j
		call	sub_code_1AD

loc_code_17E:				; CODE XREF: sub_code_103+76j
		jmp	short loc_code_195
; ---------------------------------------------------------------------------

loc_code_180:				; CODE XREF: sub_code_103+6Aj
		test	al, 80h
		jnz	short loc_code_189
		call	sub_code_19D
		jmp	short loc_code_195
; ---------------------------------------------------------------------------

loc_code_189:				; CODE XREF: sub_code_103+7Fj
		and	al, 3Fh
		push	ax
		call	sub_code_19D
		pop	ax
		inc	al
		call	sub_code_19D

loc_code_195:				; CODE XREF: sub_code_103+52j
					; sub_code_103+62j ...
		jmp	short loc_code_132
; ---------------------------------------------------------------------------

loc_code_197:				; CODE XREF: sub_code_103+44j
					; sub_code_103+66j
		mov	byte_data_9503,	0
		retn
sub_code_103	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_19D	proc near		; CODE XREF: sub_code_103+81p
					; sub_code_103+89p ...
		mov	si, 109h
		mov	[si+4],	al
		mov	bx, 120h
		call	sub_code_2121
		call	sub_code_B58
		retn
sub_code_19D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1AD	proc near		; CODE XREF: sub_code_103:loc_code_17Bp
		mov	cx, 1F40h

loc_code_1B0:				; CODE XREF: sub_code_1AD:loc_code_1BDj
		push	cx
		call	sub_code_1C0
		pop	cx
		mov	ax, word_data_954C
		test	al, 80h
		jz	short loc_code_1BD
		retn
; ---------------------------------------------------------------------------

loc_code_1BD:				; CODE XREF: sub_code_1AD+Dj
		loop	loc_code_1B0
		retn
sub_code_1AD	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1C0	proc near		; CODE XREF: sub_code_CFp
					; sub_code_103:loc_code_132p ...

; FUNCTION CHUNK AT 0096 SIZE 00000013 BYTES

		mov	bx, 8E8Ah
		mov	si, 3Dh	; '='
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_1D5
		mov	si, 3Eh	; '>'

loc_code_1CF:				; CODE XREF: sub_code_1C0+13j
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_1CF

loc_code_1D5:				; CODE XREF: sub_code_1C0+Aj
		mov	si, 3Bh	; ';'
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_1E1
		call	sub_code_33B

loc_code_1E1:				; CODE XREF: sub_code_1C0+1Cj
		mov	bx, 8E8Ah
		mov	si, word_data_8F0D
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_1F6
		mov	word_data_954C,	1
		jmp	short loc_code_20E
; ---------------------------------------------------------------------------

loc_code_1F6:				; CODE XREF: sub_code_1C0+2Cj
		mov	si, word_data_8F0F
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_208
		mov	word_data_954C,	2
		jmp	short loc_code_20E
; ---------------------------------------------------------------------------

loc_code_208:				; CODE XREF: sub_code_1C0+3Ej
		mov	word_data_954C,	0

loc_code_20E:				; CODE XREF: sub_code_1C0+34j
					; sub_code_1C0+46j
		mov	si, word_data_8F11
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_21F
		or	word_data_954C,	4
		jmp	short loc_code_22E
; ---------------------------------------------------------------------------

loc_code_21F:				; CODE XREF: sub_code_1C0+56j
		mov	si, word_data_8F13
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_22E
		or	word_data_954C,	8

loc_code_22E:				; CODE XREF: sub_code_1C0+5Dj
					; sub_code_1C0+67j
		mov	si, word_data_8F15
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_23E
		or	word_data_954C,	80h

loc_code_23E:				; CODE XREF: sub_code_1C0+76j
		mov	si, word_data_8F17
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_24D
		or	word_data_954C,	40h

loc_code_24D:				; CODE XREF: sub_code_1C0+86j
		mov	si, word_data_8F19
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_25C
		or	word_data_954C,	20h

loc_code_25C:				; CODE XREF: sub_code_1C0+95j
		mov	si, word_data_8F1B
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_28C
		call	sub_code_2C45
		mov	bx, 8E8Ah

loc_code_26C:				; CODE XREF: sub_code_1C0+BAj
		mov	al, [bx+15h]
		cmp	al, 0
		jnz	short loc_code_27C
		mov	al, [bx+31h]
		cmp	al, 0
		jnz	short loc_code_27C
		jmp	short loc_code_26C
; ---------------------------------------------------------------------------

loc_code_27C:				; CODE XREF: sub_code_1C0+B1j
					; sub_code_1C0+B8j
		mov	bx, 8E8Ah
		mov	al, [bx+15h]
		cmp	al, 0
		jz	short loc_code_289
		jmp	loc_code_96
; ---------------------------------------------------------------------------

loc_code_289:				; CODE XREF: sub_code_1C0+C4j
		call	sub_code_529

loc_code_28C:				; CODE XREF: sub_code_1C0+A4j
		mov	bx, 8E8Ah
		mov	si, 3Ch	; '<'
		mov	al, [bx+si]
		cmp	al, 0
		jz	short loc_code_2C5
		mov	al, byte_data_9505
		cmp	al, 0
		jnz	short loc_code_2B0
		mov	al, 0Eh
		call	sub_code_3840
		mov	byte_data_9505,	1
		mov	byte_data_9506,	0
		jmp	short loc_code_2C3
; ---------------------------------------------------------------------------

loc_code_2B0:				; CODE XREF: sub_code_1C0+DDj
		cmp	al, 2
		jnz	short loc_code_2C3
		mov	byte_data_9505,	3
		mov	byte_data_9506,	1
		mov	al, 0Dh
		call	sub_code_3840

loc_code_2C3:				; CODE XREF: sub_code_1C0+EEj
					; sub_code_1C0+F2j
		jmp	short loc_code_2DC
; ---------------------------------------------------------------------------

loc_code_2C5:				; CODE XREF: sub_code_1C0+D6j
		mov	al, byte_data_9505
		cmp	al, 1
		jnz	short loc_code_2D3
		mov	byte_data_9505,	2
		jmp	short loc_code_2DC
; ---------------------------------------------------------------------------

loc_code_2D3:				; CODE XREF: sub_code_1C0+10Aj
		cmp	al, 3
		jnz	short loc_code_2DC
		mov	byte_data_9505,	0

loc_code_2DC:				; CODE XREF: sub_code_1C0:loc_code_2C3j
					; sub_code_1C0+111j ...
		mov	al, byte_data_8F0A
		cmp	al, 0
		jnz	short loc_code_2E4
		retn
; ---------------------------------------------------------------------------

loc_code_2E4:				; CODE XREF: sub_code_1C0+121j
		mov	ax, 3
		int	33h		; - MS MOUSE - RETURN POSITION AND BUTTON STATUS
					; Return: BX = button status, CX = column, DX =	row
		test	bx, 1
		jz	short loc_code_2F5
		or	word_data_954C,	80h

loc_code_2F5:				; CODE XREF: sub_code_1C0+12Dj
		test	bx, 2
		jz	short loc_code_300
		or	word_data_954C,	20h

loc_code_300:				; CODE XREF: sub_code_1C0+139j
		mov	ax, word_data_954C
		and	ax, 0Fh
		jz	short loc_code_309
		retn
; ---------------------------------------------------------------------------

loc_code_309:				; CODE XREF: sub_code_1C0+146j
		mov	ax, 0Bh
		int	33h		; - MS MOUSE - READ MOTION COUNTERS
					; Return: CX = number of mickeys mouse moved horizontally since	last call
					; DX = number of mickeys mouse moved vertically
		cmp	cx, 0FFFBh
		jge	short loc_code_31A
		or	word_data_954C,	1
		jmp	short loc_code_324
; ---------------------------------------------------------------------------

loc_code_31A:				; CODE XREF: sub_code_1C0+151j
		cmp	cx, 5
		jle	short loc_code_324
		or	word_data_954C,	2

loc_code_324:				; CODE XREF: sub_code_1C0+158j
					; sub_code_1C0+15Dj
		cmp	dx, 0FFF6h
		jge	short loc_code_330
		or	word_data_954C,	4
		jmp	short locret_code_33A
; ---------------------------------------------------------------------------

loc_code_330:				; CODE XREF: sub_code_1C0+167j
		cmp	dx, 0Ah
		jle	short locret_code_33A
		or	word_data_954C,	8

locret_code_33A:			; CODE XREF: sub_code_1C0+16Ej
					; sub_code_1C0+173j
		retn
sub_code_1C0	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_33B	proc near		; CODE XREF: sub_code_1C0+1Ep
		call	sub_code_2C07
		mov	al, 4
		call	sub_code_2C9A
		call	sub_code_4F3
		mov	word_data_8F15,	ax
		mov	al, 0
		call	sub_code_2C9A

loc_code_34E:				; CODE XREF: sub_code_33B+1Aj
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_34E
		mov	word_data_8F0D,	ax
		mov	al, 1
		call	sub_code_2C9A

loc_code_35F:				; CODE XREF: sub_code_33B+2Bj
					; sub_code_33B+31j
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_35F
		cmp	ax, word_data_8F0D
		jz	short loc_code_35F
		mov	word_data_8F0F,	ax
		mov	al, 2
		call	sub_code_2C9A

loc_code_376:				; CODE XREF: sub_code_33B+42j
					; sub_code_33B+48j ...
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_376
		cmp	ax, word_data_8F0D
		jz	short loc_code_376
		cmp	ax, word_data_8F0F
		jz	short loc_code_376
		mov	word_data_8F11,	ax
		mov	al, 3
		call	sub_code_2C9A

loc_code_393:				; CODE XREF: sub_code_33B+5Fj
					; sub_code_33B+65j ...
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_393
		cmp	ax, word_data_8F0D
		jz	short loc_code_393
		cmp	ax, word_data_8F0F
		jz	short loc_code_393
		cmp	ax, word_data_8F11
		jz	short loc_code_393
		mov	word_data_8F13,	ax
		mov	al, 6
		call	sub_code_2C9A

loc_code_3B6:				; CODE XREF: sub_code_33B+82j
					; sub_code_33B+88j ...
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_3B6
		cmp	ax, word_data_8F0D
		jz	short loc_code_3B6
		cmp	ax, word_data_8F0F
		jz	short loc_code_3B6
		cmp	ax, word_data_8F11
		jz	short loc_code_3B6
		cmp	ax, word_data_8F13
		jz	short loc_code_3B6
		mov	word_data_8F17,	ax
		mov	al, 7
		call	sub_code_2C9A

loc_code_3DF:				; CODE XREF: sub_code_33B+ABj
					; sub_code_33B+B1j ...
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_3DF
		cmp	ax, word_data_8F0D
		jz	short loc_code_3DF
		cmp	ax, word_data_8F0F
		jz	short loc_code_3DF
		cmp	ax, word_data_8F11
		jz	short loc_code_3DF
		cmp	ax, word_data_8F13
		jz	short loc_code_3DF
		cmp	ax, word_data_8F17
		jz	short loc_code_3DF
		mov	word_data_8F19,	ax
		mov	al, 5
		call	sub_code_2C9A

loc_code_40E:				; CODE XREF: sub_code_33B+DAj
					; sub_code_33B+E0j ...
		call	sub_code_4F3
		cmp	ax, word_data_8F15
		jz	short loc_code_40E
		cmp	ax, word_data_8F0D
		jz	short loc_code_40E
		cmp	ax, word_data_8F0F
		jz	short loc_code_40E
		cmp	ax, word_data_8F11
		jz	short loc_code_40E
		cmp	ax, word_data_8F13
		jz	short loc_code_40E
		cmp	ax, word_data_8F17
		jz	short loc_code_40E
		cmp	ax, word_data_8F19
		jz	short loc_code_40E
		mov	word_data_8F1B,	ax
		call	sub_code_529
		retn
sub_code_33B	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_442	proc near		; CODE XREF: start+6Ap
		mov	word_data_8F0B,	0
		mov	word_data_8F0D,	4Bh ; 'K'
		mov	word_data_8F0F,	4Dh ; 'M'
		mov	word_data_8F11,	48h ; 'H'
		mov	word_data_8F13,	50h ; 'P'
		mov	word_data_8F15,	39h ; '9'
		mov	word_data_8F17,	31h ; '1'
		mov	word_data_8F19,	32h ; '2'
		mov	word_data_8F1B,	10h
		mov	ax, ds
		mov	es, ax
		assume es:dseg
		mov	ax, 0
		mov	cx, 40h	; '@'
		mov	di, 8E8Ah
		rep stosw
		mov	al, 9
		mov	ah, 35h
		int	21h		; DOS -	2+ - GET INTERRUPT VECTOR
					; AL = interrupt number
					; Return: ES:BX	= value	of interrupt vector
		mov	word_data_8E84,	bx
		mov	word_data_8E82,	es
		push	ds
		mov	dx, 4B7h
		mov	ax, cs
		mov	ds, ax
		assume ds:seg000
		mov	al, 9
		mov	ah, 25h
		int	21h		; DOS -	SET INTERRUPT VECTOR
					; AL = interrupt number
					; DS:DX	= new vector to	be used	for specified interrupt
		pop	ds
		assume ds:dseg
		retn
sub_code_442	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_4A5	proc near		; CODE XREF: sub_code_1C0-124p
		mov	dx, word_data_8E84
		mov	ax, word_data_8E82
		push	ds
		mov	ds, ax
		mov	al, 9
		mov	ah, 25h
		int	21h		; DOS -	SET INTERRUPT VECTOR
					; AL = interrupt number
					; DS:DX	= new vector to	be used	for specified interrupt
		pop	ds
		retn
sub_code_4A5	endp

; ---------------------------------------------------------------------------
		sti
		push	ax
		push	bx
		push	ds
		mov	ax, 40h	; '@'
		mov	ds, ax
		assume ds:nothing
		in	al, 60h		; AT Keyboard controller 8042.
		push	ax
		in	al, 61h		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		mov	ah, al
		or	al, 80h
		out	61h, al		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		xchg	ah, al
		out	61h, al		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		pop	bx
		mov	ax, seg	dseg
		mov	ds, ax
		assume ds:dseg
		mov	bh, 0
		test	bl, 80h
		jnz	short loc_code_4E3
		mov	byte ptr [bx-7176h], 1
		jmp	short loc_code_4EB
; ---------------------------------------------------------------------------

loc_code_4E3:				; CODE XREF: seg000:04DAj
		and	bl, 7Fh
		mov	byte ptr [bx-7176h], 0

loc_code_4EB:				; CODE XREF: seg000:04E1j
		mov	al, 20h	; ' '
		out	20h, al		; Interrupt controller,	8259A.
		pop	ds
		pop	bx
		pop	ax
		iret

; =============== S U B	R O U T	I N E =======================================


sub_code_4F3	proc near		; CODE XREF: sub_code_33B+8p
					; sub_code_33B:loc_code_34Ep ...
		cld

loc_code_4F4:				; CODE XREF: sub_code_4F3+33j
		mov	si, 8E8Ah

loc_code_4F7:				; CODE XREF: sub_code_4F3+31j
		lodsb
		cmp	al, 0
		jz	short loc_code_520
		mov	ax, si
		sub	ax, 8E8Bh
		cmp	ax, 3Bh	; ';'
		jz	short loc_code_520
		cmp	ax, 3Ch	; '<'
		jz	short loc_code_520
		cmp	ax, 3Dh	; '='
		jz	short loc_code_520
		cmp	ax, 3Eh	; '>'
		jz	short loc_code_520
		cmp	ax, 2Ah	; '*'
		jz	short loc_code_520
		cmp	ax, 36h	; '6'
		jz	short loc_code_520
		retn
; ---------------------------------------------------------------------------

loc_code_520:				; CODE XREF: sub_code_4F3+7j
					; sub_code_4F3+11j ...
		cmp	si, 8F0Ah
		jnz	short loc_code_4F7
		jmp	short loc_code_4F4
sub_code_4F3	endp

; ---------------------------------------------------------------------------
		retn

; =============== S U B	R O U T	I N E =======================================


sub_code_529	proc near		; CODE XREF: sub_code_1C0:loc_code_289p
					; sub_code_33B+103p ...
		mov	si, 8E8Ah
		mov	ah, 0

loc_code_52E:				; CODE XREF: sub_code_529+10j
		lodsb
		cmp	al, 0
		jz	short loc_code_535
		inc	ah

loc_code_535:				; CODE XREF: sub_code_529+8j
		cmp	si, 8F0Ah
		jnz	short loc_code_52E
		cmp	ah, 0
		jnz	short sub_code_529
		retn
sub_code_529	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_541	proc near		; CODE XREF: sub_code_29DB+Ep
		mov	cx, 4E20h

loc_code_544:				; CODE XREF: sub_code_541:loc_code_583j
		mov	si, 8E8Ah
		mov	ah, 0
		cld

loc_code_54A:				; CODE XREF: sub_code_541+1Cj
		lodsb
		cmp	al, 0
		jz	short loc_code_557
		mov	ah, 1
		cmp	si, word_data_8F0B
		jnz	short loc_code_55F

loc_code_557:				; CODE XREF: sub_code_541+Cj
		cmp	si, 8F0Ah
		jz	short loc_code_55F
		jmp	short loc_code_54A
; ---------------------------------------------------------------------------

loc_code_55F:				; CODE XREF: sub_code_541+14j
					; sub_code_541+1Aj
		jz	short loc_code_578
		mov	word_data_8F0B,	si
		sub	si, 8E8Bh
		mov	al, [si+5Ah]
		cmp	al, 0
		jz	short loc_code_576
		jns	short locret_code_575
		mov	al, 0

locret_code_575:			; CODE XREF: sub_code_541+30j
		retn
; ---------------------------------------------------------------------------

loc_code_576:				; CODE XREF: sub_code_541+2Ej
		jmp	short loc_code_583
; ---------------------------------------------------------------------------

loc_code_578:				; CODE XREF: sub_code_541:loc_code_55Fj
		cmp	ah, 0
		jnz	short loc_code_583
		mov	word_data_8F0B,	0

loc_code_583:				; CODE XREF: sub_code_541:loc_code_576j
					; sub_code_541+3Aj
		loop	loc_code_544
		mov	al, 0
		retn
sub_code_541	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_588	proc near		; CODE XREF: start+6Dp
		mov	ax, 0
		int	33h		; - MS MOUSE - RESET DRIVER AND	READ STATUS
					; Return: AX = status
					; BX = number of buttons
		mov	byte_data_8F0A,	al
		retn
sub_code_588	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_591	proc near		; CODE XREF: start+70p
		mov	al, 1Ch
		mov	ah, 35h
		int	21h		; DOS -	2+ - GET INTERRUPT VECTOR
					; AL = interrupt number
					; Return: ES:BX	= value	of interrupt vector
		mov	word_data_8E88,	bx
		mov	word_data_8E86,	es
		push	ds
		mov	dx, 5CEh
		mov	ax, cs
		mov	ds, ax
		assume ds:seg000
		mov	al, 1Ch
		mov	ah, 25h
		int	21h		; DOS -	SET INTERRUPT VECTOR
					; AL = interrupt number
					; DS:DX	= new vector to	be used	for specified interrupt
		pop	ds
		assume ds:dseg
		mov	al, 36h	; '6'
		out	43h, al		; Timer	8253-5 (AT: 8254.2).
		mov	ax, 4D0Eh
		out	40h, al		; Timer	8253-5 (AT: 8254.2).
		mov	al, ah
		out	40h, al		; Timer	8253-5 (AT: 8254.2).
		retn
sub_code_591	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_5BC	proc near		; CODE XREF: sub_code_1C0-127p
		mov	dx, word_data_8E88
		mov	ax, word_data_8E86
		push	ds
		mov	ds, ax
		mov	al, 1Ch
		mov	ah, 25h
		int	21h		; DOS -	SET INTERRUPT VECTOR
					; AL = interrupt number
					; DS:DX	= new vector to	be used	for specified interrupt
		pop	ds
		retn
sub_code_5BC	endp

; ---------------------------------------------------------------------------
		sti
		push	ax
		push	bx
		push	cx
		push	dx
		push	si
		push	di
		push	bp
		push	ds
		mov	ax, seg	dseg
		mov	ds, ax
		inc	byte_data_9504
		call	sub_code_387D
		pop	ds
		pop	bp
		pop	di
		pop	si
		pop	dx
		pop	cx
		pop	bx
		pop	ax
		iret

; =============== S U B	R O U T	I N E =======================================


sub_code_5EC	proc near		; CODE XREF: start+67p
		push	ds
		mov	dx, 5FCh
		mov	ax, cs
		mov	ds, ax
		assume ds:seg000
		mov	al, 24h	; '$'
		mov	ah, 25h
		int	21h		; DOS -	SET INTERRUPT VECTOR
					; AL = interrupt number
					; DS:DX	= new vector to	be used	for specified interrupt
		pop	ds
		assume ds:dseg
		retn
sub_code_5EC	endp

; ---------------------------------------------------------------------------
		sti
		mov	al, 0
		iret

; =============== S U B	R O U T	I N E =======================================


sub_code_600	proc near		; CODE XREF: start:loc_code_6Ep
		mov	dx, 1E2h
		mov	ax, word_data_94E8
		call	sub_code_637
		mov	dx, 1EAh
		mov	ax, word_data_94EA
		call	sub_code_637
		mov	dx, 1F2h
		mov	ax, word_data_94EC
		call	sub_code_637
		mov	dx, 1F9h
		mov	ax, word_data_94EE
		call	sub_code_637
		mov	dx, 203h
		mov	ax, word_data_94F0
		call	sub_code_637
		mov	dx, 20Bh
		mov	ax, word_data_94F2
		call	sub_code_637
		retn
sub_code_600	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_637	proc near		; CODE XREF: sub_code_600+6p
					; sub_code_600+Fp ...
		mov	word_data_8F20,	ax
		mov	di, 0
		mov	cx, 7D00h
		call	sub_code_64D
		retn
sub_code_637	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_644	proc near		; CODE XREF: sub_code_2762+39p
		mov	ax, ds
		mov	word_data_8F20,	ax
		call	sub_code_64D
		retn
sub_code_644	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_64D	proc near		; CODE XREF: sub_code_637+9p
					; sub_code_644+5p
		push	di
		push	cx
		mov	ax, 3D00h
		int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
					; DS:DX	-> ASCIZ filename
					; AL = access mode
					; 0 - read
		pop	cx
		pop	dx
		jnb	short loc_code_659
		retn
; ---------------------------------------------------------------------------

loc_code_659:				; CODE XREF: sub_code_64D+9j
		mov	word_data_8F1E,	ax
		mov	bx, ax
		mov	ax, word_data_8F20
		push	ds
		mov	ds, ax
		mov	ax, 3F00h
		int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
					; BX = file handle, CX = number	of bytes to read
					; DS:DX	-> buffer
		pop	ds
		mov	ax, 3E00h
		mov	bx, word_data_8F1E
		int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
					; BX = file handle
		retn
sub_code_64D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_674	proc near		; CODE XREF: sub_code_29DB+80p
		push	di
		push	cx
		mov	cx, 0
		mov	ax, 3C00h
		int	21h		; DOS -	2+ - CREATE A FILE WITH	HANDLE (CREAT)
					; CX = attributes for file
					; DS:DX	-> ASCIZ filename (may include drive and path)
		pop	cx
		pop	dx
		jnb	short loc_code_683
		retn
; ---------------------------------------------------------------------------

loc_code_683:				; CODE XREF: sub_code_674+Cj
		mov	word_data_8F1E,	ax
		mov	bx, ax
		mov	ax, 4000h
		int	21h		; DOS -	2+ - WRITE TO FILE WITH	HANDLE
					; BX = file handle, CX = number	of bytes to write, DS:DX -> buffer
		jnb	short loc_code_690
		retn
; ---------------------------------------------------------------------------

loc_code_690:				; CODE XREF: sub_code_674+19j
		mov	ax, 3E00h
		mov	bx, word_data_8F1E
		int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
					; BX = file handle
		retn
sub_code_674	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_69A	proc near		; CODE XREF: sub_code_DA7+3p
					; sub_code_DC0+38p ...
		mov	al, byte_data_9501
		mov	bl, al
		shl	bl, 1
		add	bl, al
		add	bl, byte_data_9502
		mov	bh, 0
		shl	bx, 1
		mov	si, [bx+244h]
		mov	di, 9229h
		mov	cx, 40h	; '@'
		mov	ax, ds
		mov	es, ax
		mov	ax, 0
		cld
		rep stosw
		mov	di, 9229h

loc_code_6C2:				; CODE XREF: sub_code_69A+4Fj
		lodsb
		cmp	al, 0FFh
		jz	short loc_code_6EB
		shl	al, 1
		shl	al, 1
		mov	ah, al
		lodsb
		shl	al, 1
		mov	bl, al
		mov	bh, 0
		mov	al, 0
		or	ax, [bx+0CD7h]
		mov	cx, ax
		lodsb
		neg	al
		add	al, 3Fh	; '?'
		shl	al, 1
		mov	bl, al
		or	[bx-6DD7h], cx
		jmp	short loc_code_6C2
; ---------------------------------------------------------------------------

loc_code_6EB:				; CODE XREF: sub_code_69A+2Bj
		mov	al, byte_data_9501
		mov	bl, al
		shl	bl, 1
		add	bl, al
		add	bl, byte_data_9502
		mov	bh, 0
		shl	bx, 1
		mov	si, [bx+214h]
		mov	di, 8F29h
		mov	cx, 300h
		mov	bl, 0

loc_code_708:				; CODE XREF: sub_code_69A+95j
		dec	bl
		jns	short loc_code_72C
		lodsb
		mov	dl, al
		and	dl, 3Fh
		and	al, 0C0h
		jnz	short loc_code_71A
		mov	bl, 0
		jmp	short loc_code_72C
; ---------------------------------------------------------------------------

loc_code_71A:				; CODE XREF: sub_code_69A+7Aj
		cmp	al, 40h	; '@'
		jnz	short loc_code_722
		mov	bl, 1
		jmp	short loc_code_72C
; ---------------------------------------------------------------------------

loc_code_722:				; CODE XREF: sub_code_69A+82j
		cmp	al, 80h	; '€'
		jnz	short loc_code_72A
		mov	bl, 2
		jmp	short loc_code_72C
; ---------------------------------------------------------------------------

loc_code_72A:				; CODE XREF: sub_code_69A+8Aj
		mov	bl, 3

loc_code_72C:				; CODE XREF: sub_code_69A+70j
					; sub_code_69A+7Ej ...
		mov	[di], dl
		inc	di
		loop	loc_code_708
		mov	di, 0
		mov	ax, 0A800h
		mov	es, ax
		assume es:nothing
		mov	dx, 3CEh
		mov	ah, 0
		mov	al, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		mov	ax, 0F01h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	cx, 4000h
		rep stosw
		mov	ax, 8F29h
		mov	word_data_8F25,	ax
		mov	word_data_8F23,	3F0h
		mov	cx, 40h	; '@'

loc_code_759:				; CODE XREF: sub_code_69A+112j
		push	cx
		mov	byte_data_8F22,	0
		call	sub_code_7AF
		mov	word_data_279, 0
		mov	byte_data_27D, 8
		add	word_data_283, 8
		mov	si, 274h
		call	sub_code_BC5
		mov	word_data_279, 8
		mov	byte_data_27D, 18h
		mov	cx, 0Ah

loc_code_786:				; CODE XREF: sub_code_69A+FCj
		push	cx
		call	sub_code_7AF
		mov	si, 274h
		call	sub_code_BC5
		add	word_data_279, 18h
		pop	cx
		loop	loc_code_786
		mov	byte_data_27D, 8
		call	sub_code_7AF
		mov	si, 274h
		call	sub_code_BC5
		sub	word_data_8F23,	10h
		pop	cx
		loop	loc_code_759
		retn
sub_code_69A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_7AF	proc near		; CODE XREF: sub_code_69A+C5p
					; sub_code_69A+EDp ...
		mov	al, byte_data_8F22
		mov	byte_data_277, al
		mov	bx, word_data_8F25
		mov	al, [bx]
		inc	bx
		mov	word_data_8F25,	bx
		mov	bh, 0
		mov	bl, al
		mov	al, [bx+51Dh]
		mov	byte_data_27E, al
		mov	al, [bx+571h]
		add	byte_data_8F22,	al
		mov	al, [bx+547h]
		cbw
		add	ax, word_data_8F23
		mov	word_data_27B, ax
		cmp	bx, 26h	; '&'
		jb	short loc_code_7EC
		mov	word_data_281, 2
		jmp	short loc_code_7F2
; ---------------------------------------------------------------------------

loc_code_7EC:				; CODE XREF: sub_code_7AF+33j
		mov	word_data_281, 4

loc_code_7F2:				; CODE XREF: sub_code_7AF+3Bj
		shl	bx, 1
		mov	bx, [bx+5EFh]
		mov	word_data_283, bx
		retn
sub_code_7AF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_7FD	proc near		; CODE XREF: sub_code_12EB+3Fp
					; sub_code_13A8+1Cp ...

var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 8
		mov	ax, [bp+arg_2]
		add	ax, 10h
		mov	cl, 18h
		div	cl
		push	ax
		mov	ah, 0
		mov	[bp+var_2], ax
		pop	ax
		mov	al, ah
		mov	ah, 0
		mov	cl, 3
		div	cl
		mov	ah, 0
		mov	[bp+var_4], ax
		mov	ax, [bp+arg_0]
		and	ax, 3FFh
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		neg	ax
		add	ax, 3Fh	; '?'
		mov	[bp+var_6], ax
		mov	ax, [bp+arg_0]
		and	ax, 0Fh
		shr	ax, 1
		mov	[bp+var_8], ax
		mov	ax, [bp+var_6]
		shl	ax, 1
		shl	ax, 1
		mov	bx, ax
		shl	ax, 1
		add	bx, ax
		add	bx, 8F29h
		mov	si, bx
		add	bx, [bp+var_2]
		mov	al, [bx]
		mov	ah, 0
		push	ax
		shl	ax, 1
		mov	bx, ax
		mov	bx, [bx+643h]
		mov	ax, [bp+var_8]
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		add	bx, ax
		add	bx, [bp+var_4]
		mov	cl, [bx]
		push	cx
		and	cl, 1Fh
		test	cl, 10h
		jz	short loc_code_881
		or	cl, 0E0h

loc_code_881:				; CODE XREF: sub_code_7FD+7Fj
		mov	dx, [bp+var_2]
		cld

loc_code_885:				; CODE XREF: sub_code_7FD+97j
		cmp	dx, 0
		jz	short loc_code_896
		lodsb
		mov	bh, 0
		mov	bl, al
		add	cl, [bx+571h]
		dec	dx
		jmp	short loc_code_885
; ---------------------------------------------------------------------------

loc_code_896:				; CODE XREF: sub_code_7FD+8Bj
		mov	al, cl
		cbw
		pop	cx
		pop	bx
		test	cl, 80h
		jnz	short loc_code_8A6
		mov	bl, [bx+59Bh]
		jmp	short loc_code_8AA
; ---------------------------------------------------------------------------

loc_code_8A6:				; CODE XREF: sub_code_7FD+A1j
		mov	bl, [bx+5C5h]

loc_code_8AA:				; CODE XREF: sub_code_7FD+A7j
		mov	bh, 0
		mov	cx, [bp+var_6]
		neg	cx
		add	cx, 3Fh	; '?'
		mov	sp, bp
		pop	bp
		retn	4
sub_code_7FD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_8BA	proc near		; CODE XREF: sub_code_E84+41p
					; sub_code_1BB9+4Dp

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		mov	bx, [bp+arg_0]
		shl	bx, 1
		mov	ax, [bx-6DD7h]
		cmp	ax, 0
		jz	short loc_code_946
		push	ax
		shr	ah, 1
		shr	ah, 1
		mov	bl, ah
		mov	bh, 0
		shl	bx, 1
		mov	si, [bx+28Bh]
		cmp	ah, 0Fh
		jb	short loc_code_902
		cmp	ah, 14h
		ja	short loc_code_902
		sub	ah, 0Fh
		mov	[si+1],	ah
		mov	bl, ah
		mov	bh, 0
		mov	al, [bx-6AD2h]
		cmp	al, 0
		jz	short loc_code_8F9
		pop	ax
		jmp	short loc_code_946
; ---------------------------------------------------------------------------

loc_code_8F9:				; CODE XREF: sub_code_8BA+3Aj
		shl	bx, 1
		mov	ax, [bx+32Eh]
		mov	[si+0Fh], ax

loc_code_902:				; CODE XREF: sub_code_8BA+23j
					; sub_code_8BA+28j
		mov	byte ptr [si+13h], 0Ah
		mov	ax, [bp+arg_0]
		mov	[si+14h], al
		pop	ax
		mov	cx, 0Ah

loc_code_910:				; CODE XREF: sub_code_8BA+8Aj
		shr	ax, 1
		jnb	short loc_code_941
		push	ax
		push	cx
		call	sub_code_94A
		mov	al, [si+13h]
		mov	ah, 0
		push	ax
		mov	ax, [bp+arg_0]
		push	ax
		call	sub_code_9E9
		cmp	ax, 0
		jz	short loc_code_932
		push	si
		call	sub_code_B58
		pop	si
		jmp	short loc_code_93F
; ---------------------------------------------------------------------------

loc_code_932:				; CODE XREF: sub_code_8BA+6Fj
		push	si
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_93E
		call	sub_code_A1B

loc_code_93E:				; CODE XREF: sub_code_8BA+7Fj
		pop	si

loc_code_93F:				; CODE XREF: sub_code_8BA+76j
		pop	cx
		pop	ax

loc_code_941:				; CODE XREF: sub_code_8BA+58j
		dec	byte ptr [si+13h]
		loop	loc_code_910

loc_code_946:				; CODE XREF: sub_code_8BA+Fj
					; sub_code_8BA+3Dj
		pop	bp
		retn	2
sub_code_8BA	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_94A	proc near		; CODE XREF: sub_code_8BA+5Cp
		mov	dl, [si+13h]
		push	si
		mov	al, 3Fh	; '?'
		sub	al, [si+14h]
		shl	al, 1
		shl	al, 1
		mov	ah, 0
		mov	si, ax
		shl	ax, 1
		add	si, ax
		add	si, 8F29h
		mov	cl, 0
		cld

loc_code_966:				; CODE XREF: sub_code_94A+2Cj
		cmp	dl, 0
		jz	short loc_code_978
		lodsb
		mov	bh, 0
		mov	bl, al
		add	cl, [bx+571h]
		dec	dl
		jmp	short loc_code_966
; ---------------------------------------------------------------------------

loc_code_978:				; CODE XREF: sub_code_94A+1Fj
		pop	si
		mov	[si+3],	cl
		mov	al, [si+14h]
		mov	ah, 0
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		mov	[si+7],	ax
		mov	al, [si+13h]
		mov	ah, 0
		shl	ax, 1
		mov	cx, ax
		shl	ax, 1
		add	ax, cx
		shl	ax, 1
		shl	ax, 1
		sub	ax, 4
		mov	[si+5],	ax
		retn
sub_code_94A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_9A4	proc near		; CODE XREF: sub_code_DA7p
					; sub_code_DC0:loc_code_DF5p
		mov	di, 92A9h
		mov	cx, 0C0h ; 'À'
		mov	ax, ds
		mov	es, ax
		assume es:dseg
		mov	ax, 0FFFFh
		cld
		rep stosw
		retn
sub_code_9A4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_9B5	proc near		; CODE XREF: sub_code_20DB+11p

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		mov	si, [bp+arg_4]
		call	sub_code_A1B
		mov	bx, [bp+arg_2]
		shl	bx, 1
		mov	cx, [bx+0CEBh]
		mov	bx, [bp+arg_0]
		shl	bx, 1
		mov	al, byte_data_9502
		cmp	al, 1
		jnz	short loc_code_9D9
		add	bx, 80h	; '€'
		jmp	short loc_code_9E1
; ---------------------------------------------------------------------------

loc_code_9D9:				; CODE XREF: sub_code_9B5+1Cj
		cmp	al, 2
		jnz	short loc_code_9E1
		add	bx, 100h

loc_code_9E1:				; CODE XREF: sub_code_9B5+22j
					; sub_code_9B5+26j
		and	[bx-6D57h], cx
		pop	bp
		retn	6
sub_code_9B5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_9E9	proc near		; CODE XREF: sub_code_8BA+69p

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	bx, [bp+arg_2]
		shl	bx, 1
		mov	cx, [bx+0CEBh]
		mov	bx, [bp+arg_0]
		shl	bx, 1
		mov	al, byte_data_9502
		cmp	al, 1
		jnz	short loc_code_A07
		add	bx, 80h	; '€'
		jmp	short loc_code_A0F
; ---------------------------------------------------------------------------

loc_code_A07:				; CODE XREF: sub_code_9E9+16j
		cmp	al, 2
		jnz	short loc_code_A0F
		add	bx, 100h

loc_code_A0F:				; CODE XREF: sub_code_9E9+1Cj
					; sub_code_9E9+20j
		not	cx
		mov	ax, [bx-6D57h]
		and	ax, cx
		pop	bp
		retn	4
sub_code_9E9	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_A1B	proc near		; CODE XREF: sub_code_8BA+81p
					; sub_code_9B5+6p
		mov	al, [si+12h]
		shl	al, 1
		mov	bl, al
		mov	bh, 0
		mov	di, [bx+31Eh]
		mov	al, [di]
		mov	[si], al
		mov	al, [di+9]
		mov	[si+9],	al
		mov	al, [di+0Ah]
		mov	[si+0Ah], al
		mov	al, [di+0Bh]
		mov	[si+0Bh], al
		mov	al, [di+0Ch]
		mov	[si+0Ch], al
		mov	ax, [di+0Fh]
		mov	[si+0Fh], ax
		mov	al, [di+12h]
		mov	[si+12h], al
		retn
sub_code_A1B	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_A51	proc near		; CODE XREF: sub_code_1108+8Ap
					; sub_code_1108+A0p
		mov	bl, byte_data_1B9E
		mov	bh, 0
		shl	bx, 1
		mov	si, bx
		mov	al, byte_data_9502
		cmp	al, 1
		jnz	short loc_code_A68
		add	si, 80h	; '€'
		jmp	short loc_code_A70
; ---------------------------------------------------------------------------

loc_code_A68:				; CODE XREF: sub_code_A51+Fj
		cmp	al, 2
		jnz	short loc_code_A70
		add	si, 100h

loc_code_A70:				; CODE XREF: sub_code_A51+15j
					; sub_code_A51+19j
		mov	ax, [si-6D57h]
		and	ax, [bx-6DD7h]
		cmp	ax, 0
		jz	short loc_code_AD1
		mov	bl, ah
		shr	bl, 1
		shr	bl, 1
		mov	bh, 0
		mov	cl, [bx+2B5h]
		cmp	cl, 0
		jz	short loc_code_AD1
		mov	byte_data_9429,	cl
		mov	word_data_942C,	0Ah
		shl	bx, 1
		mov	dx, [bx+2CAh]
		mov	bx, [bx+2F4h]
		mov	cx, 0Ah

loc_code_AA5:				; CODE XREF: sub_code_A51+7Ej
		shr	ax, 1
		jnb	short loc_code_AC8
		push	bx
		sub	bx, dx
		cmp	bx, word_data_1B8F
		jg	short loc_code_AC7
		add	bx, dx
		add	bx, dx
		cmp	bx, word_data_1B8F
		jl	short loc_code_AC7
		pop	ax
		mov	al, byte_data_9429
		mov	ah, 0
		mov	bx, word_data_942C
		retn
; ---------------------------------------------------------------------------

loc_code_AC7:				; CODE XREF: sub_code_A51+5Fj
					; sub_code_A51+69j
		pop	bx

loc_code_AC8:				; CODE XREF: sub_code_A51+56j
		sub	bx, 18h
		dec	word_data_942C
		loop	loc_code_AA5

loc_code_AD1:				; CODE XREF: sub_code_A51+2Aj
					; sub_code_A51+3Bj
		mov	ax, 0
		retn
sub_code_A51	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_AD5	proc near		; CODE XREF: sub_code_12EB+56p
					; sub_code_13A8+58p

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	bx, [bp+arg_0]
		shl	bx, 1
		mov	si, bx
		mov	al, byte_data_9502
		cmp	al, 1
		jnz	short loc_code_AEC
		add	si, 80h	; '€'
		jmp	short loc_code_AF4
; ---------------------------------------------------------------------------

loc_code_AEC:				; CODE XREF: sub_code_AD5+Fj
		cmp	al, 2
		jnz	short loc_code_AF4
		add	si, 100h

loc_code_AF4:				; CODE XREF: sub_code_AD5+15j
					; sub_code_AD5+19j
		mov	ax, [si-6D57h]
		and	ax, [bx-6DD7h]
		cmp	ax, 0
		jz	short loc_code_B51
		mov	bl, ah
		shr	bl, 1
		shr	bl, 1
		mov	bh, 0
		mov	cl, [bx+2B5h]
		cmp	cl, 0
		jz	short loc_code_B51
		mov	word_data_942C,	0Ah
		shl	bx, 1
		mov	dx, [bx+2CAh]
		sub	dx, 0Eh
		mov	bx, [bx+2F4h]
		mov	cx, 0Ah

loc_code_B28:				; CODE XREF: sub_code_AD5+7Aj
		shr	ax, 1
		jnb	short loc_code_B48
		push	bx
		sub	bx, dx
		cmp	bx, [bp+arg_2]
		jg	short loc_code_B47
		add	bx, dx
		add	bx, dx
		cmp	bx, [bp+arg_2]
		jl	short loc_code_B47
		pop	ax
		mov	ax, 1
		mov	bx, word_data_942C
		jmp	short loc_code_B54
; ---------------------------------------------------------------------------

loc_code_B47:				; CODE XREF: sub_code_AD5+5Dj
					; sub_code_AD5+66j
		pop	bx

loc_code_B48:				; CODE XREF: sub_code_AD5+55j
		sub	bx, 18h
		dec	word_data_942C
		loop	loc_code_B28

loc_code_B51:				; CODE XREF: sub_code_AD5+2Aj
					; sub_code_AD5+3Bj
		mov	ax, 0

loc_code_B54:				; CODE XREF: sub_code_AD5+70j
		pop	bp
		retn	4
sub_code_AD5	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_B58	proc near		; CODE XREF: sub_code_19D+Cp
					; sub_code_8BA+72p ...
		mov	ax, seg	dseg
		mov	es, ax
		mov	di, 1B8Ah

loc_code_B60:				; CODE XREF: sub_code_B58+1Ej
		mov	al, [di]
		test	al, 80h
		jnz	short loc_code_B78
		test	al, 1
		jnz	short loc_code_B73
		push	di
		mov	cx, 17h
		cld
		rep movsb
		pop	si
		retn
; ---------------------------------------------------------------------------

loc_code_B73:				; CODE XREF: sub_code_B58+10j
		add	di, 17h
		jmp	short loc_code_B60
; ---------------------------------------------------------------------------

loc_code_B78:				; CODE XREF: sub_code_B58+Cj
		mov	si, 0
		retn
sub_code_B58	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_B7C	proc near		; CODE XREF: sub_code_D98+Bp
					; sub_code_E84+15p ...
		mov	si, 1B8Ah

loc_code_B7F:				; CODE XREF: sub_code_B7C+Fj
		mov	al, [si]
		test	al, 80h
		jnz	short locret_code_B8D
		mov	byte ptr [si], 0
		add	si, 17h
		jmp	short loc_code_B7F
; ---------------------------------------------------------------------------

locret_code_B8D:			; CODE XREF: sub_code_B7C+7j
		retn
sub_code_B7C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_B8E	proc near		; CODE XREF: sub_code_CF+10p
					; sub_code_CF+1Bp ...
		mov	ax, word_data_94F8
		mov	word_data_942E,	ax
		mov	cs:word_code_D93, 28h	; '('
		mov	word_data_9430,	1
		mov	cx, 7

loc_code_BA4:				; CODE XREF: sub_code_B8E:loc_code_BC2j
		mov	si, 1B8Ah

loc_code_BA7:				; CODE XREF: sub_code_B8E+32j
		mov	al, [si]
		test	al, 80h
		jnz	short loc_code_BC2
		test	al, 1
		jz	short loc_code_BBD
		cmp	cl, [si+2]
		jnz	short loc_code_BBD
		push	cx
		push	si
		call	sub_code_BDC
		pop	si
		pop	cx

loc_code_BBD:				; CODE XREF: sub_code_B8E+21j
					; sub_code_B8E+26j
		add	si, 17h
		jmp	short loc_code_BA7
; ---------------------------------------------------------------------------

loc_code_BC2:				; CODE XREF: sub_code_B8E+1Dj
		loop	loc_code_BA4
		retn
sub_code_B8E	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_BC5	proc near		; CODE XREF: sub_code_69A+DBp
					; sub_code_69A+F3p ...
		mov	ax, 0A800h
		mov	word_data_942E,	ax
		mov	cs:word_code_D93, 20h	; ' '
		mov	word_data_9430,	0
		call	sub_code_BDC
		retn
sub_code_BC5	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_BDC	proc near		; CODE XREF: sub_code_B8E+2Ap
					; sub_code_BC5+13p
		mov	al, [si+0Bh]
		cbw
		mov	bx, [si+5]
		sub	bx, ax
		push	bx
		mov	al, [si+3]
		add	al, [si+0Ch]
		cbw
		neg	ax
		add	ax, [si+7]
		push	ax
		mov	al, [si+9]
		mov	ah, 0
		push	ax
		mov	al, [si+0Ah]
		mov	ah, 0
		push	ax
		mov	bx, [si+0Dh]
		mov	bx, [bx-6B18h]
		mov	al, [si+11h]
		mov	cs:byte_code_D95, al
		mov	cl, al
		shl	cl, 1
		shl	cl, 1
		shl	cl, 1
		shl	cl, 1
		or	al, cl
		mov	cs:byte_code_D96, al
		mov	si, [si+0Fh]
		call	sub_code_C24
		retn
sub_code_BDC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_C24	proc near		; CODE XREF: sub_code_BDC+44p

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		mov	ax, word_data_9430
		cmp	ax, 0
		jnz	short loc_code_C32
		jmp	loc_code_CBC
; ---------------------------------------------------------------------------

loc_code_C32:				; CODE XREF: sub_code_C24+9j
		mov	ax, [bp+arg_4]
		sub	ax, word_data_9528
		and	ax, 3FFh
		test	ax, 200h
		jz	short loc_code_C44
		or	ax, 0FC00h

loc_code_C44:				; CODE XREF: sub_code_C24+1Bj
		mov	[bp+arg_4], ax
		cmp	ax, 0
		jge	short loc_code_C77
		add	[bp+arg_0], ax
		jns	short loc_code_C54
		jmp	loc_code_D8F
; ---------------------------------------------------------------------------

loc_code_C54:				; CODE XREF: sub_code_C24+2Bj
		jnz	short loc_code_C59
		jmp	loc_code_D8F
; ---------------------------------------------------------------------------

loc_code_C59:				; CODE XREF: sub_code_C24:loc_code_C54j
		neg	ax
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		mov	cx, ax
		shl	ax, 1
		shl	ax, 1
		add	cx, ax
		shl	cx, 1
		shl	cx, 1
		add	si, cx
		mov	ax, 0
		mov	[bp+arg_4], ax
		jmp	short loc_code_C8F
; ---------------------------------------------------------------------------

loc_code_C77:				; CODE XREF: sub_code_C24+26j
		add	ax, [bp+arg_0]
		sub	ax, 0A0h ; ' '
		js	short loc_code_C8F
		neg	ax
		add	ax, [bp+arg_0]
		cmp	ax, 0
		jg	short loc_code_C8C
		jmp	loc_code_D8F
; ---------------------------------------------------------------------------

loc_code_C8C:				; CODE XREF: sub_code_C24+63j
		mov	[bp+arg_0], ax

loc_code_C8F:				; CODE XREF: sub_code_C24+51j
					; sub_code_C24+59j
		mov	ax, 20h	; ' '
		add	[bp+arg_6], ax
		mov	ax, 8
		add	[bp+arg_4], ax
		mov	ax, [bp+arg_6]
		cmp	ax, 20h	; ' '
		jge	short loc_code_CAB
		mov	ax, 20h	; ' '
		mov	[bp+arg_6], ax
		jmp	short loc_code_CBC
; ---------------------------------------------------------------------------

loc_code_CAB:				; CODE XREF: sub_code_C24+7Dj
		add	ax, [bp+arg_2]
		cmp	ax, 120h
		jle	short loc_code_CBC
		mov	ax, 120h
		sub	ax, [bp+arg_2]
		mov	[bp+arg_6], ax

loc_code_CBC:				; CODE XREF: sub_code_C24+Bj
					; sub_code_C24+85j ...
		push	ds
		push	bx
		mov	dx, 3CEh
		mov	ax, 0A05h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 7
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; color	masking	disable
					; bits 0-3 disable planes from compare logic in	read mode 01
		mov	ax, [bp+arg_6]
		mov	bx, [bp+arg_4]
		push	cx
		shl	bx, 1
		shl	bx, 1
		shl	bx, 1
		mov	cx, cs:word_code_D93
		cmp	cx, 28h	; '('
		jnz	short loc_code_CE4
		mov	di, bx
		jmp	short loc_code_CE7
; ---------------------------------------------------------------------------

loc_code_CE4:				; CODE XREF: sub_code_C24+BAj
		mov	di, 0

loc_code_CE7:				; CODE XREF: sub_code_C24+BEj
		shl	bx, 1
		shl	bx, 1
		add	di, bx
		mov	cl, al
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		add	di, ax
		and	cl, 7
		mov	ax, 80h	; '€'
		shr	ax, cl
		mov	ah, al
		mov	bx, word_data_942E
		mov	es, bx
		assume es:nothing
		pop	cx
		mov	cx, [bp+arg_2]
		shr	cx, 1
		mov	al, 8
		pop	ds
		mov	bx, [bp+arg_0]

loc_code_D13:				; CODE XREF: sub_code_C24+15Cj
		push	ax
		push	bx
		push	cx
		push	di
		push	si

loc_code_D18:				; CODE XREF: sub_code_C24:loc_code_D6Bj
		mov	bh, cs:byte_code_D96

loc_code_D1D:				; CODE XREF: sub_code_C24+107j
					; sub_code_C24:loc_code_D36j
		mov	bl, [si]
		inc	si
		cmp	bh, bl
		jnz	short loc_code_D3A
		shr	ah, 1
		jnz	short loc_code_D2F
		mov	ah, 40h	; '@'
		inc	di
		loop	loc_code_D1D
		jmp	short loc_code_D6D
; ---------------------------------------------------------------------------

loc_code_D2F:				; CODE XREF: sub_code_C24+102j
		shr	ah, 1
		jnz	short loc_code_D36
		mov	ah, 80h	; '€'
		inc	di

loc_code_D36:				; CODE XREF: sub_code_C24+10Dj
		loop	loc_code_D1D
		jmp	short loc_code_D6D
; ---------------------------------------------------------------------------

loc_code_D3A:				; CODE XREF: sub_code_C24+FEj
		mov	bh, bl
		shr	bl, 1
		shr	bl, 1
		shr	bl, 1
		shr	bl, 1
		cmp	bl, cs:byte_code_D95
		jz	short loc_code_D4F
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		and	es:[di], bl

loc_code_D4F:				; CODE XREF: sub_code_C24+125j
		shr	ah, 1
		jnz	short loc_code_D56
		mov	ah, 80h	; '€'
		inc	di

loc_code_D56:				; CODE XREF: sub_code_C24+12Dj
		and	bh, 0Fh
		cmp	bh, cs:byte_code_D95
		jz	short loc_code_D64
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		and	es:[di], bh

loc_code_D64:				; CODE XREF: sub_code_C24+13Aj
		shr	ah, 1
		jnz	short loc_code_D6B
		mov	ah, 80h	; '€'
		inc	di

loc_code_D6B:				; CODE XREF: sub_code_C24+142j
		loop	loc_code_D18

loc_code_D6D:				; CODE XREF: sub_code_C24+109j
					; sub_code_C24+114j
		pop	si
		add	si, 0A0h ; ' '
		pop	di
		add	di, cs:word_code_D93
		and	di, 7FFFh
		pop	cx
		pop	bx
		pop	ax
		dec	bx
		jnz	short loc_code_D13
		pop	ds
		mov	ax, 0FF08h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		mov	ax, 0F07h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register

loc_code_D8F:				; CODE XREF: sub_code_C24+2Dj
					; sub_code_C24+32j ...
		pop	bp
		retn	8
sub_code_C24	endp

; ---------------------------------------------------------------------------
word_code_D93	dw 28h			; DATA XREF: sub_code_B8E+6w
					; sub_code_BC5+6w ...
byte_code_D95	db 0			; DATA XREF: sub_code_BDC+2Dw
					; sub_code_C24+120r ...
byte_code_D96	db 0			; DATA XREF: sub_code_BDC+3Dw
					; sub_code_C24:loc_code_D18r
; ---------------------------------------------------------------------------
		retn

; =============== S U B	R O U T	I N E =======================================


sub_code_D98	proc near		; CODE XREF: sub_code_103+2Cp
		mov	word_data_9528,	1Ah
		mov	byte_data_9513,	0
		call	sub_code_B7C
		retn
sub_code_D98	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_DA7	proc near		; CODE XREF: sub_code_A9+1Cp
		call	sub_code_9A4
		call	sub_code_69A
		mov	byte_data_9519,	0
		mov	byte_data_951A,	0
		mov	byte_data_951B,	0
		call	sub_code_E3D
		retn
sub_code_DA7	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_DC0	proc near		; CODE XREF: sub_code_FDA+40p
		inc	byte_data_94FE
		mov	al, byte_data_94FE
		cmp	al, 6
		jb	short loc_code_DD3
		mov	word_data_94FC,	30h ; '0'
		jmp	short loc_code_DE5
; ---------------------------------------------------------------------------

loc_code_DD3:				; CODE XREF: sub_code_DC0+9j
		cmp	al, 3
		jb	short loc_code_DDF
		mov	word_data_94FC,	20h ; ' '
		jmp	short loc_code_DE5
; ---------------------------------------------------------------------------

loc_code_DDF:				; CODE XREF: sub_code_DC0+15j
		mov	word_data_94FC,	10h

loc_code_DE5:				; CODE XREF: sub_code_DC0+11j
					; sub_code_DC0+1Dj
		inc	byte_data_9501
		mov	al, byte_data_9501
		cmp	al, 7
		jbe	short loc_code_DF5
		mov	byte_data_9501,	1

loc_code_DF5:				; CODE XREF: sub_code_DC0+2Ej
		call	sub_code_9A4
		call	sub_code_69A
		mov	byte_data_9519,	0
		call	sub_code_E3D
		call	sub_code_2A7F
		retn
sub_code_DC0	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_E07	proc near		; CODE XREF: sub_code_FDA+10p
		mov	ax, word_data_9534
		cmp	ax, 0
		jnz	short loc_code_E15
		mov	byte_data_9500,	1
		retn
; ---------------------------------------------------------------------------

loc_code_E15:				; CODE XREF: sub_code_E07+6j
		call	sub_code_2329
		mov	al, byte_data_9502
		cmp	al, 0
		jz	short loc_code_E27
		mov	byte_data_9502,	0
		call	sub_code_69A

loc_code_E27:				; CODE XREF: sub_code_E07+16j
		call	sub_code_2200
		mov	byte_data_9519,	1
		mov	byte_data_951A,	0
		mov	byte_data_951B,	0
		call	sub_code_E3D
		retn
sub_code_E07	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_E3D	proc near		; CODE XREF: sub_code_DA7+15p
					; sub_code_DC0+40p ...
		mov	bl, byte_data_9501
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx+14F5h]
		and	ax, 3FFh
		mov	word_data_9528,	ax
		mov	ax, word_data_94FC
		mov	word_data_952A,	ax
		mov	word_data_950A,	80h ; '€'
		mov	byte_data_950E,	0
		mov	word_data_950F,	0
		mov	word_data_9511,	0
		mov	byte_data_9513,	0
		mov	byte_data_9515,	0
		mov	byte_data_9517,	0
		mov	byte_data_9432,	0
		call	sub_code_E84
		retn
sub_code_E3D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_E84	proc near		; CODE XREF: sub_code_E3D+43p
					; sub_code_FDA:loc_code_1031p
		mov	al, byte_data_950E
		cmp	al, 0
		jz	short loc_code_E93
		mov	byte_data_950E,	0
		call	sub_code_69A

loc_code_E93:				; CODE XREF: sub_code_E84+5j
		mov	word_data_952C,	0
		call	sub_code_B7C
		mov	si, 0D32h
		call	sub_code_B58
		mov	ax, word_data_950A
		mov	word_data_1B8F,	ax
		call	sub_code_1B57
		mov	ax, word_data_9528
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		sub	ax, 3
		and	ax, 3Fh
		mov	word_data_9507,	ax
		mov	cx, 0Fh

loc_code_EC2:				; CODE XREF: sub_code_E84+4Aj
		push	cx
		push	ax
		push	ax
		call	sub_code_8BA
		pop	ax
		pop	cx
		inc	ax
		and	ax, 3Fh
		loop	loc_code_EC2
		mov	al, byte_data_9432
		cmp	al, 0
		jz	short loc_code_EEA
		mov	si, 1B8Ah
		mov	bx, 0D49h
		mov	byte ptr [si+4], 0Ah
		call	sub_code_2121
		mov	byte_data_1B9C,	23h ; '#'
		retn
; ---------------------------------------------------------------------------

loc_code_EEA:				; CODE XREF: sub_code_E84+51j
		mov	al, byte_data_9519
		cmp	al, 0
		jz	short loc_code_F08
		mov	byte_data_9519,	0
		mov	si, 0DA2h
		mov	ax, word_data_1B91
		mov	[si+7],	ax
		mov	al, byte_data_1B8D
		mov	[si+3],	al
		call	sub_code_B58

loc_code_F08:				; CODE XREF: sub_code_E84+6Bj
		call	sub_code_F9D
		mov	al, byte_data_951A
		cmp	al, 0
		jz	short loc_code_F23
		mov	byte_data_951A,	1
		mov	si, 0DC3h
		and	byte ptr [si], 0DFh
		call	sub_code_1CD9
		call	sub_code_B58

loc_code_F23:				; CODE XREF: sub_code_E84+8Cj
		mov	al, byte_data_951B
		cmp	al, 0
		jz	short locret_code_F3B
		mov	byte_data_951B,	1
		mov	si, 0DC3h
		or	byte ptr [si], 20h
		call	sub_code_1CD9
		call	sub_code_B58

locret_code_F3B:			; CODE XREF: sub_code_E84+A4j
		retn
sub_code_E84	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_F3C	proc near		; CODE XREF: sub_code_FDA+2Dp
		mov	byte_data_951C,	0
		call	sub_code_2DDC
		mov	word_data_9528,	1Ah
		mov	word_data_9547,	0
		mov	word_data_951E,	0
		mov	byte_data_9524,	0
		mov	byte_data_9549,	3
		call	sub_code_B7C
		mov	si, 0D04h
		call	sub_code_B58
		call	sub_code_2DF6
		mov	al, byte_data_951A
		cmp	al, 0
		jz	short loc_code_F84
		mov	byte_data_951A,	1
		mov	si, 0D1Bh
		and	byte ptr [si], 0DFh
		call	sub_code_2F50
		call	sub_code_B58

loc_code_F84:				; CODE XREF: sub_code_F3C+35j
		mov	al, byte_data_951B
		cmp	al, 0
		jz	short locret_code_F9C
		mov	byte_data_951B,	1
		mov	si, 0D1Bh
		or	byte ptr [si], 20h
		call	sub_code_2F50
		call	sub_code_B58

locret_code_F9C:			; CODE XREF: sub_code_F3C+4Dj
		retn
sub_code_F3C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_F9D	proc near		; CODE XREF: sub_code_E84:loc_code_F08p
		mov	ax, word_data_1B8F
		mov	word_data_9433,	ax
		mov	word_data_9435,	ax
		mov	word_data_9437,	ax
		mov	word_data_9439,	ax
		mov	ax, word_data_1B91
		mov	word_data_943B,	ax
		mov	word_data_943D,	ax
		mov	word_data_943F,	ax
		mov	word_data_9441,	ax
		mov	al, byte_data_1B8E
		mov	byte_data_9443,	al
		mov	byte_data_9444,	al
		mov	byte_data_9445,	al
		mov	byte_data_9446,	al
		mov	al, byte_data_1B8D
		mov	byte_data_9447,	al
		mov	byte_data_9448,	al
		mov	byte_data_9449,	al
		mov	byte_data_944A,	al
		retn
sub_code_F9D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_FDA	proc near		; CODE XREF: sub_code_CF+3p
					; sub_code_103+32p ...
		mov	al, byte_data_94FF
		mov	byte_data_9509,	al
		mov	si, 1B8Ah

loc_code_FE3:				; CODE XREF: sub_code_FDA+7Dj
		mov	al, byte_data_9513
		cmp	al, 0
		jz	short loc_code_FF5
		call	sub_code_E07
		mov	al, byte_data_9500
		cmp	al, 0
		jz	short sub_code_FDA
		retn
; ---------------------------------------------------------------------------

loc_code_FF5:				; CODE XREF: sub_code_FDA+Ej
		mov	al, byte_data_94FF
		cmp	al, byte_data_9509
		jz	short loc_code_1036
		cmp	al, 1
		jnz	short loc_code_100E
		mov	al, 0Bh
		call	sub_code_3840
		call	sub_code_F3C
		jmp	short sub_code_FDA
; ---------------------------------------------------------------------------
		jmp	short loc_code_1036
; ---------------------------------------------------------------------------

loc_code_100E:			; CODE XREF: sub_code_FDA+26j
		mov	al, 0Bh
		call	sub_code_3840
		mov	al, byte_data_951D
		cmp	al, 0F0h ; 'ð'
		jnz	short loc_code_101F
		call	sub_code_DC0
		jmp	short loc_code_1034
; ---------------------------------------------------------------------------

loc_code_101F:			; CODE XREF: sub_code_FDA+3Ej
		mov	al, byte_data_1BA0
		and	al, 7Fh
		cmp	al, 28h	; '('
		jbe	short loc_code_1031
		cmp	al, 58h	; 'X'
		jnb	short loc_code_1031
		mov	byte_data_9432,	1

loc_code_1031:			; CODE XREF: sub_code_FDA+4Cj
					; sub_code_FDA+50j
		call	sub_code_E84

loc_code_1034:			; CODE XREF: sub_code_FDA+43j
		jmp	short sub_code_FDA
; ---------------------------------------------------------------------------

loc_code_1036:			; CODE XREF: sub_code_FDA+22j
					; sub_code_FDA+32j
		mov	al, [si]
		test	al, 80h
		jnz	short locret_code_1059
		test	al, 2
		jz	short loc_code_1054
		push	si
		mov	bl, [si+12h]
		cmp	bl, 0
		jz	short loc_code_1053
		mov	bh, 0
		dec	bx
		shl	bx, 1
		call	cs:off_code_105A[bx]

loc_code_1053:			; CODE XREF: sub_code_FDA+6Dj
		pop	si

loc_code_1054:			; CODE XREF: sub_code_FDA+64j
		add	si, 17h
		jmp	short loc_code_FE3
; ---------------------------------------------------------------------------

locret_code_1059:			; CODE XREF: sub_code_FDA+60j
		retn
sub_code_FDA	endp

; ---------------------------------------------------------------------------
off_code_105A	dw offset sub_code_1108 ; DATA XREF: sub_code_FDA+74r
		dw offset sub_code_176C
		dw offset sub_code_1783
		dw offset sub_code_10C6
		dw offset sub_code_17AC
		dw offset sub_code_17D6
		dw offset sub_code_18A9
		dw offset sub_code_1A9E
		dw offset sub_code_10C6
		dw offset sub_code_1993
		dw offset sub_code_19C2
		dw offset sub_code_2E02
		dw offset sub_code_10C6
		dw offset sub_code_2FE8
		dw offset sub_code_300A
		dw offset sub_code_16FE
		dw offset sub_code_12CB
		dw offset sub_code_10C6
		dw offset sub_code_12EB
		dw offset sub_code_15FC
		dw offset sub_code_16DF
		dw offset sub_code_16D6
		dw offset sub_code_1740
		dw offset sub_code_1384
		dw offset sub_code_13A8
		dw offset sub_code_14F0
		dw offset sub_code_10F3
		dw offset sub_code_18C7
		dw offset sub_code_1429
		dw offset sub_code_17F4
		dw offset sub_code_171F
		dw offset sub_code_1B09
		dw offset sub_code_1B4A
		dw offset sub_code_2F50
		dw offset sub_code_12A7

; =============== S U B	R O U T	I N E =======================================


sub_code_10A0	proc near		; CODE XREF: sub_code_10F3+11p
					; sub_code_12EBp ...
		mov	al, [si+0Ah]
		sub	al, [si+3]
		sub	al, [si+0Ch]
		cbw
		add	ax, [si+7]
		and	ax, 3FFh
		mov	bx, word_data_9528
		cmp	ax, bx
		jnb	short loc_code_10BB
		add	ax, 400h

loc_code_10BB:			; CODE XREF: sub_code_10A0+16j
		sub	ax, bx
		cmp	ax, 200h
		jbe	short locret_code_10C5
		mov	byte ptr [si], 0

locret_code_10C5:			; CODE XREF: sub_code_10A0+20j
		retn
sub_code_10A0	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_10C6	proc near		; CODE XREF: sub_code_FDA+74p
					; sub_code_1429p ...
		mov	al, [si+3]
		add	al, [si+0Ch]
		cbw
		neg	ax
		add	ax, [si+7]
		and	ax, 3FFh
		mov	bx, word_data_9528
		add	bx, 0A0h ; ' '
		and	bx, 3FFh
		cmp	ax, bx
		jnb	short loc_code_10E8
		add	ax, 400h

loc_code_10E8:			; CODE XREF: sub_code_10C6+1Dj
		sub	ax, bx
		cmp	ax, 200h
		jnb	short locret_code_10F2
		mov	byte ptr [si], 0

locret_code_10F2:			; CODE XREF: sub_code_10C6+27j
		retn
sub_code_10C6	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_10F3	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:108Eo
		inc	byte ptr [si+16h]
		mov	al, [si+16h]
		cmp	al, 8
		jbe	short loc_code_10FF
		mov	al, 8

loc_code_10FF:			; CODE XREF: sub_code_10F3+8j
		mov	ah, 0
		sub	[si+7],	ax
		call	sub_code_10A0
		retn
sub_code_10F3	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1108	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:off_code_105Ao
		call	sub_code_1B80
		call	sub_code_1BB9
		mov	bx, word_data_954C
		mov	ax, word_data_952C
		test	bl, 1
		jz	short loc_code_1131
		sub	ax, 1
		js	short loc_code_1127
		cmp	ax, 4
		jle	short loc_code_1127
		mov	ax, 4

loc_code_1127:			; CODE XREF: sub_code_1108+15j
					; sub_code_1108+1Aj
		cmp	ax, 0FFE8h
		jge	short loc_code_112F
		mov	ax, 0FFE8h

loc_code_112F:			; CODE XREF: sub_code_1108+22j
		jmp	short loc_code_1158
; ---------------------------------------------------------------------------

loc_code_1131:			; CODE XREF: sub_code_1108+10j
		test	bl, 2
		jz	short loc_code_114D
		add	ax, 1
		jns	short loc_code_1143
		cmp	ax, 0FFFCh
		jge	short loc_code_1143
		mov	ax, 0FFFCh

loc_code_1143:			; CODE XREF: sub_code_1108+31j
					; sub_code_1108+36j
		cmp	ax, 18h
		jle	short loc_code_114B
		mov	ax, 18h

loc_code_114B:			; CODE XREF: sub_code_1108+3Ej
		jmp	short loc_code_1158
; ---------------------------------------------------------------------------

loc_code_114D:			; CODE XREF: sub_code_1108+2Cj
		cmp	ax, 0
		jz	short loc_code_1158
		jle	short loc_code_1157
		dec	ax
		jmp	short loc_code_1158
; ---------------------------------------------------------------------------

loc_code_1157:			; CODE XREF: sub_code_1108+4Aj
		inc	ax

loc_code_1158:			; CODE XREF: sub_code_1108:loc_code_112Fj
					; sub_code_1108:loc_code_114Bj ...
		mov	word_data_952C,	ax
		add	ax, 3
		sar	ax, 1
		sar	ax, 1
		add	ax, word_data_1B8F
		cmp	ax, 14h
		jge	short loc_code_1174
		mov	ax, 14h
		mov	word_data_952C,	0

loc_code_1174:			; CODE XREF: sub_code_1108+61j
		cmp	ax, 0ECh ; 'ì'
		jle	short loc_code_1182
		mov	ax, 0ECh ; 'ì'
		mov	word_data_952C,	0

loc_code_1182:			; CODE XREF: sub_code_1108+6Fj
		mov	word_data_1B8F,	ax
		mov	al, byte_data_1B8E
		cmp	al, 0
		jz	short loc_code_118F
		call	sub_code_1B57

loc_code_118F:			; CODE XREF: sub_code_1108+82j
		call	sub_code_1C78
		call	sub_code_A51
		cmp	ax, 0
		jz	short loc_code_119F
		call	sub_code_1C56
		jmp	short loc_code_11BC
; ---------------------------------------------------------------------------

loc_code_119F:			; CODE XREF: sub_code_1108+90j
		inc	byte_data_1B9E
		and	byte_data_1B9E,	3Fh
		call	sub_code_A51
		cmp	ax, 0
		jz	short loc_code_11B3
		call	sub_code_1C56

loc_code_11B3:			; CODE XREF: sub_code_1108+A6j
		dec	byte_data_1B9E
		and	byte_data_1B9E,	3Fh

loc_code_11BC:			; CODE XREF: sub_code_1108+95j
		mov	ax, word_data_9542
		cmp	ax, 0
		jg	short loc_code_11C8
		call	sub_code_1C33
		retn
; ---------------------------------------------------------------------------

loc_code_11C8:			; CODE XREF: sub_code_1108+BAj
		mov	al, byte_data_1B8E
		cmp	al, 0
		jnz	short loc_code_11DE
		inc	byte_data_9515
		mov	al, byte_data_9515
		cmp	al, 4
		jb	short locret_code_11DD
		call	sub_code_1C33

locret_code_11DD:			; CODE XREF: sub_code_1108+D0j
		retn
; ---------------------------------------------------------------------------

loc_code_11DE:			; CODE XREF: sub_code_1108+C5j
		mov	ax, word_data_953E
		cmp	ax, 0
		jle	short loc_code_11F0
		mov	ax, word_data_954C
		test	al, 80h
		jz	short loc_code_11F0
		call	sub_code_1D1E

loc_code_11F0:			; CODE XREF: sub_code_1108+DCj
					; sub_code_1108+E3j
		mov	ax, word_data_954C
		mov	bl, byte_data_951A
		test	al, 40h
		jz	short loc_code_1235
		cmp	bl, 0
		jnz	short loc_code_1224
		mov	ax, word_data_9536
		cmp	ax, 0
		jbe	short loc_code_1222
		mov	byte_data_951A,	1
		mov	si, 0DC3h
		and	byte ptr [si], 0DFh
		call	sub_code_1CD9
		call	sub_code_B58
		dec	word_data_9538
		mov	al, 1
		call	sub_code_3840

loc_code_1222:			; CODE XREF: sub_code_1108+FEj
		jmp	short loc_code_1233
; ---------------------------------------------------------------------------

loc_code_1224:			; CODE XREF: sub_code_1108+F6j
		cmp	bl, 2
		jnz	short loc_code_1233
		mov	byte_data_951A,	3
		mov	al, 2
		call	sub_code_3840

loc_code_1233:			; CODE XREF: sub_code_1108:loc_code_1222j
					; sub_code_1108+11Fj
		jmp	short loc_code_124B
; ---------------------------------------------------------------------------

loc_code_1235:			; CODE XREF: sub_code_1108+F1j
		cmp	bl, 1
		jnz	short loc_code_1241
		mov	byte_data_951A,	2
		jmp	short loc_code_124B
; ---------------------------------------------------------------------------

loc_code_1241:			; CODE XREF: sub_code_1108+130j
		cmp	bl, 3
		jnz	short loc_code_124B
		mov	byte_data_951A,	0

loc_code_124B:			; CODE XREF: sub_code_1108:loc_code_1233j
					; sub_code_1108+137j	...
		mov	ax, word_data_954C
		mov	bl, byte_data_951B
		test	al, 20h
		jz	short loc_code_1290
		cmp	bl, 0
		jnz	short loc_code_127F
		mov	ax, word_data_9536
		cmp	ax, 0
		jbe	short loc_code_127D
		mov	byte_data_951B,	1
		mov	si, 0DC3h
		or	byte ptr [si], 20h
		call	sub_code_1CD9
		call	sub_code_B58
		dec	word_data_9538
		mov	al, 1
		call	sub_code_3840

loc_code_127D:			; CODE XREF: sub_code_1108+159j
		jmp	short loc_code_128E
; ---------------------------------------------------------------------------

loc_code_127F:			; CODE XREF: sub_code_1108+151j
		cmp	bl, 2
		jnz	short loc_code_128E
		mov	byte_data_951B,	3
		mov	al, 2
		call	sub_code_3840

loc_code_128E:			; CODE XREF: sub_code_1108:loc_code_127Dj
					; sub_code_1108+17Aj
		jmp	short locret_code_12A6
; ---------------------------------------------------------------------------

loc_code_1290:			; CODE XREF: sub_code_1108+14Cj
		cmp	bl, 1
		jnz	short loc_code_129C
		mov	byte_data_951B,	2
		jmp	short locret_code_12A6
; ---------------------------------------------------------------------------

loc_code_129C:			; CODE XREF: sub_code_1108+18Bj
		cmp	bl, 3
		jnz	short locret_code_12A6
		mov	byte_data_951B,	0

locret_code_12A6:			; CODE XREF: sub_code_1108:loc_code_128Ej
					; sub_code_1108+192j	...
		retn
sub_code_1108	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_12A7	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:109Eo
		mov	ax, word_data_952A
		sub	ax, 3
		js	short loc_code_12B4
		mov	word_data_952A,	ax
		jmp	short loc_code_12B7
; ---------------------------------------------------------------------------

loc_code_12B4:			; CODE XREF: sub_code_12A7+6j
		call	sub_code_1C33

loc_code_12B7:			; CODE XREF: sub_code_12A7+Bj
		call	sub_code_1BB9
		call	sub_code_1B57
		mov	si, 1B8Ah
		mov	bx, 0D49h
		mov	byte ptr [si+4], 0Ah
		call	sub_code_2121
		retn
sub_code_12A7	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_12CB	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:107Ao
		mov	ax, word_data_952A
		dec	ax
		js	short loc_code_12D4
		mov	word_data_952A,	ax

loc_code_12D4:			; CODE XREF: sub_code_12CB+4j
		call	sub_code_1BB9
		call	sub_code_1B57
		inc	byte_data_9514
		mov	al, byte_data_9514
		cmp	al, 28h	; '('
		jb	short locret_code_12EA
		mov	byte_data_9513,	1

locret_code_12EA:			; CODE XREF: sub_code_12CB+18j
		retn
sub_code_12CB	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_12EB	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:107Eo
		call	sub_code_10A0
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_12F5
		retn
; ---------------------------------------------------------------------------

loc_code_12F5:			; CODE XREF: sub_code_12EB+7j
		sub	word ptr [si+7], 10h
		and	word ptr [si+7], 3FFh
		mov	al, [si+4]
		cmp	al, 1
		jnz	short loc_code_1312
		mov	al, [si+3]
		cmp	al, 9Ch	; 'œ'
		jle	short loc_code_1310
		sub	byte ptr [si+3], 8

loc_code_1310:			; CODE XREF: sub_code_12EB+1Fj
		jmp	short loc_code_1321
; ---------------------------------------------------------------------------

loc_code_1312:			; CODE XREF: sub_code_12EB+18j
		cmp	al, 2
		jnz	short loc_code_1321
		mov	al, [si+3]
		cmp	al, 64h	; 'd'
		jge	short loc_code_1321
		add	byte ptr [si+3], 8

loc_code_1321:			; CODE XREF: sub_code_12EB:loc_code_1310j
					; sub_code_12EB+29j ...
		push	si
		mov	ax, [si+5]
		push	ax
		mov	ax, [si+7]
		push	ax
		call	sub_code_7FD
		pop	si
		cmp	al, [si+3]
		jl	short loc_code_1338
		call	sub_code_2092
		jmp	short locret_code_1383
; ---------------------------------------------------------------------------

loc_code_1338:			; CODE XREF: sub_code_12EB+46j
		push	si
		mov	ax, [si+5]
		push	ax
		mov	[si+14h], cl
		push	cx
		call	sub_code_AD5
		pop	si
		cmp	ax, 0
		jz	short locret_code_1383
		push	si
		mov	al, [si+14h]
		mov	ah, 0
		push	bx
		push	ax
		call	sub_code_1C0A
		mov	al, [si]
		test	al, 80h
		jnz	short loc_code_1382
		pop	bx
		push	bx
		mov	al, [si+3]
		sub	al, [bx+3]
		jns	short loc_code_1367
		neg	al

loc_code_1367:			; CODE XREF: sub_code_12EB+78j
		cmp	al, 10h
		jnb	short loc_code_1382
		dec	byte ptr [si+15h]
		jns	short loc_code_137A
		call	sub_code_20DB
		mov	al, 6
		call	sub_code_3840
		jmp	short loc_code_137D
; ---------------------------------------------------------------------------

loc_code_137A:			; CODE XREF: sub_code_12EB+83j
		call	sub_code_2662

loc_code_137D:			; CODE XREF: sub_code_12EB+8Dj
		pop	si
		push	si
		call	sub_code_2047

loc_code_1382:			; CODE XREF: sub_code_12EB+6Ej
					; sub_code_12EB+7Ej
		pop	si

locret_code_1383:			; CODE XREF: sub_code_12EB+4Bj
					; sub_code_12EB+5Dj
		retn
sub_code_12EB	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1384	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1088o
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jnz	short loc_code_138E
		mov	byte ptr [si], 0

loc_code_138E:			; CODE XREF: sub_code_1384+5j
		call	sub_code_1CD9
		mov	al, [si]
		test	al, 20h
		jnz	short loc_code_139C
		mov	al, byte_data_951A
		jmp	short loc_code_139F
; ---------------------------------------------------------------------------

loc_code_139C:			; CODE XREF: sub_code_1384+11j
		mov	al, byte_data_951B

loc_code_139F:			; CODE XREF: sub_code_1384+16j
		cmp	al, 3
		jnz	short locret_code_13A7
		mov	byte ptr [si+12h], 19h

locret_code_13A7:			; CODE XREF: sub_code_1384+1Dj
		retn
sub_code_1384	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_13A8	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:108Ao
		call	sub_code_10A0
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_13B2
		retn
; ---------------------------------------------------------------------------

loc_code_13B2:			; CODE XREF: sub_code_13A8+7j
		sub	word ptr [si+7], 6
		and	word ptr [si+7], 3FFh
		push	si
		mov	ax, [si+5]
		push	ax
		mov	ax, [si+7]
		push	ax
		call	sub_code_7FD
		pop	si
		add	al, 4
		mov	[si+3],	al
		mov	[si+14h], cl
		mov	[si+4],	bl
		mov	bx, 0DDAh
		call	sub_code_2121
		mov	al, [si+4]
		cmp	al, 0
		jnz	short loc_code_13F5
		add	word ptr [si+7], 4
		and	word ptr [si+7], 3FFh
		dec	byte ptr [si+15h]
		jns	short loc_code_13F5
		call	sub_code_20F0
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_13F5:			; CODE XREF: sub_code_13A8+36j
					; sub_code_13A8+44j
		push	si
		mov	ax, [si+5]
		push	ax
		mov	cl, [si+14h]
		mov	ch, 0
		push	cx
		call	sub_code_AD5
		pop	si
		cmp	ax, 0
		jz	short locret_code_1428
		push	si
		mov	al, [si+14h]
		mov	ah, 0
		push	bx
		push	ax
		call	sub_code_1C0A
		mov	al, [si]
		test	al, 80h
		jnz	short loc_code_1427
		call	sub_code_20DB
		mov	al, 6
		call	sub_code_3840
		pop	si
		push	si
		mov	byte ptr [si], 0

loc_code_1427:			; CODE XREF: sub_code_13A8+70j
		pop	si

locret_code_1428:			; CODE XREF: sub_code_13A8+5Fj
		retn
sub_code_13A8	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1429	proc near		; CODE XREF: sub_code_FDA+74p
					; sub_code_1FBA+46p
					; DATA XREF: ...
		call	sub_code_10C6
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_1433
		retn
; ---------------------------------------------------------------------------

loc_code_1433:			; CODE XREF: sub_code_1429+7j
		mov	al, [si+1]
		cmp	al, 2
		jnz	short loc_code_1440
		add	word ptr [si+7], 5
		jmp	short loc_code_146A
; ---------------------------------------------------------------------------

loc_code_1440:			; CODE XREF: sub_code_1429+Fj
		cmp	al, 0
		jnz	short loc_code_144A
		sub	word ptr [si+5], 5
		jmp	short loc_code_146A
; ---------------------------------------------------------------------------

loc_code_144A:			; CODE XREF: sub_code_1429+19j
		cmp	al, 1
		jnz	short loc_code_1458
		sub	word ptr [si+5], 3
		add	word ptr [si+7], 2
		jmp	short loc_code_146A
; ---------------------------------------------------------------------------

loc_code_1458:			; CODE XREF: sub_code_1429+23j
		cmp	al, 3
		jnz	short loc_code_1466
		add	word ptr [si+5], 3
		add	word ptr [si+7], 2
		jmp	short loc_code_146A
; ---------------------------------------------------------------------------

loc_code_1466:			; CODE XREF: sub_code_1429+31j
		add	word ptr [si+5], 5

loc_code_146A:			; CODE XREF: sub_code_1429+15j
					; sub_code_1429+1Fj ...
		and	word ptr [si+7], 3FFh
		mov	ax, [si+5]
		cmp	ax, 0Ch
		jge	short loc_code_147B
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_147B:			; CODE XREF: sub_code_1429+4Cj
		cmp	ax, 0F4h ; 'ô'
		jle	short loc_code_1484
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_1484:			; CODE XREF: sub_code_1429+55j
		push	si
		mov	ax, [si+5]
		push	ax
		mov	ax, [si+7]
		push	ax
		call	sub_code_7FD
		pop	si
		add	al, 8
		mov	[si+3],	al
		mov	[si+14h], cl
		mov	[si+4],	bl
		mov	bl, [si+1]
		mov	bh, 0
		shl	bx, 1
		mov	bx, [bx+10FFh]
		call	sub_code_2121
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jnz	short loc_code_14B2
		retn
; ---------------------------------------------------------------------------

loc_code_14B2:			; CODE XREF: sub_code_1429+86j
		mov	ax, [si+5]
		sub	ax, word_data_1B8F
		jns	short loc_code_14BD
		neg	ax

loc_code_14BD:			; CODE XREF: sub_code_1429+90j
		cmp	ax, 10h
		jnb	short locret_code_14EF
		mov	ax, [si+7]
		sub	ax, word_data_1B91
		sub	ax, 8
		jns	short loc_code_14D0
		neg	ax

loc_code_14D0:			; CODE XREF: sub_code_1429+A3j
		cmp	ax, 10h
		jnb	short locret_code_14EF
		mov	al, 5
		call	sub_code_3840
		sub	word_data_9544,	64h ; 'd'
		mov	byte_data_12A0,	1
		call	sub_code_20F0
		mov	byte_data_12A0,	5
		mov	byte ptr [si], 0

locret_code_14EF:			; CODE XREF: sub_code_1429+97j
					; sub_code_1429+AAj
		retn
sub_code_1429	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_14F0	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:108Co
		add	word ptr [si+7], 1
		push	si
		mov	ax, [si+5]
		push	ax
		mov	ax, [si+7]
		push	ax
		call	sub_code_7FD
		pop	si
		mov	[si+3],	al
		mov	[si+14h], cl
		mov	[si+4],	bl
		mov	bl, [si+1]
		mov	bh, 0
		shl	bx, 1
		mov	bx, [bx+0FE1h]
		call	sub_code_2121
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jz	short loc_code_1548
		mov	ax, [si+5]
		sub	ax, word_data_1B8F
		jns	short loc_code_152A
		neg	ax

loc_code_152A:			; CODE XREF: sub_code_14F0+36j
		cmp	ax, 1Ah
		jnb	short loc_code_1548
		mov	ax, [si+7]
		sub	ax, word_data_1B91
		jns	short loc_code_153A
		neg	ax

loc_code_153A:			; CODE XREF: sub_code_14F0+46j
		cmp	ax, 12h
		jnb	short loc_code_1548
		sub	word_data_9544,	0Ch
		mov	byte ptr [si+15h], 0FFh

loc_code_1548:			; CODE XREF: sub_code_14F0+2Dj
					; sub_code_14F0+3Dj ...
		mov	di, 1BA1h

loc_code_154B:			; CODE XREF: sub_code_14F0+CEj
		mov	al, [si+15h]
		cmp	al, 0
		jge	short loc_code_1561
		mov	al, 7
		call	sub_code_3840
		call	sub_code_20F0
		mov	byte ptr [si], 0
		call	sub_code_2676
		retn
; ---------------------------------------------------------------------------

loc_code_1561:			; CODE XREF: sub_code_14F0+60j
		mov	al, [di]
		test	al, 80h
		jnz	short loc_code_15C0
		test	al, 40h
		jz	short loc_code_15BB
		push	di
		mov	ax, [di+5]
		sub	ax, [si+5]
		jns	short loc_code_1576
		neg	ax

loc_code_1576:			; CODE XREF: sub_code_14F0+82j
		cmp	ax, 14h
		jnb	short loc_code_15BA
		mov	ax, [di+7]
		sub	ax, [si+7]
		jns	short loc_code_1585
		neg	ax

loc_code_1585:			; CODE XREF: sub_code_14F0+91j
		cmp	ax, 10h
		jnb	short loc_code_15BA
		mov	al, [di+12h]
		cmp	al, 19h
		jnz	short loc_code_159A
		mov	byte ptr [si+15h], 0FFh
		mov	byte ptr [di], 0
		jmp	short loc_code_15BA
; ---------------------------------------------------------------------------

loc_code_159A:			; CODE XREF: sub_code_14F0+9Fj
		mov	al, [di+3]
		sub	al, [si+3]
		jns	short loc_code_15A4
		neg	al

loc_code_15A4:			; CODE XREF: sub_code_14F0+B0j
		cmp	al, 10h
		jnb	short loc_code_15BA
		dec	byte ptr [si+15h]
		push	si
		mov	si, di
		call	sub_code_2092
		mov	al, 3
		call	sub_code_3840
		call	sub_code_2662
		pop	si

loc_code_15BA:			; CODE XREF: sub_code_14F0+89j
					; sub_code_14F0+98j ...
		pop	di

loc_code_15BB:			; CODE XREF: sub_code_14F0+79j
		add	di, 17h
		jmp	short loc_code_154B
; ---------------------------------------------------------------------------

loc_code_15C0:			; CODE XREF: sub_code_14F0+75j
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jz	short loc_code_15F8
		mov	ax, word_data_1B91
		cmp	ax, [si+7]
		jbe	short loc_code_15F8
		mov	ax, word_data_1B8F
		sub	ax, [si+5]
		jns	short loc_code_15D9
		neg	ax

loc_code_15D9:			; CODE XREF: sub_code_14F0+E5j
		cmp	ax, 20h	; ' '
		jnb	short loc_code_15F8
		dec	byte ptr [si+16h]
		jns	short loc_code_15EE
		mov	byte ptr [si+16h], 7
		mov	byte_data_9518,	1
		jmp	short loc_code_15F3
; ---------------------------------------------------------------------------

loc_code_15EE:			; CODE XREF: sub_code_14F0+F1j
		mov	byte_data_9518,	0

loc_code_15F3:			; CODE XREF: sub_code_14F0+FCj
		push	si
		call	sub_code_1DEF
		pop	si

loc_code_15F8:			; CODE XREF: sub_code_14F0+D5j
					; sub_code_14F0+DDj ...
		call	sub_code_10C6
		retn
sub_code_14F0	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_15FC	proc near		; CODE XREF: sub_code_FDA+74p
					; sub_code_1E7D+89p ...
		call	sub_code_10C6
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_1606
		retn
; ---------------------------------------------------------------------------

loc_code_1606:			; CODE XREF: sub_code_15FC+7j
		mov	al, [si+1]
		cmp	al, 2
		jnz	short loc_code_1613
		add	word ptr [si+7], 8
		jmp	short loc_code_163D
; ---------------------------------------------------------------------------

loc_code_1613:			; CODE XREF: sub_code_15FC+Fj
		cmp	al, 0
		jnz	short loc_code_161D
		sub	word ptr [si+5], 8
		jmp	short loc_code_163D
; ---------------------------------------------------------------------------

loc_code_161D:			; CODE XREF: sub_code_15FC+19j
		cmp	al, 1
		jnz	short loc_code_162B
		sub	word ptr [si+5], 6
		add	word ptr [si+7], 4
		jmp	short loc_code_163D
; ---------------------------------------------------------------------------

loc_code_162B:			; CODE XREF: sub_code_15FC+23j
		cmp	al, 3
		jnz	short loc_code_1639
		add	word ptr [si+5], 6
		add	word ptr [si+7], 4
		jmp	short loc_code_163D
; ---------------------------------------------------------------------------

loc_code_1639:			; CODE XREF: sub_code_15FC+31j
		add	word ptr [si+5], 8

loc_code_163D:			; CODE XREF: sub_code_15FC+15j
					; sub_code_15FC+1Fj ...
		and	word ptr [si+7], 3FFh
		mov	ax, [si+5]
		cmp	ax, 4
		jge	short loc_code_164E
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_164E:			; CODE XREF: sub_code_15FC+4Cj
		cmp	ax, 0FCh ; 'ü'
		jle	short loc_code_1657
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_1657:			; CODE XREF: sub_code_15FC+55j
		mov	al, [si+4]
		cmp	al, 1
		jnz	short loc_code_166B
		mov	al, [si+3]
		cmp	al, 64h	; 'd'
		jge	short loc_code_1669
		add	byte ptr [si+3], 4

loc_code_1669:			; CODE XREF: sub_code_15FC+67j
		jmp	short loc_code_167A
; ---------------------------------------------------------------------------

loc_code_166B:			; CODE XREF: sub_code_15FC+60j
		cmp	al, 2
		jnz	short loc_code_167A
		mov	al, [si+3]
		cmp	al, 9Ch	; 'œ'
		jle	short loc_code_167A
		sub	byte ptr [si+3], 4

loc_code_167A:			; CODE XREF: sub_code_15FC:loc_code_1669j
					; sub_code_15FC+71j ...
		push	si
		mov	ax, [si+5]
		push	ax
		mov	ax, [si+7]
		push	ax
		call	sub_code_7FD
		pop	si
		cmp	al, [si+3]
		jl	short loc_code_1691
		call	sub_code_2092
		jmp	short locret_code_16D5
; ---------------------------------------------------------------------------

loc_code_1691:			; CODE XREF: sub_code_15FC+8Ej
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jnz	short loc_code_1699
		retn
; ---------------------------------------------------------------------------

loc_code_1699:			; CODE XREF: sub_code_15FC+9Aj
		mov	ax, [si+5]
		sub	ax, word_data_1B8F
		jns	short loc_code_16A4
		neg	ax

loc_code_16A4:			; CODE XREF: sub_code_15FC+A4j
		cmp	ax, 0Ch
		jnb	short locret_code_16D5
		mov	ax, [si+7]
		sub	ax, word_data_1B91
		jns	short loc_code_16B4
		neg	ax

loc_code_16B4:			; CODE XREF: sub_code_15FC+B4j
		cmp	ax, 8
		jnb	short locret_code_16D5
		mov	al, [si+3]
		sub	al, byte_data_1B8D
		jns	short loc_code_16C4
		neg	al

loc_code_16C4:			; CODE XREF: sub_code_15FC+C4j
		cmp	al, 10h
		jnb	short locret_code_16D5
		sub	word_data_9544,	1
		call	sub_code_2092
		mov	al, 4
		call	sub_code_3840

locret_code_16D5:			; CODE XREF: sub_code_15FC+93j
					; sub_code_15FC+ABj ...
		retn
sub_code_15FC	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_16D6	proc near		; CODE XREF: sub_code_FDA+74p
					; sub_code_1E7D+30p ...
		dec	byte ptr [si+4]
		jns	short locret_code_16DE
		mov	byte ptr [si], 0

locret_code_16DE:			; CODE XREF: sub_code_16D6+3j
		retn
sub_code_16D6	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_16DF	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1082o
		mov	al, [si+4]
		inc	byte ptr [si+4]
		cmp	al, 4
		jb	short loc_code_16ED
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_16ED:			; CODE XREF: sub_code_16DF+8j
		shl	al, 1
		mov	bl, al
		mov	bh, 0
		mov	ax, [bx+143Eh]
		mov	[si+0Fh], ax
		call	sub_code_10C6
		retn
sub_code_16DF	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_16FE	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1078o
		inc	byte ptr [si+16h]
		mov	al, [si+16h]
		shr	al, 1
		shr	al, 1
		and	al, 7
		cmp	al, 5
		jl	short loc_code_1712
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_1712:			; CODE XREF: sub_code_16FE+Ej
		mov	[si+4],	al
		mov	bx, 12B5h
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_16FE	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_171F	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1096o
		inc	byte ptr [si+16h]
		mov	al, [si+16h]
		shr	al, 1
		shr	al, 1
		and	al, 7
		cmp	al, 6
		jl	short loc_code_1733
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_1733:			; CODE XREF: sub_code_171F+Ej
		mov	[si+4],	al
		mov	bx, 12F5h
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_171F	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1740	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1086o
		inc	byte ptr [si+16h]
		mov	al, [si+16h]
		and	al, 7
		cmp	al, 4
		jl	short loc_code_1762
		mov	al, [si]
		test	al, 20h
		jz	short loc_code_1759
		and	byte_data_9517,	7Fh
		jmp	short loc_code_175E
; ---------------------------------------------------------------------------

loc_code_1759:			; CODE XREF: sub_code_1740+10j
		and	byte_data_9517,	0FEh

loc_code_175E:			; CODE XREF: sub_code_1740+17j
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_1762:			; CODE XREF: sub_code_1740+Aj
		mov	[si+4],	al
		mov	bx, 133Dh
		call	sub_code_2121
		retn
sub_code_1740	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_176C	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:105Co
		inc	byte ptr [si+16h]
		mov	al, [si+16h]
		shr	al, 1
		and	al, 3
		mov	[si+4],	al
		mov	bx, 0E2Bh
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_176C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1783	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:105Eo
		inc	byte ptr [si+16h]
		mov	al, [si+16h]
		shr	al, 1
		and	al, 7
		cmp	al, 6
		jb	short loc_code_1797
		mov	al, 0
		mov	byte ptr [si+16h], 0

loc_code_1797:			; CODE XREF: sub_code_1783+Cj
		mov	bl, al
		mov	bh, 0
		mov	al, [bx+0E4Ch]
		mov	[si+4],	al
		mov	bx, 0E52h
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_1783	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_17AC	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1062o
		call	sub_code_215B
		cmp	cx, 0
		jz	short loc_code_17CC
		dec	byte ptr [si+16h]
		jns	short loc_code_17C4
		mov	byte ptr [si+16h], 8
		mov	byte_data_9518,	1
		jmp	short loc_code_17C9
; ---------------------------------------------------------------------------

loc_code_17C4:			; CODE XREF: sub_code_17AC+Bj
		mov	byte_data_9518,	0

loc_code_17C9:			; CODE XREF: sub_code_17AC+16j
		call	sub_code_1F0B

loc_code_17CC:			; CODE XREF: sub_code_17AC+6j
		mov	bx, 0E73h
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_17AC	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_17D6	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1064o
		call	sub_code_215B
		cmp	cx, 0
		jz	short loc_code_17EA
		dec	byte ptr [si+16h]
		jns	short loc_code_17EA
		mov	byte ptr [si+16h], 12h
		call	sub_code_2005

loc_code_17EA:			; CODE XREF: sub_code_17D6+6j
					; sub_code_17D6+Bj
		mov	bx, 0E9Ch
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_17D6	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_17F4	proc near		; CODE XREF: sub_code_FDA+74p
					; sub_code_2005+3Dp
					; DATA XREF: ...
		call	sub_code_10C6
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_17FE
		retn
; ---------------------------------------------------------------------------

loc_code_17FE:			; CODE XREF: sub_code_17F4+7j
		mov	al, [si+1]
		cmp	al, 2
		jnz	short loc_code_180B
		add	word ptr [si+7], 3
		jmp	short loc_code_1835
; ---------------------------------------------------------------------------

loc_code_180B:			; CODE XREF: sub_code_17F4+Fj
		cmp	al, 0
		jnz	short loc_code_1815
		sub	word ptr [si+5], 4
		jmp	short loc_code_1835
; ---------------------------------------------------------------------------

loc_code_1815:			; CODE XREF: sub_code_17F4+19j
		cmp	al, 1
		jnz	short loc_code_1823
		sub	word ptr [si+5], 4
		add	word ptr [si+7], 3
		jmp	short loc_code_1835
; ---------------------------------------------------------------------------

loc_code_1823:			; CODE XREF: sub_code_17F4+23j
		cmp	al, 3
		jnz	short loc_code_1831
		add	word ptr [si+5], 4
		add	word ptr [si+7], 3
		jmp	short loc_code_1835
; ---------------------------------------------------------------------------

loc_code_1831:			; CODE XREF: sub_code_17F4+31j
		add	word ptr [si+5], 4

loc_code_1835:			; CODE XREF: sub_code_17F4+15j
					; sub_code_17F4+1Fj ...
		and	word ptr [si+7], 3FFh
		mov	ax, [si+5]
		cmp	ax, 8
		jge	short loc_code_1846
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_1846:			; CODE XREF: sub_code_17F4+4Cj
		cmp	ax, 0F8h ; 'ø'
		jle	short loc_code_184F
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_184F:			; CODE XREF: sub_code_17F4+55j
		inc	byte ptr [si+16h]
		mov	bl, [si+16h]
		cmp	bl, 10h
		jb	short loc_code_185E
		call	sub_code_2099
		retn
; ---------------------------------------------------------------------------

loc_code_185E:			; CODE XREF: sub_code_17F4+64j
		mov	bh, 0
		mov	al, [bx+1467h]
		add	[si+3],	al
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jnz	short loc_code_186F
		retn
; ---------------------------------------------------------------------------

loc_code_186F:			; CODE XREF: sub_code_17F4+78j
		mov	ax, [si+5]
		sub	ax, word_data_1B8F
		jns	short loc_code_187A
		neg	ax

loc_code_187A:			; CODE XREF: sub_code_17F4+82j
		cmp	ax, 0Eh
		jnb	short locret_code_18A8
		mov	ax, [si+7]
		sub	ax, word_data_1B91
		jns	short loc_code_188A
		neg	ax

loc_code_188A:			; CODE XREF: sub_code_17F4+92j
		cmp	ax, 0Ah
		jnb	short locret_code_18A8
		mov	al, [si+3]
		sub	al, byte_data_1B8D
		jns	short loc_code_189A
		neg	al

loc_code_189A:			; CODE XREF: sub_code_17F4+A2j
		cmp	al, 10h
		jnb	short locret_code_18A8
		sub	word_data_9544,	0Ah
		mov	al, 5
		call	sub_code_3840

locret_code_18A8:			; CODE XREF: sub_code_17F4+89j
					; sub_code_17F4+99j ...
		retn
sub_code_17F4	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_18A9	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1066o
		call	sub_code_215B
		cmp	cx, 0
		jz	short loc_code_18BD
		dec	byte ptr [si+16h]
		jns	short loc_code_18BD
		mov	byte ptr [si+16h], 28h ; '('
		call	sub_code_1FBA

loc_code_18BD:			; CODE XREF: sub_code_18A9+6j
					; sub_code_18A9+Bj
		mov	bx, 0EC5h
		call	sub_code_2121
		call	sub_code_10C6
		retn
sub_code_18A9	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_18C7	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1090o
		mov	al, byte_data_952E
		and	al, byte_data_952F
		and	al, byte_data_9530
		and	al, byte_data_9531
		and	al, byte_data_9532
		and	al, byte_data_9533
		jnz	short loc_code_18E4
		call	sub_code_10C6
		retn
; ---------------------------------------------------------------------------

loc_code_18E4:			; CODE XREF: sub_code_18C7+17j
		mov	ax, word_data_1B8F
		sub	ax, [si+5]
		sub	ax, 0Ch
		jns	short loc_code_18F1
		neg	ax

loc_code_18F1:			; CODE XREF: sub_code_18C7+26j
		mov	cx, word_data_1B91
		sub	cx, 8
		sub	cx, [si+7]
		jns	short loc_code_18FF
		neg	cx

loc_code_18FF:			; CODE XREF: sub_code_18C7+34j
		mov	bl, [si+4]
		shr	bl, 1
		add	ax, cx
		cmp	ax, 40h	; '@'
		ja	short loc_code_1915
		cmp	bl, 8
		jz	short loc_code_1913
		inc	byte ptr [si+4]

loc_code_1913:			; CODE XREF: sub_code_18C7+47j
		jmp	short loc_code_191D
; ---------------------------------------------------------------------------

loc_code_1915:			; CODE XREF: sub_code_18C7+42j
		cmp	bl, 0
		jz	short loc_code_191D
		dec	byte ptr [si+4]

loc_code_191D:			; CODE XREF: sub_code_18C7:loc_code_1913j
					; sub_code_18C7+51j
		push	bx
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx+1483h]
		mov	[si+0Fh], ax
		pop	bx
		cmp	bl, 2
		jb	short loc_code_196B
		mov	ax, word_data_1B8F
		sub	ax, [si+5]
		sub	ax, 0Ch
		jns	short loc_code_1947
		neg	ax
		cmp	ax, 18h
		ja	short loc_code_1945
		inc	word_data_1B8F

loc_code_1945:			; CODE XREF: sub_code_18C7+78j
		jmp	short loc_code_1952
; ---------------------------------------------------------------------------

loc_code_1947:			; CODE XREF: sub_code_18C7+71j
		jz	short loc_code_1952
		cmp	ax, 18h
		ja	short loc_code_1952
		dec	word_data_1B8F

loc_code_1952:			; CODE XREF: sub_code_18C7:loc_code_1945j
					; sub_code_18C7:loc_code_1947j ...
		cmp	bl, 8
		jnz	short loc_code_196B
		cmp	cx, 8
		ja	short loc_code_196B
		cmp	ax, 8
		ja	short loc_code_196B
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jz	short loc_code_196B
		call	sub_code_196F

loc_code_196B:			; CODE XREF: sub_code_18C7+66j
					; sub_code_18C7+8Ej ...
		call	sub_code_10C6
		retn
sub_code_18C7	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_196F	proc near		; CODE XREF: sub_code_18C7+A1p
		mov	al, byte_data_1B8E
		cmp	al, 0
		jnz	short loc_code_1982
		mov	byte_data_951D,	0F0h ; 'ð'
		mov	byte_data_94FF,	1
		jmp	short locret_code_1992
; ---------------------------------------------------------------------------

loc_code_1982:			; CODE XREF: sub_code_196F+5j
		push	si
		mov	byte_data_1B8E,	0
		mov	si, 1B8Ah
		mov	bx, 0D49h
		call	sub_code_2121
		pop	si

locret_code_1992:			; CODE XREF: sub_code_196F+11j
		retn
sub_code_196F	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1993	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:106Co
		call	sub_code_1A04
		mov	al, byte_data_94FF
		cmp	al, 1
		jnz	short locret_code_19C1
		mov	al, byte_data_9501
		mov	bl, al
		shl	al, 1
		add	bl, al
		add	bl, byte_data_9502
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx+1495h]
		mov	bh, ah
		and	ax, 3FFh
		mov	word_data_950C,	ax
		and	bh, 0C0h
		mov	byte_data_951D,	bh

locret_code_19C1:			; CODE XREF: sub_code_1993+8j
		retn
sub_code_1993	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_19C2	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:106Eo
		call	sub_code_1A04
		mov	al, byte_data_94FF
		cmp	al, 1
		jnz	short locret_code_1A03
		mov	al, byte_data_9501
		mov	bl, al
		shl	al, 1
		add	bl, al
		add	bl, byte_data_9502
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx+14C5h]
		mov	bh, ah
		and	ax, 3FFh
		mov	word_data_950C,	ax
		and	bh, 0C0h
		mov	byte_data_951D,	bh
		mov	byte_data_950E,	1
		mov	al, byte_data_9502
		inc	al
		cmp	al, 2
		jbe	short loc_code_1A00
		mov	al, 0

loc_code_1A00:			; CODE XREF: sub_code_19C2+3Aj
		mov	byte_data_9502,	al

locret_code_1A03:			; CODE XREF: sub_code_19C2+8j
		retn
sub_code_19C2	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1A04	proc near		; CODE XREF: sub_code_1993p
					; sub_code_19C2p
		mov	ax, word_data_1B8F
		sub	ax, [si+5]
		sub	ax, 0Ch
		jns	short loc_code_1A11
		neg	ax

loc_code_1A11:			; CODE XREF: sub_code_1A04+9j
		mov	cx, word_data_1B91
		sub	cx, [si+7]
		jns	short loc_code_1A1C
		neg	cx

loc_code_1A1C:			; CODE XREF: sub_code_1A04+14j
		mov	bl, [si+4]
		shr	bl, 1
		add	ax, cx
		cmp	ax, 40h	; '@'
		ja	short loc_code_1A32
		cmp	bl, 6
		jz	short loc_code_1A30
		inc	byte ptr [si+4]

loc_code_1A30:			; CODE XREF: sub_code_1A04+27j
		jmp	short loc_code_1A3A
; ---------------------------------------------------------------------------

loc_code_1A32:			; CODE XREF: sub_code_1A04+22j
		cmp	bl, 0
		jz	short loc_code_1A3A
		dec	byte ptr [si+4]

loc_code_1A3A:			; CODE XREF: sub_code_1A04:loc_code_1A30j
					; sub_code_1A04+31j
		cmp	bl, 6
		jnz	short loc_code_1A45
		mov	byte ptr [si+2], 0
		jmp	short loc_code_1A56
; ---------------------------------------------------------------------------

loc_code_1A45:			; CODE XREF: sub_code_1A04+39j
		push	bx
		mov	byte ptr [si+2], 7
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx+1477h]
		mov	[si+0Fh], ax
		pop	bx

loc_code_1A56:			; CODE XREF: sub_code_1A04+3Fj
		cmp	bl, 1
		jb	short loc_code_1A9A
		mov	ax, word_data_1B8F
		sub	ax, [si+5]
		sub	ax, 0Ch
		jns	short loc_code_1A73
		neg	ax
		cmp	ax, 18h
		ja	short loc_code_1A71
		inc	word_data_1B8F

loc_code_1A71:			; CODE XREF: sub_code_1A04+67j
		jmp	short loc_code_1A7E
; ---------------------------------------------------------------------------

loc_code_1A73:			; CODE XREF: sub_code_1A04+60j
		jz	short loc_code_1A7E
		cmp	ax, 18h
		ja	short loc_code_1A7E
		dec	word_data_1B8F

loc_code_1A7E:			; CODE XREF: sub_code_1A04:loc_code_1A71j
					; sub_code_1A04:loc_code_1A73j ...
		cmp	cx, 8
		ja	short loc_code_1A9A
		cmp	ax, 8
		ja	short loc_code_1A9A
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jz	short loc_code_1A9A
		mov	ax, word_data_1B8F
		mov	word_data_950A,	ax
		mov	byte_data_94FF,	1

loc_code_1A9A:			; CODE XREF: sub_code_1A04+55j
					; sub_code_1A04+7Dj ...
		call	sub_code_10C6
		retn
sub_code_1A04	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1A9E	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1068o
		call	sub_code_10C6
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_1AA8
		retn
; ---------------------------------------------------------------------------

loc_code_1AA8:			; CODE XREF: sub_code_1A9E+7j
		mov	bx, word_data_1B91
		sub	bx, [si+7]
		jns	short loc_code_1ABB
		cmp	bx, 0FFF0h
		jge	short locret_code_1ABA
		mov	byte ptr [si+2], 1

locret_code_1ABA:			; CODE XREF: sub_code_1A9E+16j
		retn
; ---------------------------------------------------------------------------

loc_code_1ABB:			; CODE XREF: sub_code_1A9E+11j
		cmp	bx, 20h	; ' '
		jle	short loc_code_1AC1
		retn
; ---------------------------------------------------------------------------

loc_code_1AC1:			; CODE XREF: sub_code_1A9E+20j
		mov	ax, word_data_1B8F
		sub	ax, [si+5]
		sub	ax, 0Ch
		jns	short loc_code_1AD9
		neg	ax
		cmp	ax, 18h
		jnb	short loc_code_1AD7
		inc	word_data_1B8F

loc_code_1AD7:			; CODE XREF: sub_code_1A9E+33j
		jmp	short loc_code_1AE7
; ---------------------------------------------------------------------------

loc_code_1AD9:			; CODE XREF: sub_code_1A9E+2Cj
		cmp	ax, 18h
		jnb	short loc_code_1AE7
		cmp	ax, 0
		jz	short loc_code_1AE7
		dec	word_data_1B8F

loc_code_1AE7:			; CODE XREF: sub_code_1A9E:loc_code_1AD7j
					; sub_code_1A9E+3Ej ...
		cmp	bx, 8
		jbe	short loc_code_1AED
		retn
; ---------------------------------------------------------------------------

loc_code_1AED:			; CODE XREF: sub_code_1A9E+4Cj
		cmp	ax, 2
		ja	short loc_code_1AF8
		inc	word_data_9538
		jmp	short locret_code_1B08
; ---------------------------------------------------------------------------

loc_code_1AF8:			; CODE XREF: sub_code_1A9E+52j
		cmp	ax, 24h	; '$'
		jnb	short locret_code_1B08
		mov	word_data_9542,	0
		mov	al, 6
		call	sub_code_3840

locret_code_1B08:			; CODE XREF: sub_code_1A9E+58j
					; sub_code_1A9E+5Dj
		retn
sub_code_1A9E	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1B09	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1098o
		call	sub_code_10C6
		mov	al, [si]
		cmp	al, 0
		jnz	short loc_code_1B13
		retn
; ---------------------------------------------------------------------------

loc_code_1B13:			; CODE XREF: sub_code_1B09+7j
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jnz	short loc_code_1B1B
		retn
; ---------------------------------------------------------------------------

loc_code_1B1B:			; CODE XREF: sub_code_1B09+Fj
		mov	ax, [si+5]
		sub	ax, word_data_1B8F
		jns	short loc_code_1B26
		neg	ax

loc_code_1B26:			; CODE XREF: sub_code_1B09+19j
		cmp	ax, 12h
		jnb	short locret_code_1B49
		mov	ax, [si+7]
		sub	ax, word_data_1B91
		jns	short loc_code_1B36
		neg	ax

loc_code_1B36:			; CODE XREF: sub_code_1B09+29j
		cmp	ax, 10h
		jnb	short locret_code_1B49
		mov	byte ptr [si], 0
		mov	al, [si+1]
		call	sub_code_2B28
		mov	al, 0Ah
		call	sub_code_3840

locret_code_1B49:			; CODE XREF: sub_code_1B09+20j
					; sub_code_1B09+30j
		retn
sub_code_1B09	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1B4A	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:109Ao
		sub	word ptr [si+7], 2
		and	word ptr [si+7], 3FFh
		call	sub_code_10A0
		retn
sub_code_1B4A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1B57	proc near		; CODE XREF: sub_code_E84+24p
					; sub_code_1108+84p ...
		mov	ax, word_data_1B8F
		push	ax
		mov	ax, word_data_9528
		add	ax, 70h	; 'p'
		and	ax, 3FFh
		mov	word_data_1B91,	ax
		push	ax
		call	sub_code_7FD
		mov	byte_data_1B8D,	al
		mov	byte_data_1B9E,	cl
		mov	byte_data_1B8E,	bl
		mov	si, 1B8Ah
		mov	bx, 0D49h
		call	sub_code_2121
		retn
sub_code_1B57	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1B80	proc near		; CODE XREF: sub_code_1108p
					; sub_code_2E02+1p
		mov	bx, word_data_952A
		mov	ax, word_data_953A
		cmp	ax, 0
		jg	short loc_code_1B91
		mov	ax, 8
		jmp	short loc_code_1B94
; ---------------------------------------------------------------------------

loc_code_1B91:			; CODE XREF: sub_code_1B80+Aj
		mov	ax, word_data_954C

loc_code_1B94:			; CODE XREF: sub_code_1B80+Fj
		test	al, 4
		jz	short loc_code_1BA3
		inc	bx
		cmp	bx, 40h	; '@'
		jle	short loc_code_1BA1
		mov	bx, 40h	; '@'

loc_code_1BA1:			; CODE XREF: sub_code_1B80+1Cj
		jmp	short loc_code_1BB4
; ---------------------------------------------------------------------------

loc_code_1BA3:			; CODE XREF: sub_code_1B80+16j
		test	al, 8
		jz	short loc_code_1BB4
		sub	bx, 2
		cmp	bx, word_data_94FC
		jge	short loc_code_1BB4
		mov	bx, word_data_94FC

loc_code_1BB4:			; CODE XREF: sub_code_1B80:loc_code_1BA1j
					; sub_code_1B80+25j ...
		mov	word_data_952A,	bx
		retn
sub_code_1B80	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1BB9	proc near		; CODE XREF: sub_code_1108+3p
					; sub_code_12A7:loc_code_12B7p ...
		mov	bx, word_data_952A
		add	bx, 0Fh
		shr	bx, 1
		shr	bx, 1
		shr	bx, 1
		mov	ax, bx
		dec	ax
		shr	bx, 1
		add	ax, word_data_950F
		cmp	ax, 8Bh	; '‹'
		jbe	short loc_code_1BDD
		mov	ax, 0
		mov	word_data_953C,	0FFFFh

loc_code_1BDD:			; CODE XREF: sub_code_1BB9+19j
		mov	word_data_950F,	ax
		mov	ax, word_data_9528
		sub	ax, bx
		and	ax, 3FFh
		mov	word_data_9528,	ax
		mov	ax, word_data_9528
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		sub	ax, 3
		and	ax, 3Fh
		cmp	ax, word_data_9507
		jz	short locret_code_1C09
		mov	word_data_9507,	ax
		push	ax
		call	sub_code_8BA

locret_code_1C09:			; CODE XREF: sub_code_1BB9+47j
		retn
sub_code_1BB9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_1C0A	proc near		; CODE XREF: sub_code_12EB+67p
					; sub_code_13A8+69p ...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	bx, [bp+arg_2]
		mov	cx, [bp+arg_0]
		mov	si, 1B8Ah

loc_code_1C16:			; CODE XREF: sub_code_1C0A+23j
		mov	al, [si]
		test	al, 80h
		jnz	short loc_code_1C2F
		test	al, 8
		jz	short loc_code_1C2A
		cmp	cl, [si+14h]
		jnz	short loc_code_1C2A
		cmp	bl, [si+13h]
		jz	short loc_code_1C2F

loc_code_1C2A:			; CODE XREF: sub_code_1C0A+14j
					; sub_code_1C0A+19j
		add	si, 17h
		jmp	short loc_code_1C16
; ---------------------------------------------------------------------------

loc_code_1C2F:			; CODE XREF: sub_code_1C0A+10j
					; sub_code_1C0A+1Ej
		pop	bp
		retn	4
sub_code_1C0A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1C33	proc near		; CODE XREF: sub_code_1108+BCp
					; sub_code_1108+D2p ...
		mov	al, byte_data_1B9C
		cmp	al, 11h
		jnz	short loc_code_1C3B
		retn
; ---------------------------------------------------------------------------

loc_code_1C3B:			; CODE XREF: sub_code_1C33+5j
		mov	al, 0Ch
		call	sub_code_3840
		mov	si, 1B8Ah
		call	sub_code_20F0
		mov	byte_data_1B9C,	11h
		mov	byte_data_1B8C,	0
		mov	byte_data_9514,	0
		retn
sub_code_1C33	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1C56	proc near		; CODE XREF: sub_code_1108+92p
					; sub_code_1108+A8p
		neg	ax
		mov	word_data_9544,	ax
		push	ax
		mov	al, 6
		call	sub_code_3840
		pop	ax
		mov	ax, bx
		push	ax
		mov	al, byte_data_1B9E
		mov	ah, 0
		push	ax
		call	sub_code_1C0A
		mov	al, [si]
		test	al, 80h
		jnz	short locret_code_1C77
		call	sub_code_20DB

locret_code_1C77:			; CODE XREF: sub_code_1C56+1Cj
		retn
sub_code_1C56	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1C78	proc near		; CODE XREF: sub_code_1108:loc_code_118Fp
		mov	ax, word_data_9437
		mov	word_data_9439,	ax
		mov	ax, word_data_9435
		mov	word_data_9437,	ax
		mov	ax, word_data_9433
		mov	word_data_9435,	ax
		mov	ax, word_data_1B8F
		mov	word_data_9433,	ax
		mov	ax, word_data_943F
		mov	word_data_9441,	ax
		mov	ax, word_data_943D
		mov	word_data_943F,	ax
		mov	ax, word_data_943B
		mov	word_data_943D,	ax
		mov	ax, word_data_1B91
		mov	word_data_943B,	ax
		mov	al, byte_data_9445
		mov	byte_data_9446,	al
		mov	al, byte_data_9444
		mov	byte_data_9445,	al
		mov	al, byte_data_9443
		mov	byte_data_9444,	al
		mov	al, byte_data_1B8E
		mov	byte_data_9443,	al
		mov	al, byte_data_9449
		mov	byte_data_944A,	al
		mov	al, byte_data_9448
		mov	byte_data_9449,	al
		mov	al, byte_data_9447
		mov	byte_data_9448,	al
		mov	al, byte_data_1B8D
		mov	byte_data_9447,	al
		retn
sub_code_1C78	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1CD9	proc near		; CODE XREF: sub_code_E84+99p
					; sub_code_E84+B1p ...
		mov	ax, word_data_9439
		mov	[si+5],	ax
		mov	ax, word_data_9441
		add	ax, 6
		and	ax, 3FFh
		mov	[si+7],	ax
		mov	al, byte_data_9446
		mov	[si+4],	al
		mov	bl, al
		mov	bh, 0
		mov	cl, [bx+0DB9h]
		mov	al, byte_data_944A
		add	al, 6
		mov	[si+3],	al
		mov	al, [si]
		test	al, 20h
		jnz	short loc_code_1D10
		sub	word ptr [si+5], 8
		add	[si+3],	cl
		jmp	short loc_code_1D17
; ---------------------------------------------------------------------------

loc_code_1D10:			; CODE XREF: sub_code_1CD9+2Cj
		add	word ptr [si+5], 8
		sub	[si+3],	cl

loc_code_1D17:			; CODE XREF: sub_code_1CD9+35j
		mov	bx, 0DDAh
		call	sub_code_2121
		retn
sub_code_1CD9	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1D1E	proc near		; CODE XREF: sub_code_1108+E5p
		mov	si, 135Eh
		and	byte ptr [si], 0DFh
		mov	bl, byte_data_1B8E
		mov	bh, 0
		mov	al, [bx+139Dh]
		mov	[si+4],	al
		mov	al, [bx+1375h]
		cbw
		add	ax, word_data_1B8F
		mov	[si+5],	ax
		mov	ax, word_data_1B91
		sub	ax, 4
		and	ax, 3FFh
		mov	[si+7],	ax
		mov	al, byte_data_1B8D
		add	al, [bx+1389h]
		mov	[si+3],	al
		mov	bl, [si+4]
		mov	bh, 0
		mov	al, [bx+13A7h]
		mov	[si+0Ah], al
		shl	bx, 1
		mov	ax, [bx+13AAh]
		mov	[si+0Fh], ax
		call	sub_code_B58
		mov	si, 0FF7h
		mov	ax, word_data_1363
		mov	[si+5],	ax
		mov	ax, word_data_1365
		mov	[si+7],	ax
		mov	al, byte_data_1361
		mov	[si+3],	al
		inc	byte_data_9516
		mov	bl, byte_data_9516
		and	bx, 0Fh
		mov	al, [bx+0FE7h]
		mov	[si+4],	al
		mov	bx, 100Eh
		call	sub_code_2121
		call	sub_code_B58
		mov	si, 135Eh
		or	byte ptr [si], 20h
		mov	bl, byte_data_1B8E
		mov	bh, 0
		mov	al, [bx+137Fh]
		cbw
		add	ax, word_data_1B8F
		mov	[si+5],	ax
		mov	al, byte_data_1B8D
		add	al, [bx+1393h]
		mov	[si+3],	al
		call	sub_code_B58
		mov	si, 0FF7h
		mov	ax, word_data_1363
		mov	[si+5],	ax
		mov	ax, word_data_1365
		mov	[si+7],	ax
		mov	al, byte_data_1361
		mov	[si+3],	al
		call	sub_code_B58
		mov	ax, word_data_9511
		add	ax, bx
		cmp	ax, 10h
		jbe	short loc_code_1DEB
		mov	ax, 0
		mov	word_data_9540,	0FFFFh

loc_code_1DEB:			; CODE XREF: sub_code_1D1E+C2j
		mov	word_data_9511,	ax
		retn
sub_code_1D1E	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1DEF	proc near		; CODE XREF: sub_code_14F0+104p
		inc	byte_data_9516
		mov	bl, byte_data_9516
		and	bx, 0Fh
		mov	al, [bx+0FE7h]
		mov	byte_data_FFB, al
		mov	al, [si+1]
		cmp	al, 0
		jnz	short loc_code_1E2E
		mov	bl, [si+4]
		mov	bh, 0
		mov	cl, [bx+13CDh]
		mov	ax, 0FFFDh
		mov	bx, 8
		call	sub_code_1E7D
		mov	bl, [si+4]
		mov	bh, 0
		mov	cl, [bx+13D7h]
		mov	ax, 3
		mov	bx, 8
		call	sub_code_1E7D
		jmp	short locret_code_1E7C
; ---------------------------------------------------------------------------

loc_code_1E2E:			; CODE XREF: sub_code_1DEF+17j
		cmp	al, 1
		jnz	short loc_code_1E46
		mov	bl, [si+4]
		mov	bh, 0
		mov	cl, [bx+13E1h]
		mov	ax, 0
		mov	bx, 8
		call	sub_code_1E7D
		jmp	short locret_code_1E7C
; ---------------------------------------------------------------------------

loc_code_1E46:			; CODE XREF: sub_code_1DEF+41j
		mov	bl, [si+4]
		mov	bh, 0
		mov	cl, [bx+13EBh]
		mov	ax, 0FFF9h
		mov	bx, 8
		call	sub_code_1E7D
		mov	bl, [si+4]
		mov	bh, 0
		mov	cl, [bx+13F5h]
		mov	ax, 0
		mov	bx, 0Bh
		call	sub_code_1E7D
		mov	bl, [si+4]
		mov	bh, 0
		mov	cl, [bx+13FFh]
		mov	ax, 7
		mov	bx, 8
		call	sub_code_1E7D

locret_code_1E7C:			; CODE XREF: sub_code_1DEF+3Dj
					; sub_code_1DEF+55j
		retn
sub_code_1DEF	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1E7D	proc near		; CODE XREF: sub_code_1DEF+28p
					; sub_code_1DEF+3Ap ...
		push	si
		mov	di, 0FF7h
		add	ax, [si+5]
		mov	[di+5],	ax
		add	bx, [si+7]
		and	bx, 3FFh
		mov	[di+7],	bx
		add	cl, [si+3]
		mov	[di+3],	cl
		mov	si, di
		mov	bx, 1039h
		call	sub_code_2121
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_1EB0
		pop	ax
		push	ax
		cmp	ax, si
		jbe	short loc_code_1EB0
		call	sub_code_16D6

loc_code_1EB0:			; CODE XREF: sub_code_1E7D+28j
					; sub_code_1E7D+2Ej
		pop	si
		mov	al, byte_data_9518
		cmp	al, 0
		jnz	short loc_code_1EB9
		retn
; ---------------------------------------------------------------------------

loc_code_1EB9:			; CODE XREF: sub_code_1E7D+39j
		push	si
		mov	bl, [si+4]
		mov	bh, 0
		mov	si, 13B0h
		mov	al, [bx+139Dh]
		mov	[si+4],	al
		mov	ax, word_data_FFC
		mov	[si+5],	ax
		mov	ax, word_data_FFE
		mov	[si+7],	ax
		mov	al, byte_data_FFA
		mov	[si+3],	al
		mov	byte ptr [si+1], 2
		mov	bl, [si+4]
		mov	bh, 0
		mov	al, [bx+13A7h]
		mov	[si+0Ah], al
		mov	byte ptr [si+9], 4
		shl	bx, 1
		mov	ax, [bx+13C7h]
		mov	[si+0Fh], ax
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_1F09
		pop	ax
		push	ax
		cmp	ax, si
		jbe	short loc_code_1F09
		call	sub_code_15FC

loc_code_1F09:			; CODE XREF: sub_code_1E7D+81j
					; sub_code_1E7D+87j
		pop	si
		retn
sub_code_1E7D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1F0B	proc near		; CODE XREF: sub_code_17AC:loc_code_17C9p
		push	si
		inc	byte_data_9516
		mov	bl, byte_data_9516
		and	bx, 0Fh
		mov	al, [bx+0FE7h]
		mov	byte_data_FFB, al
		mov	di, 0FF7h
		mov	bl, [si+4]
		mov	bh, 0
		mov	al, [bx+1409h]
		cbw
		add	ax, [si+5]
		mov	[di+5],	ax
		mov	al, [bx+140Eh]
		cbw
		add	ax, [si+7]
		and	ax, 3FFh
		mov	[di+7],	ax
		mov	al, [si+3]
		add	al, 4
		mov	[di+3],	al
		shl	bx, 1
		mov	bx, [bx+102Fh]
		mov	si, di
		call	sub_code_2121
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_1F63
		pop	ax
		push	ax
		cmp	ax, si
		jbe	short loc_code_1F63
		call	sub_code_16D6

loc_code_1F63:			; CODE XREF: sub_code_1F0B+4Dj
					; sub_code_1F0B+53j
		pop	si
		mov	al, byte_data_9518
		cmp	al, 0
		jnz	short loc_code_1F6C
		retn
; ---------------------------------------------------------------------------

loc_code_1F6C:			; CODE XREF: sub_code_1F0B+5Ej
		push	si
		mov	di, 13B0h
		mov	bl, [si+4]
		mov	bh, 0
		mov	[di+1],	bl
		mov	ax, word_data_FFC
		mov	[di+5],	ax
		mov	ax, word_data_FFE
		mov	[di+7],	ax
		mov	al, byte_data_FFA
		mov	[di+3],	al
		mov	al, [bx+1413h]
		mov	[di+9],	al
		mov	al, [bx+1418h]
		mov	[di+0Ah], al
		mov	byte ptr [di+4], 0
		shl	bx, 1
		mov	ax, [bx+141Dh]
		mov	[di+0Fh], ax
		mov	si, di
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_1FB8
		pop	ax
		push	ax
		cmp	ax, si
		jbe	short loc_code_1FB8
		call	sub_code_15FC

loc_code_1FB8:			; CODE XREF: sub_code_1F0B+A2j
					; sub_code_1F0B+A8j
		pop	si
		retn
sub_code_1F0B	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_1FBA	proc near		; CODE XREF: sub_code_18A9+11p
		push	si
		mov	di, 10E8h
		mov	bl, [si+4]
		mov	[di+1],	bl
		mov	bh, 0
		mov	al, [bx+10DEh]
		cbw
		add	ax, [si+5]
		mov	[di+5],	ax
		mov	al, [bx+10E3h]
		cbw
		add	ax, [si+7]
		and	ax, 3FFh
		mov	[di+7],	ax
		mov	al, [si+3]
		add	al, 8
		mov	[di+3],	al
		shl	bx, 1
		mov	bx, [bx+10FFh]
		mov	si, di
		call	sub_code_2121
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_2003
		pop	ax
		push	ax
		cmp	ax, si
		jbe	short loc_code_2003
		call	sub_code_1429

loc_code_2003:			; CODE XREF: sub_code_1FBA+3Ej
					; sub_code_1FBA+44j
		pop	si
		retn
sub_code_1FBA	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2005	proc near		; CODE XREF: sub_code_17D6+11p
		push	si
		mov	di, 1446h
		mov	bl, [si+4]
		mov	[di+1],	bl
		mov	bh, 0
		mov	al, [bx+145Dh]
		cbw
		add	ax, [si+5]
		mov	[di+5],	ax
		mov	al, [bx+1462h]
		cbw
		add	ax, [si+7]
		and	ax, 3FFh
		mov	[di+7],	ax
		mov	al, [si+3]
		add	al, 8
		mov	[di+3],	al
		mov	si, di
		call	sub_code_B58
		cmp	si, 0
		jz	short loc_code_2045
		pop	ax
		push	ax
		cmp	ax, si
		jbe	short loc_code_2045
		call	sub_code_17F4

loc_code_2045:			; CODE XREF: sub_code_2005+35j
					; sub_code_2005+3Bj
		pop	si
		retn
sub_code_2005	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2047	proc near		; CODE XREF: sub_code_12EB+94p
		mov	al, [si]
		mov	bl, byte_data_9517
		test	al, 20h
		jz	short loc_code_2072
		test	bl, 80h
		jnz	short loc_code_206D
		or	byte_data_9517,	80h
		or	byte_data_1326,	20h
		mov	di, 1326h
		call	sub_code_20A0
		mov	al, 3
		call	sub_code_3840
		jmp	short loc_code_2070
; ---------------------------------------------------------------------------

loc_code_206D:			; CODE XREF: sub_code_2047+Dj
		mov	byte ptr [si], 0

loc_code_2070:			; CODE XREF: sub_code_2047+24j
		jmp	short locret_code_2091
; ---------------------------------------------------------------------------

loc_code_2072:			; CODE XREF: sub_code_2047+8j
		test	bl, 1
		jnz	short loc_code_208E
		or	byte_data_9517,	1
		and	byte_data_1326,	0DFh
		mov	di, 1326h
		call	sub_code_20A0
		mov	al, 3
		call	sub_code_3840
		jmp	short locret_code_2091
; ---------------------------------------------------------------------------

loc_code_208E:			; CODE XREF: sub_code_2047+2Ej
		mov	byte ptr [si], 0

locret_code_2091:			; CODE XREF: sub_code_2047:loc_code_2070j
					; sub_code_2047+45j
		retn
sub_code_2047	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2092	proc near		; CODE XREF: sub_code_12EB+48p
					; sub_code_14F0+BEp ...
		mov	di, 1427h
		call	sub_code_20A0
		retn
sub_code_2092	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2099	proc near		; CODE XREF: sub_code_17F4+66p
		mov	di, 12DEh
		call	sub_code_20A0
		retn
sub_code_2099	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_20A0	proc near		; CODE XREF: sub_code_2047+1Cp
					; sub_code_2047+3Dp ...
		mov	al, [di]
		mov	[si], al
		mov	al, [di+2]
		mov	[si+2],	al
		mov	al, [di+16h]
		mov	[si+16h], al
		mov	al, [di+4]
		mov	[si+4],	al
		mov	al, [di+9]
		mov	[si+9],	al
		mov	al, [di+0Ah]
		mov	[si+0Ah], al
		mov	al, [di+0Bh]
		mov	[si+0Bh], al
		mov	al, [di+0Ch]
		mov	[si+0Ch], al
		mov	ax, [di+0Fh]
		mov	[si+0Fh], ax
		mov	al, [di+12h]
		mov	[si+12h], al
		retn
sub_code_20A0	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_20DB	proc near		; CODE XREF: sub_code_12EB+85p
					; sub_code_13A8+72p ...
		call	sub_code_2676
		call	sub_code_20F0
		push	si
		mov	al, [si+13h]
		mov	ah, 0
		push	ax
		mov	al, [si+14h]
		push	ax
		call	sub_code_9B5
		retn
sub_code_20DB	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_20F0	proc near		; CODE XREF: sub_code_13A8+46p
					; sub_code_1429+BBp ...
		push	si
		mov	ax, [si+5]
		mov	word_data_12A3,	ax
		mov	ax, [si+7]
		mov	word_data_12A5,	ax
		mov	al, [si+3]
		mov	byte_data_12A1,	al
		mov	al, [si]
		test	al, 10h
		jz	short loc_code_2119
		sub	word_data_12A3,	0Ch
		sub	word_data_12A5,	8
		and	word_data_12A5,	3FFh

loc_code_2119:			; CODE XREF: sub_code_20F0+17j
		mov	si, 129Eh
		call	sub_code_B58
		pop	si
		retn
sub_code_20F0	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2121	proc near		; CODE XREF: sub_code_19D+9p
					; sub_code_E84+5Dp ...
		mov	cl, [bx]
		mov	ch, 0
		inc	bx
		mov	al, [si+4]
		mov	ah, 0
		mov	di, ax
		mov	al, [bx+di]
		mov	[si+9],	al
		add	bx, cx
		mov	al, [bx+di]
		mov	[si+0Ah], al
		add	bx, cx
		mov	al, [bx+di]
		mov	[si+0Bh], al
		add	bx, cx
		mov	al, [bx+di]
		mov	[si+0Ch], al
		add	bx, cx
		shl	di, 1
		shl	di, 1
		mov	ax, [bx+di]
		mov	[si+0Dh], ax
		add	bx, 2
		mov	ax, [bx+di]
		mov	[si+0Fh], ax
		retn
sub_code_2121	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_215B	proc near		; CODE XREF: sub_code_17ACp
					; sub_code_17D6p ...
		mov	cx, 1
		mov	ax, word_data_1B91
		sub	ax, [si+7]
		cmp	ax, 8Ch	; 'Œ'
		jle	short loc_code_2171
		mov	byte ptr [si+4], 2
		mov	cx, 0
		retn
; ---------------------------------------------------------------------------

loc_code_2171:			; CODE XREF: sub_code_215B+Cj
		cmp	ax, 0FFF0h
		jge	short loc_code_21A0
		mov	ah, [si+4]
		mov	al, [si]
		test	al, 20h
		jz	short loc_code_218D
		inc	ah
		cmp	ah, 4
		jle	short loc_code_218B
		and	byte ptr [si], 0DFh
		mov	ah, 4

loc_code_218B:			; CODE XREF: sub_code_215B+29j
		jmp	short loc_code_2199
; ---------------------------------------------------------------------------

loc_code_218D:			; CODE XREF: sub_code_215B+22j
		dec	ah
		cmp	ah, 0
		jge	short loc_code_2199
		or	byte ptr [si], 20h
		mov	ah, 0

loc_code_2199:			; CODE XREF: sub_code_215B:loc_code_218Bj
					; sub_code_215B+37j
		mov	[si+4],	ah
		mov	cx, 0
		retn
; ---------------------------------------------------------------------------

loc_code_21A0:			; CODE XREF: sub_code_215B+19j
		mov	bx, word_data_1B8F
		sub	bx, [si+5]
		jns	short loc_code_21C2
		cmp	bx, 0FFE0h
		jle	short loc_code_21B3
		mov	byte ptr [si+4], 2
		retn
; ---------------------------------------------------------------------------

loc_code_21B3:			; CODE XREF: sub_code_215B+51j
		cmp	ax, 20h	; ' '
		jle	short loc_code_21BD
		mov	byte ptr [si+4], 1
		retn
; ---------------------------------------------------------------------------

loc_code_21BD:			; CODE XREF: sub_code_215B+5Bj
		mov	byte ptr [si+4], 0
		retn
; ---------------------------------------------------------------------------

loc_code_21C2:			; CODE XREF: sub_code_215B+4Cj
		cmp	bx, 20h	; ' '
		jge	short loc_code_21CC
		mov	byte ptr [si+4], 2
		retn
; ---------------------------------------------------------------------------

loc_code_21CC:			; CODE XREF: sub_code_215B+6Aj
		cmp	ax, 20h	; ' '
		jle	short loc_code_21D6
		mov	byte ptr [si+4], 3
		retn
; ---------------------------------------------------------------------------

loc_code_21D6:			; CODE XREF: sub_code_215B+74j
		mov	byte ptr [si+4], 4
		retn
sub_code_215B	endp

; ---------------------------------------------------------------------------
		align 2

; =============== S U B	R O U T	I N E =======================================


sub_code_21DC	proc near		; CODE XREF: sub_code_A9+22p
		mov	ax, 403Ch
		push	ax
		mov	ax, 1E11h
		push	ax
		mov	ax, 38h	; '8'
		push	ax
		mov	ax, 7
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		call	sub_code_2200
		call	sub_code_264A
		call	sub_code_2A7F
		call	sub_code_22B1
		retn
sub_code_21DC	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2200	proc near		; CODE XREF: sub_code_E07:loc_code_E27p
					; sub_code_21DC+17p
		call	sub_code_250B
		call	sub_code_2553
		call	sub_code_259B
		call	sub_code_237C
		retn
sub_code_2200	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_220D	proc near		; CODE XREF: sub_code_CF:loc_code_EDp
		inc	byte_data_944C
		mov	al, byte_data_944C
		and	al, 3
		jnz	short loc_code_2228
		mov	ax, 0
		push	ax
		push	ax
		push	ax
		mov	al, byte_data_94FE
		push	ax
		call	sub_code_269E
		call	sub_code_2714

loc_code_2228:			; CODE XREF: sub_code_220D+9j
		mov	ax, word_data_953C
		cmp	ax, 0
		jz	short loc_code_2246
		jns	short loc_code_2237
		call	sub_code_252F
		jmp	short loc_code_2240
; ---------------------------------------------------------------------------

loc_code_2237:			; CODE XREF: sub_code_220D+23j
		mov	cx, ax

loc_code_2239:			; CODE XREF: sub_code_220D+31j
		push	cx
		call	sub_code_2542
		pop	cx
		loop	loc_code_2239

loc_code_2240:			; CODE XREF: sub_code_220D+28j
		mov	word_data_953C,	0

loc_code_2246:			; CODE XREF: sub_code_220D+21j
		mov	ax, word_data_9540
		cmp	ax, 0
		jz	short loc_code_2264
		jns	short loc_code_2255
		call	sub_code_2577
		jmp	short loc_code_225E
; ---------------------------------------------------------------------------

loc_code_2255:			; CODE XREF: sub_code_220D+41j
		mov	cx, ax

loc_code_2257:			; CODE XREF: sub_code_220D+4Fj
		push	cx
		call	sub_code_258A
		pop	cx
		loop	loc_code_2257

loc_code_225E:			; CODE XREF: sub_code_220D+46j
		mov	word_data_9540,	0

loc_code_2264:			; CODE XREF: sub_code_220D+3Fj
		mov	ax, word_data_9544
		cmp	ax, 0
		jz	short loc_code_228A
		jns	short loc_code_227B
		neg	ax
		mov	cx, ax

loc_code_2272:			; CODE XREF: sub_code_220D+6Aj
		push	cx
		call	sub_code_25BF
		pop	cx
		loop	loc_code_2272
		jmp	short loc_code_2284
; ---------------------------------------------------------------------------

loc_code_227B:			; CODE XREF: sub_code_220D+5Fj
		mov	cx, ax

loc_code_227D:			; CODE XREF: sub_code_220D+75j
		push	cx
		call	sub_code_25D2
		pop	cx
		loop	loc_code_227D

loc_code_2284:			; CODE XREF: sub_code_220D+6Cj
		mov	word_data_9544,	0

loc_code_228A:			; CODE XREF: sub_code_220D+5Dj
		mov	ax, word_data_9538
		cmp	ax, 0
		jz	short locret_code_22B0
		jns	short loc_code_22A1
		neg	ax
		mov	cx, ax

loc_code_2298:			; CODE XREF: sub_code_220D+90j
		push	cx
		call	sub_code_2464
		pop	cx
		loop	loc_code_2298
		jmp	short loc_code_22AA
; ---------------------------------------------------------------------------

loc_code_22A1:			; CODE XREF: sub_code_220D+85j
		mov	cx, ax

loc_code_22A3:			; CODE XREF: sub_code_220D+9Bj
		push	cx
		call	sub_code_239B
		pop	cx
		loop	loc_code_22A3

loc_code_22AA:			; CODE XREF: sub_code_220D+92j
		mov	word_data_9538,	0

locret_code_22B0:			; CODE XREF: sub_code_220D+83j
		retn
sub_code_220D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_22B1	proc near		; CODE XREF: sub_code_21DC+20p
		mov	word_data_9534,	3
		call	sub_code_22E1
		call	sub_code_22F9
		call	sub_code_2311
		retn
sub_code_22B1	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_22C1	proc near		; CODE XREF: sub_code_269E+5Ep
		inc	word_data_9534
		mov	ax, word_data_9534
		cmp	ax, 3
		jbe	short loc_code_22D4
		mov	word_data_9534,	3
		retn
; ---------------------------------------------------------------------------

loc_code_22D4:			; CODE XREF: sub_code_22C1+Aj
		jz	short sub_code_2311
		cmp	ax, 2
		jz	short sub_code_22F9
		cmp	ax, 1
		jz	short sub_code_22E1
		retn
sub_code_22C1	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_22E1	proc near		; CODE XREF: sub_code_22B1+6p
					; sub_code_22C1+1Dj
		mov	ax, 43E6h
		push	ax
		mov	ax, 1B90h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_22E1	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_22F9	proc near		; CODE XREF: sub_code_22B1+9p
					; sub_code_22C1+18j
		mov	ax, 43E6h
		push	ax
		mov	ax, 1B93h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_22F9	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2311	proc near		; CODE XREF: sub_code_22B1+Cp
					; sub_code_22C1:loc_code_22D4j
		mov	ax, 43E6h
		push	ax
		mov	ax, 1B96h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2311	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2329	proc near		; CODE XREF: sub_code_E07:loc_code_E15p
		dec	word_data_9534
		mov	ax, word_data_9534
		cmp	ax, 2
		jz	short loc_code_2368
		cmp	ax, 1
		jz	short loc_code_2354
		cmp	ax, 0
		jz	short loc_code_2340
		retn
; ---------------------------------------------------------------------------

loc_code_2340:			; CODE XREF: sub_code_2329+14j
		mov	ax, 1B90h
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_2354:			; CODE XREF: sub_code_2329+Fj
		mov	ax, 1B93h
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_2368:			; CODE XREF: sub_code_2329+Aj
		mov	ax, 1B96h
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
sub_code_2329	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_237C	proc near		; CODE XREF: sub_code_2200+9p
		mov	word_data_9536,	6
		mov	word_data_9538,	0
		call	sub_code_23D4
		call	sub_code_23EC
		call	sub_code_2404
		call	sub_code_241C
		call	sub_code_2434
		call	sub_code_244C
		retn
sub_code_237C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_239B	proc near		; CODE XREF: sub_code_220D+97p
		inc	word_data_9536
		mov	ax, word_data_9536
		cmp	ax, 6
		jbe	short loc_code_23AE
		mov	word_data_9536,	6
		retn
; ---------------------------------------------------------------------------

loc_code_23AE:			; CODE XREF: sub_code_239B+Aj
		push	ax
		mov	al, 8
		call	sub_code_3840
		pop	ax
		cmp	ax, 1
		jz	short sub_code_23D4
		cmp	ax, 2
		jz	short sub_code_23EC
		cmp	ax, 3
		jz	short sub_code_2404
		cmp	ax, 4
		jz	short sub_code_241C
		cmp	ax, 5
		jz	short sub_code_2434
		cmp	ax, 6
		jz	short sub_code_244C
		retn
sub_code_239B	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_23D4	proc near		; CODE XREF: sub_code_237C+Cp
					; sub_code_239B+1Dj
		mov	ax, 43EEh
		push	ax
		mov	ax, 1B99h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_23D4	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_23EC	proc near		; CODE XREF: sub_code_237C+Fp
					; sub_code_239B+22j
		mov	ax, 43EEh
		push	ax
		mov	ax, 1B9Bh
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_23EC	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2404	proc near		; CODE XREF: sub_code_237C+12p
					; sub_code_239B+27j
		mov	ax, 43EEh
		push	ax
		mov	ax, 1B9Dh
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2404	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_241C	proc near		; CODE XREF: sub_code_237C+15p
					; sub_code_239B+2Cj
		mov	ax, 43EEh
		push	ax
		mov	ax, 1B9Fh
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_241C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2434	proc near		; CODE XREF: sub_code_237C+18p
					; sub_code_239B+31j
		mov	ax, 43EEh
		push	ax
		mov	ax, 1BA1h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2434	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_244C	proc near		; CODE XREF: sub_code_237C+1Bp
					; sub_code_239B+36j
		mov	ax, 43EEh
		push	ax
		mov	ax, 1BA3h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_244C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2464	proc near		; CODE XREF: sub_code_220D+8Cp
		mov	ax, word_data_9536
		dec	word_data_9536
		jns	short loc_code_2474
		mov	word_data_9536,	0
		retn
; ---------------------------------------------------------------------------

loc_code_2474:			; CODE XREF: sub_code_2464+7j
		cmp	ax, 1
		jz	short loc_code_2493
		cmp	ax, 2
		jz	short loc_code_24A7
		cmp	ax, 3
		jz	short loc_code_24BB
		cmp	ax, 4
		jz	short loc_code_24CF
		cmp	ax, 5
		jz	short loc_code_24E3
		cmp	ax, 6
		jz	short loc_code_24F7
		retn
; ---------------------------------------------------------------------------

loc_code_2493:			; CODE XREF: sub_code_2464+13j
		mov	ax, 1B99h
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_24A7:			; CODE XREF: sub_code_2464+18j
		mov	ax, 1B9Bh
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_24BB:			; CODE XREF: sub_code_2464+1Dj
		mov	ax, 1B9Dh
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_24CF:			; CODE XREF: sub_code_2464+22j
		mov	ax, 1B9Fh
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_24E3:			; CODE XREF: sub_code_2464+27j
		mov	ax, 1BA1h
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
; ---------------------------------------------------------------------------

loc_code_24F7:			; CODE XREF: sub_code_2464+2Cj
		mov	ax, 1BA3h
		push	ax
		mov	ax, 2
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_2D9A
		retn
sub_code_2464	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_250B	proc near		; CODE XREF: sub_code_2200p
		mov	word_data_953A,	2Ch ; ','
		mov	word_data_953C,	0
		mov	ax, 48F6h
		push	ax
		mov	ax, 1B88h
		push	ax
		mov	ax, 2Ch	; ','
		push	ax
		mov	ax, 7
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_250B	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_252F	proc near		; CODE XREF: sub_code_220D+25p
		mov	ax, word_data_953A
		dec	ax
		jns	short sub_code_2536
		retn
sub_code_252F	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2536	proc near		; CODE XREF: sub_code_252F+4j
					; sub_code_2542:loc_code_254Bp
		mov	word_data_953A,	ax
		push	ax
		mov	ax, 1B88h
		push	ax
		call	sub_code_25E3
		retn
sub_code_2536	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2542	proc near		; CODE XREF: sub_code_220D+2Dp
		mov	ax, word_data_953A
		cmp	ax, 2Ch	; ','
		jb	short loc_code_254B
		retn
; ---------------------------------------------------------------------------

loc_code_254B:			; CODE XREF: sub_code_2542+6j
		call	sub_code_2536
		inc	word_data_953A
		retn
sub_code_2542	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2553	proc near		; CODE XREF: sub_code_2200+3p
		mov	word_data_953E,	30h ; '0'
		mov	word_data_9540,	0
		mov	ax, 2CE6h
		push	ax
		mov	ax, 1CC8h
		push	ax
		mov	ax, 30h	; '0'
		push	ax
		mov	ax, 7
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2553	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2577	proc near		; CODE XREF: sub_code_220D+43p
		mov	ax, word_data_953E
		dec	ax
		jns	short sub_code_257E
		retn
sub_code_2577	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_257E	proc near		; CODE XREF: sub_code_2577+4j
					; sub_code_258A:loc_code_2593p
		mov	word_data_953E,	ax
		push	ax
		mov	ax, 1CC8h
		push	ax
		call	sub_code_25E3
		retn
sub_code_257E	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_258A	proc near		; CODE XREF: sub_code_220D+4Bp
		mov	ax, word_data_953E
		cmp	ax, 30h	; '0'
		jb	short loc_code_2593
		retn
; ---------------------------------------------------------------------------

loc_code_2593:			; CODE XREF: sub_code_258A+6j
		call	sub_code_257E
		inc	word_data_953E
		retn
sub_code_258A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_259B	proc near		; CODE XREF: sub_code_2200+6p
		mov	word_data_9542,	38h ; '8'
		mov	word_data_9544,	0
		mov	ax, 4496h
		push	ax
		mov	ax, 1E08h
		push	ax
		mov	ax, 38h	; '8'
		push	ax
		mov	ax, 7
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		retn
sub_code_259B	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_25BF	proc near		; CODE XREF: sub_code_220D+66p
		mov	ax, word_data_9542
		dec	ax
		jns	short sub_code_25C6
		retn
sub_code_25BF	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_25C6	proc near		; CODE XREF: sub_code_25BF+4j
					; sub_code_25D2:loc_code_25DBp
		mov	word_data_9542,	ax
		push	ax
		mov	ax, 1E08h
		push	ax
		call	sub_code_25E3
		retn
sub_code_25C6	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_25D2	proc near		; CODE XREF: sub_code_220D+71p
		mov	ax, word_data_9542
		cmp	ax, 38h	; '8'
		jb	short loc_code_25DB
		retn
; ---------------------------------------------------------------------------

loc_code_25DB:			; CODE XREF: sub_code_25D2+6j
		call	sub_code_25C6
		inc	word_data_9542
		retn
sub_code_25D2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_25E3	proc near		; CODE XREF: sub_code_2536+8p
					; sub_code_257E+8p ...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	ax, 0A000h
		mov	es, ax
		assume es:nothing
		mov	ax, [bp+arg_2]
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		add	ax, [bp+arg_0]
		mov	di, ax
		mov	dx, 3CEh
		mov	ax, 805h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	cx, [bp+arg_2]
		and	cx, 7
		mov	ah, 80h	; '€'
		shr	ah, cl
		mov	al, 8
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		mov	bl, ah
		mov	ax, 1803h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 0F01h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 700h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	cx, 7

loc_code_261E:			; CODE XREF: sub_code_25E3+4Dj
		mov	al, es:[di]
		test	al, bl
		jnz	short loc_code_262D
		mov	es:[di], bl
		mov	es:[di+2000h], bl

loc_code_262D:			; CODE XREF: sub_code_25E3+40j
		add	di, 28h	; '('
		loop	loc_code_261E
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		mov	ax, 0FF08h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 3
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; data rotate and function select for write mode 00. Bits:
					; 0-2: set rotate count	for write mode 00
					; 3-4: fn for write modes 00 and 02
					;      00=no change; 01=AND; 10=OR; 11=XOR
		mov	ax, 1
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; enable set/reset
		mov	ax, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		pop	bp
		retn	4
sub_code_25E3	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_264A	proc near		; CODE XREF: sub_code_21DC+1Ap
		mov	al, 0
		mov	byte_data_94A9,	al
		mov	byte_data_94AA,	al
		mov	byte_data_94AB,	al
		mov	byte_data_94AC,	al
		mov	byte_data_94AD,	al
		mov	byte_data_94AE,	al
		call	sub_code_2714
		retn
sub_code_264A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2662	proc near		; CODE XREF: sub_code_12EB:loc_code_137Ap
					; sub_code_14F0+C6p
		mov	ax, 0
		push	ax
		mov	ax, 0
		push	ax
		mov	ax, 1
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_269E
		retn
sub_code_2662	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2676	proc near		; CODE XREF: sub_code_14F0+6Dp
					; sub_code_20DBp
		mov	ax, 0
		push	ax
		mov	ax, 1
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_269E
		retn
sub_code_2676	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_268A	proc near		; CODE XREF: sub_code_3059:loc_code_3080p
		mov	ax, 2
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, 0
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_269E
		retn
sub_code_268A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_269E	proc near		; CODE XREF: sub_code_220D+15p
					; sub_code_2662+10p ...

arg_0		= byte ptr  4
arg_2		= byte ptr  6
arg_4		= byte ptr  8
arg_6		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		mov	al, byte_data_94AE
		add	al, [bp+arg_0]
		cmp	al, 9
		jbe	short loc_code_26B1
		sub	al, 0Ah
		inc	byte_data_94AD

loc_code_26B1:			; CODE XREF: sub_code_269E+Bj
		mov	byte_data_94AE,	al
		mov	al, byte_data_94AD
		add	al, [bp+arg_2]
		cmp	al, 9
		jbe	short loc_code_26C4
		sub	al, 0Ah
		inc	byte_data_94AC

loc_code_26C4:			; CODE XREF: sub_code_269E+1Ej
		mov	byte_data_94AD,	al
		mov	al, byte_data_94AC
		add	al, [bp+arg_4]
		cmp	al, 9
		jbe	short loc_code_26D7
		sub	al, 0Ah
		inc	byte_data_94AB

loc_code_26D7:			; CODE XREF: sub_code_269E+31j
		mov	byte_data_94AC,	al
		mov	al, byte_data_94AB
		add	al, [bp+arg_6]
		cmp	al, 9
		jbe	short loc_code_26EA
		sub	al, 0Ah
		inc	byte_data_94AA

loc_code_26EA:			; CODE XREF: sub_code_269E+44j
		mov	byte_data_94AB,	al
		mov	al, byte_data_94AA
		cmp	al, 9
		jbe	short loc_code_2701
		sub	al, 0Ah
		inc	byte_data_94A9
		push	ax
		push	si
		call	sub_code_22C1
		pop	si
		pop	ax

loc_code_2701:			; CODE XREF: sub_code_269E+54j
		mov	byte_data_94AA,	al
		mov	al, byte_data_94A9
		cmp	al, 9
		jbe	short loc_code_270D
		sub	al, 0Ah

loc_code_270D:			; CODE XREF: sub_code_269E+6Bj
		mov	byte_data_94A9,	al
		pop	bp
		retn	8
sub_code_269E	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2714	proc near		; CODE XREF: sub_code_220D+18p
					; sub_code_264A+14p
		mov	byte_data_944D,	1
		mov	si, 94A9h
		mov	cx, 6
		mov	dx, 0

loc_code_2722:			; CODE XREF: sub_code_2714+4Bj
		push	cx
		lodsb
		cmp	al, 0
		jz	short loc_code_272D
		mov	byte_data_944D,	0

loc_code_272D:			; CODE XREF: sub_code_2714+12j
		mov	cl, byte_data_944D
		cmp	cl, 0
		jnz	short loc_code_275E
		push	dx
		push	si
		mov	bh, 0
		mov	bl, al
		shl	bx, 1
		mov	ax, [bx+155Fh]
		push	ax
		mov	bx, dx
		mov	ax, [bx+1573h]
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 9
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		pop	si
		pop	dx
		add	dx, 2

loc_code_275E:			; CODE XREF: sub_code_2714+20j
		pop	cx
		loop	loc_code_2722
		retn
sub_code_2714	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2762	proc near		; CODE XREF: start+64p
		mov	cx, 12h
		mov	ax, ds
		mov	es, ax
		assume es:dseg
		mov	di, 94AFh
		cld
		mov	ax, 0
		rep stosw
		mov	cx, 2Ah	; '*'
		mov	di, 9455h
		mov	al, 2Eh	; '.'
		mov	ah, 2Eh	; '.'
		rep stosw
		mov	byte_data_9455,	5Fh ; '_'
		mov	al, 0
		mov	cx, 7
		mov	si, 94DAh

loc_code_278B:			; CODE XREF: sub_code_2762+2Ej
		mov	[si], al
		inc	al
		inc	si
		loop	loc_code_278B
		mov	di, 9455h
		mov	dx, 1506h
		mov	cx, 8Ch	; 'Œ'
		call	sub_code_644
		retn
sub_code_2762	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_279F	proc near		; CODE XREF: sub_code_103+Dp
		call	sub_code_2809
		mov	al, byte_data_94E0
		cmp	al, 0
		jnz	short loc_code_27AF
		mov	byte_data_9546,	0
		retn
; ---------------------------------------------------------------------------

loc_code_27AF:			; CODE XREF: sub_code_279F+8j
		mov	byte_data_9546,	1
		mov	bl, al
		shl	bl, 1
		add	bl, al
		mov	bh, 0
		shl	bx, 1
		push	bx
		add	bx, 94A9h
		mov	si, 94A9h
		mov	cx, 6

loc_code_27C9:			; CODE XREF: sub_code_279F+2Ej
		lodsb
		mov	[bx], al
		inc	bx
		loop	loc_code_27C9
		pop	bx
		shl	bx, 1
		add	bx, 9455h
		mov	word_data_9451,	bx
		mov	si, 9455h
		mov	cx, 0Ch

loc_code_27E0:			; CODE XREF: sub_code_279F+45j
		lodsb
		mov	[bx], al
		inc	bx
		loop	loc_code_27E0
		mov	si, 94DAh

loc_code_27E9:			; CODE XREF: sub_code_279F+51j
		mov	al, [si]
		cmp	al, 0
		jz	short loc_code_27F2
		inc	si
		jmp	short loc_code_27E9
; ---------------------------------------------------------------------------

loc_code_27F2:			; CODE XREF: sub_code_279F+4Ej
		mov	al, byte_data_94E0
		mov	[si], al
		mov	byte_data_94E0,	0
		sub	si, 94DAh
		mov	ax, si
		mov	byte_data_9450,	al
		call	sub_code_28DA
		retn
sub_code_279F	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2809	proc near		; CODE XREF: sub_code_279Fp
		mov	al, byte_data_94DA
		mov	byte_data_94D3,	al
		mov	al, byte_data_94DB
		mov	byte_data_94D4,	al
		mov	al, byte_data_94DC
		mov	byte_data_94D5,	al
		mov	al, byte_data_94DD
		mov	byte_data_94D6,	al
		mov	al, byte_data_94DE
		mov	byte_data_94D7,	al
		mov	al, byte_data_94DF
		mov	byte_data_94D8,	al
		mov	al, byte_data_94E0
		mov	byte_data_94D9,	al
		mov	si, 94D3h
		mov	di, 94DAh
		mov	cx, 7

loc_code_283C:			; CODE XREF: sub_code_2809+66j
		push	cx
		push	si

loc_code_283E:			; CODE XREF: sub_code_2809+3Cj
		mov	al, [si]
		cmp	al, 0FFh
		jnz	short loc_code_2847
		inc	si
		jmp	short loc_code_283E
; ---------------------------------------------------------------------------

loc_code_2847:			; CODE XREF: sub_code_2809+39j
		cmp	si, 94D9h
		jz	short loc_code_2865
		mov	bx, si

loc_code_284F:			; CODE XREF: sub_code_2809+5Aj
		inc	bx
		mov	al, [bx]
		cmp	al, 0FFh
		jz	short loc_code_285F
		call	sub_code_2872
		cmp	al, 0
		jz	short loc_code_285F
		mov	si, bx

loc_code_285F:			; CODE XREF: sub_code_2809+4Bj
					; sub_code_2809+52j
		cmp	bx, 94D9h
		jnz	short loc_code_284F

loc_code_2865:			; CODE XREF: sub_code_2809+42j
		mov	al, [si]
		mov	byte ptr [si], 0FFh
		mov	[di], al
		inc	di
		pop	si
		pop	cx
		loop	loc_code_283C
		retn
sub_code_2809	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2872	proc near		; CODE XREF: sub_code_2809+4Dp
		push	si
		push	di
		mov	al, [si]
		mov	ah, al
		shl	al, 1
		add	al, ah
		shl	al, 1
		mov	ah, 0
		add	ax, 94A9h
		mov	si, ax
		mov	al, [bx]
		mov	ah, al
		shl	al, 1
		add	al, ah
		shl	al, 1
		mov	ah, 0
		add	ax, 94A9h
		mov	di, ax
		mov	al, [di]
		cmp	al, [si]
		ja	short loc_code_28D5
		jb	short loc_code_28D0
		mov	al, [di+1]
		cmp	al, [si+1]
		ja	short loc_code_28D5
		jb	short loc_code_28D0
		mov	al, [di+2]
		cmp	al, [si+2]
		ja	short loc_code_28D5
		jb	short loc_code_28D0
		mov	al, [di+3]
		cmp	al, [si+3]
		ja	short loc_code_28D5
		jb	short loc_code_28D0
		mov	al, [di+4]
		cmp	al, [si+4]
		ja	short loc_code_28D5
		jb	short loc_code_28D0
		mov	al, [di+5]
		cmp	al, [si+5]
		ja	short loc_code_28D5
		jb	short $+2

loc_code_28D0:			; CODE XREF: sub_code_2872+2Aj
					; sub_code_2872+34j ...
		mov	al, 0
		pop	di
		pop	si
		retn
; ---------------------------------------------------------------------------

loc_code_28D5:			; CODE XREF: sub_code_2872+28j
					; sub_code_2872+32j ...
		mov	al, 1
		pop	di
		pop	si
		retn
sub_code_2872	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_28DA	proc near		; CODE XREF: sub_code_103+18p
					; sub_code_279F+66p
		mov	si, 94DAh
		mov	di, 1B1h
		mov	cx, 6

loc_code_28E3:			; CODE XREF: sub_code_28DA+2Aj
		push	cx
		add	di, 2
		mov	ax, [di]
		add	di, 2
		push	si
		push	di
		call	sub_code_2959
		pop	di
		pop	si
		add	di, 2
		mov	ax, [di]
		add	di, 2
		push	si
		push	di
		call	sub_code_2907
		pop	di
		pop	si
		inc	si
		pop	cx
		loop	loc_code_28E3
		retn
sub_code_28DA	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2907	proc near		; CODE XREF: sub_code_28DA+23p
		mov	word_data_944E,	ax
		mov	al, [si]
		mov	ah, al
		shl	al, 1
		add	al, ah
		mov	ah, 0
		shl	ax, 1
		add	ax, 94A9h
		mov	si, ax
		mov	byte_data_944D,	1
		mov	cx, 6
		mov	dx, 0

loc_code_2926:			; CODE XREF: sub_code_2907+4Fj
		push	cx
		lodsb
		cmp	al, 0
		jz	short loc_code_2931
		mov	byte_data_944D,	0

loc_code_2931:			; CODE XREF: sub_code_2907+23j
		mov	cl, byte_data_944D
		cmp	cl, 0
		jz	short loc_code_293F
		mov	ax, 6F6Ch
		jmp	short loc_code_2949
; ---------------------------------------------------------------------------

loc_code_293F:			; CODE XREF: sub_code_2907+31j
		mov	bh, 0
		mov	bl, al
		shl	bx, 1
		mov	ax, [bx+157Fh]

loc_code_2949:			; CODE XREF: sub_code_2907+36j
		push	dx
		push	si
		push	ax
		push	dx
		call	sub_code_29AE
		pop	si
		pop	dx
		add	dx, 6
		pop	cx
		loop	loc_code_2926
		retn
sub_code_2907	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2959	proc near		; CODE XREF: sub_code_28DA+14p
		mov	word_data_944E,	ax
		mov	al, [si]
		mov	ah, al
		shl	al, 1
		add	al, ah
		mov	ah, 0
		shl	ax, 1
		shl	ax, 1
		add	ax, 9455h
		mov	si, ax
sub_code_2959	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_code_296F	proc near		; CODE XREF: sub_code_2A64+17p
		mov	cx, 0Ch
		mov	dx, 0

loc_code_2975:			; CODE XREF: sub_code_296F+3Cj
		push	cx
		lodsb
		push	si
		push	dx
		cmp	al, 20h	; ' '
		jnz	short loc_code_2982
		mov	ax, 6546h
		jmp	short loc_code_29A0
; ---------------------------------------------------------------------------

loc_code_2982:			; CODE XREF: sub_code_296F+Cj
		cmp	al, 2Eh	; '.'
		jnz	short loc_code_298B
		mov	ax, 6F6Ch
		jmp	short loc_code_29A0
; ---------------------------------------------------------------------------

loc_code_298B:			; CODE XREF: sub_code_296F+15j
		cmp	al, 5Fh	; '_'
		jnz	short loc_code_2994
		mov	ax, 764Ch
		jmp	short loc_code_29A0
; ---------------------------------------------------------------------------

loc_code_2994:			; CODE XREF: sub_code_296F+1Ej
		sub	al, 41h	; 'A'
		mov	ah, al
		shl	al, 1
		add	al, ah
		shl	al, 1
		mov	ah, 0

loc_code_29A0:			; CODE XREF: sub_code_296F+11j
					; sub_code_296F+1Aj ...
		push	ax
		push	dx
		call	sub_code_29AE
		pop	dx
		add	dx, 6
		pop	si
		pop	cx
		loop	loc_code_2975
		retn
sub_code_296F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_29AE	proc near		; CODE XREF: sub_code_2907+46p
					; sub_code_296F+33p

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	ax, word_data_94F0
		mov	es, ax
		assume es:nothing
		mov	di, word_data_944E
		add	di, [bp+arg_0]
		mov	ax, word_data_94EA
		push	ds
		mov	ds, ax
		mov	si, [bp+arg_2]
		mov	cx, 0Bh

loc_code_29C9:			; CODE XREF: sub_code_29AE+26j
		movsw
		movsw
		movsw
		add	di, 9Ah	; 'š'
		add	si, 9Ah	; 'š'
		loop	loc_code_29C9
		pop	ds
		pop	bp
		retn	4
sub_code_29AE	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_29DB	proc near		; CODE XREF: sub_code_103+73p
		mov	word_data_9453,	0

loc_code_29E1:			; CODE XREF: sub_code_29DB+5Cj
		mov	ax, word_data_9453
		cmp	ax, 0Ch
		jnb	short loc_code_2A39
		call	sub_code_541
		cmp	al, 0
		jz	short loc_code_2A39
		cmp	al, 8
		jnz	short loc_code_2A0D
		mov	bx, word_data_9451
		add	bx, word_data_9453
		mov	byte ptr [bx], 2Eh ; '.'
		dec	word_data_9453
		jns	short loc_code_2A0B
		mov	word_data_9453,	0

loc_code_2A0B:			; CODE XREF: sub_code_29DB+28j
		jmp	short loc_code_2A1B
; ---------------------------------------------------------------------------

loc_code_2A0D:			; CODE XREF: sub_code_29DB+17j
		mov	bx, word_data_9451
		add	bx, word_data_9453
		mov	[bx], al
		inc	word_data_9453

loc_code_2A1B:			; CODE XREF: sub_code_29DB:loc_code_2A0Bj
		mov	bx, word_data_9453
		cmp	bx, 0Ch
		jnb	short loc_code_2A2B
		add	bx, word_data_9451
		mov	byte ptr [bx], 5Fh ; '_'

loc_code_2A2B:			; CODE XREF: sub_code_29DB+47j
		call	sub_code_2A64
		call	sub_code_3498
		call	sub_code_B8E
		call	sub_code_3383
		jmp	short loc_code_29E1
; ---------------------------------------------------------------------------

loc_code_2A39:			; CODE XREF: sub_code_29DB+Cj
					; sub_code_29DB+13j
		mov	bx, word_data_9453
		cmp	bx, 0Ch
		jnb	short loc_code_2A52
		add	bx, word_data_9451
		mov	al, [bx]
		cmp	al, 5Fh	; '_'
		jnz	short loc_code_2A52
		mov	byte ptr [bx], 2Eh ; '.'
		call	sub_code_2A64

loc_code_2A52:			; CODE XREF: sub_code_29DB+65j
					; sub_code_29DB+6Fj
		mov	di, 9455h
		mov	dx, 1506h
		mov	cx, 8Ch	; 'Œ'
		call	sub_code_674
		mov	byte_data_9546,	0
		retn
sub_code_29DB	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2A64	proc near		; CODE XREF: sub_code_29DB:loc_code_2A2Bp
					; sub_code_29DB+74p
		mov	si, word_data_9451
		mov	bl, byte_data_9450
		mov	bh, 0
		shl	bx, 1
		shl	bx, 1
		shl	bx, 1
		mov	ax, [bx+1B3h]
		mov	word_data_944E,	ax
		call	sub_code_296F
		retn
sub_code_2A64	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2A7F	proc near		; CODE XREF: sub_code_DC0+43p
					; sub_code_21DC+1Dp
		mov	byte_data_952E,	0
		mov	byte_data_952F,	0
		mov	byte_data_9530,	0
		mov	byte_data_9531,	0
		mov	byte_data_9532,	0
		mov	byte_data_9533,	0
		mov	ax, 1178h
		push	ax
		mov	ax, 1B82h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		mov	ax, 1678h
		push	ax
		mov	ax, 1CC2h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		mov	ax, 1B78h
		push	ax
		mov	ax, 1E02h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		mov	ax, 2078h
		push	ax
		mov	ax, 1B85h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		mov	ax, 2578h
		push	ax
		mov	ax, 1CC5h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		mov	ax, 2A78h
		push	ax
		mov	ax, 1E05h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2A7F	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2B28	proc near		; CODE XREF: sub_code_1B09+38p
		push	ax
		mov	ax, 0
		push	ax
		mov	ax, 1
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_269E
		pop	ax
		cmp	al, 0
		jz	short loc_code_2B59
		cmp	al, 1
		jz	short loc_code_2B76
		cmp	al, 2
		jz	short loc_code_2B93
		cmp	al, 3
		jz	short loc_code_2BB0
		cmp	al, 4
		jz	short loc_code_2BCD
		cmp	al, 5
		jnz	short locret_code_2B58
		jmp	loc_code_2BEA
; ---------------------------------------------------------------------------

locret_code_2B58:			; CODE XREF: sub_code_2B28+2Bj
		retn
; ---------------------------------------------------------------------------

loc_code_2B59:			; CODE XREF: sub_code_2B28+17j
		mov	byte_data_952E,	1
		mov	ax, 2F78h
		push	ax
		mov	ax, 1B82h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
; ---------------------------------------------------------------------------

loc_code_2B76:			; CODE XREF: sub_code_2B28+1Bj
		mov	byte_data_952F,	1
		mov	ax, 2F78h
		push	ax
		mov	ax, 1CC2h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
; ---------------------------------------------------------------------------

loc_code_2B93:			; CODE XREF: sub_code_2B28+1Fj
		mov	byte_data_9530,	1
		mov	ax, 2F78h
		push	ax
		mov	ax, 1E02h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
; ---------------------------------------------------------------------------

loc_code_2BB0:			; CODE XREF: sub_code_2B28+23j
		mov	byte_data_9531,	1
		mov	ax, 2F78h
		push	ax
		mov	ax, 1B85h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
; ---------------------------------------------------------------------------

loc_code_2BCD:			; CODE XREF: sub_code_2B28+27j
		mov	byte_data_9532,	1
		mov	ax, 2F78h
		push	ax
		mov	ax, 1CC5h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
; ---------------------------------------------------------------------------

loc_code_2BEA:			; CODE XREF: sub_code_2B28+2Dj
		mov	byte_data_9533,	1
		mov	ax, 2F78h
		push	ax
		mov	ax, 1E05h
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 8
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2B28	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2C07	proc near		; CODE XREF: sub_code_33Bp
		mov	ax, 0A0Bh
		push	ax
		mov	ax, 13h
		push	ax
		mov	ax, 30h	; '0'
		push	ax
		mov	ax, 5
		push	ax
		call	sub_code_2D9A
		mov	ax, 0AACh
		push	ax
		mov	ax, 11h
		push	ax
		mov	ax, 28h	; '('
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2D9A
		mov	ax, 5A5Ch
		push	ax
		mov	ax, 0B4Dh
		push	ax
		mov	ax, 78h	; 'x'
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2C07	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2C45	proc near		; CODE XREF: sub_code_1C0+A6p
		mov	ax, 0AACh
		push	ax
		mov	ax, 10h
		push	ax
		mov	ax, 28h	; '('
		push	ax
		mov	ax, 5
		push	ax
		call	sub_code_2D9A
		mov	ax, 0B4Dh
		push	ax
		mov	ax, 0Eh
		push	ax
		mov	ax, 20h	; ' '
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2D9A
		mov	ax, 7592h
		push	ax
		mov	ax, 0C8Fh
		push	ax
		mov	ax, 28h	; '('
		push	ax
		mov	ax, 0Ch
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2CEA
		mov	ax, 1AB8h
		push	ax
		mov	ax, 0CE4h
		push	ax
		mov	ax, 20h	; ' '
		push	ax
		mov	ax, 0Dh
		push	ax
		mov	ax, 4
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2C45	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2C9A	proc near		; CODE XREF: sub_code_33B+5p
					; sub_code_33B+10p ...
		push	ax
		mov	ax, 0DCCh
		push	ax
		mov	ax, 11h
		push	ax
		mov	ax, 0Fh
		push	ax
		mov	ax, 2
		push	ax
		call	sub_code_2D9A
		pop	ax
		cmp	al, 6
		jnz	short loc_code_2CBC
		mov	al, 0
		call	sub_code_2CC7
		mov	al, 6
		jmp	short sub_code_2CC7
; ---------------------------------------------------------------------------

loc_code_2CBC:			; CODE XREF: sub_code_2C9A+17j
		cmp	al, 7
		jnz	short sub_code_2CC7
		mov	al, 1
		call	sub_code_2CC7
		mov	al, 7
sub_code_2C9A	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_code_2CC7	proc near		; CODE XREF: sub_code_2C9A+1Bp
					; sub_code_2C9A+20j ...
		mov	bl, al
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx+151Fh]
		push	ax
		mov	ax, [bx+152Fh]
		push	ax
		mov	ax, [bx+153Fh]
		push	ax
		mov	ax, [bx+154Fh]
		push	ax
		mov	ax, [bx+150Fh]
		push	ax
		call	sub_code_2CEA
		retn
sub_code_2CC7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_2CEA	proc near		; CODE XREF: sub_code_21DC+14p
					; sub_code_22E1+14p ...

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah
arg_8		= word ptr  0Ch

		push	bp
		mov	bp, sp
		mov	ax, 0A000h
		mov	es, ax
		assume es:nothing
		mov	di, [bp+arg_6]
		mov	bx, [bp+arg_0]
		mov	bx, [bx-6B18h]
		mov	si, [bp+arg_8]
		push	ds
		push	bx
		mov	dx, 3CEh
		mov	ax, 0A05h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 7
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; color	masking	disable
					; bits 0-3 disable planes from compare logic in	read mode 01
		mov	cx, [bp+arg_4]
		shr	cx, 1
		mov	ah, 80h	; '€'
		mov	al, 8
		pop	ds
		mov	bx, [bp+arg_2]

loc_code_2D19:			; CODE XREF: sub_code_2CEA+9Dj
		push	ax
		push	bx
		push	cx
		push	di
		push	si

loc_code_2D1E:			; CODE XREF: sub_code_2CEA:loc_code_2D74j
		mov	bh, 22h	; '"'

loc_code_2D20:			; CODE XREF: sub_code_2CEA+44j
					; sub_code_2CEA:loc_code_2D39j
		mov	bl, [si]
		inc	si
		cmp	bh, bl
		jnz	short loc_code_2D3D
		shr	ah, 1
		jnz	short loc_code_2D32
		mov	ah, 40h	; '@'
		inc	di
		loop	loc_code_2D20
		jmp	short loc_code_2D76
; ---------------------------------------------------------------------------

loc_code_2D32:			; CODE XREF: sub_code_2CEA+3Fj
		shr	ah, 1
		jnz	short loc_code_2D39
		mov	ah, 80h	; '€'
		inc	di

loc_code_2D39:			; CODE XREF: sub_code_2CEA+4Aj
		loop	loc_code_2D20
		jmp	short loc_code_2D76
; ---------------------------------------------------------------------------

loc_code_2D3D:			; CODE XREF: sub_code_2CEA+3Bj
		mov	bh, bl
		shr	bl, 1
		shr	bl, 1
		shr	bl, 1
		shr	bl, 1
		cmp	bl, 2
		jz	short loc_code_2D55
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		and	es:[di], bl
		and	es:[di+2000h], bl

loc_code_2D55:			; CODE XREF: sub_code_2CEA+60j
		shr	ah, 1
		jnz	short loc_code_2D5C
		mov	ah, 80h	; '€'
		inc	di

loc_code_2D5C:			; CODE XREF: sub_code_2CEA+6Dj
		and	bh, 0Fh
		cmp	bh, 2
		jz	short loc_code_2D6D
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		and	es:[di], bh
		and	es:[di+2000h], bh

loc_code_2D6D:			; CODE XREF: sub_code_2CEA+78j
		shr	ah, 1
		jnz	short loc_code_2D74
		mov	ah, 80h	; '€'
		inc	di

loc_code_2D74:			; CODE XREF: sub_code_2CEA+85j
		loop	loc_code_2D1E

loc_code_2D76:			; CODE XREF: sub_code_2CEA+46j
					; sub_code_2CEA+51j
		pop	si
		add	si, 0A0h ; ' '
		pop	di
		add	di, 28h	; '('
		and	di, 7FFFh
		pop	cx
		pop	bx
		pop	ax
		dec	bx
		jnz	short loc_code_2D19
		pop	ds
		mov	ax, 0FF08h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		mov	ax, 0F07h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		pop	bp
		retn	0Ah
sub_code_2CEA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_2D9A	proc near		; CODE XREF: sub_code_2329+27p
					; sub_code_2329+3Bp ...

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		mov	ax, 0A000h
		mov	es, ax
		mov	di, [bp+arg_6]
		mov	dx, 3CEh
		mov	ax, [bp+arg_0]
		mov	ah, al
		mov	al, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		mov	ax, 0F01h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		cld
		mov	bx, [bp+arg_2]

loc_code_2DB8:			; CODE XREF: sub_code_2D9A+34j
		push	di
		mov	cx, [bp+arg_4]
		rep stosb
		pop	di
		push	di
		add	di, 2000h
		mov	cx, [bp+arg_4]
		rep stosb
		pop	di
		add	di, 28h	; '('
		dec	bx
		jnz	short loc_code_2DB8
		mov	ax, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		inc	al
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; enable set/reset
		pop	bp
		retn	8
sub_code_2D9A	endp

; ---------------------------------------------------------------------------
		align 2

; =============== S U B	R O U T	I N E =======================================


sub_code_2DDC	proc near		; CODE XREF: sub_code_F3C+5p
		mov	bl, byte_data_94E4
		and	bx, 3
		shl	bx, 1
		mov	ax, [bx+1A2Ah]
		mov	word_data_94E2,	ax
		inc	byte_data_94E4
		mov	byte_data_9527,	0FFh
		retn
sub_code_2DDC	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2DF6	proc near		; CODE XREF: sub_code_F3C+2Dp
		mov	al, 0
		mov	byte_data_94E5,	al
		mov	byte_data_94E6,	al
		mov	byte_data_94E7,	al
		retn
sub_code_2DF6	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2E02	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1070o
		push	si
		call	sub_code_1B80
		call	sub_code_309D
		pop	si
		mov	ax, word_data_952A
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		mov	bx, word_data_954C
		test	bl, 1
		jz	short loc_code_2E23
		neg	ax
		sub	ax, 3
		jmp	short loc_code_2E30
; ---------------------------------------------------------------------------

loc_code_2E23:			; CODE XREF: sub_code_2E02+18j
		test	bl, 2
		jz	short loc_code_2E2D
		add	ax, 3
		jmp	short loc_code_2E30
; ---------------------------------------------------------------------------

loc_code_2E2D:			; CODE XREF: sub_code_2E02+24j
		mov	ax, 0

loc_code_2E30:			; CODE XREF: sub_code_2E02+1Fj
					; sub_code_2E02+29j
		mov	word_data_9522,	ax
		mov	al, [si+16h]
		and	ax, 7Fh
		cmp	al, 3Fh	; '?'
		jbe	short loc_code_2E48
		neg	al
		add	al, 7Fh	; ''
		call	sub_code_3084
		neg	ax
		jmp	short loc_code_2E4B
; ---------------------------------------------------------------------------

loc_code_2E48:			; CODE XREF: sub_code_2E02+39j
		call	sub_code_3084

loc_code_2E4B:			; CODE XREF: sub_code_2E02+44j
		mov	word_data_9520,	ax
		mov	ax, word_data_951E
		add	ax, word_data_9522
		add	ax, word_data_9520
		jz	short loc_code_2E6A
		jns	short loc_code_2E63
		inc	ax
		jns	short loc_code_2E61
		inc	ax

loc_code_2E61:			; CODE XREF: sub_code_2E02+5Cj
		jmp	short loc_code_2E6A
; ---------------------------------------------------------------------------

loc_code_2E63:			; CODE XREF: sub_code_2E02+59j
		dec	ax
		cmp	ax, 0
		jle	short loc_code_2E6A
		dec	ax

loc_code_2E6A:			; CODE XREF: sub_code_2E02+57j
					; sub_code_2E02:loc_code_2E61j ...
		cmp	ax, 40h	; '@'
		jle	short loc_code_2E74
		mov	ax, 40h	; '@'
		jmp	short loc_code_2E7C
; ---------------------------------------------------------------------------

loc_code_2E74:			; CODE XREF: sub_code_2E02+6Bj
		cmp	ax, 0FFC0h
		jge	short loc_code_2E7C
		mov	ax, 0FFC0h

loc_code_2E7C:			; CODE XREF: sub_code_2E02+70j
					; sub_code_2E02+75j
		mov	word_data_951E,	ax
		sar	ax, 1
		sar	ax, 1
		add	[si+16h], al
		mov	al, [si+16h]
		and	ax, 7Fh
		mov	bx, ax
		mov	al, [bx+1675h]
		cbw
		shl	ax, 1
		add	ax, 80h	; '€'
		mov	[si+5],	ax
		mov	al, [bx+16F5h]
		cbw
		shl	ax, 1
		add	ax, 80h	; '€'
		push	bx
		cmp	ax, 0
		jz	short loc_code_2EBE
		mov	bx, ax
		shl	ax, 1
		shl	ax, 1
		add	ax, bx
		shl	ax, 1
		add	ax, 5
		mov	bl, 0Ch
		div	bl
		mov	ah, 0

loc_code_2EBE:			; CODE XREF: sub_code_2E02+A7j
		pop	bx
		mov	[si+7],	ax
		mov	al, [bx+1775h]
		mov	[si+4],	al
		mov	bx, 1594h
		call	sub_code_2121
		mov	al, byte_data_94E6
		mov	byte_data_94E7,	al
		mov	al, byte_data_94E5
		mov	byte_data_94E6,	al
		mov	al, byte_data_1BA0
		mov	byte_data_94E5,	al
		mov	ax, word_data_954C
		mov	bl, byte_data_951A
		test	al, 40h
		jz	short loc_code_2F02
		cmp	bl, 2
		jnz	short loc_code_2F00
		mov	byte_data_951A,	3
		mov	al, 2
		call	sub_code_3840
		mov	byte_data_951C,	2

loc_code_2F00:			; CODE XREF: sub_code_2E02+EDj
		jmp	short loc_code_2F18
; ---------------------------------------------------------------------------

loc_code_2F02:			; CODE XREF: sub_code_2E02+E8j
		cmp	bl, 1
		jnz	short loc_code_2F0E
		mov	byte_data_951A,	2
		jmp	short loc_code_2F18
; ---------------------------------------------------------------------------

loc_code_2F0E:			; CODE XREF: sub_code_2E02+103j
		cmp	bl, 3
		jnz	short loc_code_2F18
		mov	byte_data_951A,	0

loc_code_2F18:			; CODE XREF: sub_code_2E02:loc_code_2F00j
					; sub_code_2E02+10Aj	...
		mov	ax, word_data_954C
		mov	bl, byte_data_951B
		test	al, 20h
		jz	short loc_code_2F39
		cmp	bl, 2
		jnz	short loc_code_2F37
		mov	byte_data_951B,	3
		mov	al, 2
		call	sub_code_3840
		mov	byte_data_951C,	2

loc_code_2F37:			; CODE XREF: sub_code_2E02+124j
		jmp	short locret_code_2F4F
; ---------------------------------------------------------------------------

loc_code_2F39:			; CODE XREF: sub_code_2E02+11Fj
		cmp	bl, 1
		jnz	short loc_code_2F45
		mov	byte_data_951B,	2
		jmp	short locret_code_2F4F
; ---------------------------------------------------------------------------

loc_code_2F45:			; CODE XREF: sub_code_2E02+13Aj
		cmp	bl, 3
		jnz	short locret_code_2F4F
		mov	byte_data_951B,	0

locret_code_2F4F:			; CODE XREF: sub_code_2E02:loc_code_2F37j
					; sub_code_2E02+141j	...
		retn
sub_code_2E02	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2F50	proc near		; CODE XREF: sub_code_F3C+42p
					; sub_code_F3C+5Ap ...
		mov	al, [si]
		test	al, 20h
		jnz	short loc_code_2F5E
		mov	ah, byte_data_951A
		mov	al, 0F8h ; 'ø'
		jmp	short loc_code_2F64
; ---------------------------------------------------------------------------

loc_code_2F5E:			; CODE XREF: sub_code_2F50+4j
		mov	ah, byte_data_951B
		mov	al, 8

loc_code_2F64:			; CODE XREF: sub_code_2F50+Cj
		cmp	ah, 3
		jz	short loc_code_2F6E
		cmp	ah, 0
		jnz	short loc_code_2F90

loc_code_2F6E:			; CODE XREF: sub_code_2F50+17j
		mov	byte ptr [si], 0
		mov	si, 1BA1h

loc_code_2F74:			; CODE XREF: sub_code_2F50+3Dj
		mov	al, [si]
		test	al, 80h
		jnz	short locret_code_2F8F
		test	al, 1
		jz	short loc_code_2F8A
		mov	al, [si+12h]
		cmp	al, 0Fh
		jnz	short loc_code_2F8A
		push	si
		call	sub_code_3059
		pop	si

loc_code_2F8A:			; CODE XREF: sub_code_2F50+2Cj
					; sub_code_2F50+33j
		add	si, 17h
		jmp	short loc_code_2F74
; ---------------------------------------------------------------------------

locret_code_2F8F:			; CODE XREF: sub_code_2F50+28j
		retn
; ---------------------------------------------------------------------------

loc_code_2F90:			; CODE XREF: sub_code_2F50+1Cj
		add	al, byte_data_94E7
		and	ax, 7Fh
		mov	bx, ax
		mov	al, [bx+1675h]
		cbw
		mov	cx, ax
		sar	cx, 1
		add	ax, cx
		add	ax, 80h	; '€'
		mov	[si+5],	ax
		mov	al, [bx+16F5h]
		cbw
		mov	cx, ax
		sar	cx, 1
		add	ax, cx
		add	ax, 80h	; '€'
		cmp	ax, 0
		jz	short loc_code_2FD0
		mov	bx, ax
		shl	ax, 1
		shl	ax, 1
		add	ax, bx
		shl	ax, 1
		add	ax, 5
		mov	bl, 0Ch
		div	bl
		mov	ah, 0

loc_code_2FD0:			; CODE XREF: sub_code_2F50+6Bj
		mov	bl, byte_data_1BA0
		and	bx, 7Fh
		mov	[si+7],	ax
		mov	al, [bx+1892h]
		mov	[si+4],	al
		mov	bx, 1811h
		call	sub_code_2121
		retn
sub_code_2F50	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_2FE8	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1074o
		mov	bx, word_data_9525
		shr	bx, 1
		shr	bx, 1
		shr	bx, 1
		and	bx, 1Fh
		mov	al, [bx+1A0Ah]
		mov	byte_data_9549,	al
		mov	al, [bx+19EAh]
		mov	[si+4],	al
		mov	bx, 1929h
		call	sub_code_2121
		retn
sub_code_2FE8	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_300A	proc near		; CODE XREF: sub_code_FDA+74p
					; DATA XREF: seg000:1076o
		mov	ax, word_data_9547
		sub	ax, [si+13h]
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		cmp	ax, 2Dh	; '-'
		jbe	short loc_code_301F
		mov	byte ptr [si], 0
		retn
; ---------------------------------------------------------------------------

loc_code_301F:			; CODE XREF: sub_code_300A+Fj
		push	ax
		call	sub_code_3130
		pop	ax
		shr	ax, 1
		mov	[si+4],	al
		mov	bx, ax
		mov	al, [bx+1A9Ah]
		mov	[si+2],	al
		mov	bx, 1AC9h
		call	sub_code_2121
		mov	al, [si+2]
		cmp	al, 2
		jz	short loc_code_3040
		retn
; ---------------------------------------------------------------------------

loc_code_3040:			; CODE XREF: sub_code_300A+33j
		mov	bl, byte_data_1B8E
		mov	bh, 0
		mov	al, [bx+17F5h]
		cmp	al, [si+1]
		jz	short loc_code_3050
		retn
; ---------------------------------------------------------------------------

loc_code_3050:			; CODE XREF: sub_code_300A+43j
		mov	al, 9
		call	sub_code_3840
		call	sub_code_3059
		retn
sub_code_300A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3059	proc near		; CODE XREF: sub_code_2F50+36p
					; sub_code_300A+4Bp
		mov	byte ptr [si], 0
		mov	al, byte_data_951D
		cmp	al, 40h	; '@'
		jnz	short loc_code_306A
		add	word_data_9540,	6
		jmp	short locret_code_3083
; ---------------------------------------------------------------------------

loc_code_306A:			; CODE XREF: sub_code_3059+8j
		cmp	al, 80h	; '€'
		jnz	short loc_code_3075
		add	word_data_953C,	4
		jmp	short locret_code_3083
; ---------------------------------------------------------------------------

loc_code_3075:			; CODE XREF: sub_code_3059+13j
		cmp	al, 0C0h ; 'À'
		jnz	short loc_code_3080
		add	word_data_9544,	8
		jmp	short locret_code_3083
; ---------------------------------------------------------------------------

loc_code_3080:			; CODE XREF: sub_code_3059+1Ej
		call	sub_code_268A

locret_code_3083:			; CODE XREF: sub_code_3059+Fj
					; sub_code_3059+1Aj ...
		retn
sub_code_3059	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3084	proc near		; CODE XREF: sub_code_2E02+3Fp
					; sub_code_2E02:loc_code_2E48p
		sub	al, 5
		jns	short loc_code_308D
		mov	ax, 0
		jmp	short locret_code_309C
; ---------------------------------------------------------------------------

loc_code_308D:			; CODE XREF: sub_code_3084+2j
		cmp	al, 38h	; '8'
		jbe	short loc_code_3093
		mov	al, 38h	; '8'

loc_code_3093:			; CODE XREF: sub_code_3084+Bj
		shr	al, 1
		mov	ah, 0
		neg	ax
		sub	ax, 3

locret_code_309C:			; CODE XREF: sub_code_3084+7j
		retn
sub_code_3084	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_309D	proc near		; CODE XREF: sub_code_2E02+4p
		mov	bx, word_data_952A
		add	bx, 7
		shr	bx, 1
		shr	bx, 1
		shr	bx, 1
		add	bx, 2
		add	word_data_9547,	bx
		mov	ax, word_data_950F
		add	ax, bx
		cmp	ax, 2E8h
		jbe	short loc_code_30C4
		mov	ax, 0
		mov	word_data_953C,	0FFFFh

loc_code_30C4:			; CODE XREF: sub_code_309D+1Cj
		mov	word_data_950F,	ax
		mov	ax, word_data_9547
		sub	ax, 380h
		jns	short loc_code_3124
		neg	ax
		cmp	ax, 100h
		jnb	short loc_code_30ED
		mov	word_data_9525,	ax
		mov	al, byte_data_9524
		cmp	al, 0
		jnz	short loc_code_30EB
		mov	si, 1912h
		call	sub_code_B58
		mov	byte_data_9524,	1

loc_code_30EB:			; CODE XREF: sub_code_309D+41j
		jmp	short loc_code_3122
; ---------------------------------------------------------------------------

loc_code_30ED:			; CODE XREF: sub_code_309D+37j
		mov	ax, word_data_9547
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		cmp	al, byte_data_9527
		jz	short loc_code_3122
		mov	byte_data_9527,	al
		mov	bl, al
		mov	bh, 0
		add	bx, word_data_94E2
		mov	al, [bx]
		cmp	al, 0
		jz	short loc_code_3122
		mov	si, 1AB2h
		mov	[si+1],	al
		mov	ax, word_data_9547
		mov	[si+13h], ax
		call	sub_code_B58

loc_code_3122:			; CODE XREF: sub_code_309D:loc_code_30EBj
					; sub_code_309D+63j ...
		jmp	short locret_code_312F
; ---------------------------------------------------------------------------

loc_code_3124:			; CODE XREF: sub_code_309D+30j
		mov	byte_data_94FF,	0
		mov	ax, word_data_950C
		mov	word_data_9528,	ax

locret_code_312F:			; CODE XREF: sub_code_309D:loc_code_3122j
		retn
sub_code_309D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3130	proc near		; CODE XREF: sub_code_300A+16p

; FUNCTION CHUNK AT 3167 SIZE 00000009 BYTES
; FUNCTION CHUNK AT 3178 SIZE 00000009 BYTES
; FUNCTION CHUNK AT 3188 SIZE 00000009 BYTES
; FUNCTION CHUNK AT 319B SIZE 00000009 BYTES

		mov	bl, al
		mov	bh, 0
		mov	cl, [bx+1A6Ah]
		mov	ch, 0
		mov	al, [si+1]
		cmp	al, 1
		jz	short sub_code_315E
		cmp	al, 2
		jz	short loc_code_3167
		cmp	al, 3
		jz	short sub_code_3170
		cmp	al, 4
		jz	short loc_code_3178
		cmp	al, 5
		jz	short sub_code_3181
		cmp	al, 6
		jz	short loc_code_3188
		cmp	al, 7
		jz	short sub_code_3191
		cmp	al, 8
		jz	short loc_code_319B
		retn
sub_code_3130	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_315E	proc near		; CODE XREF: sub_code_3130+Fj
					; sub_code_3130+38p ...
		neg	cx
		add	cx, 6Ah	; 'j'
		mov	[si+7],	cx
		retn
sub_code_315E	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_code_3130

loc_code_3167:			; CODE XREF: sub_code_3130+13j
		push	cx
		call	sub_code_315E
		pop	cx
		call	sub_code_3170
		retn
; END OF FUNCTION CHUNK	FOR sub_code_3130

; =============== S U B	R O U T	I N E =======================================


sub_code_3170	proc near		; CODE XREF: sub_code_3130+17j
					; sub_code_3130+3Cp ...
		add	cx, 80h	; '€'
		mov	[si+5],	cx
		retn
sub_code_3170	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_code_3130

loc_code_3178:			; CODE XREF: sub_code_3130+1Bj
		push	cx
		call	sub_code_3170
		pop	cx
		call	sub_code_3181
		retn
; END OF FUNCTION CHUNK	FOR sub_code_3130

; =============== S U B	R O U T	I N E =======================================


sub_code_3181	proc near		; CODE XREF: sub_code_3130+1Fj
					; sub_code_3130+4Dp ...
		add	cx, 6Ah	; 'j'
		mov	[si+7],	cx
		retn
sub_code_3181	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_code_3130

loc_code_3188:			; CODE XREF: sub_code_3130+23j
		push	cx
		call	sub_code_3181
		pop	cx
		call	sub_code_3191
		retn
; END OF FUNCTION CHUNK	FOR sub_code_3130

; =============== S U B	R O U T	I N E =======================================


sub_code_3191	proc near		; CODE XREF: sub_code_3130+27j
					; sub_code_3130+5Dp ...
		neg	cx
		add	cx, 80h	; '€'
		mov	[si+5],	cx
		retn
sub_code_3191	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_code_3130

loc_code_319B:			; CODE XREF: sub_code_3130+2Bj
		push	cx
		call	sub_code_3191
		pop	cx
		call	sub_code_315E
		retn
; END OF FUNCTION CHUNK	FOR sub_code_3130

; =============== S U B	R O U T	I N E =======================================


sub_code_31A4	proc near		; CODE XREF: sub_code_CF+18p
		mov	ax, word_data_94F8
		mov	es, ax
		assume es:nothing
		mov	di, 144h
		mov	bx, word_data_94F4
		mov	si, 340h
		call	sub_code_31E7
		not	ax
		and	ax, 0Fh
		mov	ah, al
		mov	al, 1
		mov	dx, 3CEh
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		call	sub_code_3209
		mov	ah, al
		mov	al, 0
		out	dx, ax
		push	ds
		mov	ds, bx
		cld
		mov	cx, 0A0h ; ' '

loc_code_31D2:			; CODE XREF: sub_code_31A4+38j
		push	cx
		mov	cx, 20h	; ' '
		rep movsb
		add	di, 8
		pop	cx
		loop	loc_code_31D2
		pop	ds
		mov	ax, 0
		out	dx, ax
		inc	al
		out	dx, ax
		retn
sub_code_31A4	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_31E7	proc near		; CODE XREF: sub_code_31A4+Fp
		mov	al, byte_data_951D
		cmp	al, 40h	; '@'
		jnz	short loc_code_31F3
		mov	ax, 2
		jmp	short locret_code_3208
; ---------------------------------------------------------------------------

loc_code_31F3:			; CODE XREF: sub_code_31E7+5j
		cmp	al, 80h	; '€'
		jnz	short loc_code_31FC
		mov	ax, 4
		jmp	short locret_code_3208
; ---------------------------------------------------------------------------

loc_code_31FC:			; CODE XREF: sub_code_31E7+Ej
		cmp	al, 0C0h ; 'À'
		jnz	short loc_code_3205
		mov	ax, 1
		jmp	short locret_code_3208
; ---------------------------------------------------------------------------

loc_code_3205:			; CODE XREF: sub_code_31E7+17j
		mov	ax, 3

locret_code_3208:			; CODE XREF: sub_code_31E7+Aj
					; sub_code_31E7+13j ...
		retn
sub_code_31E7	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3209	proc near		; CODE XREF: sub_code_31A4+1Fp
		mov	al, byte_data_951C
		cmp	al, 0
		jnz	short loc_code_3215
		mov	ax, 0
		jmp	short locret_code_322B
; ---------------------------------------------------------------------------

loc_code_3215:			; CODE XREF: sub_code_3209+5j
		cmp	al, 1
		jnz	short loc_code_3223
		mov	ax, 7
		mov	byte_data_951C,	0
		jmp	short locret_code_322B
; ---------------------------------------------------------------------------

loc_code_3223:			; CODE XREF: sub_code_3209+Ej
		mov	ax, 0Fh
		mov	byte_data_951C,	1

locret_code_322B:			; CODE XREF: sub_code_3209+Aj
					; sub_code_3209+18j
		retn
sub_code_3209	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	ax, word_data_94F8
		mov	es, ax
		mov	di, [bp+0Ah]
		mov	bx, [bp+4]
		mov	bx, [bx-6B18h]
		mov	si, [bp+0Ch]
		mov	dx, 3CEh
		mov	ax, 805h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 7
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; color	masking	disable
					; bits 0-3 disable planes from compare logic in	read mode 01
		mov	dl, 0C4h ; 'Ä'
		mov	ax, 802h
		push	ds
		mov	ds, bx

loc_code_3254:			; CODE XREF: seg000:327Cj
		out	dx, ax		; EGA: sequencer address reg
					; unknown register
		push	ax
		push	di
		push	si
		mov	cx, [bp+6]

loc_code_325B:			; CODE XREF: seg000:3271j
		push	di
		push	si
		push	cx
		mov	cx, [bp+8]

loc_code_3261:			; CODE XREF: seg000:3266j
		lodsb
		and	es:[di], al
		inc	di
		loop	loc_code_3261
		pop	cx
		pop	si
		pop	di
		add	si, 28h	; '('
		add	di, 28h	; '('
		loop	loc_code_325B
		pop	si
		pop	di
		pop	ax
		add	si, 1F40h
		shr	ah, 1
		jnz	short loc_code_3254
		pop	ds
		mov	ax, 0F02h
		out	dx, ax		; EGA: sequencer address reg
					; unknown register
		mov	dl, 0CEh ; 'Î'
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		mov	ax, 0F07h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		pop	bp
		retn	0Ah

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_3291	proc near		; CODE XREF: sub_code_3472+22p
					; sub_code_3498+Bp

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	ax, [bp+arg_0]
		mov	es, ax
		mov	di, 144h
		mov	bx, [bp+arg_2]
		mov	si, 144h
		mov	dx, 3CEh
		mov	ax, 105h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		push	ds
		mov	ds, bx
		cld
		mov	cx, 0A0h ; ' '

loc_code_32B0:			; CODE XREF: sub_code_3291+2Cj
		push	cx
		mov	cx, 20h	; ' '
		rep movsb
		add	si, 8
		add	di, 8
		pop	cx
		loop	loc_code_32B0
		pop	ds
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		pop	bp
		retn	4
sub_code_3291	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	ax, word_data_94F8
		mov	es, ax
		mov	di, [bp+0Ah]
		mov	dx, 3CEh
		mov	ax, [bp+4]
		mov	ah, al
		mov	al, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		mov	ax, 0F01h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		cld
		mov	bx, [bp+6]

loc_code_32E6:			; CODE XREF: seg000:32F1j
		push	di
		mov	cx, [bp+8]
		rep stosb
		pop	di
		add	di, 28h	; '('
		dec	bx
		jnz	short loc_code_32E6
		mov	ax, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		inc	al
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; enable set/reset
		pop	bp
		retn	8

; =============== S U B	R O U T	I N E =======================================


sub_code_32FE	proc near		; CODE XREF: sub_code_CF+Dp
		mov	dx, 3CEh
		mov	ax, 105h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, word_data_94F8
		mov	es, ax
		mov	di, 144h
		mov	ax, word_data_9528
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		mov	si, ax
		push	ds
		mov	ax, 0A800h
		mov	ds, ax
		assume ds:nothing
		cld
		mov	cx, 0A0h ; ' '

loc_code_3326:			; CODE XREF: sub_code_32FE+36j
		push	cx
		mov	cx, 20h	; ' '
		rep movsb
		and	si, 7FFFh
		add	di, 8
		pop	cx
		loop	loc_code_3326
		pop	ds
		assume ds:dseg
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		retn
sub_code_32FE	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_333C	proc near		; CODE XREF: start+61p
		mov	ax, 0Dh
		int	10h		; - VIDEO - SET	VIDEO MODE
					; AL = mode
		mov	ax, 0A000h
		mov	word_data_94FA,	ax
		add	ax, 200h
		mov	word_data_94F8,	ax
		mov	ax, 0
		call	sub_code_33B3
		mov	ax, word_data_94F8
		mov	bx, word_data_94FA
		mov	word_data_94F8,	bx
		mov	word_data_94FA,	ax
		call	sub_code_33D7
		mov	bx, word_data_94FA
		shl	bx, 1
		shl	bx, 1
		shl	bx, 1
		shl	bx, 1
		cli
		mov	dx, 3D4h
		mov	ah, bh
		mov	al, 0Ch
		out	dx, ax		; Video: CRT cntrlr addr
					; horizontal total
		mov	ah, bl
		inc	al
		out	dx, ax		; Video: CRT cntrlr addr
					; horizontal total
		sti
		call	sub_code_33D7
		retn
sub_code_333C	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3383	proc near		; CODE XREF: sub_code_CF+21p
					; sub_code_103+3Bp ...
		mov	ax, word_data_94F8
		mov	bx, word_data_94FA
		mov	word_data_94F8,	bx
		mov	word_data_94FA,	ax
		mov	bx, word_data_94FA
		shl	bx, 1
		shl	bx, 1
		shl	bx, 1
		shl	bx, 1
		cli
		mov	dx, 3D4h
		mov	ah, bh
		mov	al, 0Ch
		out	dx, ax		; Video: CRT cntrlr addr
					; horizontal total
		sti
		mov	dx, 3DAh

loc_code_33AA:			; CODE XREF: sub_code_3383+2Aj
		in	al, dx		; Video	status bits:
					; 0: retrace.  1=display is in vert or horiz retrace.
					; 1: 1=light pen is triggered; 0=armed
					; 2: 1=light pen switch	is open; 0=closed
					; 3: 1=vertical	sync pulse is occurring.
		and	al, 8
		jnz	short loc_code_33AA
		call	sub_code_33D7
		retn
sub_code_3383	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_33B3	proc near		; CODE XREF: sub_code_333C+14p
					; sub_code_3423+3p ...
		push	ax
		mov	ax, word_data_94F8
		mov	es, ax
		mov	di, 0
		mov	dx, 3CEh
		pop	ax
		mov	ah, al
		mov	al, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		mov	ax, 0F01h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		cld
		mov	cx, 0FA0h
		rep stosw
		mov	ax, 0
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; set/reset.
					; Data bits 0-3	select planes for write	mode 00
		inc	al
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; enable set/reset
		retn
sub_code_33B3	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_33D7	proc near		; CODE XREF: sub_code_333C+25p
					; sub_code_333C+43p ...
		mov	dx, 3DAh

loc_code_33DA:			; CODE XREF: sub_code_33D7+6j
		in	al, dx		; Video	status bits:
					; 0: retrace.  1=display is in vert or horiz retrace.
					; 1: 1=light pen is triggered; 0=armed
					; 2: 1=light pen switch	is open; 0=closed
					; 3: 1=vertical	sync pulse is occurring.
		and	al, 8
		jz	short loc_code_33DA

loc_code_33DF:			; CODE XREF: sub_code_33D7+Bj
		in	al, dx		; Video	status bits:
					; 0: retrace.  1=display is in vert or horiz retrace.
					; 1: 1=light pen is triggered; 0=armed
					; 2: 1=light pen switch	is open; 0=closed
					; 3: 1=vertical	sync pulse is occurring.
		and	al, 8
		jnz	short loc_code_33DF
		retn
sub_code_33D7	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_33E5	proc near		; CODE XREF: sub_code_3472+7p
					; sub_code_3472+14p
		mov	ax, word_data_94F8
		mov	es, ax
		mov	di, 0
		mov	dx, 3CEh
		mov	ax, 805h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		mov	ax, 7
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; color	masking	disable
					; bits 0-3 disable planes from compare logic in	read mode 01
		mov	dl, 0C4h ; 'Ä'
		mov	ax, 802h
		push	ds
		mov	ds, bx

loc_code_3400:			; CODE XREF: sub_code_33E5+2Cj
		out	dx, ax		; EGA: sequencer address reg
					; unknown register
		push	ax
		push	di
		mov	cx, 1F40h

loc_code_3406:			; CODE XREF: sub_code_33E5+26j
		lodsb
		and	es:[di], al
		inc	di
		loop	loc_code_3406
		pop	di
		pop	ax
		shr	ah, 1
		jnz	short loc_code_3400
		pop	ds
		mov	ax, 0F02h
		out	dx, ax		; EGA: sequencer address reg
					; unknown register
		mov	dl, 0CEh ; 'Î'
		mov	ax, 5
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; mode register.Data bits:
					; 0-1: Write mode 0-2
					; 2: test condition
					; 3: read mode:	1=color	compare, 0=direct
					; 4: 1=use odd/even RAM	addressing
					; 5: 1=use CGA mid-res map (2-bits/pixel)
		mov	ax, 0F07h
		out	dx, ax		; EGA: graph 1 and 2 addr reg:
					; unknown register
		retn
sub_code_33E5	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3423	proc near		; CODE XREF: sub_code_A9+1Fp
		mov	ax, 0
		call	sub_code_33B3
		call	sub_code_3439
		call	sub_code_3383
		mov	ax, 0
		call	sub_code_33B3
		call	sub_code_3439
		retn
sub_code_3423	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3439	proc near		; CODE XREF: sub_code_3423+6p
					; sub_code_3423+12p
		mov	ax, word_data_94F8
		mov	es, ax
		mov	di, 11Ch
		mov	ax, 0FFFFh
		mov	cx, 10h
		rep stosw
		mov	di, 1A44h
		mov	cx, 10h
		rep stosw
		mov	di, 11Bh
		mov	al, 1
		mov	cx, 0A2h ; '¢'

loc_code_3459:			; CODE XREF: sub_code_3439+26j
		mov	es:[di], al
		add	di, 28h	; '('
		loop	loc_code_3459
		mov	di, 13Ch
		mov	al, 80h	; '€'
		mov	cx, 0A2h ; '¢'

loc_code_3469:			; CODE XREF: sub_code_3439+36j
		mov	es:[di], al
		add	di, 28h	; '('
		loop	loc_code_3469
		retn
sub_code_3439	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3472	proc near		; CODE XREF: sub_code_103+1Ep
		mov	si, 0
		mov	bx, word_data_94F2
		call	sub_code_33E5
		call	sub_code_3383
		mov	si, 0
		mov	bx, word_data_94F2
		call	sub_code_33E5
		mov	ax, word_data_94F8
		push	ax
		mov	ax, 0A000h
		add	ax, 400h
		push	ax
		call	sub_code_3291
		retn
sub_code_3472	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3498	proc near		; CODE XREF: sub_code_103+35p
					; sub_code_29DB+53p
		mov	ax, 0A000h
		add	ax, 400h
		push	ax
		mov	ax, word_data_94F8
		push	ax
		call	sub_code_3291
		retn
sub_code_3498	endp

; ---------------------------------------------------------------------------
		align 2

; =============== S U B	R O U T	I N E =======================================


sub_code_34A8	proc near		; CODE XREF: sub_code_CF:loc_code_E4p
		mov	di, 0
		mov	ax, word_data_94F4
		mov	es, ax
		mov	ax, 0
		mov	cx, 1000h
		cld
		rep stosw
		mov	ax, 4Fh	; 'O'
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	ax, 0B0h ; '°'
		push	ax
		mov	ax, 0
		push	ax
		call	sub_code_36D4
		mov	ax, 4Fh	; 'O'
		push	ax
		mov	ax, 0
		push	ax
		mov	ax, 0B0h ; '°'
		push	ax
		mov	ax, 0FFh
		push	ax
		call	sub_code_36D4
		mov	ax, 0
		push	ax
		mov	ax, 4Fh	; 'O'
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	ax, 0B0h ; '°'
		push	ax
		call	sub_code_36D4
		mov	ax, 0
		push	ax
		mov	ax, 0B0h ; '°'
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	ax, 4Fh	; 'O'
		push	ax
		call	sub_code_36D4
		mov	ax, word_data_9547
		and	ax, 3Fh
		mov	word_data_954E,	ax
		mov	bx, ax
		add	ax, 40h	; '@'
		push	ax
		mov	al, [bx+1FDCh]
		mov	ah, 0
		push	ax
		call	sub_code_35BC
		mov	ax, word_data_954E
		cmp	ax, 0Ch
		jbe	short loc_code_3527
		retn
; ---------------------------------------------------------------------------

loc_code_3527:			; CODE XREF: sub_code_34A8+7Cj
		mov	bx, word_data_954E
		mov	al, [bx+201Ch]
		mov	ah, 0
		add	ax, 80h	; '€'
		push	ax
		mov	ax, 0
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	al, [bx+2029h]
		mov	ah, 0
		neg	ax
		add	ax, 7Fh	; ''
		push	ax
		call	sub_code_36D4
		mov	bx, word_data_954E
		mov	al, [bx+201Ch]
		mov	ah, 0
		neg	ax
		add	ax, 7Fh	; ''
		push	ax
		mov	ax, 0
		push	ax
		mov	ax, 0
		push	ax
		mov	al, [bx+2029h]
		mov	ah, 0
		neg	ax
		add	ax, 7Fh	; ''
		push	ax
		call	sub_code_36D4
		mov	bx, word_data_954E
		mov	al, [bx+201Ch]
		mov	ah, 0
		add	ax, 80h	; '€'
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	al, [bx+2029h]
		mov	ah, 0
		add	ax, 80h	; '€'
		push	ax
		call	sub_code_36D4
		mov	bx, word_data_954E
		mov	al, [bx+201Ch]
		mov	ah, 0
		neg	ax
		add	ax, 7Fh	; ''
		push	ax
		mov	ax, 0FFh
		push	ax
		mov	ax, 0
		push	ax
		mov	al, [bx+2029h]
		mov	ah, 0
		add	ax, 80h	; '€'
		push	ax
		call	sub_code_36D4
		retn
sub_code_34A8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_35BC	proc near		; CODE XREF: sub_code_34A8+73p

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp

loc_code_35BF:			; CODE XREF: sub_code_35BC+111j
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		call	sub_code_36D4
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		call	sub_code_36D4
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		call	sub_code_36D4
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		call	sub_code_36D4
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		call	sub_code_36D4
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_2]
		push	ax
		call	sub_code_36D4
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, 80h	; '€'
		add	ax, [bp+arg_0]
		push	ax
		call	sub_code_36D4
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_0]
		push	ax
		mov	ax, 7Fh	; ''
		sub	ax, [bp+arg_2]
		push	ax
		call	sub_code_36D4
		mov	ax, [bp+arg_2]
		shr	ax, 1
		cmp	al, byte_data_9549
		jbe	short loc_code_36D0
		mov	[bp+arg_2], ax
		mov	ax, [bp+arg_0]
		shr	ax, 1
		mov	[bp+arg_0], ax
		jmp	loc_code_35BF
; ---------------------------------------------------------------------------

loc_code_36D0:			; CODE XREF: sub_code_35BC+104j
		pop	bp
		retn	4
sub_code_35BC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_code_36D4	proc near		; CODE XREF: sub_code_34A8+21p
					; sub_code_34A8+34p ...

var_A		= word ptr -0Ah
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		mov	ax, word_data_94F4
		mov	es, ax
		mov	ax, [bp+arg_4]
		cmp	ax, 0
		jz	short loc_code_36FA
		mov	bx, ax
		shl	ax, 1
		shl	ax, 1
		add	ax, bx
		shl	ax, 1
		add	ax, 5
		mov	bl, 0Ch
		div	bl
		mov	ah, 0

loc_code_36FA:			; CODE XREF: sub_code_36D4+11j
		mov	[bp+arg_4], ax
		mov	ax, [bp+arg_0]
		cmp	ax, 0
		jz	short loc_code_3718
		mov	bx, ax
		shl	ax, 1
		shl	ax, 1
		add	ax, bx
		shl	ax, 1
		add	ax, 5
		mov	bl, 0Ch
		div	bl
		mov	ah, 0

loc_code_3718:			; CODE XREF: sub_code_36D4+2Fj
		mov	[bp+arg_0], ax
		mov	ax, [bp+arg_6]
		mov	bx, [bp+arg_2]
		cmp	bx, ax
		jnb	short loc_code_3737
		mov	[bp+arg_6], bx
		mov	[bp+arg_2], ax
		mov	ax, [bp+arg_4]
		mov	bx, [bp+arg_0]
		mov	[bp+arg_4], bx
		mov	[bp+arg_0], ax

loc_code_3737:			; CODE XREF: sub_code_36D4+4Fj
		mov	ax, [bp+arg_2]
		sub	ax, [bp+arg_6]
		mov	[bp+var_2], ax
		mov	ax, [bp+arg_0]
		sub	ax, [bp+arg_4]
		jns	short loc_code_3751
		neg	ax
		mov	[bp+var_A], 0FFE0h
		jmp	short loc_code_3756
; ---------------------------------------------------------------------------

loc_code_3751:			; CODE XREF: sub_code_36D4+72j
		mov	[bp+var_A], 20h	; ' '

loc_code_3756:			; CODE XREF: sub_code_36D4+7Bj
		mov	[bp+var_4], ax
		mov	cx, [bp+var_2]
		cmp	cx, 0
		jz	short loc_code_37DB
		cmp	ax, 0
		jnz	short loc_code_3769
		jmp	loc_code_37ED
; ---------------------------------------------------------------------------

loc_code_3769:			; CODE XREF: sub_code_36D4+90j
		cmp	ax, [bp+var_2]
		jnb	short loc_code_37A4
		mov	ax, [bp+var_2]
		shr	ax, 1
		mov	[bp+var_6], ax
		call	sub_code_3801
		mov	cx, [bp+var_2]

loc_code_377C:			; CODE XREF: sub_code_36D4+CCj
		shr	al, 1
		jnz	short loc_code_3783
		mov	al, 80h	; '€'
		inc	di

loc_code_3783:			; CODE XREF: sub_code_36D4+AAj
		mov	bx, [bp+var_6]
		add	bx, [bp+var_4]
		mov	[bp+var_6], bx
		cmp	bx, [bp+var_2]
		jbe	short loc_code_379D
		sub	bx, [bp+var_2]
		mov	[bp+var_6], bx
		mov	bx, [bp+var_A]
		add	di, [bp+var_A]

loc_code_379D:			; CODE XREF: sub_code_36D4+BBj
		or	es:[di], al
		loop	loc_code_377C
		jmp	short loc_code_37D5
; ---------------------------------------------------------------------------

loc_code_37A4:			; CODE XREF: sub_code_36D4+98j
		mov	ax, [bp+var_4]
		shr	ax, 1
		mov	[bp+var_6], ax
		call	sub_code_3801
		mov	cx, [bp+var_4]

loc_code_37B2:			; CODE XREF: sub_code_36D4+FFj
		add	di, [bp+var_A]
		mov	bx, [bp+var_6]
		add	bx, [bp+var_2]
		mov	[bp+var_6], bx
		cmp	bx, [bp+var_4]
		jbe	short loc_code_37D0
		sub	bx, [bp+var_4]
		mov	[bp+var_6], bx
		shr	al, 1
		jnz	short loc_code_37D0
		mov	al, 80h	; '€'
		inc	di

loc_code_37D0:			; CODE XREF: sub_code_36D4+EDj
					; sub_code_36D4+F7j
		or	es:[di], al
		loop	loc_code_37B2

loc_code_37D5:			; CODE XREF: sub_code_36D4+CEj
					; sub_code_36D4+10Dj	...
		mov	sp, bp
		pop	bp
		retn	8
; ---------------------------------------------------------------------------

loc_code_37DB:			; CODE XREF: sub_code_36D4+8Bj
		call	sub_code_3801
		mov	cx, [bp+var_4]
		jcxz	short loc_code_37D5

loc_code_37E3:			; CODE XREF: sub_code_36D4+115j
		add	di, [bp+var_A]
		or	es:[di], al
		loop	loc_code_37E3
		jmp	short loc_code_37D5
; ---------------------------------------------------------------------------

loc_code_37ED:			; CODE XREF: sub_code_36D4+92j
		call	sub_code_3801
		mov	cx, [bp+var_2]

loc_code_37F3:			; CODE XREF: sub_code_36D4+129j
		shr	al, 1
		jnz	short loc_code_37FA
		mov	al, 80h	; '€'
		inc	di

loc_code_37FA:			; CODE XREF: sub_code_36D4+121j
		or	es:[di], al
		loop	loc_code_37F3
		jmp	short loc_code_37D5
sub_code_36D4	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3801	proc near		; CODE XREF: sub_code_36D4+A2p
					; sub_code_36D4+D8p ...
		mov	ax, [bp+8]
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		shl	ax, 1
		mov	di, ax
		mov	ax, [bp+0Ah]
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		add	di, ax
		mov	cx, [bp+0Ah]
		and	cx, 7
		mov	al, 80h	; '€'
		shr	al, cl
		or	es:[di], al
		retn
sub_code_3801	endp

; ---------------------------------------------------------------------------
		align 2

; =============== S U B	R O U T	I N E =======================================


sub_code_382A	proc near		; CODE XREF: start+73p
		mov	al, 0
		mov	byte_data_9550,	al
		mov	byte_data_9551,	al
		mov	byte_data_9552,	al
		mov	byte_data_9506,	1
		mov	byte_data_9505,	0
		retn
sub_code_382A	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3840	proc near		; CODE XREF: sub_code_1C0+E1p
					; sub_code_1C0+100p ...
		mov	ah, byte_data_955E
		cmp	ah, 0
		jz	short loc_code_384A
		retn
; ---------------------------------------------------------------------------

loc_code_384A:			; CODE XREF: sub_code_3840+7j
		mov	ah, byte_data_9506
		cmp	ah, 0
		jnz	short loc_code_3854
		retn
; ---------------------------------------------------------------------------

loc_code_3854:			; CODE XREF: sub_code_3840+11j
		mov	ah, byte_data_9550
		cmp	ah, 0
		jnz	short loc_code_3866
		push	bx
		mov	byte_data_9550,	al
		call	sub_code_3914
		pop	bx
		retn
; ---------------------------------------------------------------------------

loc_code_3866:			; CODE XREF: sub_code_3840+1Bj
		mov	ah, byte_data_9551
		cmp	ah, 0
		jnz	short loc_code_3873
		mov	byte_data_9551,	al
		retn
; ---------------------------------------------------------------------------

loc_code_3873:			; CODE XREF: sub_code_3840+2Dj
		cmp	al, byte_data_9552
		jbe	short locret_code_387C
		mov	byte_data_9552,	al

locret_code_387C:			; CODE XREF: sub_code_3840+37j
		retn
sub_code_3840	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_387D	proc near		; CODE XREF: seg000:05E0p
		mov	al, byte_data_955E
		cmp	al, 0
		jz	short loc_code_389B
		mov	al, byte_data_9506
		cmp	al, 0
		jz	short loc_code_3890
		call	sub_code_39DB
		jmp	short loc_code_389B
; ---------------------------------------------------------------------------

loc_code_3890:			; CODE XREF: sub_code_387D+Cj
		mov	word_data_955F,	0
		mov	byte_data_955E,	0

loc_code_389B:			; CODE XREF: sub_code_387D+5j
					; sub_code_387D+11j
		mov	al, byte_data_9550
		cmp	al, 0
		jnz	short loc_code_38A3
		retn
; ---------------------------------------------------------------------------

loc_code_38A3:			; CODE XREF: sub_code_387D+23j
		dec	byte_data_9557
		jnz	short loc_code_38D4
		mov	al, byte_data_9506
		cmp	al, 0
		jnz	short loc_code_38B4
		call	sub_code_39A3
		retn
; ---------------------------------------------------------------------------

loc_code_38B4:			; CODE XREF: sub_code_387D+31j
		mov	al, byte_data_9551
		cmp	al, 0
		jz	short loc_code_38D0
		mov	byte_data_9550,	al
		mov	bl, byte_data_9552
		mov	byte_data_9551,	bl
		mov	byte_data_9552,	0
		call	sub_code_3914
		jmp	short locret_code_38D3
; ---------------------------------------------------------------------------

loc_code_38D0:			; CODE XREF: sub_code_387D+3Cj
		call	sub_code_39A3

locret_code_38D3:			; CODE XREF: sub_code_387D+51j
		retn
; ---------------------------------------------------------------------------

loc_code_38D4:			; CODE XREF: sub_code_387D+2Aj
		mov	ax, word_data_9558
		add	ax, word_data_955A
		mov	word_data_9558,	ax
		mov	al, byte_data_9553
		cmp	al, 0
		jz	short loc_code_38FD
		mov	bl, byte_data_9554
		inc	byte_data_9554
		and	bx, 0Fh
		shl	bx, 1
		add	bx, word_data_9555
		mov	ax, [bx]
		mov	word_data_955C,	ax
		jmp	short loc_code_3903
; ---------------------------------------------------------------------------

loc_code_38FD:			; CODE XREF: sub_code_387D+66j
		mov	word_data_955C,	0

loc_code_3903:			; CODE XREF: sub_code_387D+7Ej
		mov	ax, word_data_9558
		add	word_data_955C,	ax
		mov	ax, word_data_955C
		out	42h, al		; Timer	8253-5 (AT: 8254.2).
		mov	al, ah
		out	42h, al		; Timer	8253-5 (AT: 8254.2).
		retn
sub_code_387D	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3914	proc near		; CODE XREF: sub_code_3840+21p
					; sub_code_387D+4Ep ...
		dec	al
		mov	bl, al
		mov	bh, 0
		shl	bx, 1
		mov	bx, [bx-741Ch]
		mov	al, [bx+1]
		mov	byte_data_9557,	al
		cmp	bx, 8C2Ch
		jnz	short loc_code_3941
		mov	ax, word_data_9536
		mov	ah, al
		mov	al, 0
		shl	ax, 1
		shl	ax, 1
		neg	ax
		add	ax, 1F40h
		mov	word_data_8C2E,	ax
		jmp	short loc_code_3966
; ---------------------------------------------------------------------------

loc_code_3941:			; CODE XREF: sub_code_3914+16j
		cmp	bx, 8C32h
		jnz	short loc_code_3966
		mov	al, byte_data_1BA0
		and	ax, 7Fh
		cmp	ax, 3Fh	; '?'
		jbe	short loc_code_3957
		sub	ax, 40h	; '@'
		jmp	short loc_code_395C
; ---------------------------------------------------------------------------

loc_code_3957:			; CODE XREF: sub_code_3914+3Cj
		neg	ax
		add	ax, 3Fh	; '?'

loc_code_395C:			; CODE XREF: sub_code_3914+41j
		shl	ax, 1
		shl	ax, 1
		add	ax, 190h
		mov	word_data_8C34,	ax

loc_code_3966:			; CODE XREF: sub_code_3914+2Bj
					; sub_code_3914+31j
		mov	ax, [bx+2]
		mov	word_data_9558,	ax
		mov	ax, [bx+4]
		mov	word_data_955A,	ax
		mov	bl, [bx]
		mov	byte_data_9553,	bl
		cmp	bl, 0
		jle	short loc_code_398F
		dec	bl
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx-73A4h]
		mov	word_data_9555,	ax
		mov	byte_data_9554,	0

loc_code_398F:			; CODE XREF: sub_code_3914+67j
		mov	al, 0B6h ; '¶'
		out	43h, al		; Timer	8253-5 (AT: 8254.2).
		mov	ax, word_data_9558
		out	42h, al		; Timer	8253-5 (AT: 8254.2).
		mov	al, ah
		out	42h, al		; Timer	8253-5 (AT: 8254.2).
		in	al, 61h		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		or	al, 3
		out	61h, al		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		retn
sub_code_3914	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_39A3	proc near		; CODE XREF: sub_code_1C0:loc_code_96p
					; sub_code_387D+33p ...
		mov	al, 0
		mov	byte_data_9550,	al
		mov	byte_data_9551,	al
		mov	byte_data_9552,	al
		mov	byte_data_9557,	al
		in	al, 61h		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		and	al, 0FCh
		out	61h, al		; PC/XT	PPI port B bits:
					; 0: Tmr 2 gate	ÍËÍ OR	03H=spkr ON
					; 1: Tmr 2 data	Í¼  AND	0fcH=spkr OFF
					; 3: 1=read high switches
					; 4: 0=enable RAM parity checking
					; 5: 0=enable I/O channel check
					; 6: 0=hold keyboard clock low
					; 7: 0=enable kbrd
		retn
sub_code_39A3	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_39B8	proc near		; CODE XREF: sub_code_103:loc_code_11Ep
		mov	byte_data_9561,	0
		mov	word_data_955F,	0
		mov	byte_data_955E,	1
		mov	al, byte_data_9546
		cmp	al, 0
		jnz	short loc_code_39D4
		mov	ax, 8DECh
		jmp	short loc_code_39D7
; ---------------------------------------------------------------------------

loc_code_39D4:			; CODE XREF: sub_code_39B8+15j
		mov	ax, 8D4Ch

loc_code_39D7:			; CODE XREF: sub_code_39B8+1Aj
		mov	word_data_9562,	ax
		retn
sub_code_39B8	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_39DB	proc near		; CODE XREF: sub_code_387D+Ep
		dec	byte_data_9561
		js	short loc_code_39E2
		retn
; ---------------------------------------------------------------------------

loc_code_39E2:			; CODE XREF: sub_code_39DB+4j
		mov	byte_data_9561,	7
		mov	byte_data_8C57,	0Eh
		mov	byte_data_8C56,	4
		mov	bx, word_data_955F
		mov	si, word_data_9562
		mov	al, [bx+si]
		cmp	al, 0FFh
		jnz	short loc_code_3A05
		mov	byte_data_955E,	0
		retn
; ---------------------------------------------------------------------------

loc_code_3A05:			; CODE XREF: sub_code_39DB+22j
		cmp	al, 0
		jnz	short loc_code_3A29
		mov	al, byte_data_9550
		cmp	al, 0
		jnz	short loc_code_3A25
		mov	byte_data_8C56,	0
		mov	byte_data_8C57,	6
		and	bx, 1Fh
		mov	al, [bx-71A3h]
		sub	al, 0Ch
		jmp	short loc_code_3A27
; ---------------------------------------------------------------------------

loc_code_3A25:			; CODE XREF: sub_code_39DB+33j
		mov	al, 0

loc_code_3A27:			; CODE XREF: sub_code_39DB+48j
		jmp	short loc_code_3A33
; ---------------------------------------------------------------------------

loc_code_3A29:			; CODE XREF: sub_code_39DB+2Cj
		cmp	al, 0FEh ; 'þ'
		jnz	short loc_code_3A31
		mov	al, 0
		jmp	short loc_code_3A33
; ---------------------------------------------------------------------------

loc_code_3A31:			; CODE XREF: sub_code_39DB+50j
		add	al, 0Ch

loc_code_3A33:			; CODE XREF: sub_code_39DB:loc_code_3A27j
					; sub_code_39DB+54j
		call	sub_code_3A3B
		inc	word_data_955F
		retn
sub_code_39DB	endp


; =============== S U B	R O U T	I N E =======================================


sub_code_3A3B	proc near		; CODE XREF: sub_code_39DB:loc_code_3A33p
		dec	al
		jns	short loc_code_3A40
		retn
; ---------------------------------------------------------------------------

loc_code_3A40:			; CODE XREF: sub_code_3A3B+2j
		mov	bl, al
		mov	bh, 0
		shl	bx, 1
		mov	ax, [bx-731Ch]
		mov	word_data_8C58,	ax
		mov	al, 0Fh
		mov	byte_data_9550,	al
		call	sub_code_3914
		retn
sub_code_3A3B	endp

seg000		ends
