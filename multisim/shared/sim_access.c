#include "OsVar.h"
#include "adr_c.h"
#include "OsFunc.h"
#include "kvSIM_var.h"
#include "a3a8.h"

__no_init KV_SIM_CTRL_BLOCK *SIM_Data @ UNUSED_RAM_BASE_ADR ;

#define A38_Data_buffer       (SIM_Data->A38_Data_buffer)
#define Response_State        (SIM_Data->Response_State)
#define SIM_State             (SIM_Data->SIM_State)
#define SIM_number            (SIM_Data->SIM_number)
#define Block5400             (SIM_Data->Block5400)

#define REAL_SIM_IMSI         (SIM_Data->REAL_SIM_IMSI)
#define REAL_SIM_LOCI         (SIM_Data->REAL_SIM_LOCI)
#define REAL_SIM_SPN          (SIM_Data->REAL_SIM_SPN)
#define REAL_SIM_F14          (SIM_Data->REAL_SIM_F14)

#define RAM_TIMER1            (SIM_Data->RamTimer1)
//#define RAM_TIMER2            (SIM_Data->RamTimer2)

extern "C" void SIM_Cmd_Hook(int what, int cla, int ins, int p1, int p2, int rw, int SendLen, unsigned char *SendBuf, int RecvLen, unsigned char *RecvBuf);
extern "C" void SIM_Rsp_Hook(void);
extern "C" void MultisimINIT(void);
extern "C" void SaveHTTPProfile(int profile);
extern "C" void SaveSMSProfile(char profile);
extern "C" void InitMenu (); 
extern "C" int ReadFile(); 

void ChangeSIM(int SimNum);

void Clear_FPNMN()
{
  LIB_Memset(&RAM_FPLMN, 0xFF, 0x0C);
}

void CopySPN(unsigned char *dest, unsigned char *src)
{
  int k = 2, lng = 0;
  *dest++=*src++;
  *dest++ = 0x95;
  for(; *src && k < 15; k++)
  {
    unsigned char c = *src++;
    if(c >= 0xC0)
    {
      if(!lng)
      {
        *dest++ = 0x9B;
        k++;
        lng = 1;
      }
      *dest++ = c - 0xB0;
    }
    else
    {
      if(lng)
      {
        *dest++ = 0x91;
        k++;
        lng = 0;
      }
      *dest++ = c;
    }
  }
  for(int i = k; i < 16; i++)
    *dest++ = 0;
}

void SIM_Cmd_Hook(int what, int cla, int ins,
                int p1, int p2, int rw, 
                int SendLen, unsigned char *SendBuf,
                int RecvLen, unsigned char *RecvBuf)
{
  MultisimINIT();

  switch (ins)
  {
    case CONST_Run_GSM_A38:
      SIM_State = CONST_Run_GSM_A38;
      LIB_Memcpy(A38_Data_buffer, SendBuf, KI_BYTE_LEN); // copy the 'Rand'
      break;
    case CONST_Select_File:
      if (CONST_Select_Elementary_File == SendBuf[0])
      {
        switch (SendBuf[1])
        {
          // add the File Id we are care here
          case CONST_Select_IMSI_File:
            SIM_number = Block5400[0x330];
//            case CONST_Select_SMS_Param_File:
          case CONST_Select_SPN_File:
          case CONST_Select_File_14:
          case CONST_Select_LOCI_File:
            SIM_State = SendBuf[1];
            break;
          default:
            break;
        }
      }
      break;
    case CONST_Get_Response:
      switch (SIM_State)
      {
        case CONST_Run_GSM_A38:
        case CONST_Select_LOCI_File:
          Response_State = CONST_Response_OK;
          break;
        default:
          break;
      }
      break;
    case CONST_Read_Binary:
      switch (SIM_State)
      {
        case CONST_Select_IMSI_File:
        case CONST_Select_SPN_File:
        case CONST_Select_File_14:
          Response_State = CONST_Response_OK;
          break;
        case CONST_Select_LOCI_File:
          Response_State = CONST_Response_OK;
          SIM_State = CONST_Get_LOCI_File;
          break;
        default:
          break;
      }
      break;
    case CONST_Update_Binary:
      switch (SIM_State)
      {
        case CONST_Select_LOCI_File:
          if(SIM_number)
          {
            SetEEFULLBlock(5400, SendBuf, (SIM_number-1) * 0x50 + 0x40, LOCI_DATA_BYTE_LEN);
            LIB_Memcpy(&Block5400[(SIM_number-1) * 0x50 + 0x40], SendBuf, LOCI_DATA_BYTE_LEN);
          }      //SaveSIMData
          break;
        default:
          break;
      }
      break;
/* 
    case CONST_Read_Record:
      switch (SIM_State)
      {
        case CONST_Select_SMS_Param_File:
          Response_State = CONST_Response_OK;
          break;
        default:
          break;
      }
      break;
*/
    default:
      break;      
  }                                      

  SIM_Access(what, cla, ins, p1, p2, rw, SendLen, SendBuf, RecvLen, RecvBuf);
}

void SIM_Rsp_Hook(void)
{
  unsigned char CUR_KI[KI_BYTE_LEN];

  MultisimINIT();

  if (CONST_Response_OK != Response_State) return;
  if (CONST_Response_FALSE == SIM_State) return;
  switch (SIM_State)
  {
    case CONST_Run_GSM_A38:
      if(SIM_number)
        {
          LIB_Memcpy(CUR_KI, &Block5400[(SIM_number-1) * 0x50 + 0x10], KI_BYTE_LEN);
          A3A8(A38_Data_buffer, CUR_KI, LAST_SIM_BUF_POINTER);
        }
      break;
    case CONST_Select_IMSI_File:
      LIB_Memcpy(REAL_SIM_IMSI, LAST_SIM_BUF_POINTER, IMSI_DATA_BYTE_LEN);
      if(SIM_number)
        LIB_Memcpy(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50], IMSI_DATA_BYTE_LEN);
      break;
    case CONST_Select_LOCI_File:
      LIB_Memcpy(REAL_SIM_LOCI, LAST_SIM_BUF_POINTER, LOCI_DATA_BYTE_LEN);
      if(SIM_number)
        LIB_Memcpy(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x40], LOCI_DATA_BYTE_LEN);
      break;
    case CONST_Select_SPN_File:
      LIB_Memcpy(REAL_SIM_SPN, LAST_SIM_BUF_POINTER, SPN_DATA_BYTE_LEN);
      if(SIM_number)
        CopySPN(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x20]);
//      LIB_Memcpy(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x20], SPN_DATA_BYTE_LEN);
      break;
    case CONST_Select_File_14:
      LIB_Memcpy(REAL_SIM_F14, LAST_SIM_BUF_POINTER, SPN_DATA_BYTE_LEN);
      if(SIM_number)
        CopySPN(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x20]);
//      LIB_Memcpy(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x20], SPN_DATA_BYTE_LEN);
      break;
    case CONST_Select_SMS_Param_File:
      break;
    default:
      break;
  }
  // clear the flags
  Response_State = CONST_Response_FALSE;
  SIM_State = CONST_Response_FALSE;
}

void ReturnToPhysicalSIM(void)
{
  if (RAM_STBY)
    if (!SIM_number)
    {
      ChangeSIM(Block5400[0x334]);
    }
    else
    {
      ChangeSIM(Block5400[(SIM_number-1) * 0x50 + 0x0C]);
    }
  else
    StartTimerProc(&RAM_TIMER1, 13000, &ReturnToPhysicalSIM);
}
/*
void AttachGPRS(void)
{
  SwitchGPRS(0, 0); // attach
}  

void CheckOnline(void)
{
  if (RAM_NET_ONLINE)
  {
    SwitchGPRS(0, 1); // detach
    StartTimerProc(&RAM_TIMER2, 2*216, &AttachGPRS);
  }
  else
    StartTimerProc(&RAM_TIMER2, 216, &CheckOnline);
}
*/
void ChangeSIM(int SimNum)
{

  unsigned char k;

  Clear_FPNMN();
  if(SimNum)
  {

    k = Block5400[(SimNum-1) * 0x50]; // if sim data present
//    GetEEFULLBlock(5400, &k, (SimNum-1) * 0x50, 1);
    if(k == 0)
      SimNum = 0;
    else
    {
      LIB_Memcpy(&RAM_IMSI, &Block5400[(SimNum-1) * 0x50], IMSI_DATA_BYTE_LEN);
      LIB_Memcpy(&RAM_LOCI, &Block5400[(SimNum-1) * 0x50 + 0x40], LOCI_DATA_BYTE_LEN);
//      LIB_Memcpy(&RAM_SPN,  &Block5400[(SimNum-1) * 0x50 + 0x20], SPN_DATA_BYTE_LEN);
      CopySPN((unsigned char *)&RAM_SPN, &Block5400[(SimNum-1) * 0x50 + 0x20]);
      
//      SIM_number = SimNum;
//      if (Block5400[(SimNum-1) * 0x50 + 0x0D]>0)
//        StartTimerProc(&RAM_TIMER1, 13000*Block5400[(SimNum-1) * 0x50 + 0x0D], &ReturnToPhysicalSIM);
    }
  }
  if(!SimNum)
  {
    LIB_Memcpy(&RAM_IMSI, REAL_SIM_IMSI, IMSI_DATA_BYTE_LEN);
    LIB_Memcpy(&RAM_LOCI, REAL_SIM_LOCI, LOCI_DATA_BYTE_LEN);
    LIB_Memcpy(&RAM_SPN,  REAL_SIM_SPN,  SPN_DATA_BYTE_LEN);
    LIB_Memcpy(&RAM_F14,  REAL_SIM_F14,  SPN_DATA_BYTE_LEN);
//    SIM_number = 0;
  }
  SIM_number = SimNum;

//  LIB_Memset(&RAM_KCGPRS, 0xFF, 9);
//  LIB_Memset(&RAM_LOCIGPRS, 0xFF, 14);

  if (!SimNum)
  {
    if (Block5400[0x333] > 0)
      StartTimerProc(&RAM_TIMER1, 13000*Block5400[0x333], &ReturnToPhysicalSIM);
  }
  else
  {
    if (Block5400[(SimNum-1) * 0x50 + 0x0D]>0)
    StartTimerProc(&RAM_TIMER1, 13000*Block5400[(SimNum-1) * 0x50 + 0x0D], &ReturnToPhysicalSIM);
  }

  Set_LAI();

  SetEEFULLBlock(5400, &SIM_number, 0x330, 1);
  Block5400[0x330] = SIM_number;

  Search();

  if (!SimNum)
  {
    Set_HTTP_Profile(Block5400[0x331]);
    Set_SMS_Profile(Block5400[0x332]);
  }
  else
  {
    Set_HTTP_Profile(Block5400[(SIM_number-1) * 0x50 + 0x0F]);
    Set_SMS_Profile(Block5400[(SIM_number-1) * 0x50 + 0x0E]);
  }
//  StartTimerProc(&RAM_TIMER2, 216, &CheckOnline);

}

void MultisimINIT()
{
 
  if(((int)SIM_Data & 0xA8000000) != 0xA8000000)
  {
    SIM_Data = (KV_SIM_CTRL_BLOCK *) malloc(sizeof(KV_SIM_CTRL_BLOCK));
    LIB_Memset(SIM_Data, 0xFF, sizeof(KV_SIM_CTRL_BLOCK));
    if (!(ReadFile()))
      GetEEFULLBlock(5400, Block5400, 0, 1024);
    SIM_number = Block5400[0x330];
    SIM_State = CONST_Response_FALSE;
    if (!SIM_number) 
    {
      Set_HTTP_Profile(Block5400[0x331]);
      Set_SMS_Profile(Block5400[0x332]);
    }
    else
    {
      Set_HTTP_Profile(Block5400[(SIM_number-1) * 0x50 + 0x0F]);
      Set_SMS_Profile(Block5400[(SIM_number-1) * 0x50 + 0x0E]);
    }
    InitMenu();
  }
 
}

void SaveHTTPProfile(int profile)
{
  if (!SIM_number) 
  {
    Block5400[0x331] = profile;
    SetEEFULLBlock(5400, &Block5400[0x331], 0x331, 1);
  }
  else
  {
    Block5400[(SIM_number-1) * 0x50 + 0x0F] = profile;
    SetEEFULLBlock(5400, &Block5400[(SIM_number-1) * 0x50 + 0x0F], (SIM_number-1) * 0x50 + 0x0F, 1);
  }
 
}

void SaveSMSProfile(char profile)
{
  char *curprof = (char *)Current_SMS_Profile_ADR;
  if (profile>5) return;
  *curprof = profile;
  Save_SMS_Profile(5138);
  if (!SIM_number) 
  {
    Block5400[0x332] = profile;
    SetEEFULLBlock(5400, &Block5400[0x332], 0x332, 1);
  }
  else
  {
    Block5400[(SIM_number-1) * 0x50 + 0x0E] = profile;
    SetEEFULLBlock(5400, &Block5400[(SIM_number-1) * 0x50 + 0x0E], (SIM_number-1) * 0x50 + 0x0E, 1);
  }
 
}
