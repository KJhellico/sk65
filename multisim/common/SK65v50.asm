defadr  MACRO   a,b
        PUBLIC  a
a       EQU     b
        ENDM

  RSEG  CODE:CODE

  PUBLIC csa1_ret
  PUBLIC csa2_ret
  PUBLIC Msg_dispatch_ret
  PUBLIC SetHTTPProfile_ret
  PUBLIC HeaderIcon
  PUBLIC IconIDList

Msg_dispatch_ret               DCD 0xA0997922+1
csa1_ret                       DCD 0xA09494D0+1
csa2_ret                       DCD 0xA0949882+1
SetHTTPProfile_ret             DCD 0xA07B3628

PIC_SIM_insert                 EQU 0x308
PIC_r_sel                      EQU 0x33C
PIC_r_unsel                    EQU 0x33B

HeaderIcon                     DCD PIC_SIM_insert, 0
IconIDList                     DCD PIC_r_sel, PIC_r_unsel

  defadr RAM_F14,              0xA8E39D42
  defadr RAM_SPN,              0xA8E39D18
  defadr RAM_IMSI,             0xA8E39972
  defadr RAM_LOCI,             0xA8E3997B
  defadr RAM_FPLMN,            0xA8E399B6

  defadr LAST_SIM_BUF_POINTER, 0xA8E39F84
  defadr RAM_STBY,             0xA8E3A604

  defadr SIM_Access,           0xA097C8E8
  defadr memcpy,               0xA0D1D4D0
  defadr memset,               0xA0D1D62C
  defadr malloc,               0xA02036DC
  defadr Set_LAI,              0xA094808B
  defadr RegisterInNetwork,    0xA076056F
  defadr SetEEFULLBlock,       0xA09440F0
  defadr GetEEFULLBlock,       0xA0943FAC
  defadr CreateMenu,           0xA06EDF5B
  defadr SetMenuItemIcon,      0xA06F2C41
  defadr GetCurMenuItem,       0xA06F177F

  defadr SIM_Data,             0xA8000380

  defadr Set_HTTP_Profile,     0xA07B3610
  defadr Set_SMS_Profile,      0xA07655C9
  defadr StartTimerProc,       0xA020A9D8
  defadr Current_SMS_Profile,  0xA8E90EB0
  defadr Save_SMS_Profile,     0xA070E7C9

  defadr OpenReadCloseFile,    0xA07F051B
  defadr mfree,                0xA0203744
  defadr IsGPRSConnected,      0xA09FF4A9

  END
