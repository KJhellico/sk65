#ifndef __SIEMENS_H__
#define __SIEMENS_H__

#define LGP_DOIT_PIC 0x7FFFC0FB

typedef struct
{
  short key1;
  short key2;
  int lgp_id;
} SOFTKEY_DESC;

typedef struct
{
  const SOFTKEY_DESC *desc;
  int n;
} SOFTKEYSTAB;

typedef struct
{
  int *icon;
  int lgp_id_small;
  int lgp_id_large;
  int zero;
  const int *softkeys; //{6,0x22,0x1D}
  int flag1; //0
  int flag2; //0x59D
} MENUITEM_DESC;

typedef struct{
  short x;
  short y;
  short x2;
  short y2;
} RECT;

typedef struct
{
  RECT rc;
  int *icon;
  int lgp_id;
  int lgp_null; //LGP_NULL
} HEADER_DESC;

typedef struct{
#ifdef NEWSGOLD
  int pid_from;
  int msg;
#else
  short pid_from;
  short msg;
#endif
  int submess;
  void *data0;
  void *data1;
} GBS_MSG;

typedef struct
{
  char zero;
  char unk1;
  short keys;
  GBS_MSG *gbsmsg;
} GUI_MSG;

typedef struct
{
  void *first;
  void *last;
  void (*data_mfree)(void *);
} LLQ;

#ifdef NEWSGOLD
typedef struct
{
  RECT *canvas;
  void *methods;
  void *definition;
  char state;
  char unk2;
  char unk3;
  char unk4;
  int color1; //Параметр GeneralFunc пишется сюда?????
  int color2;
  LLQ item_ll;
  int unk5;
  char unk6;
  char unk7;
  char unk8;
  char unk9;
  int unk10;
  int flag30; //Используется при создании (бывает |=0x02)
}GUI;
#else
typedef struct
{
  RECT *canvas;
  void *methods;
  void *definition;
  char state;
  char unk2;
  char unk3;
  char unk4;
  int color1; //Параметр GeneralFunc пишется сюда?????
//  int color2;
  LLQ item_ll;
  int unk5;
  char unk6;
  char unk7;
  char unk8;
  char unk9;
  int unk10;
  int flag30; //Используется при создании (бывает |=0x02)
}GUI;
#endif

typedef void (__interwork *MENUPROCS_DESC)(GUI *);

typedef struct
{
  int flag; //0,8 etc
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int ); //GUI * gui, int cmd
  void *proc3;
  const int *softkeys; //{6,0x22,0x1D}, mb default for all items, if item.softkeys==NULL
  const SOFTKEYSTAB *softkeystab;
  int flags2; //2
  void (*itemproc)(void *, int, void *); //Called when draw item
  const MENUITEM_DESC *items; //Table of items desc;
  const MENUPROCS_DESC *procs;//  void ** procs; //Table of procs when item selected
  int n_items; //Number of items
} MENU_DESC;
#endif
