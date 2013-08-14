#include <stdio.h>
#include <stdlib.h>

#define INCL_DOS
#define INCL_ERRORS
#include <os2.h>

#include "death.h"

#define INCL_DOSPROCESS
#define INCL_WIN

static void* win;

/* This is in the watchcat 2.1 package: */
#include "dllbase.c"

void deathIt() {
    ULONG wcatPID;
    ULONG rc;
    wcatPID=WCatQueryPID();
    if(wcatPID==-1)return;
    rc = death(wcatPID);
    return;
}


int WCEXPORT WCSYSTEM WCatInit() {
    win=WCatBegWindow("Question","Death Window","This Function kills deadly the window of a Process.",deathIt);
                return 0;
  }


