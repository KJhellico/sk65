#include "file.h"
#include "OsFunc.h"
#include "kvSIM_var.h"
#include "siemens.h"

extern KV_SIM_CTRL_BLOCK * SIM_Data;
#define Block5400		        (SIM_Data->Block5400)

unsigned char htoi(char c)
{
  if ((c >= '0') && (c <='9'))
    return c - '0';
  if ((c >= 'A') && (c <='F'))
    return c - ('A' - 0xA) ;
  return 0;
}


int ReadFile(void)
{
  int size;
  int i, cnt;
  char *filebuf;

//  char Block5400[1024];

  size = OpenReadCloseFile("0:\\Misc\\5400.txt\0", &filebuf);
  if (size < 0)
    return 0;

  // parse file
  cnt = 0;

  for (i=0;i<size;i++)
    if (filebuf[i] > 32)
      Block5400[cnt++] = (htoi(filebuf[i++])<<4) + htoi(filebuf[i++]);

  mfree(filebuf);
  SetEEFULLBlock(5400, Block5400, 0, 1024);
  return 1;
}
