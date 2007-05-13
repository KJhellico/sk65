GSM_ALGHORITM_BUFFER                    EQU             0xA851ABE8
off_A84F6208                            EQU             0xA851AA58
RAM_F14                                 EQU             0xA84CAB92
RAM_SPN                                 EQU             0xA84CAB68
RAM_IMSI                                EQU             0xA84CA7C2
RAM_LOCI                                EQU             0xA84CA7CB
RAM_FPLMN                               EQU             0xA84CA806

LAST_SIM_BUF_POINTER                    EQU             0xA84CADD4
LAST_LGP_BUF                            EQU             0xA84AE130
RAM_STBY                                EQU             0xA84CB464
;RAM_NET_ONLINE				EQU		0xA8E3ED50
;RAM_KCGPRS				EQU		0xA8E3998F
;RAM_LOCIGPRS				EQU		0xA8E39998

;PATCH_BASE                              EQU             0xA00D0000 ; основное тело патча

;Menu_Hook                               EQU             0xA045EA24 ; перехват вызова меню
;csa1                                    EQU             0xA09494C4 ; перехват обращения к сим 1
;csa2                                    EQU             0xA0949874 ; перехват обращения к сим 2
;Msg_dispatch                            EQU             0xA0997914 ; перехват ответа

;GetLgp                                  EQU             0xA0BA55D8 ; перехват обращения к ленгпаку
