#ifndef _INIT_
#define _INIT_
#define RELOAD_VALUE 0xdc00
#define WDT_CLR() (WDT |= 0xdf)
void init(void);
extern unsigned int uiSet_Value;
extern bit bFisrt_Init;
#endif
