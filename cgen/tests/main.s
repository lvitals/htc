psect	text
global	_main
_main:
global	ncsv, cret, indir
call	ncsv
defw	f75
global	_printf
ld	hl,19f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,29f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,39f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
global	_demonstrate_variables_and_types
call	_demonstrate_variables_and_types
ld	hl,0
add	hl,sp
ld	sp,hl
global	_demonstrate_operators
call	_demonstrate_operators
ld	hl,0
add	hl,sp
ld	sp,hl
global	_demonstrate_control_flow
call	_demonstrate_control_flow
ld	hl,0
add	hl,sp
ld	sp,hl
global	_demonstrate_functions_and_point
call	_demonstrate_functions_and_point
ld	hl,0
add	hl,sp
ld	sp,hl
global	_demonstrate_arrays_and_strings
call	_demonstrate_arrays_and_strings
ld	hl,0
add	hl,sp
ld	sp,hl
global	_demonstrate_structs_unions_enum
call	_demonstrate_structs_unions_enum
ld	hl,0
add	hl,sp
ld	sp,hl
global	_demonstrate_file_io
call	_demonstrate_file_io
ld	hl,0
add	hl,sp
ld	sp,hl
ld	hl,49f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,0
jp	l2
l2:
jp	cret
f75	equ	0
_demonstrate_variables_and_types:
call	ncsv
defw	f76
ld	(ix+-2),.low.42
ld	(ix+1+-2),.high.42
psect	data
e77:	deff 3.14
psect	text
ld	de,(e77)
ld	hl,(e77+2)
ld	(ix+-6),e
ld	(ix+1+-6),d
ld	(ix+2+-6),l
ld	(ix+3+-6),h
psect	data
e78:	deff 2.71828
psect	text
ld	de,(e78)
ld	hl,(e78+2)
ld	(ix+-10),e
ld	(ix+1+-10),d
ld	(ix+2+-10),l
ld	(ix+3+-10),h
ld	(ix+-11),67
ld	(ix+-13),.low.1
ld	(ix+1+-13),.high.1
psect	data
e79:	deff 3.14159
psect	text
ld	de,(e79)
ld	hl,(e79+2)
ld	(ix+-17),e
ld	(ix+1+-17),d
ld	(ix+2+-17),l
ld	(ix+3+-17),h
ld	hl,59f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	de,2
ld	hl,0
push	hl
push	de
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
ld	hl,69f
push	hl
call	_printf
ld	hl,2+2+4
add	hl,sp
ld	sp,hl
ld	de,4
ld	hl,0
push	hl
push	de
ld	e,(ix+-6)
ld	d,(ix+1+-6)
ld	l,(ix+2+-6)
ld	h,(ix+3+-6)
push	hl
push	de
ld	hl,79f
push	hl
call	_printf
ld	hl,2+4+4
add	hl,sp
ld	sp,hl
ld	de,4
ld	hl,0
push	hl
push	de
ld	e,(ix+-10)
ld	d,(ix+1+-10)
ld	l,(ix+2+-10)
ld	h,(ix+3+-10)
push	hl
push	de
ld	hl,89f
push	hl
call	_printf
ld	hl,2+4+4
add	hl,sp
ld	sp,hl
ld	de,1
ld	hl,0
push	hl
push	de
ld	a,(ix+-11)
ld	l,a
rla
sbc	a,a
ld	h,a
push	hl
ld	hl,99f
push	hl
call	_printf
ld	hl,2+2+4
add	hl,sp
ld	sp,hl
ld	de,2
ld	hl,0
push	hl
push	de
ld	l,(ix+-13)
ld	h,(ix+1+-13)
push	hl
ld	hl,109f
push	hl
call	_printf
ld	hl,2+2+4
add	hl,sp
ld	sp,hl
ld	e,(ix+-17)
ld	d,(ix+1+-17)
ld	l,(ix+2+-17)
ld	h,(ix+3+-17)
push	hl
push	de
ld	hl,119f
push	hl
call	_printf
ld	hl,2+4
add	hl,sp
ld	sp,hl
l3:
jp	cret
f76	equ	-17
_demonstrate_operators:
call	ncsv
defw	f80
ld	(ix+-2),.low.10
ld	(ix+1+-2),.high.10
ld	(ix+-4),.low.3
ld	(ix+1+-4),.high.3
ld	(ix+-6),.low.10
ld	(ix+1+-6),.high.10
ld	(ix+-8),.low.12
ld	(ix+1+-8),.high.12
ld	hl,129f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	l,(ix+-4)
ld	h,(ix+1+-4)
push	hl
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
ld	hl,139f
push	hl
call	_printf
ld	hl,2+2+2
add	hl,sp
ld	sp,hl
ld	e,(ix+-4)
ld	d,(ix+1+-4)
ld	l,(ix+-2)
ld	h,(ix+1+-2)
add	hl,de
push	hl
ld	hl,149f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	e,(ix+-4)
ld	d,(ix+1+-4)
ld	l,(ix+-2)
ld	h,(ix+1+-2)
global	amod
call	amod
push	hl
ld	hl,159f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	hl,169f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	a,(ix+-6)
and	(ix+-8)
ld	l,a
ld	a,(ix+1+-6)
and	(ix+1+-8)
ld	h,a
push	hl
ld	hl,179f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	a,(ix+-6)
or	(ix+-8)
ld	l,a
ld	a,(ix+1+-6)
or	(ix+1+-8)
ld	h,a
push	hl
ld	hl,189f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	l,(ix+-6)
ld	h,(ix+1+-6)
add	hl,hl
push	hl
ld	hl,199f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	hl,209f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	e,(ix+-2)
ld	d,(ix+1+-2)
ld	l,(ix+-4)
ld	h,(ix+1+-4)
global	wrelop
call	wrelop
jp	alt,20f
jp	21f
20:
ld	a,(ix+-6)
or	(ix+1+-6)
jp	nz,20f
jp	21f
21:jp	11f
20:jp	10f
10:
ld	hl,1
jp	12f
11:
ld	hl,0
12:
ld	(ix+-10),l
ld	(ix+1+-10),h
ld	a,(ix+-10)
or	(ix+1+-10)
jp	nz,10f
jp	11f
11:
ld	hl,239f
jp	12f
10:
ld	hl,229f
12:
push	hl
ld	hl,219f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	e,(ix+-4)
ld	d,(ix+1+-4)
ld	hl,5
global	wrelop
call	wrelop
jp	alt,10f
jp	11f
11:
ld	hl,259f
jp	12f
10:
ld	hl,249f
12:
ld	(ix+-12),l
ld	(ix+1+-12),h
ld	l,(ix+-12)
ld	h,(ix+1+-12)
push	hl
ld	hl,269f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
l4:
jp	cret
f80	equ	-12
_demonstrate_control_flow:
call	ncsv
defw	f81
ld	(ix+-2),.low.5
ld	(ix+1+-2),.high.5
ld	(ix+-3),66
ld	(ix+-7),.low.0
ld	(ix+1+-7),.high.0
ld	hl,279f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	e,(ix+-2)
ld	d,(ix+1+-2)
ld	hl,10
global	wrelop
call	wrelop
jp	age,l6
ld	hl,289f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l7
l6:
ld	de,5
ld	l,(ix+-2)
ld	h,(ix+1+-2)
or	a
sbc	hl,de
jp	nz,l8
ld	hl,299f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
l8:
l7:
ld	a,(ix+-3)
ld	l,a
rla
sbc	a,a
ld	h,a
push	hl
ld	hl,309f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
jp	l10
l11:
ld	hl,319f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l9
l12:
ld	hl,329f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l9
l13:
ld	hl,339f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l9
jp	l9
l10:
ld	a,(ix+-3)
cp	65
jp	z,l11
cp	66
jp	z,l12
jp	l13
l9:
ld	hl,349f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	(ix+-5),.low.0
ld	(ix+1+-5),.high.0
jp	l17
l14:
ld	l,(ix+-5)
ld	h,(ix+1+-5)
push	hl
ld	hl,359f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
l16:
ld	l,(ix+-5)
ld	h,(ix+1+-5)
inc	hl
ld	(ix+-5),l
ld	(ix+1+-5),h
l17:
ld	de,5
ld	l,(ix+-5)
ld	h,(ix+1+-5)
global	wrelop
call	wrelop
jp	alt,l14
l15:
ld	hl,369f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,379f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l18
l19:
ld	l,(ix+-7)
ld	h,(ix+1+-7)
push	hl
ld	hl,389f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	l,(ix+-7)
ld	h,(ix+1+-7)
inc	hl
ld	(ix+-7),l
ld	(ix+1+-7),h
l18:
ld	de,5
ld	l,(ix+-7)
ld	h,(ix+1+-7)
global	wrelop
call	wrelop
jp	alt,l19
l20:
ld	hl,399f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
l5:
jp	cret
f81	equ	-7
_add_one_by_reference:
call	ncsv
defw	f82
ld	l,(ix+6)
ld	h,(ix+1+6)
ld	c,(hl)
inc	hl
ld	b,(hl)
inc	bc
ld	(hl),b
dec	hl
ld	(hl),c
l21:
jp	cret
f82	equ	0
global	_factorial
_factorial:
call	ncsv
defw	f83
ld	e,(ix+6)
ld	d,(ix+1+6)
ld	hl,1
global	wrelop
call	wrelop
jp	alt,l23
ld	de,1
ld	hl,0
jp	l22
l23:
ld	l,(ix+6)
ld	h,(ix+1+6)
dec	hl
push	hl
call	_factorial
exx
ld	hl,2
add	hl,sp
ld	sp,hl
exx
push	hl
push	de
ld	e,(ix+6)
ld	d,(ix+1+6)
ld	a,d
rla
sbc	a,a
ld	l,a
ld	h,a
global	almul
call	almul
jp	l22
l22:
jp	cret
f83	equ	0
_demonstrate_functions_and_point:
call	ncsv
defw	f84
ld	(ix+-2),.low.10
ld	(ix+1+-2),.high.10
ld	(ix+-4),.low.6
ld	(ix+1+-4),.high.6
ld	hl,409f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
push	ix
pop	hl
dec	hl
dec hl
push	hl
call	_add_one_by_reference
ld	hl,2
add	hl,sp
ld	sp,hl
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
ld	hl,419f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	l,(ix+-4)
ld	h,(ix+1+-4)
push	hl
call	_factorial
exx
ld	hl,2
add	hl,sp
ld	sp,hl
exx
push	hl
push	de
ld	l,(ix+-4)
ld	h,(ix+1+-4)
push	hl
ld	hl,429f
push	hl
call	_printf
ld	hl,2+2+4
add	hl,sp
ld	sp,hl
ld	hl,_factorial
ld	(ix+-6),l
ld	(ix+1+-6),h
ld	hl,5
push	hl
ld	l,(ix+-6)
ld	h,(ix+1+-6)
call	indir
exx
ld	hl,2
add	hl,sp
ld	sp,hl
exx
push	hl
push	de
ld	hl,439f
push	hl
call	_printf
ld	hl,2+4
add	hl,sp
ld	sp,hl
l24:
jp	cret
f84	equ	-6
_demonstrate_arrays_and_strings:
call	ncsv
defw	f85
ld	hl,449f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	(ix+-32),.low.0
ld	(ix+1+-32),.high.0
jp	l29
l26:
ld	de,10
ld	l,(ix+-32)
ld	h,(ix+1+-32)
inc	hl
global	amul
call	amul
ex	de,hl
push	de
push	ix
pop	de
ld	l,(ix+-32)
ld	h,(ix+1+-32)
add	hl,hl
add	hl,de
ld	de,-10
add	hl,de
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
l28:
ld	l,(ix+-32)
ld	h,(ix+1+-32)
inc	hl
ld	(ix+-32),l
ld	(ix+1+-32),h
l29:
ld	de,5
ld	l,(ix+-32)
ld	h,(ix+1+-32)
global	wrelop
call	wrelop
jp	alt,l26
l27:
ld	l,(ix+-6)
ld	h,(ix+1+-6)
push	hl
ld	hl,459f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
global	_strcpy
ld	hl,469f
push	hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_strcpy
ld	hl,2+2
add	hl,sp
ld	sp,hl
global	_strcat
ld	hl,479f
push	hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_strcat
ld	hl,2+2
add	hl,sp
ld	sp,hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
ld	hl,489f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
global	_strlen
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_strlen
exx
ld	hl,2
add	hl,sp
ld	sp,hl
exx
ld	e,l
ld	d,h
ld	hl,0
push	hl
push	de
ld	hl,499f
push	hl
call	_printf
ld	hl,2+4
add	hl,sp
ld	sp,hl
l25:
jp	cret
f85	equ	-32
_demonstrate_structs_unions_enum:
call	ncsv
defw	f86
ld	(ix+-53),1
ld	hl,509f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,519f
push	hl
push	ix
pop	de
ld	hl,-52
add	hl,de
push	hl
call	_strcpy
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	(ix+-2),.low.123
ld	(ix+1+-2),.high.123
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
push	ix
pop	de
ld	hl,-52
add	hl,de
push	hl
ld	hl,529f
push	hl
call	_printf
ld	hl,2+2+2
add	hl,sp
ld	sp,hl
ld	a,(ix+-53)
cp	.low.1
jp	nz,l32
ld	l,(ix+-53)
ld	h,0
push	hl
ld	hl,539f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
l32:
l31:
jp	cret
f86	equ	-53
_demonstrate_file_io:
call	ncsv
defw	f87
ld	hl,549f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
global	_fopen
ld	hl,569f
push	hl
ld	hl,559f
push	hl
call	_fopen
exx
ld	hl,2+2
add	hl,sp
ld	sp,hl
exx
ld	l,l
ld	h,h
ld	(ix+-2),l
ld	(ix+1+-2),h
ld	a,(ix+-2)
or	(ix+1+-2)
jp	nz,l34
ld	hl,579f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l33
l34:
global	_fprintf
ld	hl,589f
push	hl
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
call	_fprintf
ld	hl,2+2
add	hl,sp
ld	sp,hl
global	_fclose
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
call	_fclose
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,599f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
ld	hl,619f
push	hl
ld	hl,609f
push	hl
call	_fopen
exx
ld	hl,2+2
add	hl,sp
ld	sp,hl
exx
ld	l,l
ld	h,h
ld	(ix+-2),l
ld	(ix+1+-2),h
ld	a,(ix+-2)
or	(ix+1+-2)
jp	nz,l35
ld	hl,629f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l33
l35:
ld	hl,639f
push	hl
call	_printf
ld	hl,2
add	hl,sp
ld	sp,hl
jp	l36
l37:
push	ix
pop	de
ld	hl,-102
add	hl,de
push	hl
ld	hl,649f
push	hl
call	_printf
ld	hl,2+2
add	hl,sp
ld	sp,hl
l36:
global	_fgets
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
ld	hl,100
push	hl
push	ix
pop	de
ld	hl,-102
add	hl,de
push	hl
call	_fgets
exx
ld	hl,2+2+2
add	hl,sp
ld	sp,hl
exx
ld	l,l
ld	h,h
ld	a,l
or	h
jp	nz,l37
l38:
ld	l,(ix+-2)
ld	h,(ix+1+-2)
push	hl
call	_fclose
ld	hl,2
add	hl,sp
ld	sp,hl
l33:
jp	cret
f87	equ	-102
psect	data
19:
defb	61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
defb	61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
defb	61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
defb	61,10,0
29:
defb	61,61,32,83,104,111,119,99,97,115,101,32,80,111,114,116
defb	97,116,105,108,32,100,97,32,76,105,110,103,117,97,103,101
defb	109,32,67,32,40,65,78,83,73,41,10,0
39:
defb	61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
defb	61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
defb	61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
defb	61,10,0
49:
defb	10,68,101,109,111,110,115,116,114,97,99,97,111,32,99,111
defb	110,99,108,117,105,100,97,32,99,111,109,32,115,117,99,101
defb	115,115,111,46,10,0
59:
defb	10,45,45,45,32,49,46,32,86,97,114,105,97,118,101,105
defb	115,32,101,32,84,105,112,111,115,32,100,101,32,68,97,100
defb	111,115,32,45,45,45,10,0
69:
defb	73,110,116,101,103,101,114,58,32,37,100,32,40,116,97,109
defb	97,110,104,111,58,32,37,108,117,32,98,121,116,101,115,41
defb	10,0
79:
defb	70,108,111,97,116,58,32,32,32,37,102,32,40,116,97,109
defb	97,110,104,111,58,32,37,108,117,32,98,121,116,101,115,41
defb	10,0
89:
defb	68,111,117,98,108,101,58,32,32,37,102,32,40,116,97,109
defb	97,110,104,111,58,32,37,108,117,32,98,121,116,101,115,41
defb	10,0
99:
defb	67,104,97,114,58,32,32,32,32,37,99,32,40,116,97,109
defb	97,110,104,111,58,32,37,108,117,32,98,121,116,101,41,10
defb	0
109:
defb	66,111,111,108,58,32,32,32,32,37,100,32,40,116,97,109
defb	97,110,104,111,58,32,37,108,117,32,98,121,116,101,41,10
defb	0
119:
defb	67,111,110,115,116,97,110,116,101,32,80,73,58,32,37,102
defb	10,0
129:
defb	10,45,45,45,32,50,46,32,79,112,101,114,97,100,111,114
defb	101,115,32,45,45,45,10,0
139:
defb	65,114,105,116,109,101,116,105,99,111,115,58,32,97,61,37
defb	100,44,32,98,61,37,100,10,0
149:
defb	32,32,83,111,109,97,32,40,97,32,43,32,98,41,32,32
defb	32,32,32,32,61,32,37,100,10,0
159:
defb	32,32,82,101,115,116,111,32,40,97,32,37,37,32,98,41
defb	32,32,32,32,32,32,61,32,37,100,10,0
169:
defb	10,66,105,116,45,97,45,98,105,116,58,32,120,61,49,48
defb	32,40,48,120,65,41,44,32,121,61,49,50,32,40,48,120
defb	67,41,10,0
179:
defb	32,32,65,78,68,32,40,120,32,38,32,121,41,32,32,32
defb	32,32,32,32,61,32,37,100,10,0
189:
defb	32,32,79,82,32,32,40,120,32,124,32,121,41,32,32,32
defb	32,32,32,32,61,32,37,100,10,0
199:
defb	32,32,83,104,105,102,116,32,69,115,113,32,40,120,32,60
defb	60,32,49,41,61,32,37,100,10,0
209:
defb	10,76,111,103,105,99,111,115,32,101,32,84,101,114,110,97
defb	114,105,111,58,10,0
219:
defb	32,32,40,97,32,62,32,98,41,32,38,38,32,40,120,32
defb	33,61,32,48,41,32,101,32,37,115,10,0
229:
defb	84,82,85,69,0
239:
defb	70,65,76,83,69,0
249:
defb	98,32,101,32,109,97,105,111,114,32,113,117,101,32,53,0
259:
defb	98,32,110,97,111,32,101,32,109,97,105,111,114,32,113,117
defb	101,32,53,0
269:
defb	32,32,82,101,115,117,108,116,97,100,111,32,100,111,32,116
defb	101,114,110,97,114,105,111,58,32,37,115,10,0
279:
defb	10,45,45,45,32,51,46,32,67,111,110,116,114,111,108,101
defb	32,100,101,32,70,108,117,120,111,32,45,45,45,10,0
289:
defb	105,102,58,32,105,32,101,32,109,97,105,111,114,32,113,117
defb	101,32,49,48,10,0
299:
defb	105,102,58,32,105,32,101,32,101,120,97,116,97,109,101,110
defb	116,101,32,53,10,0
309:
defb	115,119,105,116,99,104,58,32,65,32,110,111,116,97,32,101
defb	32,37,99,46,32,0
319:
defb	69,120,99,101,108,101,110,116,101,33,10,0
329:
defb	77,117,105,116,111,32,66,111,109,33,10,0
339:
defb	80,114,101,99,105,115,97,32,101,115,116,117,100,97,114,32
defb	109,97,105,115,46,10,0
349:
defb	102,111,114,32,108,111,111,112,58,32,0
359:
defb	37,100,32,0
369:
defb	10,0
379:
defb	119,104,105,108,101,32,108,111,111,112,58,32,0
389:
defb	37,100,32,0
399:
defb	10,0
409:
defb	10,45,45,45,32,52,46,32,70,117,110,99,111,101,115,32
defb	101,32,80,111,110,116,101,105,114,111,115,32,45,45,45,10
defb	0
419:
defb	78,117,109,101,114,111,32,97,112,111,115,32,99,104,97,109
defb	97,100,97,32,112,111,114,32,114,101,102,101,114,101,110,99
defb	105,97,58,32,37,100,10,0
429:
defb	70,97,116,111,114,105,97,108,32,100,101,32,37,100,32,101
defb	32,37,108,100,10,0
439:
defb	70,97,116,111,114,105,97,108,32,100,101,32,53,32,40,118
defb	105,97,32,112,111,110,116,101,105,114,111,41,32,101,32,37
defb	108,100,10,0
449:
defb	10,45,45,45,32,53,46,32,65,114,114,97,121,115,32,101
defb	32,83,116,114,105,110,103,115,32,45,45,45,10,0
459:
defb	79,32,116,101,114,99,101,105,114,111,32,101,108,101,109,101
defb	110,116,111,32,100,111,32,97,114,114,97,121,32,101,58,32
defb	37,100,10,0
469:
defb	79,108,97,0
479:
defb	44,32,77,117,110,100,111,33,0
489:
defb	83,116,114,105,110,103,32,102,105,110,97,108,58,32,37,115
defb	10,0
499:
defb	67,111,109,112,114,105,109,101,110,116,111,32,40,115,116,114
defb	108,101,110,41,58,32,37,108,117,10,0
509:
defb	10,45,45,45,32,54,46,32,83,116,114,117,99,116,115,44
defb	32,85,110,105,111,110,115,32,101,32,69,110,117,109,115,32
defb	45,45,45,10,0
519:
defb	76,101,97,110,100,114,111,0
529:
defb	69,109,112,114,101,103,97,100,111,58,32,37,115,32,40,73
defb	68,58,32,37,100,41,10,0
539:
defb	69,110,117,109,58,32,65,32,109,97,113,117,105,110,97,32
defb	101,115,116,97,32,110,111,32,101,115,116,97,100,111,32,82
defb	85,78,78,73,78,71,32,40,37,100,41,46,10,0
549:
defb	10,45,45,45,32,55,46,32,69,110,116,114,97,100,97,32
defb	101,32,83,97,105,100,97,32,100,101,32,65,114,113,117,105
defb	118,111,115,32,40,70,105,108,101,32,73,47,79,41,32,45
defb	45,45,10,0
559:
defb	116,101,115,116,101,46,116,120,116,0
569:
defb	119,0
579:
defb	69,114,114,111,32,97,111,32,97,98,114,105,114,32,111,32
defb	97,114,113,117,105,118,111,32,112,97,114,97,32,101,115,99
defb	114,105,116,97,33,10,0
589:
defb	79,108,97,32,100,111,32,109,117,110,100,111,32,100,111,32
defb	67,33,10,0
599:
defb	65,114,113,117,105,118,111,32,39,116,101,115,116,101,46,116
defb	120,116,39,32,101,115,99,114,105,116,111,32,99,111,109,32
defb	115,117,99,101,115,115,111,46,10,0
609:
defb	116,101,115,116,101,46,116,120,116,0
619:
defb	114,0
629:
defb	69,114,114,111,32,97,111,32,97,98,114,105,114,32,111,32
defb	97,114,113,117,105,118,111,32,112,97,114,97,32,108,101,105
defb	116,117,114,97,33,10,0
639:
defb	76,101,110,100,111,32,100,111,32,97,114,113,117,105,118,111
defb	32,39,116,101,115,116,101,46,116,120,116,39,58,10,0
649:
defb	32,32,62,32,37,115,0
