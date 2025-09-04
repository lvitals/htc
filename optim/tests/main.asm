global	_main
global	ncsv, cret, indir
global	_printf
global	_demonstrate_variables_and_types
global	_demonstrate_operators
global	_demonstrate_control_flow
global	_demonstrate_functions_and_point
global	_demonstrate_arrays_and_strings
global	_demonstrate_structs_unions_enum
global	_demonstrate_file_io
psect	text
_main:
ld	hl,19f
push	hl
call	_printf
ld	hl,29f
ex	(sp),hl
call	_printf
ld	hl,39f
ex	(sp),hl
call	_printf
pop	bc
call	_demonstrate_variables_and_types
call	_demonstrate_operators
call	_demonstrate_control_flow
call	_demonstrate_functions_and_point
call	_demonstrate_arrays_and_strings
call	_demonstrate_structs_unions_enum
call	_demonstrate_file_io
ld	hl,49f
push	hl
call	_printf
pop	bc
ld	hl,0
ret	
psect	data
e77:
deff	3.14
e78:
deff	2.71828
e79:
deff	3.14159
psect	text
_demonstrate_variables_and_types:
call ncsv
defw -17
ld	(ix+-2),42
ld	(ix+-1),0
ld	de,(e77)
ld	hl,(e77+2)
ld	(ix+-6),e
ld	(ix+-5),d
ld	(ix+-4),l
ld	(ix+-3),h
ld	de,(e78)
ld	hl,(e78+2)
ld	(ix+-10),e
ld	(ix+-9),d
ld	(ix+-8),l
ld	(ix+-7),h
ld	(ix+-11),67
ld	(ix+-13),1
ld	(ix+-12),0
ld	de,(e79)
ld	hl,(e79+2)
ld	(ix+-17),e
ld	(ix+-16),d
ld	(ix+-15),l
ld	(ix+-14),h
ld	hl,59f
push	hl
call	_printf
ld	de,2
ld	hl,0
ex	(sp),hl
push	de
ld	l,(ix+-2)
ld	h,(ix+-1)
push	hl
ld	hl,69f
push	hl
call	_printf
pop	bc
pop	bc
pop	bc
ld	de,4
ld	hl,0
ex	(sp),hl
push	de
ld	e,(ix+-6)
ld	d,(ix+-5)
ld	l,(ix+-4)
ld	h,(ix+-3)
push	hl
push	de
ld	hl,79f
push	hl
call	_printf
ld	hl,10
add	hl,sp
ld	sp,hl
ld	de,4
ld	hl,0
push	hl
push	de
ld	e,(ix+-10)
ld	d,(ix+-9)
ld	l,(ix+-8)
ld	h,(ix+-7)
push	hl
push	de
ld	hl,89f
push	hl
call	_printf
ld	hl,10
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
pop	bc
pop	bc
pop	bc
ld	de,2
ld	hl,0
ex	(sp),hl
push	de
ld	l,(ix+-13)
ld	h,(ix+-12)
push	hl
ld	hl,109f
push	hl
call	_printf
pop	bc
pop	bc
pop	bc
ld	e,(ix+-17)
ld	d,(ix+-16)
ld	l,(ix+-15)
ld	h,(ix+-14)
ex	(sp),hl
push	de
ld	hl,119f
push	hl
call	_printf
jp	cret
global	amod
global	wrelop
global	wrelop
_demonstrate_operators:
call ncsv
defw -12
ld	(ix+-2),10
ld	(ix+-1),0
ld	(ix+-4),3
ld	(ix+-3),0
ld	(ix+-6),10
ld	(ix+-5),0
ld	(ix+-8),12
ld	(ix+-7),0
ld	hl,129f
push	hl
call	_printf
ld	l,(ix+-4)
ld	h,(ix+-3)
ex	(sp),hl
ld	l,(ix+-2)
ld	h,(ix+-1)
push	hl
ld	hl,139f
push	hl
call	_printf
pop	bc
pop	bc
ld	e,(ix+-4)
ld	d,(ix+-3)
ld	l,(ix+-2)
ld	h,(ix+-1)
add	hl,de
ex	(sp),hl
ld	hl,149f
push	hl
call	_printf
pop	bc
pop	bc
ld	e,(ix+-4)
ld	d,(ix+-3)
ld	l,(ix+-2)
ld	h,(ix+-1)
call	amod
push	hl
ld	hl,159f
push	hl
call	_printf
pop	bc
ld	hl,169f
ex	(sp),hl
call	_printf
ld	a,(ix+-6)
and	(ix+-8)
ld	l,a
ld	a,(ix+-5)
and	(ix+-7)
ld	h,a
ex	(sp),hl
ld	hl,179f
push	hl
call	_printf
pop	bc
ld	a,(ix+-6)
or	(ix+-8)
ld	l,a
ld	a,(ix+-5)
or	(ix+-7)
ld	h,a
ex	(sp),hl
ld	hl,189f
push	hl
call	_printf
pop	bc
ld	l,(ix+-6)
ld	h,(ix+-5)
add	hl,hl
ex	(sp),hl
ld	hl,199f
push	hl
call	_printf
pop	bc
ld	hl,209f
ex	(sp),hl
call	_printf
pop	bc
ld	e,(ix+-2)
ld	d,(ix+-1)
ld	l,(ix+-4)
ld	h,(ix+-3)
call	wrelop
jp	p,L6
ld	a,(ix+-6)
or	(ix+-5)
jp	z,L6
ld	hl,1
jp	L5
L6:
ld	hl,0
L5:
ld	(ix+-10),l
ld	(ix+-9),h
ld	a,l
or	(ix+-9)
jp	nz,L4
ld	hl,239f
jp	L3
L4:
ld	hl,229f
L3:
push	hl
ld	hl,219f
push	hl
call	_printf
pop	bc
pop	bc
ld	e,(ix+-4)
ld	d,(ix+-3)
ld	hl,5
call	wrelop
jp	m,L2
ld	hl,259f
jp	L1
L2:
ld	hl,249f
L1:
ld	(ix+-12),l
ld	(ix+-11),h
push	hl
ld	hl,269f
push	hl
call	_printf
jp	cret
global	wrelop
global	wrelop
global	wrelop
_demonstrate_control_flow:
call ncsv
defw -7
ld	(ix+-2),5
ld	(ix+-1),0
ld	(ix+-3),66
ld	(ix+-7),0
ld	(ix+-6),0
ld	hl,279f
push	hl
call	_printf
pop	bc
ld	e,(ix+-2)
ld	d,(ix+-1)
ld	hl,10
call	wrelop
jp	p,l6
ld	hl,289f
push	hl
call	_printf
pop	bc
jp	l7
l6:
ld	de,5
ld	l,(ix+-2)
ld	h,(ix+-1)
or	a
sbc	hl,de
jp	nz,l7
ld	hl,299f
push	hl
call	_printf
pop	bc
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
pop	bc
pop	bc
ld	a,(ix+-3)
cp	65
jp	z,l11
cp	66
jp	z,l12
ld	hl,339f
push	hl
call	_printf
pop	bc
l9:
ld	hl,349f
push	hl
call	_printf
pop	bc
ld	(ix+-5),0
ld	(ix+-4),0
jp	l17
l11:
ld	hl,319f
L10:
push	hl
call	_printf
pop	bc
jp	l9
l12:
ld	hl,329f
jp	L10
l14:
ld	l,(ix+-5)
ld	h,(ix+-4)
push	hl
ld	hl,359f
push	hl
call	_printf
pop	bc
pop	bc
ld	l,(ix+-5)
ld	h,(ix+-4)
inc	hl
ld	(ix+-5),l
ld	(ix+-4),h
l17:
ld	de,5
ld	l,(ix+-5)
ld	h,(ix+-4)
call	wrelop
jp	m,l14
ld	hl,369f
push	hl
call	_printf
ld	hl,379f
ex	(sp),hl
call	_printf
pop	bc
jp	l18
l19:
ld	l,(ix+-7)
ld	h,(ix+-6)
push	hl
ld	hl,389f
push	hl
call	_printf
pop	bc
pop	bc
ld	l,(ix+-7)
ld	h,(ix+-6)
inc	hl
ld	(ix+-7),l
ld	(ix+-6),h
l18:
ld	de,5
ld	l,(ix+-7)
ld	h,(ix+-6)
call	wrelop
jp	m,l19
ld	hl,399f
push	hl
call	_printf
jp	cret
_add_one_by_reference:
global csv
call csv
ld	l,(ix+6)
ld	h,(ix+7)
ld	c,(hl)
inc	hl
ld	b,(hl)
inc	bc
ld	(hl),b
dec	hl
ld	(hl),c
jp	cret
global	_factorial
global	wrelop
global	almul
_factorial:
global csv
call csv
ld	e,(ix+6)
ld	d,(ix+7)
ld	hl,1
call	wrelop
jp	m,l23
ld	de,1
ld	hl,0
jp	cret
l23:
ld	l,(ix+6)
ld	h,(ix+7)
dec	hl
push	hl
call	_factorial
pop	bc
push	hl
push	de
ld	e,(ix+6)
ld	d,(ix+7)
ld	a,d
rla
sbc	a,a
ld	l,a
ld	h,a
call	almul
jp	cret
_demonstrate_functions_and_point:
call ncsv
defw -6
ld	(ix+-2),10
ld	(ix+-1),0
ld	(ix+-4),6
ld	(ix+-3),0
ld	hl,409f
push	hl
call	_printf
pop	bc
push	ix
pop	hl
dec	hl
dec	hl
push	hl
call	_add_one_by_reference
ld	l,(ix+-2)
ld	h,(ix+-1)
ex	(sp),hl
ld	hl,419f
push	hl
call	_printf
pop	bc
ld	l,(ix+-4)
ld	h,(ix+-3)
ex	(sp),hl
call	_factorial
ex	(sp),hl
push	de
ld	l,(ix+-4)
ld	h,(ix+-3)
push	hl
ld	hl,429f
push	hl
call	_printf
pop	bc
pop	bc
pop	bc
pop	bc
ld	hl,_factorial
ld	(ix+-6),l
ld	(ix+-5),h
ld	hl,5
push	hl
ld	l,(ix+-6)
ld	h,(ix+-5)
call	indir
ex	(sp),hl
push	de
ld	hl,439f
push	hl
call	_printf
jp	cret
global	amul
global	wrelop
global	_strcpy
global	_strcat
global	_strlen
_demonstrate_arrays_and_strings:
call ncsv
defw -32
ld	hl,449f
push	hl
call	_printf
pop	bc
ld	(ix+-32),0
ld	(ix+-31),0
jp	l29
l26:
ld	de,10
ld	l,(ix+-32)
ld	h,(ix+-31)
inc	hl
call	amul
push	hl
push	ix
pop	de
ld	l,(ix+-32)
ld	h,(ix+-31)
add	hl,hl
add	hl,de
ld	de,-10
add	hl,de
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
ld	l,(ix+-32)
ld	h,(ix+-31)
inc	hl
ld	(ix+-32),l
ld	(ix+-31),h
l29:
ld	de,5
ld	l,(ix+-32)
ld	h,(ix+-31)
call	wrelop
jp	m,l26
ld	l,(ix+-6)
ld	h,(ix+-5)
push	hl
ld	hl,459f
push	hl
call	_printf
pop	bc
ld	hl,469f
ex	(sp),hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_strcpy
pop	bc
ld	hl,479f
ex	(sp),hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_strcat
pop	bc
push	ix
pop	de
ld	hl,-30
add	hl,de
ex	(sp),hl
ld	hl,489f
push	hl
call	_printf
pop	bc
push	ix
pop	de
ld	hl,-30
add	hl,de
ex	(sp),hl
call	_strlen
ex	de,hl
ld	hl,0
ex	(sp),hl
push	de
ld	hl,499f
push	hl
call	_printf
jp	cret
_demonstrate_structs_unions_enum:
call ncsv
defw -53
ld	(ix+-53),1
ld	hl,509f
push	hl
call	_printf
ld	hl,519f
ex	(sp),hl
push	ix
pop	de
ld	hl,-52
add	hl,de
push	hl
call	_strcpy
pop	bc
ld	(ix+-2),123
ld	(ix+-1),0
ld	l,(ix+-2)
ld	h,(ix+-1)
ex	(sp),hl
push	ix
pop	de
ld	hl,-52
add	hl,de
push	hl
ld	hl,529f
push	hl
call	_printf
pop	bc
pop	bc
pop	bc
ld	a,(ix+-53)
cp	1
jp	nz,cret
ld	l,a
ld	h,0
push	hl
ld	hl,539f
push	hl
call	_printf
jp	cret
global	_fopen
global	_fprintf
global	_fclose
global	_fgets
_demonstrate_file_io:
call ncsv
defw -102
ld	hl,549f
push	hl
call	_printf
ld	hl,569f
ex	(sp),hl
ld	hl,559f
push	hl
call	_fopen
pop	bc
pop	bc
ld	(ix+-2),l
ld	(ix+-1),h
ld	a,l
or	(ix+-1)
jp	nz,l34
ld	hl,579f
L11:
push	hl
call	_printf
pop	bc
jp	cret
l34:
ld	hl,589f
push	hl
ld	l,(ix+-2)
ld	h,(ix+-1)
push	hl
call	_fprintf
pop	bc
ld	l,(ix+-2)
ld	h,(ix+-1)
ex	(sp),hl
call	_fclose
ld	hl,599f
ex	(sp),hl
call	_printf
ld	hl,619f
ex	(sp),hl
ld	hl,609f
push	hl
call	_fopen
pop	bc
pop	bc
ld	(ix+-2),l
ld	(ix+-1),h
ld	a,l
or	(ix+-1)
jp	nz,l35
ld	hl,629f
jp	L11
l35:
ld	hl,639f
push	hl
call	_printf
pop	bc
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
pop	bc
pop	bc
l36:
ld	l,(ix+-2)
ld	h,(ix+-1)
push	hl
ld	hl,100
push	hl
push	ix
pop	de
ld	hl,-102
add	hl,de
push	hl
call	_fgets
pop	bc
pop	bc
pop	bc
ld	a,l
or	h
jp	nz,l37
ld	l,(ix+-2)
ld	h,(ix+-1)
push	hl
call	_fclose
jp	cret
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
psect	text
