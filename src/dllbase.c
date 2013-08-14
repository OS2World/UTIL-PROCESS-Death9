#include "wcapi.h"
#include <stdarg.h>
#include <stdio.h>

static WCATFN *table;

int WCEXPORT WCSYSTEM WCatRegister(WCATFN *fntable)
  {
  table=fntable;
  return 0;
  }

void * WCSYSTEM WCatBegWindow(char *title, char *Menuentry,
                             char *description, void (*fn)())
  {
  return (void *)table[0](title, Menuentry, description, fn);
  }

void WCSYSTEM WCatClearWindow(void *win)
  {
  table[1](win);
  }

void WCSYSTEM WCatShowWindow(void *win)
  {
  table[2](win);
  }

void WCSYSTEM WCatAddLine(void *win, char *text)
  {
  table[3](win, text);
  }

void WCSYSTEM WCatAddLineAndScroll(void *win, char *text)
  {
  table[11](win, text);
  }

void WCSYSTEM WCatChangeLine(void *win, int line, char *text)
  {
  table[4](win, line, text);
  }

void WCSYSTEM WCatPrintf(void *win, char *format, ...)
  {
  va_list arglist;
  char buffer[256];

  va_start(arglist, format);
  vsprintf(buffer, format, arglist);
  WCatAddLine(win, buffer);
  va_end(arglist);
  }

void WCSYSTEM WCatChangePrintf(void *win, int line, char *format, ...)
  {
  va_list arglist;
  char buffer[256];

  va_start(arglist, format);
  vsprintf(buffer, format, arglist);
  WCatChangeLine(win, line, buffer);
  va_end(arglist);
  }

unsigned long WCSYSTEM WCatQueryPID()
  {
  return table[7]();
  }

unsigned long WCSYSTEM WCatQueryHandle()
  {
  return table[8]();
  }

void WCSYSTEM WCatSetTitle(void *win, int i, char *text)
  {
  table[9](win, i, text);
  }

void WCSYSTEM WCatPopup()
  {
  table[10]();
  }

void *WCSYSTEM   WCatBegFrameWindow(char *title, char *Menuentry,
                                   char *description, void (*fn)())
  {
  return (void *)table[12](title, Menuentry, description, fn);
  }


void *WCSYSTEM   WCatBegListbox(char *title, char *Menuentry,
                               char *description, void (*fn)())
  {
  return (void *)table[13](title, Menuentry, description, fn);
  }

void WCSYSTEM   WCatHideCursor(void *win)
  {
  table[14](win);
  }
void WCSYSTEM   WCatShowCursor(void *win)
  {
  table[15](win);
  }
void WCSYSTEM   WCatSetCursor(void *win, int x, int y)
  {
  table[16](win,x,y);
  }
int  WCSYSTEM   WCatQueryCursor(void *win, int *x, int *y)
  {
  table[17](win,x,y);
  }
void WCSYSTEM   WCatClrScr(void *win)
  {
  table[18](win);
  }
void WCSYSTEM   WCatPuts(void *win, char *s)
  {
  table[19](win,s);
  }
int WCSYSTEM   WCatIsVisible(void *win)
  {
  table[20](win);
  }

