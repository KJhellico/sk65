$INCLUDE (..\macro.inc)
$INCLUDE (..\library.inc)

Patch           equ     0x0FC2100
VrezkaIdle      equ     0x02C93E2
VrezkaSS        equ     0x02CCB26
Loader          equ     0x01FF100
PatchID         equ     0x00001E00

org     Loader
LoadIdle:
        LoadReg 3, aEntryIdle
        bx      r3

Align4
LoadSS:
        LoadReg 3, aEntrySS
        bx      r3

aEntryIdle      dd      EntryIdle + q1
aEntrySS        dd      EntrySS + q1

org VrezkaIdle
        bl      LoadIdle

org VrezkaSS
        bl      LoadSS

org     Patch
EntryIdle:
        push    {lr}
        mov     r3, #2
        ldrsh   r0, [r5,r3]
        bl      Main
        cmp     r0, #0
        bne     _1
        CallLib IsDirectCallActive
        pop     {pc}
_1:
        add     sp, #4
        mov     r0, #1
        CallLib EndUpdateScreen
        mov     r0, r4
        pop     {r4,r5,r7,pc}

Align4
EntrySS:
        mov     r3, #2
        ldrsh   r0, [r4,r3]
        push    {r0,lr}
        bl      Main
        cmp     r0, #0
        bne     _2
        pop     {r0,pc}
_2:
        add     sp, #8
        mov     r0, #1
        CallLib EndUpdateScreen
        mov     r0, r6
        pop     {r4-r6,pc}

Main:
        push    {r0-r7,lr}
        GetPoint FreeRam
        add     r0, #10h
        mov     r7, r0
        LoadReg 0, config + 4
        CallLib GetBuffer
        mov     r6, r0
        pop     {r5} ; key
        beq     _ret0
        CallLib IsUnlocked
        cmp     r0, #0
        beq     _no_ss ; locked
        CallLib IsScreenSaver
        cmp     r0, #1
        bne     _no_ss
        ldrb    r1, [r6,#1]
        lsr     r1, #2
        bcc     _ret0
_no_ss:
        mov     r0, r5
        cmp     r0, #53h
        beq     _4
        cmp     r0, #0
        beq     _6
        cmp     r0, #1
        beq     _8
        cmp     r0, #5
        beq     _10
        cmp     r0, #0Eh
        beq     _12
        cmp     r0, #0Fh
        beq     _14
        cmp     r0, #25h
        beq     _16
        cmp     r0, #26h
        beq     _18
        cmp     r0, #27h
        beq     _20
        cmp     r0, #28h
        beq     _22
        cmp     r0, #29h
        beq     _24
        cmp     r0, #14h
        beq     _26
        cmp     r0, #15h
;        beq     _reshetka
        beq     _resh
        cmp     r0, #16h
;        beq     _num
        beq     _num1
        b       _ret1
_4:
        mov     r4, #4
        b       _do
_6:
        mov     r4, #6
        b       _do
_8:
        mov     r4, #8
        b       _do
_10:
        mov     r4, #10
        b       _do
_12:
        mov     r4, #12
        b       _do
_14:
        mov     r4, #14
        b       _do
_16:
        mov     r4, #16
        b       _do
_18:
        mov     r4, #18
        b       _do
_20:
        mov     r4, #20
        b       _do
_22:
        mov     r4, #22
        b       _do
_24:
        mov     r4, #24
        b       _do
_26:
        mov     r4, #26
_do:
        ldrb    r3, [r6,r4]
        add     r4, #1
        ldrb    r2, [r6,r4]
        mov     r1, #1
        test    1, 2
        beq     _n1
        bl      check_twice
        cmp     r1, #0
        beq     _ret1
_n1:
        mov     r1, #2
        test    1, 2
        beq     _n2
        bl      light
_n2:
        mov     r1, #4
        test    1, 2
        beq     _n3
        bl      unlock
_n3:
        strb    r0, [r7]
        cmp     r3, #0FFh
        beq     _ret1
        cmp     r3, #1
        beq     _speak
        cmp     r3, #2
        beq     _read_sms
        cmp     r3, #0E0h
        bcs     _run_proc
        cmp     r3, #0D0h
        bcs     _run_midlet
        cmp     r3, #90h
        bgt     _set_profile
;        b       _ret1
_ret1:
        bl      timeout
        mov     r0, #1
        pop     {r1-r7,pc}
;_reshetka:
;        b       _resh
;_num:
;        b       _num1
_ret:
        bl      timeout
_ret0:
        mov     r0, #0
        pop     {r1-r7,pc}

_num1:
        ldrb    r1, [r6,#2]
        cmp     r1, #0
        bne     _no0
        strb    r0, [r7]
        b       _ret
_no0:
        cmp     r1, #1
        bne     _no1
        strb    r0, [r7]
        b       _ret1
_no1:
        bl      check_twice
        cmp     r1, #1
        bne     _ret1
        bl      light
        b       _ret1

_resh:
        ldrb    r1, [r6,#1]
        lsr     r1, #1
        bcs     _double
        strb    r0, [r7]
        b       _ret
_double:
        bl      check_twice
        cmp     r1, #0
        beq     _ret1
        bl      light
        bl      unlock
        b       _ret1

_speak:
        CallLib SpellTime
        b       _ret1

_read_sms:
        CallLib HasFlashSMS
        cmp     r0, #1
        beq     _readflash
        CallLib HasNewSMS
        cmp     r0, #1
        bne     _ret1
_readnew:
        CallLib ReadNewSMS
        b       _ret1
_readflash:
        CallLib ReadFlashSMS
        b       _ret1

_set_profile:
        cmp     r3, #98h
        bgt     _ret1
        sub     r3, #91h
        mov     r0, r3
        CallLib SetProfile
        b       _ret1

_run_midlet:
        cmp     r3, #0DFh
        bgt     _ret1
        sub     r3, #0D0h
        mov     r0, #92
        mov     r1, #60
        mul     r1, r3
        add     r1, r0
        add     r0, r1, r6
        CallLib StartMidlet
        b       _ret1

_run_proc:
        cmp     r3, #0EFh
        bgt     _ret1
        sub     r3, #0E0h
        lsl     r3, #2
        add     r3, #28
        ldr     r3, [r6,r3]
        cmp     r3, #0
        beq     _ret1
        push    {r0-r7}
        blx     r3
        pop     {r0-r7}
        b       _ret1

check_twice:
        push    {r2,lr}
        mov     r1, #0
        ldrb    r2, [r7]
        cmp     r0, r2
        strb    r0, [r7]
        bne     _ct_ex
        mov     r1, #1
_ct_ex:
        pop     {r2,pc}

light:
        push    {r0-r7,lr}
        mov     r0, #3
        CallLib TempLightOn
        pop     {r0-r7,pc}

unlock:
        push    {r0-r3,lr}
        CallLib KbdUnlock
;        GetPoint RamIsLocked
;        mov     r3, #0
;        strb    r3, [r0]
        CallLib GetScreenSaverRam
        mov     r3, #10h
        strb    r3, [r0]
        pop     {r0-r3,pc}

timeout:
        push    {r0-r7,lr}
        add     r0, r7, #4
        AdrReg  2, clear
        add     r2, #1
        ldrb    r1, [r6,#3]
        CallLib CallAfterTimer
        pop     {r0-r7,pc}

Align4
clear:
        push    {r0,r1,lr}
        GetPoint FreeRam
        add     r0, #10h
        mov     r1, #0FFh
        strb    r1, [r0]
        pop     {r0,r1,pc}

Align16
config  dd      Magic, PatchID, 0, 0

end

/*
"{p RSFWKL id=1E00 cp=1nvisible ver=11.0}","\
{info `The phone runs some functions while keyboard is locked.\n","\
Functions: 01 - Speak time, 02 - read SMS, 91-98 - set profile,\n","\
D0-DF - run midlet, E0-EF - run function, FF - no action.","\
Options: 01 - double press, 02 - temp light, 04 - kbd unlock.`}","\
{1.0 cb `Unlock by # double press` v=1}","\
{1.1 cb `Work in screensaver`}","\
{2 o Numbers `Show locked screen`=0 `Do not show`=1 `Light on by double press`=2 v=2}","\
{3 b `Delay for double-click` v=200}","\
{of +4}","\
{sm `Key Bindings`}","\
{sm `Left SoftKey`}","\
{0 h Function ml=1 v=02}","\
{1 h Option ml=1 v=06}","\
{endsm}","\
{sm `Right SoftKey`}","\
{2 h Function ml=1 v=FF}","\
{3 h Option ml=1 v=07}","\
{endsm}","\
{sm `Red Button`}","\
{4 h Function ml=1 v=FF}","\
{5 h Option ml=1 v=02}","\
{endsm}","\
{sm `Green Button`}","\
{6 h Function ml=1 v=02}","\
{7 h Option ml=1 v=02}","\
{endsm}","\
{sm `Volume Down`}","\
{8 h Function ml=1 v=E0}","\
{9 h Option ml=1 v=07}","\
{endsm}","\
{sm `Volume Up`}","\
{10 h Function ml=1 v=01}","\
{11 h Option ml=1 v=00}","\
{endsm}","\
{sm `Joy Down`}","\
{12 h Function ml=1 v=92}","\
{13 h Option ml=1 v=03}","\
{endsm}","\
{sm `Joy Up`}","\
{14 h Function ml=1 v=91}","\
{15 h Option ml=1 v=03}","\
{endsm}","\
{sm `Joy Right`}","\
{16 h Function ml=1 v=D0}","\
{17 h Option ml=1 v=07}","\
{endsm}","\
{sm `Joy Left`}","\
{18 h Function ml=1 v=D1}","\
{19 h Option ml=1 v=07}","\
{endsm}","\
{sm `Joy Press`}","\
{20 h Function ml=1 v=E1}","\
{21 h Option ml=1 v=07}","\
{endsm}","\
{sm Asterisk}","\
{22 h Function ml=1 v=E2}","\
{23 h Option ml=1 v=07}","\
{endsm}","\
{endsm}","\
{sm Functions}","\
{24 a 0 v=A0318941}","\
{28 a 1 v=A031894B}","\
{32 a 2 v=A0319119}","\
{36 a 3 v=A0319363}","\
{40 a 4 v=A0319363}","\
{44 a 5 v=A0319363}","\
{48 a 6 v=A0319363}","\
{52 a 7 v=A0319363}","\
{56 a 8 v=A0319363}","\
{60 a 9 v=A0319363}","\
{64 a A v=A0319363}","\
{68 a B v=A0319363}","\
{72 a C v=A0319363}","\
{76 a D v=A0319363}","\
{80 a E v=A0319363}","\
{84 a F v=A0319363}","\
{endsm}","\
{sm Midlets}","\
{88 sf 0 mask=`*.jar` ml=59}","\
{148 sf 1 mask=`*.jar` ml=59}","\
{208 sf 2 mask=`*.jar` ml=59}","\
{268 sf 3 mask=`*.jar` ml=59}","\
{328 sf 4 mask=`*.jar` ml=59}","\
{388 sf 5 mask=`*.jar` ml=59}","\
{448 sf 6 mask=`*.jar` ml=59}","\
{508 sf 7 mask=`*.jar` ml=59}","\
{568 sf 8 mask=`*.jar` ml=59}","\
{628 sf 9 mask=`*.jar` ml=59}","\
{688 sf A mask=`*.jar` ml=59}","\
{748 sf B mask=`*.jar` ml=59}","\
{808 sf C mask=`*.jar` ml=59}","\
{868 sf D mask=`*.jar` ml=59}","\
{928 sf E mask=`*.jar` ml=59}","\
{988 sf F mask=`*.jar` ml=59}","\
{endsm}",00
#pragma disable old_equal_ff

*/