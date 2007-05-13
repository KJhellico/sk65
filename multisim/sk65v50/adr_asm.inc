GSM_ALGHORITM_BUFFER                    EQU             0xA8E7D0D4
off_A84F6208                            EQU             0xA8E7CF44
RAM_F14                                 EQU             0xA8E39D42
RAM_SPN                                 EQU             0xA8E39D18
RAM_IMSI                                EQU             0xA8E39972
RAM_LOCI                                EQU             0xA8E3997B
RAM_FPLMN                               EQU             0xA8E399B6

LAST_SIM_BUF_POINTER                    EQU             0xA8E39F84
LAST_LGP_BUF                            EQU             0xA8E34010
RAM_STBY                                EQU             0xA8E3A604
RAM_NET_ONLINE				EQU		0xA8E3ED50
RAM_KCGPRS				EQU		0xA8E3998F
RAM_LOCIGPRS				EQU		0xA8E39998

;PATCH_BASE                              EQU             0xA00D0000 ; основное тело патча

;Menu_Hook                               EQU             0xA045EA24 ; перехват вызова меню
;csa1                                    EQU             0xA09494C4 ; перехват обращения к сим 1
;csa2                                    EQU             0xA0949874 ; перехват обращения к сим 2
;Msg_dispatch                            EQU             0xA0997914 ; перехват ответа

;GetLgp                                  EQU             0xA0BA55D8 ; перехват обращения к ленгпаку
