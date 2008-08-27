#ifndef __FUNC_H__
#define __FUNC_H__
#include "siemens.h"

extern void SIM_Access(int what, int cla, int ins,
                       int p1, int p2, int op,
                       int SendLen, unsigned char *SendBuf,
                       int RecvLen, unsigned char *RecvBuf);

extern void memcpy(void *pDst, void *pSrc, int nLen);
extern void memset(void *s, int c, int n);

extern void CreateMenu(unsigned long, const MENU_DESC*, const HEADER_DESC*, unsigned long);
extern void SetMenuItemIcon(void *gui,int item_n,int icon_n);
extern void CloseMenu(unsigned long);
extern int GetCurMenuItem(void *gui);

extern void Set_LAI(void);
//typedef void P_SEARCH(void);
extern void *malloc(unsigned int size);
extern void mfree(void *);
extern void StartTimerProc(void *htimer, long ms, void ptr());
extern void Set_HTTP_Profile(unsigned char Profile);
extern void Set_SMS_Profile(unsigned char SMS_Profile);
//typedef void P_SWITCH_GPRS(int, unsigned char Mode);
extern void Save_SMS_Profile(int block);
extern int OpenReadCloseFile(char *name, char **buf);
extern void RegisterInNetwork(int type, unsigned char *New_LAI, int _207);

extern void GetEEFULLBlock(int block, void *buf, int offset, int size);
extern void SetEEFULLBlock(int block, void *buf, int offset, int size);

extern char IsGPRSConnected(void);

#endif
