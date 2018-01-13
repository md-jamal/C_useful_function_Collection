#include "stdtypes.h"

#ifdef KERNEL_SPACE
//kernel space header
#include <linux/in.h>
#else
//user space header
#include <netinet/in.h>
#endif

#define EVENT_INTERESTED_IN                     1
#define GET_EVENT                               3
#define SEND_EVENT                              4
#define DEBUG_EVENT                             5
#define ACK_EVENT                               6

#define RG                                      1

#define IPV4_IP                                 1

#define WIFI_RESTART_EVENT                      0x00000001

#define MTA_LINE1_STATUS_OFFSET                 0

typedef struct RGEvent_s
{
    unsigned int EventType;
    unsigned int AppType;
    unsigned int TotalSize;
    void         *pOpaque;
    union
    {
        int        restart_time;
        Uint32     dsfreq;
        int        state;
        char       buffer[512];
    } EventInfo;
    Uint16       length;
} RGEvent_t;


