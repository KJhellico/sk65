$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0010000 ; for dis
PatchID         equ     0x0100AB02

ShowIn          equ     1 ; 1.0 - in lock, 1.1 - in unlock
T12_X           equ     2
T12_Y           equ     3
Gap12           equ     4
T24_X           equ     5
T24_Y           equ     6
Gap24           equ     7

memTime         equ     8 ; 8 bytes
hour            equ     8
min             equ     9
sec             equ     10

BgColor         equ     16
FontColor       equ     20

org Patch
Entry:
        push    {r4-r7,lr}
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
        b       _do-2
_checkstby:
        GetPoint RamStby
        ldr     r0, [r0]
        cmp     r0, #0
        bne     _do
        ldrb    r1, [r7,#ShowIn]
        lsr     r1, #4
        bcc     _ex
_do:
        mov     r0, #0
        mov     r1, r7
        add     r1, #memTime
        CallLib GetDateTime
        CallLib GetTimeFormat
        mov     r6, r0
        ldrb    r0, [r7,#hour]
        cmp     r6, #1
        beq     _t12
        ldrb    r5, [r7,#T24_Y]
        ldrb    r4, [r7,#T24_X]
        ldrb    r3, [r7,#Gap24]
        b       _2
_t12:
        ldrb    r5, [r7,#T12_Y]
        ldrb    r4, [r7,#T12_X]
        ldrb    r3, [r7,#Gap12]
        cmp     r0, #0
        bne     _1
        mov     r0, #12
        b       _2
_1:
        cmp     r0, #12
        blt     _2
_3:
        mov     r6, #2 ; PM
        cmp     r0, #12
        beq     _2
        sub     r0, #12
_2:
        bl      Draw2Dig

        push    {r4}
        mov     r0, #11
        bl      DrawPic ; ":"
        pop     {r1}
        push    {r4}
        ldrb    r0, [r7,#ShowIn]
        lsr     r0, #5
        bcc     _no_sec
        push    {r5-r6}
        sub     r4, r1, #4
        add     r5, #28
        ldrb    r0, [r7,#sec]
        mov     r6, #3
        bl      Draw2Dig
        pop     {r5-r6}
_no_sec:
        pop     {r4}

        ldrb    r0, [r7,#min]
        bl      Draw2Dig
        cmp     r6, #0
        beq     _ex ; t24
        mov     r0, #10 ; "AM"
        cmp     r6, #1
        beq     $+4
        add     r0, #2 ; "PM"
        bl      DrawPic

_ex:
        mov     r0, #0
        pop     {r4-r7,pc}

; in: R0 = number
Draw2Dig:
        push    {r0,lr}
        CallLib HexToDec
        bl      DrawPic
        b       DrawPic+2

; in: R0 = digit, 
DrawPic:
        push    {r1,lr}

        push    {r3} ; save gap
        mov     r2, r0
        GetPoint Pic_Big0
        cmp     r6, #3
        bne     _big
        GetPoint Pic_Little0
_big:
        add     r2, r0 ; pic
        push    {r2}
;        mov     r0, r4 ; X
;        mov     r1, r5 ; Y
;        mov     r3, r7
        push    {r4,r5,r7}
        pop     {r0,r1,r3}
        add     r3, #BgColor
        push    {r3}
        add     r3, #4 ; FontColor
        CallLib DrawColorPicWithCanvas
        add     sp, #4
        
        pop     {r0} ; pic
        CallLib GetImgWidth
        pop     {r3} ; gap
        add     r4, r0
        add     r4, r3
        cmp     r6, #3
        bne     _big1
        sub     r4, r3
        add     r4, #2
_big1:
        pop     {r0,pc}

Align16
config  dd      Magic, PatchID, config - Entry, 0
/*
{p=`Big Digital Clock` ver=2.0 id=0100AB02}","\
{sm `Show in`}
{1.0 cb lock}
{1.1 cb unlock v=1}
{1.2 cb call}
{1.3 cb stby}
{endsm}
{2 xy T12 y=73}\
{4 sl Gap12 r=0..6 v=3}","\
{5 xy T24 y=73}\
{7 sl Gap24 r=0..6 v=6}","\
{1.4 cb `Show seconds` v=1}
{16 h BColor ml=4 v=00000000}","\
{20 h FColor ml=4 v=00000064}","\
*/
end