$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0010000 ; for dis
PatchID         equ     0x0100CD11

ShowIn          equ     1 ; 1.0 - in lock, 1.1 - in unlock
TempAdjust      equ     2
ShowFreeSpaceFor equ    3


/*
RamTable:
0-3 BGColor
4-7 Color
8 fontsize
9 align
10 width
11 height
12-13 start x
14-15 start y
*/

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
        bcs     _do
_ex:
        mov     r0, #0
        pop     {r4-r7,pc}

_do:
Net:
        GetPoint RamNet
        ldrb    r3, [r0, #6]
        mov     r2, #'-'

        ldrh    r1, [r0]
        cmp     r1, #0FFh
        bcc     drawNet
        mov     r2, #'='
drawNet:
        mov     r0, #1
        mov     r1, #NetStr-FormatStrings
        bl      drawfs
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Temperature:
        mov     r0, #1
        mov     r1, #3
        CallLib GetAkku
        mvi     r1, 0xAAA

        sub     r0, r1
        mov     r1, #TempAdjust
        ldrsb   r1, [r7,r1]
        add     r0, r1
        bpl     plus
        neg     r0, r0
plus:
        CallLib HexToDec
        mov     r2, r0
        mov     r3, r1
        mov     r0, #2
        mov     r1, #TempStr-FormatStrings
        bl      drawfs
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Voltage:
        mov     r0, #0
        mov     r1, #9
        CallLib GetAkku
        mov     r1, r0

        mov     r0, #0FAh
        lsl     r0, r0, #2

        CallLib  dwMODdw
        mov      r4, r0
        mov      r0, r1
        CallLib  HexToDec
        mov      r3, r0
        mov      r2, r4

        mov      r0, #3
        mov      r1, #VoltStr-FormatStrings
        bl       drawfs
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Capacity:
        GetPoint RamCap
        ldrh     r2, [r0]
        mov      r0, #4
        bl       ShowPercent
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
GPRS:   
        CallLib  RefreshGPRSTraffic
        CallLib  GetGPRSTrafficPointer
        ldr      r1, [r0]
        mov      r0, #5
        bl       ShowKB
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
NonPermanentRAM:
        CallLib  GetFreeRamAvail
        mov      r1, r0
        mov      r0, #6
        bl       ShowKB
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
FreeSpace:
        ldrb    r0, [r7, #ShowFreeSpaceFor]
        mov     r1, #0
        CallLib GetFreeFlexSpace
        lsr     r4, r0, #8

        mov     r1, #100
        mul     r4, r1
        ldrb    r0, [r7,#ShowFreeSpaceFor]
        CallLib GetTotalFlexSpace
        lsr     r0, #8
        mov     r1, r4
        CallLib dwMODdw
        mov     r2, r0
        mov     r0, #7
        bl      ShowPercent
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CpuLoad:
        CallLib GetCPULoad
        mov     r2, r0
        mov     r0, #8
        bl      ShowPercent
        b       _ex
; --------------------------------------------------------------------
ShowKB: 
        lsr     r2, r1, #10      ;  r0 - id, r1 - size (Byte)
        mov     r1, #GPRSStr-FormatStrings
        b       drawfs
; --------------------------------------------------------------------          
ShowPercent:
        mov     r1, #CapStr-FormatStrings
; --------------------------------------------------------------------
drawfs:
        push       {r4-r5, lr}   ; r0- id, r1- string  offset r2,r3 - parameters
        sub        sp, #72

        AdrReg     4, FormatStrings
        add        r1, r4

        lsl        r0, #4
        add        r5, r0, r7

        add        r0, sp, #40
        str        r0, [sp,#36]
        sub        r0, #4
        CallLib    ws_sprintf

        ldrh       r1, [r5,#12]  ; x
        lsr        r0, r1, #15
        bne        exdrawfs
        ldrh       r2, [r5,#14]  ; y
        ldrb       r3, [r5,#10]  ; width
        add        r3, r1     ; end x
        ldrb       r0, [r5,#11]  ; height
        add        r0, r2     ; end y
        str        r0, [sp] 

        add        r4, sp, #20
        stmia      r4!, {r0-r3}

        mov        r0, #1
        str        r0, [sp,#4]
        CallLib    GetBuildCanvas
        CallLib    DrawCanvas

        ldrb       r1, [r5,#8]  ; fontsize
        ldrb       r2, [r5,#9]  ; option
        add        r3, r5, #4
        mov        r4, r5
        add        r0, sp, #4
        stmia      r0!, {r1-r4}
        
        add        r4, sp, #20
        ldmia      r4!, {r0-r3}

        str        r0, [sp]
        add        r0, sp, #36
        CallBigLib DrawString

exdrawfs:
        add        sp, #72
        pop        {r4-r5, pc}

Align16
FormatStrings:
NetStr:  db "%c%ddb", 0
AlignData4
TempStr:  db "%d,%d°C",0
AlignData4
VoltStr: db "%d,%02dV",0
AlignData4
CapStr: db "%02d%",0
AlignData4
GPRSStr: db "%dKb",0
;AlignData4
;MBStr: db "%d,%2dMb",0

Align16
config  dd      Magic, PatchID, config - Entry, 0

/*

{p=TextInfo ver=1.1 cp=KreN id=0100CD11}
{tp ti}
{0 co BgColor v=0x00000000}
{4 co BorderColor v=0x6400FFF7}
{8 b fontsize r=0..10 v=7}
{9 o Align left=0 center=2 right=4}
{10 sl Width r=0..40 v=30}
{11 sl Height r=0..18 v=11}
{endtp}

{sm `Show in`}
{1.0 cb lock}
{1.1 cb unlock v=1}
{1.2 cb call}
{1.3 cb stby}
{endsm}

{sm Net}
{16 usetp ti}
{28 xy2 Position y=20}
{endsm}

{sm Temperature}
{32 usetp ti}
{44 xy2 Position x=36 y=20}
{2 b TempAdjust r=-50..50 v=15}
{endsm}

{sm Voltage}
{48 usetp ti}
{60 xy2 Position x=75 y=20}
{endsm}

{sm Capacity}
{64 usetp ti}
{76 xy2 Position x=112 y=20}
{endsm}

{sm GPRSMonitor}
{80 usetp ti}
{92 xy2 Position x=89 y=132}
{endsm}

{sm AvailableRAM}
{96 usetp ti}
{108 xy2 Position x=35 y=132}
{endsm}

{sm FreeSpace}
{112 usetp ti}
{124 xy2 Position x=68 y=144}
{3 b ShowFreeSpaceFor: r=0..4}
{endsm}

{sm CpuLoad}
{128 usetp ti}
{140 xy2 Position x=93 y=144}
{endsm}

*/

end
