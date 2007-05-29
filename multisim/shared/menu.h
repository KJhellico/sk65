#ifndef __MENU_H__
#define __MENU_H__

typedef void P_CreateMenu(unsigned long, const struct MENUSTRUCT*, const struct MENUFRAME*, unsigned long);
typedef void P_SetMenuState(unsigned long, unsigned long, unsigned long);
typedef void P_CloseMenu(unsigned long);
typedef unsigned long P_GetMenuCurItem(unsigned long);

typedef char* P_malloc(unsigned int iSize);
typedef void P_mfree(char *cArray);
typedef char *P_strcpy(char *strDestination, const char *strSource);
typedef void P_MEMSET(void *s, int c, int n);

//typedef void P_GETNOTLGP(unsigned id, unsigned b, unsigned c);
//typedef unsigned P_GETFROMLGP(unsigned id, unsigned c);
//typedef unsigned P_CONVLGP(unsigned b, unsigned lgpptr, unsigned one, unsigned zero);

P_CreateMenu     *const CreateMenu = (P_CreateMenu*) CreateMenu_ADR;
P_SetMenuState   *const SetMenuState = (P_SetMenuState*) SetMenuState_ADR;
P_CloseMenu      *const CloseMenu = (P_CloseMenu*) CloseMenu_ADR;
P_GetMenuCurItem *const GetMenuCurItem = (P_GetMenuCurItem*) GetMenuCurItem_ADR;

typedef void P_GetEEFULLBlock(int block, void *buf, int offset, int size);
typedef void P_MEMCPY(void *pDst, void *pSrc, int nLen);

//extern unsigned char *LAST_LGP_BUF;
//typedef void P_SetEEFULLBlock(int block, void *buf, int offset, int size);

// extern P_GetEEFULLBlock *const GetEEFULLBlock;
// extern P_SetEEFULLBlock *const SetEEFULLBlock;

#endif
