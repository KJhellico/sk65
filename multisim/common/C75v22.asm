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

  defadr Msg_dispatch_ret,     0xA0A30EF6+1
  defadr csa1_ret,             0xA0A17B58+1
  defadr csa2_ret,             0xA0A17F0A+1
  defadr SetHTTPProfile_ret,   0xA082AF88

PIC_SIM_insert                 EQU 0x34C
PIC_r_sel                      EQU 0x380
PIC_r_unsel                    EQU 0x37F

HeaderIcon                     DCD PIC_SIM_insert, 0
IconIDList                     DCD PIC_r_sel, PIC_r_unsel

  defadr RAM_F14,              0xA84BF65E
  defadr RAM_SPN,              0xA84BF634
  defadr RAM_IMSI,             0xA84BF28E
  defadr RAM_LOCI,             0xA84BF297
  defadr RAM_FPLMN,            0xA84BF2D2

  defadr LAST_SIM_BUF_POINTER, 0xA84BF8A0
  defadr RAM_STBY,             0xA84BFF30

  defadr SIM_Access,           0xA07E7A10
  defadr memcpy,               0xA0E4F4F8
  defadr memset,               0xA0E4F654
  defadr malloc,               0xA0203C24
  defadr Set_LAI,              0xA0A16713
  defadr RegisterInNetwork,    0xA07EF40F
  defadr SetEEFULLBlock,       0xA077ED38
  defadr GetEEFULLBlock,       0xA077EBF4
  defadr CreateMenu,           0xA07775BF
  defadr SetMenuItemIcon,      0xA077C525
  defadr GetCurMenuItem,       0xA077B063

  defadr SIM_Data,             0xA84BF888

  defadr Set_HTTP_Profile,     0xA082AF70
  defadr Set_SMS_Profile,      0xA07F4491
  defadr StartTimerProc,       0xA020AF00
  defadr Current_SMS_Profile,  0xA8514B5C
  defadr Save_SMS_Profile,     0xA04D83D5

  defadr OpenReadCloseFile,    0xA05C400F
  defadr mfree,                0xA0203C8C
  defadr IsGPRSConnected,      0xA0A4F975

  END
