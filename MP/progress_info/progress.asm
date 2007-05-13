$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0FC7D00
Vrezka1         equ     0x045A9B4
Vrezka2         equ     0x04654DC
Vrezka3         equ     0x099E768
Vrezka4         equ     0x099E820

PatchID         equ     0x1EFF

Flag            equ     1 ; (1)
KBInfoString    equ     4
PInfoString     equ     20
KBString_Pos    equ     36
PString_Pos     equ     38
TextColor       equ     40
BgColor         equ     44
Buf1            equ     48
Buf2            equ     52

org Vrezka1
        dd      Proc4 + q1
        dd      Proc3 + q1

org Vrezka2
        dd      Proc2 + q1
        dd      Proc1 + q1

org Vrezka3
        CallReg 7, aEntry1
aEntry1 dd      Entry1 + q1
        nop
        nop

org Vrezka4
        CallReg 7, aEntry2
aEntry2 dd      Entry2 + q1
        nop

org Patch

Proc1:
        push    {r0-r7,lr}
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _1_ex
        mov     r1, #'R'
        strb    r1, [r0,#Flag]
_1_ex:
        pop     {r0-r7,pc}

Align4
Proc2:
        push    {r0-r7,lr}
        cmp     r1, #3
        bne     _2_ex
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _2_ex
        mov     r1, #0
        strb    r1, [r0,#Flag]
_2_ex:
        pop     {r0-r7,pc}

Align4
Proc3:
        push    {r0-r7,lr}
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _3_ex
        mov     r1, #'S'
        strb    r1, [r0,#Flag]
_3_ex:
        pop     {r0-r7,pc}
        
Align4
Proc4:
        push    {r0-r7,lr}
        cmp     r1, #3
        bne     _4_ex
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _4_ex
        mov     r1, #0
        strb    r1, [r0,#Flag]
        LoadReg 1, aRam
        str     r0, [r1,#8]
_4_ex:
        pop     {r0-r7,pc}

AlignData4
aRam    dd      0xA8E7F4EC

Entry1:
        push    {r2-r7,lr}
        ldr     r1, [r4,#30h] ; \
        lsr     r0, #16       ;
        mul     r1, r0        ;  old
        ldr     r0, [r4,#2Ch] ;
        CallLib dwMODdw       ; /
        push    {r0,r1}
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _E1_ex
        mov     r7, r0 ; buffer
        ldrb    r3, [r7,#Flag]
        ldr     r5, [r4,#30h]
        ldr     r6, [r4,#2Ch]
        cmp     r3, #0
        beq     _1
        cmp     r3, #'R'
        beq     _2
        cmp     r3, #'S'
        bne     _1
        lsr     r5, #9
        lsr     r6, #9
_2:
        lsr     r5, #1
        lsr     r6, #1
_1:
        mov     r1, #Buf1
        add     r0, r1
        str     r5, [r0]
        str     r6, [r0,#4] ; Buf2
        cmp     r3, #0
        beq     _E1_ex
        sub     sp, #48
        mov     r0, #16
        CallBigLib AllocWS
        mov     r4, r0
        add     r1, r7, #KBInfoString
        mov     r2, r5
        mov     r3, r6
        CallBigLib wsprintf
        mov     r3, #90 ; w
        str     r3, [sp]
        mov     r3, #20 ; h
        str     r3, [sp,#4]
        mov     r3, #2
        str     r3, [sp,#8] ; align
        mov     r0, r7
        add     r0, #TextColor
        str     r0, [sp,#12] ; text color
        mov     r0, r7
        add     r0, #BgColor
        str     r0, [sp,#16] ; bg color
        mov     r3, #0
        str     r3, [sp,#20] ; inversion
        ldr     r0, [r4] ; wstring
        mov     r3, r7
        add     r3, #KBString_Pos
        ldrb    r1, [r3] ; x
        ldrb    r2, [r3,#1] ; y
        mov     r3, #8 ; font
        CallLib DrawText
        mov     r0, r4
        CallBigLib FreeWS
        add     sp, #48
_E1_ex:
        pop     {r0-r7}
        pop	{r7}
        add	r7, #4
        bx	r7

Align4
Entry2:
        mov     r0, #12      ; \
        ldrsh   r0, [r3,r0]  ;  old
        mov     r3, r4       ; 
        mov     r5, r1
        CallLib DrawRect     ; /
        LoadReg 0, config + 4
        CallLib GetBuffer
        beq     _E2_ex
        mov     r7, r0
        push    {r4,r5}
	add	r0, #Buf1
        ldr     r1, [r0]
        ldr     r0, [r0,#4]
        mov     r3, #100
        mul     r1, r3
        CallLib dwMODdw
        mov     r5, r0
        sub     sp, #48
        mov     r0, #16
        CallBigLib AllocWS
        mov     r6, r0
        mov     r1, r7
        add     r1, #PInfoString
        mov     r2, r5
        CallBigLib wsprintf
        mov     r3, #30
        str     r3, [sp]
        mov     r3, #10
        str     r3, [sp,#4]
        mov     r3, #2
        str     r3, [sp,#8]
        mov     r0, #0
        str     r0, [sp,#16]
        mov     r3, #0
        str     r3, [sp,#20]
        mov     r0, r7
        add     r0, #TextColor
        str     r0, [sp,#12]
        mov     r0, r7
        add     r0, #PString_Pos
        ldrb    r1, [r0]
        ldr     r4, [sp,#48+0] ; r4
        ldr     r5, [sp,#48+4] ; r5
        sub     r0, r4, r5
        add     r2, r5, #1
        cmp     r0, #9
        blt     _4
        mov     r3, #8
        b       _5
_4:
        mov     r3, #6
        cmp     r0, #6
        bge     _5
        sub     r2, #1
_5:
        ldr     r0, [r6]
        CallLib DrawText
        mov     r0, r6
        CallBigLib FreeWS
        add     sp, #48
        pop     {r4,r5}
_E2_ex:
        add     sp, #20 ; old
        pop     {r4-r7,pc} ; old

Align16
config  dd      Magic, PatchID, 0, 0

end