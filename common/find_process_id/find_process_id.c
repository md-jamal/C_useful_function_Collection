#include <stdio.h> 
#include <sys/stat.h> 
#include <fcntl.h>

int find_process_id( char *name )
{
    int fd = -1;
    char filename[ 25 ];
    char lbuf[ 255 ];
    int currPid, endPid;

    endPid = getpid();

    for (currPid = 1; currPid < endPid; currPid++)
    {
        /* Read command line from /proc/PID/stat */
        sprintf( filename, "/proc/%d/stat", currPid );
         fd = open( filename, O_RDONLY );

         if ( fd >= 0 )
         {
             if ( read( fd, lbuf, 255 ) > 0 )
             {
                 char *p1, *p2;

                 /* command is sorrounded by () */
                 p1 = strchr( lbuf, '(' );
                 p2 = strchr( lbuf, ')' );

                 if ( ( p1 ) && ( p2 ) )
                 {
                    p1++;
                    *p2 = '\0';

                    if( strstr( name, p1 ) )
                    {
                        close(fd);
                        return currPid;
                   }
                 }
             }

             close(fd);
         }
    }

    /* Not found */
    return 0;
}


int main (int argc,char *argv[])
{
    if (PCD_api_find_process_id(argv[1]) > 0)
        printf("Happy");

}
