#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "event.h"

static int FdGW = -1;

static int FavAppType = RG;

#define PSEUDO_EVENTMGR_DRIVER "/dev/eventmgr"

static void GW_Event_Handler(int no)
{
    int msg_loop = 0, msg_result = -1;
    RGEvent_t TmpRGEvent_t;
    
    if ((no == SIGUSR2))
    {
        printf("GW_Event_Handler error.\n");
    }
    msg_loop = 0;
    while (msg_loop < 10)
    {
        memset(&TmpRGEvent_t, 0, sizeof(RGEvent_t));
        TmpRGEvent_t.AppType=RG;
        lockf(FdGW,F_LOCK,0);
        msg_result = ioctl(FdGW, GET_EVENT, &TmpRGEvent_t);
        lockf(FdGW,F_ULOCK,0);
        
        if (msg_result == 1)
        {
            if (no == 0)  printf("Process GW event!(%d)\n", (msg_loop+1));
            switch (TmpRGEvent_t.EventType)
            {
                case WIFI_RESTART_EVENT:
                    printf("Receive WIFI_RESTART_EVENT message.\n");
                    break;
                default:
                    break;
            }
        }
        msg_loop++;
    }
}



void StartVendorMainLoop()
{
    while (1)
    {
        GW_Event_Handler(0);
    }
}

int main(int argc, char *argv[])
{
    struct sigaction sigchld_action2;
    sigset_t block_mask2;
    
    sigemptyset (&block_mask2);
    memset(&sigchld_action2, 0, sizeof (sigchld_action2));
    sigchld_action2.sa_handler = &GW_Event_Handler;
    
    if (sigaddset (&block_mask2, SIGUSR2)== -1)
        perror("Can not set SIGUSR2 mask");
        
    sigchld_action2.sa_mask = block_mask2;
    sigchld_action2.sa_flags = 0;
    sigaction(SIGUSR2, &sigchld_action2, 0);
    
    if ((FdGW = open(PSEUDO_EVENTMGR_DRIVER, O_RDONLY)) < 0)
    {
        printf("Unable to open the eventmgr driver!\n");
        return 0;
    }
    
    if (ioctl(FdGW, EVENT_INTERESTED_IN, &FavAppType) < 0)
    {
        close(FdGW);
        printf("Unable to perform EVENT_INTERESTED_IN!\n");
        return 0;
    }
    
    StartVendorMainLoop();
}




