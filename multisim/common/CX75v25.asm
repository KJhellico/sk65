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

  defadr Msg_dispatch_ret,     0xA0AB2B3A+1
  defadr csa1_ret,             0xA0A891E0+1
  defadr csa2_ret,             0xA0A89592+1
  defadr SetHTTPProfile_ret,   0xA0882F38

PIC_SIM_insert                 EQU 0x34D
PIC_r_sel                      EQU 0x381
PIC_r_unsel                    EQU 0x380

HeaderIcon                     DCD PIC_SIM_insert, 0
IconIDList                     DCD PIC_r_sel, PIC_r_unsel

  defadr RAM_F14,              0xA868BE66
  defadr RAM_SPN,              0xA868BE3C
  defadr RAM_IMSI,             0xA868BA96
  defadr RAM_LOCI,             0xA868BA9F
  defadr RAM_FPLMN,            0xA868BADA

  defadr LAST_SIM_BUF_POINTER, 0xA868C0A8
  defadr RAM_STBY,             0xA868C730

  defadr SIM_Access,           0xA116C314
  defadr memcpy,               0xA16EEC5C
  defadr memset,               0xA16EEDB8
  defadr malloc,               0xA0820F98
  defadr Set_LAI,              0xA12407BB
  defadr RegisterInNetwork,    0xA0BA514F
  defadr SetEEFULLBlock,       0xA11399F4
  defadr GetEEFULLBlock,       0xA11398B0
  defadr CreateMenu,           0xA0C91EDB
  defadr SetMenuItemIcon,      0xA0C96BC1
  defadr GetCurMenuItem,       0xA0C956FF

  defadr SIM_Data,             0xA8000380

  defadr Set_HTTP_Profile,     0xA0CD115C
  defadr Set_SMS_Profile,      0xA0BAA1A9
  defadr StartTimerProc,       0xA0828294
  defadr Current_SMS_Profile,  0xA86EB914
  defadr Save_SMS_Profile,     0xA0B87459

  defadr OpenReadCloseFile,    0xA0C378FF
  defadr mfree,                0xA0821000
  defadr IsGPRSConnected,      0xA0AED489

  END
