#define KERNEL_SPACE
#include <linux/module.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/spinlock.h>
#include <linux/timer.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/delay.h>

#include "event.h"

typedef struct Event_s
{
    unsigned int     EventType;
    unsigned int     AppType;
    unsigned int     TotalSize;
    struct Event_s   *pNextEvent;
} Event_t;

typedef struct EvMgrEvent_s
{
    unsigned int EventId;
    unsigned int AppType;
    unsigned int TotalSize;
    void         *pOpaque;
} EvMgrEvent_t;

typedef struct DeviceOpenInstance_s
{
    unsigned int    Interested;
    Event_t         *pHeadEvent;
    Event_t         *pTailEvent;
    unsigned int    EveCnt;
    int             CurrentPid;
    int             ChangeFlag;
} DeviceOpenInstance_t;

DeviceOpenInstance_t *DeviceOpenInstanceList[32];

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static struct class*  ebbcharClass  = NULL; ///< The device-driver class struct pointer
static struct device* ebbcharDevice = NULL; ///< The device-driver device struct pointer

#define EVENTMGR_PSEUDO_MAJOR   100
#define  DEVICE_NAME "eventmgr"    ///< The device will appear at /dev/ebbchar using this value
#define  CLASS_NAME  "event"        ///< The device class -- this is a character device driver

#define GLOBALMEM_SIZE          0x1000

struct semaphore sw_lock;

DEFINE_RWLOCK(db_lock);

static int debug = 0;
static int do_cmd = 0;

int SendEvent(void *pevent)
{
    int i;
    Event_t *pTempEvent=NULL;
    int result = 0;

    if (pevent == NULL) return -1;
    pTempEvent=(Event_t *)pevent;
    
    if (pTempEvent->TotalSize<=0)
        return result;
        
    pTempEvent->pNextEvent = NULL;
    for (i = 0; i < 32; i++)
    {
        if (DeviceOpenInstanceList[i])
        {
            if (DeviceOpenInstanceList[i]->Interested & pTempEvent->AppType)
            {
                if (DeviceOpenInstanceList[i]->EveCnt >= 500)
                    continue;
                if  (DeviceOpenInstanceList[i]->pHeadEvent==NULL)
                {
                    DeviceOpenInstanceList[i]->pHeadEvent=kmalloc(pTempEvent->TotalSize, GFP_KERNEL);
                    if (DeviceOpenInstanceList[i]->pHeadEvent)
                    {
                        memcpy(DeviceOpenInstanceList[i]->pHeadEvent,(void *)pTempEvent, pTempEvent->TotalSize);
                        DeviceOpenInstanceList[i]->pTailEvent = DeviceOpenInstanceList[i]->pHeadEvent;
                        DeviceOpenInstanceList[i]->pHeadEvent->pNextEvent=DeviceOpenInstanceList[i]->pTailEvent->pNextEvent = NULL;
                    }
                }
                else
                {
                    DeviceOpenInstanceList[i]->pTailEvent->pNextEvent = kmalloc(pTempEvent->TotalSize, GFP_KERNEL);
                    if (DeviceOpenInstanceList[i]->pTailEvent->pNextEvent)
                    {
                        memcpy(DeviceOpenInstanceList[i]->pTailEvent->pNextEvent,(void *)pTempEvent, pTempEvent->TotalSize);
                        DeviceOpenInstanceList[i]->pTailEvent = DeviceOpenInstanceList[i]->pTailEvent->pNextEvent;
                        DeviceOpenInstanceList[i]->pTailEvent->pNextEvent = NULL;
                    }
                }
                DeviceOpenInstanceList[i]->EveCnt++;
                DeviceOpenInstanceList[i]->ChangeFlag++;
                result = 1;
            }
        }
    }
    return result;
}

int EvMgrIoctlHandler(unsigned int cmd, void *pBuf)
{
    unsigned int dataLength = 0;
    int result=0;
    int EvType = 0;
    EvMgrEvent_t *pTempEvent=NULL;
    void *pTempBuf = NULL;
    
    if (pBuf == NULL)
    {
        if (debug) printk("[EVENT MGR] Null pointer.\n");
        return result;
    }
    pTempEvent = (EvMgrEvent_t *)kmalloc(sizeof(EvMgrEvent_t), GFP_KERNEL);
    if (pTempEvent == NULL)
    {
        if (debug) printk("[EVENT MGR] Can't allocate memory!\n");
        return result;
    }
    if (copy_from_user(pTempEvent, pBuf, sizeof(EvMgrEvent_t)) != 0)
    {
        if (debug) printk("[EVENT MGR] Command error!\n");
        return result;
    }
    dataLength = pTempEvent->TotalSize;
    EvType = pTempEvent->EventId;
    kfree(pTempEvent);
    pTempBuf = kmalloc(dataLength, GFP_KERNEL);
    
    if (pTempBuf == NULL) return result;
    if (copy_from_user(pTempBuf, pBuf, dataLength) != 0)
        return result;
    result = SendEvent(pTempBuf);
    kfree(pTempBuf);

    return 1;
}

int IoctlEventInterested(struct file *filp, int* buf)
{
    unsigned int App;
    int i = 0;
    int result=0;
    
    i = copy_from_user(&App,(unsigned int *)buf,sizeof(unsigned int));
    if (i < 0) return result;
    for (i=0; i<32; i++)
    {
        if (DeviceOpenInstanceList[i] && (filp->private_data == DeviceOpenInstanceList[i]))
        {
            if (DeviceOpenInstanceList[i]->CurrentPid == current->pid)
            {
                DeviceOpenInstanceList[i]->Interested = App;
                return 1;
            }
        }
    }
    return result;
}

int GetEvent(struct file *filp,void *buf)
{
    int i, j;
    Event_t TempEvent1;
    Event_t *pTempEvent;
    int result=0;
    
    if ((!filp)||(!buf)) return result;
    i = copy_from_user(&TempEvent1,(Event_t *)buf,sizeof(Event_t));
    if (i < 0) return result;
    
    for (i=0; i<32; i++)
    {
        if (DeviceOpenInstanceList[i] && (filp->private_data == DeviceOpenInstanceList[i]))
        {
            if ((DeviceOpenInstanceList[i]->Interested & TempEvent1.AppType) && (DeviceOpenInstanceList[i]->pHeadEvent != NULL))
            {
                pTempEvent = DeviceOpenInstanceList[i]->pHeadEvent;
                j = copy_to_user(buf,pTempEvent,pTempEvent->TotalSize);
                if (j < 0) return result;
                DeviceOpenInstanceList[i]->pHeadEvent = pTempEvent->pNextEvent;
                if (DeviceOpenInstanceList[i]->pHeadEvent==NULL)
                    DeviceOpenInstanceList[i]->pTailEvent=NULL;
                DeviceOpenInstanceList[i]->ChangeFlag--;
                DeviceOpenInstanceList[i]->EveCnt--;
                if (pTempEvent) kfree(pTempEvent);
                return 1;
            }
        }
    }
    return result;
}

static long eventmgr_ioctl(struct file * file, unsigned int cmd, unsigned long buf)
{
    int result=0;
    
    down(&sw_lock);
    switch(cmd)
    {
        case  EVENT_INTERESTED_IN:
            write_lock(&db_lock);
            if (debug) printk("[EVENT MGR] Got EVENT_INTERESTED_IN\n");
            result = IoctlEventInterested(file,(int *)buf);
            write_unlock(&db_lock);
            break;
            
        case  GET_EVENT:
            read_lock(&db_lock);
            result = GetEvent(file,(Event_t *)buf);
            read_unlock(&db_lock);
            break;
            
        case DEBUG_EVENT:
            debug = !debug;
            printk("[EVENT MGR] Debug is %s\n", (debug ? "ON":"OFF"));
            break;
            
        case  SEND_EVENT:
            write_lock(&db_lock);
            result = EvMgrIoctlHandler(cmd,(void *)buf);
            write_unlock(&db_lock);
            break;
            
        case  ACK_EVENT:
            do_cmd = 0;
            if (debug) printk("[EVENT MGR] Got ACK_EVENT\n");
            break;
            
        default:
            printk("BAD command\n");
            break;
    }
    up(&sw_lock);
    return result;
}

static int eventmgr_open(struct inode *inode, struct file *filp)
{
    int i =0;
    int rv = 0;
    DeviceOpenInstance_t *pTempEvent = NULL;
    pTempEvent=(DeviceOpenInstance_t *)kmalloc(sizeof(DeviceOpenInstance_t), GFP_KERNEL);
    if (!pTempEvent) return -1;
    memset(pTempEvent, 0, sizeof(DeviceOpenInstance_t));
    pTempEvent->CurrentPid=current->pid;
    
    rv = down_interruptible(&sw_lock);
    if(rv != 0)
    {
        return NULL;
    }
    
    for (i=0; i<32; i++)
    {
        if (DeviceOpenInstanceList[i] == NULL)
        {
            DeviceOpenInstanceList[i]=pTempEvent;
            filp->private_data = pTempEvent;
            up(&sw_lock);
            return 0;
        }
    }

    up(&sw_lock);
    kfree(pTempEvent);
    return -1;
}

static int eventmgr_release(struct inode *inode, struct file *filp)
{
    int i = 0;
    Event_t *pTempEvent1, *pTempEvent2;
    
    down(&sw_lock);
    for (i=0; i<32; i++)
    {
        if (DeviceOpenInstanceList[i] && (filp->private_data == DeviceOpenInstanceList[i]))
        {
            if (DeviceOpenInstanceList[i]->CurrentPid == current->pid)
            {
                pTempEvent1 = DeviceOpenInstanceList[i]->pHeadEvent;
                kfree(DeviceOpenInstanceList[i]);
                DeviceOpenInstanceList[i] = NULL;
                while (pTempEvent1)
                {
                    pTempEvent2 = pTempEvent1;
                    pTempEvent1 = pTempEvent1->pNextEvent;
                    kfree(pTempEvent2);
                }
            }
            up(&sw_lock);
            return 0;
        }
    }
    up(&sw_lock);
    
    return -1;
}

static unsigned int eventmgr_poll(struct file *filp, poll_table *wait)
{
    return -1;
}

struct file_operations eventmgr_fops =
{
poll:
    eventmgr_poll,
unlocked_ioctl:
    eventmgr_ioctl,
open:
    eventmgr_open,
release:
    eventmgr_release,
};

static int __init eventmgr_init(void)
{
    // Try to dynamically allocate a major number for the device -- more difficult but worth it
    majorNumber = register_chrdev(0, DEVICE_NAME, &eventmgr_fops);
    if (majorNumber<0)
    {
        printk(KERN_ALERT "EBBChar failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "EBBChar: registered correctly with major number %d\n", majorNumber);
    
    // Register the device class
    ebbcharClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(ebbcharClass))                 // Check for error and clean up if there is
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(ebbcharClass);          // Correct way to return an error on a pointer
    }
    printk(KERN_INFO "EBBChar: device class registered correctly\n");
    
    // Register the device driver
    ebbcharDevice = device_create(ebbcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(ebbcharDevice))                // Clean up if there is an error
    {
        class_destroy(ebbcharClass);           // Repeated code but the alternative is goto statements
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(ebbcharDevice);
    }
    printk(KERN_INFO "EBBChar: device class created correctly\n"); // Made it! device was initialized
    
    sema_init(&sw_lock,1);
    
    return 0;
}

static void __exit eventmgr_exit(void)
{
    unregister_chrdev(EVENTMGR_PSEUDO_MAJOR,"eventmgr");
    printk("EVENTMGR: Cleanup module failed\n");
}

module_init(eventmgr_init);
module_exit(eventmgr_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jumbo Fang");
MODULE_DESCRIPTION("Event Manager");
