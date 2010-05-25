$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0010000 ; for dis
PatchID         equ     0x0100CD01

ShowIn          equ     1 ; 1.0 - in lock, 1.1 - in unlock
Cycle           equ     2
;Y_week         equ     3
;Y_date         equ     4

X               equ     3
Y               equ     4

Holidays        equ     5
GapX            equ     6
GapY            equ     7

memDate         equ     8 ; (8)
year            equ     8
month           equ     12
day             equ     13


BgColor         equ     16
WeekColor       equ     20
BorderColor     equ     24
WorkdayColor    equ     28
HolidayColor    equ     32

; Day   1  2  3  4  5  6  7
; X    13 28 43 58 73 88 103

org Patch

Entry:
        push    {r4-r7,lr}
;       mov     r5, r1 ; cycle
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _ex
        mov     r7, r0
        CallLib IsUnlocked
        add     r0, #1
        ldrb    r1, [r7,#ShowIn]
        lsr     r1, r0
        bcc     _ex
        CallLib IsCalling
        cmp     r0, #0
        beq     _checkstby
        ldrb    r1, [r7,#ShowIn]
        lsr     r1, #3
        bcc     _ex
_checkstby:
        GetPoint RamStby
        ldr     r0, [r0]
        cmp     r0, #0
;        bne     _cycle
        bne     _do
        ldrb    r1, [r7,#ShowIn]
        lsr     r1, #4
        bcs     _do
/*
_cycle:
        ldrb    r0, [r7,#Cycle]
        lsr     r0, r5 ; 1..8
        bcs     _do
*/
_ex:
        mov     r0, #0
        pop     {r4-r7,pc}
_do:
        ldrb    r1, [r7,#Y]
        GetPoint Pic_Calendar
        mov     r2, r0
        mov     r3, #WeekColor
        ldrb    r0, [r7,#X]
        add     r0, #1
        ldrb    r5, [r7,#GapX]
        mov     r6, #0
_for:
        bl      Draw
        add     r0, r5
        add     r2, #1
        add     r6, #1
        cmp     r6, #7
        blt     _for
        mov     r0, r7
        add     r0, #memDate
        mov     r1, #0
        CallLib GetDateTime
        mov     r0, r7
        add     r0, #memDate
        CallLib GetWeek
        add     r0, #2
        ldrb    r1, [r7,#day]
_1:
        sub     r1, #7
        cmp     r1, #0
        bgt     _1
        neg     r1, r1
        add     r1, r0
        cmp     r1, #7
        ble     _2
        sub     r1, #7
_2:
        sub     r1, #1 ; (N-1)
        ldrb    r0, [r7,#month]
        sub     r0, #1
        AdrReg  5, Days
        ldrb    r5, [r5,r0] ; days in month
; Leap year checking
        cmp     r0, #1
        bne     _no_leap
        ldr     r0, [r7,#year]
        mov     r6, #03
        and     r0, r6
        cmp     r0, #0
        bne     _no_leap
        add     r5, #1
_no_leap:
;       lsl     r4, r1, #4
;       sub     r4, r1 ; r1*15
;       sub     r0, r4, #2 ; X
        add     r6, r1, #1
        ldrb    r4, [r7,#GapX]
        mul     r1, r4
        ldrb    r4, [r7,#X]
        add     r0, r1, r4 ; X + (N-1)*GapX

        ldrb    r1, [r7,#Y]
        ldrb    r4, [r7,#GapY]
        add     r1, r4
        mov     r4, #1
_beg:
        push    {r5}
        cmp     r6, #8
        blt     _3
        ldrb    r0, [r7,#X]
        ldrb    r5, [r7,#GapY]
        add     r1, r5
        mov     r6, #1
_3:
        ldrb    r5, [r7,#day]
        cmp     r4, r5
        bne     _no_today
        push    {r0-r7}
        sub     r5, r0, #1
        sub     r1, #1
        GetPoint Pic_Calendar
        add     r2, r0, #7
        mov     r0, r5
        mov     r3, #BorderColor
        bl      Draw ; today border
        pop     {r0-r7}
_no_today:
        push    {r0,r1}
        mov     r0, r4
        CallLib HexToDec
        mov     r3, r1 ; 2nd digit
        cmp     r0, #0
        beq     _5
        mov     r2, r0
        GetPoint Pic_Little0
        add     r2, r0 ; 1st digit
        pop     {r0,r1}
        push    {r3}
        mov     r3, #WorkdayColor
        ldrb    r5, [r7,#Holidays]
        lsr     r5, r6
        bcc     $+4
        add     r3, #4
        bl      Draw
        pop     {r3}
        b       _6
_5:
        pop     {r0,r1}
_6:
        mov     r5, r0
        GetPoint Pic_Little0
        add     r2, r0, r3
        push    {r5} ; X
        mov     r0, r2
;        push    {r1}
        push    {r1,r2}
        CallLib GetImgWidth
;        pop     {r1}
        pop     {r1,r2}
        add     r0, r5
;       add     r0, r5, #6
        mov     r3, #WorkdayColor
        ldrb    r5, [r7,#Holidays]
        lsr     r5, r6
        bcc     $+4
        add     r3, #4
        bl      Draw
        pop     {r0} ; X
        ldrb    r5, [r7,#GapX]
        add     r0, r5
        add     r4, #1
        add     r6, #1
        pop     {r5}
        cmp     r4, r5
        ble     _beg
        b       _ex

Draw:
; in: R0 = x, R1= y, R2 = pic num, R3 = font color (24 -> r7+24)
        push    {r0-r4,lr}
        mov     r4, r7
        add     r4, #BgColor
        add     r3, r7
        push    {r4}
        CallLib DrawColorPicWithCanvas
        add     sp, #4
        pop     {r0-r4,pc}

AlignData4
Days    db      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31

Align16
config  dd      Magic, PatchID, config - Entry, 0
/*
{p=Calendar ver=6.0 id=0100CD01}
{1.0 cb lock}
{1.1 cb unlock v=1}
{1.2 call}
{1.3 stby}
---
{sm Cycles}
{2.0 cb 1 v=1}
{2.1 cb 2 v=1}
{2.2 cb 3 v=1}
{2.3 cb 4 v=1}
{2.4 cb 5 v=1}
{2.5 cb 6 v=1}
{2.6 cb 7 v=1}
{2.7 cb 8 v=1}
{endsm}
---
{3 xy Pos}
{6 b DeltaX}
{7 b DeltaY}
{sm Holidays}
{5.0 Mo}
{5.1 Tu}
{5.2 We}
{5.3 Th}
{5.4 Fr}
{5.5 Sa v=1}
{5.6 Su v=1}
{endsm}
{sm Colors}
{16 co Background v=0x00000000}
{20 co Weekdays v=0x64FF0000}
{24 co TodayBorder v=0x6400FFFF}
{28 co Workday v=0x64800000}
{32 co Holiday v=0x64000080}
{endsm}
*/
end
