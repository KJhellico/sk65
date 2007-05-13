$nolist
;Macros for KEIL
;(c) avkiev

$SET (IS_SWI = 1)

$ARM9E
$genonly
AREA    STARTUPCODE, CODE, at 10000h
;AREA   STARTUPCODE, CODE, at A000000h
code16

q0  equ 0xA0000000
q1  equ 0xA0000001
q8  equ 0xA8000000

Lib         equ     0x0FD4000 ; x65 test

Patches     equ     0xA0FC1000 - q0
Magic       equ     0xB1C2D3E4

;***********************************************************
DoAlign   macro   al
              al2 set -al
              org ($+al-1) & al2
endm
;***********************************************************
Align4  macro
              $if (($ & 3) != 0)
                nop
              $endif
endm
;***********************************************************
AlignData4  macro
        rept 3
                $if (($ & 3) != 0)
                db 0xFF
                $endif
        endm
endm
;***********************************************************
Align16  macro
              org ($+15)&0xFFFFFFF0
endm
;***********************************************************
LoadReg macro   reg, ad
              dw    0x4800 + (reg << 8) + (ad-$-2)/4
endm
;***********************************************************
AdrReg  macro   reg, ad
              dw    0xA000 + (reg << 8) + (ad-$-2)/4
endm
;***********************************************************
CallReg macro   reg, ad
              LoadReg reg, ad
              blx     R&reg  
endm
;***********************************************************
mvi  macro   reg, yy
              mov     reg, #(yy >> 8)
              lsl     reg, #8
              add         reg, #(yy & 0xFF)
endm
;***********************************************************
test macro reg1, reg2
        db      (reg2 << 3) | (reg1)
        db      0x42
endm 
;***********************************************************
CallARM macro   addr
              a     set addr - q0 - $ - 2
              dw    0xF000 + ((a>>12)&0x7FF)
              dw    0xE800 + ((a & 0xFFC)>>1)
endm
;***********************************************************
CallThumb macro   addr
              a     set ((addr - q0 - $ - 8) >> 2) & 0xFFFFFF
              dw    a & 0xFFFF
              dw    0xFA00 + (a>>16) + ((addr & 2) << 7)
endm
;***********************************************************
SwitchToThumb macro
    code32
            add     r12, PC, #1
            bx      r12
    code16
endm
;***********************************************************
SwitchToARM macro
    code16
    Align4
            mov     r3, PC
            bx      r3
    code32
endm
;***********************************************************
CallLib     macro   N
            swi     N
endm
;***********************************************************
GetPoint    macro   N
            swi     199
            dw      0x8000 + N
endm
;***********************************************************
CallBigLib  macro   N
            swi     199
            dw      N
endm

$list