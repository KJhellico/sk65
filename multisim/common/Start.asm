  RSEG Menu_Hook
  EXTERN ShowMenu
  DCD ShowMenu

  EXTERN SIM_Cmd_Hook
  EXTERN SIM_Rsp_Hook
  EXTERN SaveHTTPProfile
  EXTERN SaveSMSProfile

  EXTERN Msg_dispatch_ret
  EXTERN csa1_ret
  EXTERN csa2_ret
  EXTERN SetHTTPProfile_ret
  
  RSEG CODE:CODE:NOROOT(4)
  THUMB
MsgDispatchRpl:
	push    {r0-r7}
	ldr     r4, =SIM_Rsp_Hook
	blx     r4
	pop     {r0-r7}
	ldrh    r1, [r3,#2]
        subs    r6, #0x28
	movs    r5, #1
	lsls    r2, r1, #24
	lsrs	r2, r2, #24
	ldr	r4, =Msg_dispatch_ret
	ldr	r4, [r4]
	bx	r4

  RSEG CODE:CODE:NOROOT(4)
Cmd_Hook1:
	ldr     r2, [sp,#1Ch]
	ldr     r1, [sp,#20h]
	movs    r0, #0
	str     r4, [sp,#0Ch]
	ldr     r4, =SIM_Cmd_Hook
	blx     r4
	ldr	r6, =csa1_ret
	ldr	r6, [r6]
	bx	r6

  RSEG CODE:CODE:NOROOT(4)
Cmd_Hook2:
	ldr     r2, [sp,#1Ch]
	movs    r0, #0
	str     r4, [sp,#14h]
	ldr     r4, =SIM_Cmd_Hook
	blx     r4
	ldr	r6, =csa2_ret
	ldr	r6, [r6]
	bx	r6

  ARM
SetHTTPProfilel:
	mov     r3, #0
	strh    r0, [r1]
#ifdef X75
	stmea   sp, {r2,r3}
#else
	str     r3, [sp]
	str     r3, [sp,#4]
#endif
	stmfd   sp!, {r0-r7}
	ldr	r4, =SaveHTTPProfile
	blx	r4
	ldmfd   sp!, {r0-r7}
	ldr	r3, =SetHTTPProfile_ret
	ldr	r3, [r3]
	bx	r3
                                
  THUMB
  RSEG csa1:CODE:ROOT(1)
	LDR     R2, =Cmd_Hook1
	BX      R2

  RSEG csa2:CODE:ROOT(1)
	LDR     R2, =Cmd_Hook2
	BX      R2

  RSEG Msg_dispatch:CODE:ROOT(1)
	LDR     r4, =MsgDispatchRpl
	BX      r4

  RSEG SetSMSProfile:CODE:ROOT(1)
	push	{r7,lr}
	ldr	r7, =SaveSMSProfile
	blx	r7
	pop	{r7,pc}

  RSEG SetHTTPProfile:CODE:ROOT(1)
  ARM
	LDR	r3, =SetHTTPProfilel
	BX	r3


  END
