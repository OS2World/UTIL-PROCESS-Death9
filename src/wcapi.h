#ifndef _WCAPI_H_
#define _WCAPI_H_

#include "stddef.h"

#ifdef __cplusplus
  extern "C" {
#endif

#if defined (__WATCOMC__)                               /* Watcom C/C++  */
  #define WCSYSTEM __syscall
  #define WCEXPORT __export
#elif defined(__BORLANDC__)                             /* Borland C/C++ */
  #define WCSYSTEM _syscall
  #define WCEXPORT _export
#elif defined(__IBMC__) || defined (__IBMCPP__)         /* IBM C/C++     */
    #define WCSYSTEM _System
    #define WCEXPORT _Export
#else                                                   /* EMX, other    */
    #define WCSYSTEM
    #define WCEXPORT
#endif

typedef int (* WCSYSTEM WCATFN)();

/* These functions can be used, when linked with dllbase.c */
/* They are intended to be used when writing one's own DLL */

void * WCSYSTEM WCatBegWindow(char *title, char *Menuentry,
                             char *description, void (*fn)());
void WCSYSTEM   WCatClearWindow(void *win);
void WCSYSTEM   WCatShowWindow(void *win);
void WCSYSTEM   WCatAddLine(void *win, char *text);
void WCSYSTEM   WCatAddLineAndScroll(void *win, char *text);
void WCSYSTEM   WCatChangeLine(void *win, int line, char *text);
void WCSYSTEM   WCatPrintf(void *win, char *format, ...);
void WCSYSTEM   WCatChangePrintf(void *win, int line, char *format, ...);
unsigned long   WCSYSTEM WCatQueryPID();
unsigned long   WCSYSTEM WCatQueryHandle();
void WCSYSTEM   WCatSetTitle(void *win, int i, char *text);
void WCSYSTEM   WCatPopup();

/* new (WatchCat 2.1) functions */
void *WCSYSTEM   WCatBegFrameWindow(char *title, char *Menuentry,
                                   char *description, void (*fn)());
void *WCSYSTEM   WCatBegListbox(char *title, char *Menuentry,
                               char *description, void (*fn)());
void WCSYSTEM   WCatHideCursor(void *win);
void WCSYSTEM   WCatShowCursor(void *win);
void WCSYSTEM   WCatSetCursor(void *win, int x, int y);
int  WCSYSTEM   WCatQueryCursor(void *win, int *x, int *y);
void WCSYSTEM   WCatClrScr(void *win);
void WCSYSTEM   WCatPuts(void *win, char *s);
int  WCSYSTEM   WCatIsVisible(void *win);

/* The following functions are useful for some debugging purposes */
/* They are intended to be used in your own application and can   */
/* be used to activate WatchCat or to print debugging text        */

void WCSYSTEM  WatchCat();              /* Activate Watchcat */

/* The following functions are not intended to be called directly */
extern void WCSYSTEM _multithreaded_wcprintf(char *format, ...);
extern void WCSYSTEM _multithreaded_wcprintp(char *fn, char *file, int line);
extern void WCSYSTEM _singlethreaded_wcprintf(char *format, ...);
extern void WCSYSTEM _singlethreaded_wcprintp(char *fn, char *file, int line);

/* Use the Macro wcprintf instead */
/* Usage:                         */
/* #define WCDEBUG                */
/* wcprintf("a debugging string");*/

#ifdef __cplusplus
  #define WC_ONE_INSTANCE inline
#else
  #ifdef __IBMC__
    #define WC_ONE_INSTANCE _Inline
  #else
    #define WC_ONE_INSTANCE  static
  #endif
#endif

#ifdef WCDEBUG
  #if (defined(__IBMC__)|| defined(__IBMCPP__))
    #ifdef __MULTI__
     #define wcprintf _multithreaded_wcprintp(__FUNCTION__,__FILE__,__LINE__),_multithreaded_wcprintf
    #else
     #define wcprintf _singlethreaded_wcprintp(__FUNCTION__,__FILE__,__LINE__),_singlethreaded_wcprintf
    #endif
  #elif defined (__WATCOMC__)
    #ifdef __SW_BM
     #define wcprintf _multithreaded_wcprintp(0,__FILE__,__LINE__),_multithreaded_wcprintf
    #else
     #define wcprintf _singlethreaded_wcprintp(0,__FILE__,__LINE__),_singlethreaded_wcprintf
    #endif
  #elif (defined(__BORLANDC__) || defined (__BCPLUSPLUS))
    #ifdef __MT__
     #define wcprintf _multithreaded_wcprintp(0,__FILE__,__LINE__),_multithreaded_wcprintf
    #else
     #define wcprintf _singlethreaded_wcprintp(0,__FILE__,__LINE__),_singlethreaded_wcprintf
    #endif
  #else
    #if defined (__MULTI__) || defined (__MT__)
     #define wcprintf _multithreaded_wcprintp(0,__FILE__,__LINE__),_multithreaded_wcprintf
    #else
     #define wcprintf _singlethreaded_wcprintp(0,__FILE__,__LINE__),_singlethreaded_wcprintf
    #endif
  #endif
#else
  WC_ONE_INSTANCE void wcprintf(char *format, ...)
     {
     }
#endif

#ifdef __cplusplus
  }
#endif

#ifdef __cplusplus
/* Now the class declarations follow */

#ifndef __IBMCPP__
  #define _Optlink
#endif

class WCatBaseWindow;
void WCatAddWindowPtr(WCatBaseWindow *p, void *vp);

class WCatBaseWindow {
  protected:
    void *win;
  public:
    virtual int key(int scan, int ascii, int shift) { return 0; }
    virtual int selected(int i)                     { return 0; }
    virtual int processChanged(int i)               { return 0; }
    virtual int b1click(int x, int y)               { return 0; }
    virtual int b1dbclick(int x, int y)             { return 0; }
    virtual int receiveFocus()                      { return 0; }
    virtual int looseFocus()                        { return 0; }
    virtual int handleShow()                        { return 0; }

    virtual void setTitle(int i, char *s)=0;
    virtual void hideCursor()=0;
    virtual void showCursor()=0;
    virtual void setCursor(int x, int y)=0;
    virtual int queryCursor(int& x, int& y)=0;
    virtual void clrscr()=0;
    virtual void puts(char *s)=0;

    void show()
      { WCatShowWindow(win); }
    int  isVisible()
      { return WCatIsVisible(win); }
  };

class WCatWindow : public WCatBaseWindow {
  public:
    WCatWindow(char *title, void (* _Optlink fn)(), char *Menuentry=0, char *description=0)
      { WCatAddWindowPtr(this,
            win=WCatBegFrameWindow(title, Menuentry, description, fn)); }

    virtual void setTitle(int i, char *s)
      { WCatSetTitle(win,i,s); }
    virtual void hideCursor()
      { WCatHideCursor(win); }
    virtual void showCursor()
      { WCatShowCursor(win); }
    virtual void setCursor(int x, int y)
      { WCatSetCursor(win,x,y); }
    virtual int queryCursor(int& x, int& y)
      { return WCatQueryCursor(win, &x, &y); }
    virtual void clrscr()
      { WCatClearWindow(win); }
    virtual void puts(char *s)
      { WCatPuts(win, s); }
  };

class WCatListbox : public WCatBaseWindow {
  public:
    WCatListbox(char *title, void (* _Optlink fn)(), char *Menuentry=0, char *description=0)
      { WCatAddWindowPtr(this,
            win=WCatBegListbox(title, Menuentry, description, fn)); }

    void addLine(char *p)
      { WCatAddLine(win, p); }
    void scrollLine(int i)
      { /* ??? */ }
    void addLineAndScroll(char *p)
      { WCatAddLineAndScroll(win, p); }
    void changeLine(int i, char *p);
    virtual void setTitle(int i, char *s)
      { WCatSetTitle(win,i,s); }
    virtual void hideCursor()
      { WCatHideCursor(win); }
    virtual void showCursor()
      { WCatShowCursor(win); }
    virtual void setCursor(int x, int y)
      { WCatSetCursor(win,x,y); }
    virtual int queryCursor(int& x, int& y)
      { return WCatQueryCursor(win, &x, &y); }
    virtual void clrscr()
      { WCatClearWindow(win); }
    virtual void puts(char *s)
      { WCatPuts(win, s); }
  };
#endif


#endif
