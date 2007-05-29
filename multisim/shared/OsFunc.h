#ifndef __FUNC_H__
#define __FUNC_H__

#include "siemens.h"
//#include "eeprom.h"

//typedef struct SIM_EEPROM_BLOCK;
/* ----------  ---------- */
typedef void P_MEMCPY(void *pDst, void *pSrc, int nLen);
typedef void P_MEMSET(void *s, int c, int n);
typedef void P_SIM_ACCESS(int what, int cla, int ins,
                               int p1, int p2, int op,
                               int SendLen, unsigned char *SendBuf,
                               int RecvLen, unsigned char *RecvBuf);
typedef void P_SET_LAI(void);
typedef void P_SEARCH(void);
typedef void P_STARTTIMERPROC(void *htimer, long ms, void ptr());
typedef void *P_MALLOC(unsigned int size);
typedef void P_SET_HTTP_PROFILE(unsigned char Profile);
typedef void P_SET_SMS_PROFILE(unsigned char SMS_Profile);
//typedef void P_SWITCH_GPRS(int, unsigned char Mode);
typedef void P_SAVE_SMS_PROFILE(int block);
typedef int P_OPENREADCLOSEFILE(char *name, char **buf);
typedef void P_MFREE(void *);

/* ----------  ---------- */
P_SIM_ACCESS        *const SIM_Access = (P_SIM_ACCESS*) SIM_Access_Function_ADR;
extern "C" P_MEMCPY *const LIB_Memcpy = (P_MEMCPY*) memcpy_ADR;
P_MEMSET            *const LIB_Memset = (P_MEMSET*) memset_ADR;
P_SET_LAI           *const Set_LAI    = (P_SET_LAI*) Set_LAI_ADR;
P_SEARCH            *const Search    = (P_SEARCH*) Net_Search_ADR;
P_MALLOC            *const malloc     = (P_MALLOC*) malloc_ADR;
P_SET_SMS_PROFILE   *const Set_SMS_Profile = (P_SET_SMS_PROFILE*) Set_SMS_Profile_ADR;
P_STARTTIMERPROC    *const StartTimerProc = (P_STARTTIMERPROC*) StartTimerProc_ADR;
P_SET_HTTP_PROFILE  *const Set_HTTP_Profile = (P_SET_HTTP_PROFILE*) Set_HTTP_Profile_ADR;
// P_SWITCH_GPRS      *const SwitchGPRS = (P_SWITCH_GPRS *) SwitchGPRS_ADR;
P_SAVE_SMS_PROFILE  *const Save_SMS_Profile = (P_SAVE_SMS_PROFILE*) Save_SMS_Profile_ADR;
extern "C" P_OPENREADCLOSEFILE *const OpenReadCloseFile = (P_OPENREADCLOSEFILE *) OpenReadCloseFile_ADR;
extern "C" P_MFREE  *const mfree = (P_MFREE *) mfree_ADR;

typedef void P_GetEEFULLBlock(int block, void *buf, int offset, int size);
typedef void P_SetEEFULLBlock(int block, void *buf, int offset, int size);

extern "C" P_GetEEFULLBlock	*const GetEEFULLBlock = (P_GetEEFULLBlock*) GetEEFULLBlock_ADR;
extern "C" P_SetEEFULLBlock     *const SetEEFULLBlock = (P_SetEEFULLBlock*) SetEEFULLBlock_ADR;

#endif
