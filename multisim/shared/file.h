#ifndef __FILE_H__
#define __FILE_H__

typedef void P_SetEEFULLBlock(int block, void *buf, int offset, int size);
typedef int P_OPENREADCLOSEFILE(char *name, char **buf);
typedef void P_MFREE(void *);

#endif
