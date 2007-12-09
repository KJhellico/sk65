#include "OsVar.h"
#include "OsFunc.h"
#include "file.h"
#include "kvSIM_var.h"
#include "a3a8.h"

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

extern void SIM_Cmd_Hook(int what, int cla, int ins, int p1, int p2, int rw, int SendLen, unsigned char *SendBuf, int RecvLen, unsigned char *RecvBuf);
extern void SIM_Rsp_Hook(void);
extern void MultisimINIT(void);
extern void SaveHTTPProfile(int profile);
extern void SaveSMSProfile(char profile);
extern void InitMenu ();

#pragma inline
void Clear_FPNMN()
{
  memset(&RAM_FPLMN, 0xFF, 0x0C);
}

void CopySPN(unsigned char *dest, unsigned char *src)
{
  int k = 2, lng = 0;
  *dest ++= *src++;
  *dest ++= 0x95;
  for (; *src && k < 15; k++)
  {
    unsigned char c = *src++;
    if (c >= 0xC0)
    {
      if (!lng)
      {
        *dest++ = 0x9B;
        k++;
        lng = 1;
      }
      *dest++ = c - 0xB0;
    }
    else
    {
      if (lng)
      {
        *dest++ = 0x91;
        k++;
        lng = 0;
      }
      *dest++ = c;
    }
  }
  for (int i = k; i < 16; i++)
    *dest++ = 0;
}

void SIM_Cmd_Hook(int what, int cla, int ins,
                  int p1, int p2, int rw,
                  int SendLen, unsigned char *SendBuf,
                  int RecvLen, unsigned char *RecvBuf)
{
  int flag = 0;
  unsigned char SendBuf2[16];

  MultisimINIT();

  switch (ins)
  {
    case CONST_Run_GSM_A38:
      SIM_State = CONST_Run_GSM_A38;
      memcpy(A38_Data_buffer, SendBuf, KI_BYTE_LEN); // copy the 'Rand'
      break;
    case CONST_Select_File:
      if (CONST_Select_Elementary_File == SendBuf[0])
      {
        switch (SendBuf[1])
        {
          // add the File Id we are care here
          case CONST_Select_IMSI_File:
            SIM_number = Block5400[0x330];
//          case CONST_Select_SMS_Param_File:
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
          if (SIM_number)
          {
            int k = (SIM_number-1) * 0x50 + 0x40;
            memcpy(&Block5400[k], SendBuf, LOCI_DATA_BYTE_LEN);
            SetEEFULLBlock(5400, &Block5400[k], k, LOCI_DATA_BYTE_LEN);
            memcpy(SendBuf2, REAL_SIM_LOCI, LOCI_DATA_BYTE_LEN);
            flag=1;
          }      //SaveSIMData
          else
            memcpy(REAL_SIM_LOCI, SendBuf, LOCI_DATA_BYTE_LEN);

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

  if (flag)
    SIM_Access(what, cla, ins, p1, p2, rw, SendLen, SendBuf2, RecvLen, RecvBuf);
  else
    SIM_Access(what, cla, ins, p1, p2, rw, SendLen, SendBuf, RecvLen, RecvBuf);
}

void SIM_Rsp_Hook(void)
{
  unsigned char CUR_KI[KI_BYTE_LEN];
  int k;

  MultisimINIT();

  if (Response_State != CONST_Response_OK) return;
  if (SIM_State == CONST_Response_FALSE) return;
  k = (SIM_number-1) * 0x50;
  switch (SIM_State)
  {
    case CONST_Run_GSM_A38:
      if (SIM_number)
      {
        memcpy(CUR_KI, &Block5400[k + 0x10], KI_BYTE_LEN);
        A3A8(A38_Data_buffer, CUR_KI, LAST_SIM_BUF_POINTER);
      }
      break;
    case CONST_Select_IMSI_File:
      memcpy(REAL_SIM_IMSI, LAST_SIM_BUF_POINTER, IMSI_DATA_BYTE_LEN);
      if (SIM_number)
        memcpy(LAST_SIM_BUF_POINTER, &Block5400[k], IMSI_DATA_BYTE_LEN);
      break;
    case CONST_Select_LOCI_File:
      memcpy(REAL_SIM_LOCI, LAST_SIM_BUF_POINTER, LOCI_DATA_BYTE_LEN);
      if (SIM_number)
        memcpy(LAST_SIM_BUF_POINTER, &Block5400[k + 0x40], LOCI_DATA_BYTE_LEN);
      break;
    case CONST_Select_SPN_File:
      memcpy(REAL_SIM_SPN, LAST_SIM_BUF_POINTER, SPN_DATA_BYTE_LEN);
      if (SIM_number)
        CopySPN(LAST_SIM_BUF_POINTER, &Block5400[k + 0x20]);
//      memcpy(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x20], SPN_DATA_BYTE_LEN);
      break;
    case CONST_Select_File_14:
      memcpy(REAL_SIM_F14, LAST_SIM_BUF_POINTER, SPN_DATA_BYTE_LEN);
      if (SIM_number)
        CopySPN(LAST_SIM_BUF_POINTER, &Block5400[k + 0x20]);
//      memcpy(LAST_SIM_BUF_POINTER, &Block5400[(SIM_number-1) * 0x50 + 0x20], SPN_DATA_BYTE_LEN);
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

void ChangeSIM(int SimNum);

void ReturnToPhysicalSIM(void)
{
  if (RAM_STBY)
    if (SIM_number == 0)
      ChangeSIM(Block5400[0x334]);
    else
      ChangeSIM(Block5400[(SIM_number-1) * 0x50 + 0x0C]);
  else
    StartTimerProc(&RAM_TIMER1, 13000, &ReturnToPhysicalSIM);
}

void ChangeSIM(int SimNum)
{
  int timer, k;

  if (SimNum==SIM_number) return; // если та же карта, не переключаемся

  Clear_FPNMN();

  if (SIM_number)
  {
    SetEEFULLBlock(5400, &Block5400[(SIM_number-1) * 0x50 + 0x40], (SIM_number-1) * 0x50 + 0x40, LOCI_DATA_BYTE_LEN);
  }      //SaveSIMData

  SIM_number = SimNum;
  k = (SIM_number-1) * 0x50;
  if (SIM_number)
  {
    if (Block5400[k] == 0) // if sim data present
      SIM_number = SimNum = 0;
    else
    {
      memcpy(&RAM_IMSI, &Block5400[k], IMSI_DATA_BYTE_LEN);
      memcpy(&RAM_LOCI, &Block5400[k + 0x40], LOCI_DATA_BYTE_LEN);
//      memcpy(&RAM_SPN,  &Block5400[(SimNum-1) * 0x50 + 0x20], SPN_DATA_BYTE_LEN);
      CopySPN((unsigned char *)&RAM_SPN, &Block5400[k + 0x20]);
    }
  }
  if (!SimNum)
  {
    memcpy(&RAM_IMSI, REAL_SIM_IMSI, IMSI_DATA_BYTE_LEN);
    memcpy(&RAM_LOCI, REAL_SIM_LOCI, LOCI_DATA_BYTE_LEN);
    memcpy(&RAM_SPN,  REAL_SIM_SPN,  SPN_DATA_BYTE_LEN);
    memcpy(&RAM_F14,  REAL_SIM_F14,  SPN_DATA_BYTE_LEN);
//    SIM_number = 0;
  }

//  LIB_Memset(&RAM_KCGPRS, 0xFF, 9);
//  LIB_Memset(&RAM_LOCIGPRS, 0xFF, 14);

  if (SimNum == 0)
    timer = Block5400[0x333];
  else
    timer = Block5400[k + 0x0D];
  if (timer > 0)
    StartTimerProc(&RAM_TIMER1, 13000*timer, &ReturnToPhysicalSIM);

  Set_LAI();

  RegisterInNetwork(1, (unsigned char *)(&RAM_LOCI)+4, 0x207);

  SetEEFULLBlock(5400, &SIM_number, 0x330, 1);
  Block5400[0x330] = SIM_number;

  //Search();
  void SetProfiles(void);
  SetProfiles();

//  StartTimerProc(&RAM_TIMER2, 216, &CheckOnline);

}

void SetProfiles(void)
{
  int http_profile, sms_profile;
  if (SIM_number == 0)
  {
    http_profile = Block5400[0x331];
    sms_profile = Block5400[0x332];
  }
  else
  {
    http_profile = Block5400[(SIM_number-1) * 0x50 + 0x0F];
    sms_profile = Block5400[(SIM_number-1) * 0x50 + 0x0E];
  }
  if (http_profile != 0xFF)
    Set_HTTP_Profile(http_profile);
  if (sms_profile != 0xFF)
    Set_SMS_Profile(sms_profile);
}

void MultisimINIT()
{
  if (((int)SIM_Data & 0xA8000000) != 0xA8000000)
  {
    SIM_Data = (KV_SIM_CTRL_BLOCK *) malloc(sizeof(KV_SIM_CTRL_BLOCK));
    memset(SIM_Data, 0xFF, sizeof(KV_SIM_CTRL_BLOCK));
    if (!(ReadFile()))
      GetEEFULLBlock(5400, Block5400, 0, 1024);
    SIM_number = Block5400[0x330];
    SIM_State = CONST_Response_FALSE;
    SetProfiles();
    InitMenu();
  }
}

void SaveHTTPProfile(int profile)
{
  int k;
  if (SIM_number == 0)
    k = 0x331;
  else
    k = (SIM_number-1) * 0x50 + 0x0F;
  if (Block5400[k] != profile && Block5400[k] != 0xFF)
  {
    Block5400[k] = profile;
    SetEEFULLBlock(5400, &Block5400[k], k, 1);
  }
}

void SaveSMSProfile(char profile)
{
  char *curprof = (char *)&(Current_SMS_Profile);
  if (profile>5) return;
  *curprof = profile;
//  (char*)Current_SMS_Profile = profile;
  Save_SMS_Profile(5138);

  int k;
  if (SIM_number == 0)
    k = 0x332;
  else
    k = (SIM_number-1) * 0x50 + 0x0E;
  if (Block5400[k] != profile && Block5400[k] != 0xFF)
  {
    Block5400[k] = profile;
    SetEEFULLBlock(5400, &Block5400[k], k, 1);
  }
}
