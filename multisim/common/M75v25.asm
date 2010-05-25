defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

  RSEG	CODE:CODE

  PUBLIC csa1_ret
  PUBLIC csa2_ret
  PUBLIC Msg_dispatch_ret
  PUBLIC SetHTTPProfile_ret
  PUBLIC HeaderIcon
  PUBLIC IconIDList

  defadr Msg_dispatch_ret,     0xA0AB1CF6+1
  defadr csa1_ret,             0xA0A87DF0+1
  defadr csa2_ret,             0xA0A881A2+1
  defadr SetHTTPProfile_ret,   0xA0881E18

PIC_SIM_insert                 EQU 0x33B
PIC_r_sel                      EQU 0x36F
PIC_r_unsel                    EQU 0x36E

HeaderIcon                     DCD PIC_SIM_insert, 0
IconIDList                     DCD PIC_r_sel, PIC_r_unsel

  defadr RAM_F14,              0xA84CAB92
  defadr RAM_SPN,              0xA84CAB68
  defadr RAM_IMSI,             0xA84CA7C2
  defadr RAM_LOCI,             0xA84CA7CB
  defadr RAM_FPLMN,            0xA84CA806

  defadr LAST_SIM_BUF_POINTER, 0xA84CADD4
  defadr RAM_STBY,             0xA84CB464

  defadr SIM_Access,           0xA0A961EC
  defadr memcpy,               0xA0EF2D20
  defadr memset,               0xA0EF2E7C
  defadr malloc,               0xA0203C24
  defadr Set_LAI,              0xA0A869AB
  defadr RegisterInNetwork,    0xA0836E93
  defadr SetEEFULLBlock,       0xA07CA044
  defadr GetEEFULLBlock,       0xA07C9F00
  defadr CreateMenu,           0xA07C283B
  defadr SetMenuItemIcon,      0xA07C77A1
  defadr GetCurMenuItem,       0xA07C62DF

  defadr SIM_Data,             0xA8000380

  defadr Set_HTTP_Profile,     0xA0881E00
  defadr Set_SMS_Profile,      0xA083BF15
  defadr StartTimerProc,       0xA020AF00
  defadr Current_SMS_Profile,  0xA852F94C
  defadr Save_SMS_Profile,     0xA0A3274C

  defadr OpenReadCloseFile,    0xA08F90CF
  defadr mfree,                0xA0203C8C
  defadr IsGPRSConnected,      0xA0AECB35

  END
