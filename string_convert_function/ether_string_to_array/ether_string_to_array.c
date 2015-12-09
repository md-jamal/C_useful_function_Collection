#include <stdio.h>

/*
 *  * -----------------------------------------------------------------
    * ether_aton: take an ethernet (string) address of the form
    *"%x:%x:%x:%x:%x:%x" and, if valid, convert to an array
    *of six unsigned chars n[6] in NETWORK BYTE ORDER, and
    *return 0, otherwise return 1.
    * -----------------------------------------------------------------
 */

int ether_aton(char *a, unsigned char *n)
{
    int i, o[6];

    i = sscanf(a, "%x:%x:%x:%x:%x:%x", &o[0], &o[1], &o[2],
      &o[3], &o[4], &o[5]);
    if (i != 6) 
    {
        fprintf(stderr, "arp: invalid Ethernet address '%s'\n", a);
        fflush(stderr);
        return (1);
    }
    for (i=0; i<6; i++)
        n[i] = o[i];
    return (0);
}  /* end of ether_aton */

int main()
{
    char buf[6] = "\0";
    ether_aton("01:01:01:01:01:01",buf);

    printf("%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
}
