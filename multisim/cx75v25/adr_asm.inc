GSM_ALGHORITM_BUFFER                    EQU             0xA851AC90
off_A84F6208                            EQU             0xA851AB00
RAM_F14                                 EQU             0xA84CAC3A
RAM_SPN                                 EQU             0xA84CAC10
RAM_IMSI                                EQU             0xA84CA86A
RAM_LOCI                                EQU             0xA84CA873
RAM_FPLMN                               EQU             0xA84CA8AE

LAST_SIM_BUF_POINTER                    EQU             0xA84CAE7C
LAST_LGP_BUF                            EQU             0xA84AE130
RAM_STBY                                EQU             0xA84CB50C
;RAM_NET_ONLINE				EQU		0xA8E3ED50
;RAM_KCGPRS				EQU		0xA8E3998F
;RAM_LOCIGPRS				EQU		0xA8E39998

;PATCH_BASE                              EQU             0xA00D0000 ; основное тело патча

;Menu_Hook                               EQU             0xA045EA24 ; перехват вызова меню
;csa1                                    EQU             0xA09494C4 ; перехват обращения к сим 1
;csa2                                    EQU             0xA0949874 ; перехват обращения к сим 2
;Msg_dispatch                            EQU             0xA0997914 ; перехват ответа

;GetLgp                                  EQU             0xA0BA55D8 ; перехват обращения к ленгпаку
