#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "event.h"

#define PSEUDO_EVENTMGR_DRIVER "/dev/eventmgr"

int SendEvent (void *pevent)
{
    int Fd, iRet;
    if ((Fd = open (PSEUDO_EVENTMGR_DRIVER, O_RDONLY)) < 0)
    {
        printf("Unable to open the eventmgr driver!\n");
        return 0;
    }
    
    lockf(Fd,F_LOCK,0);
    if ((iRet = ioctl (Fd, SEND_EVENT, pevent)) < 0)
    {
        printf("Ioctl call failed for EVMGR_DISPATCH!\n");
    }
    lockf(Fd,F_ULOCK,0);
    
    close (Fd);
    return iRet;
}

int main ()
{
    RGEvent_t TmpRGEvent_t;
    
    memset(&TmpRGEvent_t, 0, sizeof(RGEvent_t));
    TmpRGEvent_t.AppType=RG;
    TmpRGEvent_t.EventType=WIFI_RESTART_EVENT;
    //sprintf(TmpRGEvent_t.EventInfo.buffer,"iwpriv ath1 set 0");
    TmpRGEvent_t.TotalSize = sizeof(RGEvent_t);
    SendEvent(&TmpRGEvent_t);
    
    return 0;
}
