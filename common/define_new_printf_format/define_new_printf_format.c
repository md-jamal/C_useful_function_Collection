/*
 *
 * define_new_printf_format.c
 * Description:
 * Know how to define new printf format
 *
 *
*/


/*! \file define_new_printf_format.c
    \brief Know how to define new printf format
*/

/**************************************************************************/
/*      INCLUDES:                                                         */
/**************************************************************************/
#include <stdio.h>
#include <stdbool.h>

/**************************************************************************/
/*      EXTERNS Declaration:                                              */
/**************************************************************************/


/**************************************************************************/
/*      DEFINES:                                                          */
/**************************************************************************/

/* A time value that is accurate to the nearest
 *    microsecond but also has a range of years.  */
struct timeval
{
__time_t tv_sec;            /* Seconds.  */
__suseconds_t tv_usec;      /* Microseconds.  */
};


/**************************************************************************/
/*      LOCAL DECLARATIONS:                                               */
/**************************************************************************/
#define True 1
#define PRINT_PREFIX                                                        "happy: "

#define FUNC_ENTER_PRINT                                            PRINTF_STDOUT( "--->Entering %s", __FUNCTION__ );
#define FUNC_EXIT_PRINT                                             PRINTF_STDOUT( "<---Exiting %s",  __FUNCTION__ );

#if 1
#define PRINTF_STDOUT( format, args... )            if( verbose ) fprintf( stdout, PRINT_PREFIX "(%d): " format ".\n", getpid(), ## args )
#else
/* keep this if we ever want to check happy timing (again) */
#define PRINTF_STDOUT( format, args... ) \
    { \
        struct timeval __t = {0, 0}; \
        gettimeofday(&__t, NULL); \
        fprintf( stdout, PRINT_PREFIX "(%d):%d.%03d: " format ".\n", getpid(), (int)__t.tv_sec, (int)__t.tv_usec / 1000, ## args ); \
    } while (0)
#endif

/*************************************************************************/
/*      LOCAL VARIABLES:                                                  */
/**************************************************************************/
bool verbose = True;

/**************************************************************************/
/*      INTERFACE FUNCTIONS Implementation:                               */
/**************************************************************************/

/**************************************************************************/
/*      LOCAL FUNCTIONS:                                                  */
/**************************************************************************/

/**************************************************************************/
/*! \fn int main()
 **************************************************************************
 *  \brief 
 *  \Know how to define new printf format
 *  \return OK .
 **************************************************************************/
int main()
{
    FUNC_ENTER_PRINT 
    FUNC_EXIT_PRINT
}




