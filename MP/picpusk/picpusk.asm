$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch		equ	0x0010000 ; for dis
PatchID		equ	0x01003104

ShowIn		equ	1 ; 1.0 - in lock, 1.1 - in unlock
DateFont	equ	ShowIn + 1 ; 1
memDate		equ	DateFont + 2 ; 8
year		equ	memDate
month		equ	memDate + 4
day		equ	memDate + 5

PicX		equ	memDate + 8 ; 2
PicY		equ	PicX + 2
DateX		equ	PicY + 2
DateY		equ	DateX + 2

DateColor	equ	DateY + 2 ; 4
BgColor		equ	DateColor + 4 ; 4

PicPath		equ	BgColor + 4 ; 32

org Patch

Entry:
	push	{r4-r7,lr}
	LoadReg	0, config + 4
	CallLib	GetBuffer
	beq	_ex
	mov	r7, r0
	CallLib	IsUnlocked
	add	r0, #1
	ldrb	r1, [r7,#ShowIn]
	lsr	r1, r0
	bcc	_ex
	CallLib	IsCalling
	cmp	r0, #0
	beq	_checkstby
	ldrb	r1, [r7,#ShowIn]
	lsr	r1, #3
	bcc	_ex
_checkstby:
	GetPoint RamStby
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_do
	ldrb	r1, [r7,#ShowIn]
	lsr	r1, #4
	bcc	_ex
_do:

	ldrh	r0, [r7,#PicX]
        lsr	r1, r0, #15
	bne	_no_pic
	ldrh	r1, [r7,#PicY]
	mov	r2, r7
	add	r2, #PicPath
	CallLib	DrawPicWithCanvas
_no_pic:
	ldrh	r0, [r7,#DateX]
        lsr	r1, r0, #15
	bne	_ex

	add	r0, r7, #memDate
	mov	r1, #0
	CallLib	GetDateTime
	add	r0, r7, #memDate
	CallLib	GetWeek
	mov	r2, r0

	GetPoint LP_MonthsShort
	add	r2, r0 ; weekday name ID
	add	r2, #13

	sub	sp, #72

	ldrb	r3, [r7,#day] ; day
	ldrb	r4, [r7,#month]
	GetPoint LP_MonthsShort
	add	r0, r4
	str	r0, [sp] ; month name ID

;	mov	r0, #16
;	CallBigLib AllocWS
;	mov	r5, r0
	add	r0, sp, #40
	str	r0, [sp,#36]
	sub	r0, #4
	AdrReg	1, DateFormat
        CallBigLib wsprintf

	ldrb	r1, [r7,#DateFont]
	add	r0, sp, #36
	CallBigLib Get_WS_width ; string width
	ldrh	r1, [r7,#DateX]
	ldrh	r2, [r7,#DateY]
	add	r3, r0, r1 ; x2 = x1 + w
	mov	r0, #10 ; h
	add	r0, r2 ; y2
	str	r0, [sp]
	add	r4, sp, #20
	stmia	r4!, {r0-r3}
	mov	r0, #1
	str	r0, [sp,#4]
	CallLib	GetBuildCanvas
	CallLib	DrawCanvas

	ldrb	r1, [r7,#DateFont]
	mov	r2, #1 ; left
	mov	r3, r7
	add	r3, #DateColor
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

;	mov	r0, r5
;	CallBigLib FreeWS

_ex:
	mov	r0, #0
	pop	{r4-r7,pc}

AlignData4
DateFormat	db	"%t %02d %t", 0

Align16
config	dd	Magic, PatchID, config - Entry, 0

end
