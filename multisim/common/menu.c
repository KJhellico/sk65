#include "siemens.h"
#include "OsFunc.h"
#include "kvSIM_var.h"

extern KV_SIM_CTRL_BLOCK *SIM_Data;

#define SIM_number          (SIM_Data->SIM_number)
#define Block5400           (SIM_Data->Block5400)

#define SPN_DATA_BYTE_LEN   16

extern void ShowMenu(); 
extern void InitMenu(); 

//void SelectMenu(unsigned long unc);
void OnAppearItem(void *data, int curitem, void *unk);
extern void ChangeSIM(int SimNum);

//static const unsigned long ENTRYS[]={(unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu};
extern int HeaderIcon[];
extern int IconIDList[];
static const int menusoftkeys[] = {0, 1, 2}; // MENUSTRUCT_pUnkData1
static const char LG_PHYSSIM[] = "Физическая SIM";
static const char LG_SIM[] = "Выбор SIM:";
const SOFTKEY_DESC menu_sk[]=
{
  {0x0001, 0, (int)""},
  {0x0018, 0, (int)"Выбор"},
  {0x003D, 0, (int)LGP_DOIT_PIC},
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 3
};

/*
static const MENUITEM_DESC items[]={
  {IconIDList, (int)LG_PHYSSIM, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C},
  {IconIDList, 0, 0, 0, 0, 3, 0x59C}};
*/
const HEADER_DESC sim_menuHeader={{0, 0, 131, 17}, HeaderIcon, (int)LG_SIM, 0x7FFFFFFF};
int MenuOnKey(void *data, GUI_MSG *msg);
const MENU_DESC sim_menu={0, MenuOnKey, 0, 0, menusoftkeys, &menu_skt, 0x201, OnAppearItem, 0, /*ENTRYS*/0, 10};

int MenuOnKey(void *data, GUI_MSG *msg)
{
  int i;
  if (msg->keys==0x18 || msg->keys==0x3D)
  {
    i = GetCurMenuItem(data);
    ChangeSIM(i);
    return 1;
  }
  return 0;
}

/*
void SelectMenu(unsigned long unc)
{
  unsigned long curr;

  curr=GetMenuCurItem(unc);

  ChangeSIM(curr);
  CloseMenu(unc);
}
*/

void OnAppearItem(void *data, int curitem, void *unk)
{
  int Icon = (curitem==SIM_number)?0:1;
  SetMenuItemIcon(data, curitem, Icon);
}

void ShowMenu()
{
/*
  int i;

  for (i=0; i<10&&(Block5400[0x50*(i)+0x20+2]!=0); i++);
  SIM_Data->sim_menu.ItemsCount = i+1;
*/
  CreateMenu(0, &(SIM_Data->sim_menu), &sim_menuHeader, 0); 
}

void InitMenu()
{
  int i;

  //memcpy(&(SIM_Data->items), (void*)&items, 10*sizeof(MENUITEM_DESC));
  memset (&(SIM_Data->items), 0, 10*sizeof(MENUITEM_DESC));
  SIM_Data->items[0].icon = IconIDList;
  SIM_Data->items[0].lgp_id_small = SIM_Data->items[0].lgp_id_large = (int)LG_PHYSSIM;
  SIM_Data->items[0].flag1 = 3;
  SIM_Data->items[0].flag2 = 0x59C;

  memcpy(&(SIM_Data->sim_menu), (void*)&sim_menu, sizeof(MENU_DESC));

  // + подрезка меню by Shadows
  for (i=1; i<10&&(Block5400[0x50*(i-1)+0x20+2]!=0); i++)
  {
    SIM_Data->items[i].icon = IconIDList;
    SIM_Data->items[i].lgp_id_small = SIM_Data->items[i].lgp_id_large = (int)&Block5400[0x50*(i-1)+0x20+1];
    SIM_Data->items[i].flag1 = 3;
    SIM_Data->items[i].flag2 = 0x59C;
  }
  SIM_Data->sim_menu.n_items = i;
  SIM_Data->sim_menu.items = SIM_Data->items;
  
/*  for (i=1;i<10;i++)
  {
    SIM_Data->items[i].lgp_id_small = SIM_Data->items[i].lgp_id_large = (unsigned long)&Block5400[0x50*(i-1)+0x20+1];
  }
*/
}
