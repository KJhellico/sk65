$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0FC5600
Vrezka          equ     0x0848F78
PatchID         equ     0x3102

FillColor       equ     2
FontColor       equ     6
BorderColor     equ     10
PIC_X           equ     14
PIC_Y           equ     15

PIC_X_size      equ     16
PIC_Y_size      equ     17
PIC_0           equ     18 ; 2 bytes

code32
org     Vrezka
        ldr     r1, aEntry
        blx     r1
aEntry  dd      Entry + q1

code16
org     Patch

Entry:
        push    {r0-r7,lr}
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _ex
        mov     r7, r0
        sub     sp, #8
        mov     r4, #0 ; i
        mov     r5, #0 ; j
        GetPoint Pic_Little0
        strh    r0, [r7,#PIC_0]
        CallLib GetImgWidth
        strb    r0, [r7,#PIC_X_size]
        ldrh    r0, [r7,#PIC_0]
        CallLib GetImgHeight
        strb    r0, [r7,#PIC_Y_size]

        CallLib RefreshGPRSTraffic
        CallLib GetGPRSTrafficPointer
        ldr     r3, [r0] ; traffic
        mov     r1, r3
        asr     r3, #10
        asr     r1, #9
        mov     r0, #1
        and     r1, r0
        add     r3, r1 ; traffic
        ldrb    r2, [r7,#PIC_X] ; x
_while1:
        cmp     r3, #0
        beq     _endw1
        mov     r0, r3
        push    {r2}
        CallLib HexToDec ; change r2
        pop     {r2}
        mov     r3, r0 ; traffic/10
        mov     r0, sp
        strb    r1, [r0,r5] ; digits
        ldrb    r0, [r7,#PIC_X_size]
        sub     r2, r0
        add     r4, #1
        cmp     r4, #3
        bne     _1
        cmp     r3, #0
        beq     _1
        add     r5, #1
        sub     r2, r0
        mov     r4, #10
        mov     r0, sp
        strb    r4, [r0,r5]
        mov     r4, #0
_1:
        add     r5, #1
        b       _while1

; r5 = digit cnt
_endw1:
        mov     r0, r7
        add     r0, #BorderColor
        add     r1, r7, #FillColor
        push    {r2} ; x

        push    {r0,r1}
;       push    {r1}
        mov     r0, #1
        push    {r0}
        mov     r0, #4
        push    {r0}
        push    {r0}
        ldrb    r3, [r7,#PIC_Y] ; y
        ldrb    r0, [r7,#PIC_Y_size]
        add     r3, r0
        add     r3, #1
        sub     r0, r2, #2 ; x
        ldrb    r1, [r7,#PIC_Y]
        ldrb    r2, [r7,#PIC_X]
        sub     r2, #1
        CallLib DrawFrame
        add     sp, #20
        pop     {r3} ; x
        sub     r3, #1

_while2:
        cmp     r5, #0
        beq     _endw2
        mov     r0, r3
        mov     r6, sp
        sub     r5, #1
        ldrb    r2, [r6,r5]
        bl      DrawNum
;        sub     r4, #1
;        cmp     r4, #0
;        bne     _2
;        cmp     r5, #0
;        beq     _2
;        ldrb    r0, [r7,#PIC_X_size]
;        add     r3, r0
;        mov     r0, r3
;        mov     r2, #10
;        bl      DrawNum
;        mov     r4, #3
_2:
        ldrb    r0, [r7,#PIC_X_size]
        add     r3, r0
        b       _while2
_endw2:

        add     sp, #8
        pop     {r0-r7}
        pop     {r7}
        add     r7, #32 ; no old code
        bx      r7
_ex:
        pop     {r0-r7}
        pop     {r3} ; stack == old, r3 = lr
        str     r7, [sp, #16] ; old code
        mov     r1, #2 ; old code
        sub     r0, r4, #2 ; old code
        add     r3, #4
        bx      r3

DrawNum:
; in R0 = x, R2 = 0-10
        push    {r3-r7,lr}
        add     r3, r7, #FontColor
        add     r6, r7, #FillColor
        push    {r6} ;[sp] = * BgColor
        ldrb    r1, [r7,#PIC_Y]
        add     r1, #1 ; Y
        ldrh    r6, [r7,#PIC_0]
        add     r2, r6 ; Pic
        CallLib DrawImgBW
        add     sp, #4
        pop     {r3-r7,pc}

Align16
config  dd      Magic, PatchID, 0, 0
/*
{patch=TrafficIndicator id=3102 cp=Sinclair ver=1.3 mem=20}","\
{14 xy Position x=132 y=0}","\
{2 h FillColor ml=4 v=F8FCF864}","\
{10 h BorderColor ml=4 v=00000064}"","\
{6 h FontColor ml=4 v=FF000064}"","\
,00 
*/
end