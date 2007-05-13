GSM_ALGHORITM_BUFFER                    EQU             0xA86CF240
off_A84F6208                            EQU             0xA86CF0B0
RAM_F14                                 EQU             0xA868BBF6
RAM_SPN                                 EQU             0xA868BBCC
RAM_IMSI                                EQU             0xA868B826
RAM_LOCI                                EQU             0xA868B82F
RAM_FPLMN                               EQU             0xA868B86A

LAST_SIM_BUF_POINTER                    EQU             0xA868BE38
RAM_STBY                                EQU             0xA868C4B8

Menu_Hook                               EQU             0xA092E978 ; перехват вызова меню
csa1                                    EQU             0xA1407460 ; перехват обращения к сим 1
csa2                                    EQU             0xA1407810 ; перехват обращения к сим 2
Msg_dispatch                            EQU             0xA1407E3C ; перехват ответа
