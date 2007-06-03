$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch		equ	0x0010000 ; for dis
PatchID		equ	0x01003104

ShowIn		equ	1 ; 1.0 - in lock, 1.1 - in unlock

memDate		equ	ShowIn + 3 ; 8
year		equ	memDate
month		equ	memDate + 4
day		equ	memDate + 5

memTime		equ	memDate + 8 ; 8
hour		equ	memTime
min		equ	memTime + 1

DateX		equ	memTime + 8 ; 2
DateY		equ	DateX + 2 ; 2
DateColor	equ	DateY + 2 ; 4
DateFont	equ	DateColor + 4 ; 1
DateAttr	equ	DateFont + 1 ; 1

TimeX		equ	DateAttr + 3
TimeY		equ	TimeX + 2 ; 2
TimeColor	equ	TimeY + 2 ; 4
TimeFont	equ	TimeColor + 4 ; 1
TimeAttr	equ	TimeFont + 1 ; 1

dX		equ	0
dY		equ	2
dColor		equ	4
dFont		equ	8
dAttr		equ	9

BgColor		equ	TimeAttr + 3 ; 4

PicX		equ	BgColor + 4 ; 2
PicY		equ	PicX + 2 ; 2

PicPath		equ	PicY + 2 ; 32

org Patch

Entry:
	push	{r4-r7,lr}
	LoadReg	0, config + 4
	CallLib	GetBuffer
	beq	_ex1
	mov	r7, r0
	CallLib	IsUnlocked
	add	r0, #1
	ldrb	r1, [r7,#ShowIn]
	lsr	r1, r0
	bcc	_ex1
	CallLib	IsCalling
	cmp	r0, #0
	beq	_checkstby
	ldrb	r1, [r7,#ShowIn]
	lsr	r1, #3
	bcc	_ex1
_checkstby:
	GetPoint RamStby
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_do
	ldrb	r1, [r7,#ShowIn]
	lsr	r1, #4
	bcs	_do
_ex1:
	mov	r0, #0
	pop	{r4-r7,pc}

_do:
	ldrh	r0, [r7,#PicX]
	lsr	r1, r0, #15
	bne	_no_pic
	ldrh	r1, [r7,#PicY]
	mov	r2, r7
	add	r2, #PicPath
	CallLib	DrawPicWithCanvas

_no_pic:
	add	r0, r7, #memDate
	mov	r1, r7
	add	r1, #memTime
	CallLib	GetDateTime

	ldrh	r0, [r7,#DateX]
	lsr	r1, r0, #15
	bne	_no_date

	add	r0, r7, #memDate
	CallLib	GetWeek
	mov	r2, r0

	GetPoint LP_MonthsShort
	add	r2, r0 ; weekday name ID
	add	r2, #13

	ldrb	r3, [r7,#day] ; day
	ldrb	r4, [r7,#month]
	add	r4, r0
	AdrReg	1, DateFormat
	mov	r6, r7
	add	r6, #DateX
	bl	DrawStr

_no_date:
	ldrh	r0, [r7,#TimeX]
        lsr	r1, r0, #15
	bne	_ex

	ldrb	r2, [r7,#hour]
	ldrb	r3, [r7,#min]

	AdrReg	1, TimeFormat
	mov	r6, r7
	add	r6, #TimeX
	bl	DrawStr
_ex:
	mov	r0, #0
	pop	{r4-r7,pc}

DrawStr:
; R1 - sprintf format
; R2-R4 - sprintf args
; R6 - addr of (X, Y, color, font, attr)
	push	{r7,lr}
	sub	sp, #72

	str	r4, [sp]

	add	r0, sp, #40
	str	r0, [sp,#36]
	sub	r0, #4
	CallBigLib wsprintf

	ldrb	r1, [r6,#dFont]
	add	r0, sp, #36
	CallBigLib Get_WS_width ; string width
	ldrh	r1, [r6,#dX]
	ldrh	r2, [r6,#dY]
	add	r3, r0, r1 ; x2 = x1 + w
	add	r3, #2
	ldrb	r0, [r6,#dFont]
	push	{r1-r3}
	CallBigLib GetFontYSIZE
	pop	{r1-r3}
	add	r0, r2 ; y2
	str	r0, [sp]
	add	r4, sp, #20
	stmia	r4!, {r0-r3}
	mov	r0, #1
	str	r0, [sp,#4]
	CallLib	GetBuildCanvas
	CallLib	DrawCanvas

	ldrb	r1, [r6,#dFont]
	ldrb	r2, [r6,#dAttr]
	add	r3, r6,#dColor
	mov	r4, r7
	add	r4, #BgColor
	add	r0, sp, #4
	stmia	r0!, {r1-r4}

	add	r4, sp, #20
	ldmia	r4!, {r0-r3}
	str	r0, [sp]
	add	r0, sp, #36
	CallBigLib DrawString
	add	sp, #72

	pop	{r7,pc}

AlignData4
DateFormat	db	"%t %02d %t", 0
AlignData4
TimeFormat	db	"%02d:%02d", 0

Align16
config	dd	Magic, PatchID, config - Entry, 0

end
