$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0010000 ; for dis
PatchID         equ     0x01003103

AdvNet_X        equ     1
AdvNet_Y        equ     2
ShowIn          equ     3
Limits          equ     4 ; (8)

IncR2ifR0lt macro   imm
        ldrb    r3, [r7,#imm]
        cmp     r3, r0
        adc     r2, r1
endm

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
        bcc     _ex ; <
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
        ldrb    r4, [r7,#AdvNet_X]
        ldrb    r5, [r7,#AdvNet_Y]
        mov     r1, #7
        GetPoint RamNet
_nextcell:
        push    {r0}
        ldrb    r0, [r0,#6]
        add     r0, #1
        mov     r2, #0
        IncR2ifR0lt Limits
        IncR2ifR0lt Limits + 1
        IncR2ifR0lt Limits + 2
        IncR2ifR0lt Limits + 3
        IncR2ifR0lt Limits + 4
        IncR2ifR0lt Limits + 5
        IncR2ifR0lt Limits + 6
        IncR2ifR0lt Limits + 7
        mov     r0, #14
        mov     r3, #7
        and     r2, r3
        beq     _showcell
        sub     r0, r2, #1
        ldr     r3, [sp]
        ldrh    r3, [r3]
        cmp     r3, #0FFh
        bcc     _showcell
        add     r0, #7
_showcell:
        mov     r2, r0
        GetPoint Pic_AdvNet
        add     r2, r0
        push    {r1}
        mov     r0, r4
        mov     r1, r5
        CallLib DrawPicWithCanvas
        add     r4, #5 ; X

        pop     {r1}
        pop     {r0}
        add     r0, #12
        sub     r1, #1
        bne     _nextcell
_ex:
        mov     r0, #0
        pop     {r4-r7,pc}

Align16
config  dd      Magic, PatchID, config - Entry, 0

end