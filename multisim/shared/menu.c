#include "adr_c.h"
#include "pic_def.h"
#include "lgp_def.h"
#include "menu.h"
#include "siemens.h"
#include "kvSIM_var.h"

extern KV_SIM_CTRL_BLOCK * SIM_Data;
//extern struct MENUSTRUCT test_menu;
//extern struct ITEMSDATA items[];

#define SIM_number		        (SIM_Data->SIM_number)
#define Block5400		        (SIM_Data->Block5400)

#define SPN_DATA_BYTE_LEN       16

extern "C" void LgpHook(unsigned id, unsigned b, unsigned c); 
extern "C" void ShowMenu (); 
extern "C" void InitMenu (); 

void SelectMenu(unsigned long unc);
void OnAppearItem(unsigned long unc1, unsigned long unc2);
extern void ChangeSIM(int SimNum);

extern P_GetEEFULLBlock *const GetEEFULLBlock;
extern P_MEMCPY	*const LIB_Memcpy;
static const unsigned long ENTRYS[]={(unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu, (unsigned long)SelectMenu};
static const unsigned long HeaderIcon[]={PIC_SIM_insert, 0};
static const unsigned long IconIDList[]={PIC_empty, PIC_checked, PIC_unchecked, PIC_unc, PIC_err, PIC_r_sel, PIC_r_unsel, PIC_bell_on, PIC_bell_off, PIC_bell_beep};
static const struct ITEMSDATA items[]={
                                 {IconIDList, LGP_This_SIM, LGP_This_SIM, 0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group1, LGP_Group1,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group2, LGP_Group2,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group3, LGP_Group3,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group4, LGP_Group4,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group5, LGP_Group5,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group6, LGP_Group6,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group7, LGP_Group7,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group8, LGP_Group8,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C},
                                 {IconIDList, LGP_Group9, LGP_Group9,     0, ITEMSDATA_Unk2_ADR, 3, 0x59C}};
static const struct MENUFRAME test_MenuHeader={0, 0, 131, 17, (unsigned long *)&HeaderIcon, LGP_SIM, 0x7FFFFFFF};
static const struct MENUSTRUCT test_menu={0, 0, 0, 0, MENUSTRUCT_pUnkData1_ADR, MENUSTRUCT_pUnkData2_ADR, 0x201, 0, (void *)OnAppearItem, (ITEMSDATA*)&(items), ENTRYS, 10};

void SelectMenu(unsigned long unc)
{
   unsigned long curr;

   curr=GetMenuCurItem(unc);

   ChangeSIM(curr);
   CloseMenu(unc);
}

/*int OnKeyPressed(void *data, char *key_data) __thumb
{
//   int key=*(char far*)(key_data+0x02);
//   int state=*(int far*)(0x04+*(char far**)(key_data+0x04));
} */
/*
int OnMessage() __thumb
{

} */

void OnAppearItem(unsigned long unc1, unsigned long ItemNum)
{
   int Icon=6;
   if (ItemNum==SIM_number)
   {
      Icon=5;
   }

   SetMenuState(unc1, ItemNum, Icon);
}


void ShowMenu ()
{
  CreateMenu(0, &(SIM_Data->test_menu), &test_MenuHeader, 0); 
}

void InitMenu ()
{
  int i;

  LIB_Memcpy(&(SIM_Data->items), (void*)&items[0], 10*sizeof(ITEMSDATA));
  LIB_Memcpy(&(SIM_Data->test_menu), (void*)&test_menu, sizeof(MENUSTRUCT));
  for (i=1;i<10;i++)
  {
    SIM_Data->items[i].StrID_NormalMenu = SIM_Data->items[i].StrID_CapsMenu = (unsigned long)&Block5400[0x50*(i-1)+0x20+1];
  }
  SIM_Data->test_menu.ItemsData = SIM_Data->items;
}
