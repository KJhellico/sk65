$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0010000
PatchID         equ     0x0100CCCD

ShowIn          equ     1 ; 1.0 - in lock, 1.1 - in unlock,...
Pos_X           equ     2
Pos_Y           equ     3
Temp1stIcon     equ     4
Range           equ     5
Calibration     equ     6

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
        bcc     _ex
_checkstby:
        GetPoint RamStby
        ldr     r0, [r0]
        cmp     r0, #0
        bne     _do
        ldrb    r1, [r7,#ShowIn]
        lsr     r1, #4
        bcc     _ex

_do:
        mov     r0, #1
        mov     r1, #3
        CallLib GetAkku
        mvi     r1, 0xAAA
        sub     r0, r1
        mov     r5, #Calibration
        ldrsb   r1, [r7,r5]
        add     r4, r0, r1
        mov     r1, #192
        ldrb    r5, [r7,#Range]
        cmp     r5, #0
        beq     _192
        add     r1, #192
        mov     r3, #27
        mov     r5, #5
        b       _2
_192:
        mov     r3, #28
        mov     r5, #4
_2:
        GetPoint Pic_AccuGraph
        mov     r2, r0

        ldrb    r6, [r7,#Temp1stIcon]
        sub     r4, r6
        bpl     _no_min
        add     r2, #13
        b       _show
_no_min:
        cmp     r4, r1
        blt     _no_max
        add     r2, #12
        b       _show
_no_max:
        asr     r1, r4, #31
        lsr     r1, r3
        add     r4, r1
        asr     r4, r5
        add     r2, r4
_show:
        ldrb    r0, [r7,#Pos_X]
        ldrb    r1, [r7,#Pos_Y]
        CallLib DrawPicWithCanvas
_ex:
        mov     r0, #0
        pop     {r4-r7,pc}

Align16
config  dd      Magic, PatchID, config - Entry, 0

/*
{p=AccuTempIndicator ver=2.3 cp=benj9 id=0100CCCD}
{sm `Show in`}
{1.0 cb lock}
{1.1 cb unlock v=1}
{1.2 cb call}
{1.3 cb stby}
{endsm}  
{2 xy Position x=55 y=30}
{sm `Thermometer Setup`}
{4 b `1st icon temperature (0..25.5°C x 10)` v=150}
{5 o `range cold to hot` `19.2°C`=0 `38.4°C`=1}
{6 b `temperature calibration (-3..3°C x 10)` r=-30..30}
{endsm}
*/
end