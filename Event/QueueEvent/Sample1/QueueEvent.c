#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 10

/********************************************************************
    STRUCTURES AND ENUMS FOR
    EVENT HANDLING FUNCTIONS
********************************************************************/
typedef enum Events {
    TEST1,
    TEST2,
    TEST3,
    MAX_EVENTS
} e_Events;

typedef void (*callback) (void *);

typedef struct EventHandlers {
    callback cb;
    struct EventHandlers *next;
} s_EventHandlers;

s_EventHandlers *listeners[MAX_EVENTS];

/********************************************************************
    FORWARD DECLARES FOR
    EVENT HANDLING FUNCTIONS
********************************************************************/
void InitListeners(s_EventHandlers *handlers[], int size);
void DestroyListeners(s_EventHandlers *handlers[], int size);
int RegisterEvent(e_Events event, callback cb);

/********************************************************************
    TEST EVENT HANDLERS FUNCTIONS
********************************************************************/
void Test1Handler1(void *data)
{
    printf("In Test1 Handler 1 %s\n", (char*)data);
}
void Test1Handler2(void *data)
{
    printf("In Test1 Handler 2 %s\n", (char*)data);
}
void Test1Handler3(void *data)
{
    printf("In Test1 Handler 3 %s\n", (char*)data);
}
void Test1Handler4(void *data)
{
    printf("In Test1 Handler 4 %s\n", (char*)data);
}
void Test2Handler1(void *data)
{
    printf("In Test2 Handler 1 %s\n", (char*)data);
}
void Test3Handler1(void *data)
{
    printf("In Test3 Handler 1 %s\n", (char*)data);
}
void Test3Handler2(void *data)
{
    printf("In Test3 Handler 2 %s\n", (char*)data);
}

/*********************************************************************
    MAIN ENTRY POINT
 ********************************************************************/

int main(int argc, char *argv[])
{
    s_EventHandlers *handlers = NULL;
    char data[] = "this is the data";
    
    InitListeners(listeners,MAX_EVENTS);
    /*
     * Event number (eg. TEST1) and Event function (eg. Test1Handler) put into the function of RegisterEvent.
    */
    if(RegisterEvent(TEST1, Test1Handler1)==-1)
        printf("duplicate test handler\n");
    if(RegisterEvent(TEST1, Test1Handler2)==-1)
        printf("duplicate test handler\n");
    if(RegisterEvent(TEST1, Test1Handler2)==-1)
        printf("duplicate test handler\n");
    if(RegisterEvent(TEST1, Test1Handler4)==-1)
        printf("duplicate test handler\n");
    if(RegisterEvent(TEST2, Test2Handler1)==-1)
        printf("duplicate test handler\n");
    if(RegisterEvent(TEST3, Test3Handler1)==-1)
        printf("duplicate test handler\n");
    if(RegisterEvent(TEST3, Test3Handler2)==-1)
        printf("duplicate test handler\n");
        
    handlers = listeners[TEST1];
    for(; handlers != NULL; handlers = handlers->next) {
        handlers->cb(data);
    }
    
    handlers = listeners[TEST2];
    for(; handlers != NULL; handlers = handlers->next) {
        handlers->cb(data);
    }
    
    handlers = listeners[TEST3];
    for(; handlers != NULL; handlers = handlers->next) {
        handlers->cb(data);
    }
    
    DestroyListeners(listeners,MAX_EVENTS);
    
    return 0;
}

int RegisterEvent(e_Events event, callback cb)
{
    s_EventHandlers *handlers = listeners[event];
    
    if (handlers == NULL) {
        if(!(handlers = (s_EventHandlers*) malloc(sizeof(s_EventHandlers))))
            return 0; // error returned from malloc
            
        handlers->cb = cb;
        handlers->next = NULL;
        listeners[event] = handlers;
    } else {
        while (handlers->next != NULL) {
            // handlers already registered for this event
            // check to see if it is a redundant handler for this event
            handlers = handlers->next;
            
            if (handlers->cb == cb)
                return -1;
        }
        
        s_EventHandlers *nextHandler;
        if (!(nextHandler = (s_EventHandlers*) malloc(sizeof(s_EventHandlers))))
            return 0; // error returned from malloc
            
        nextHandler->cb = cb;
        nextHandler->next = NULL;
        
        handlers->next = nextHandler;
    }
    
    return 1;
}

void InitListeners(s_EventHandlers *handlers[], int size)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++) {
        handlers[i] = NULL;
    }
}

void DestroyListeners(s_EventHandlers *handlers[], int size)
{
    int i;
    s_EventHandlers *deleteMe, *next;
    for (i = 0; i < MAX_EVENTS; i++) {
        deleteMe = handlers[i];
        
        while (deleteMe) {
            next = deleteMe->next;
            free(deleteMe);
            deleteMe = next;
        }
    }
}
