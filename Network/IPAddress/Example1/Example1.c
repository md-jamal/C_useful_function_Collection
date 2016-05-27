#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/if.h>

#define IFNAMSIZ 16
#define NETWORK_INTERFACE "eth1"
/*******************************************************************************
 *
 * Common types for all compilers, all targets
 *
 ******************************************************************************/
typedef unsigned char UINT8;
typedef unsigned int UINT32;

/*********************************************************************************
  FUNCTION: get_local_ip_address

  DESCRIPTION:
*********************************************************************************/

int get_local_ip_address(char *ifname, unsigned long* ip)
{

  int           skfd;
  struct ifreq  ifr;
  int           err;
  struct sockaddr_in addr;

  skfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (skfd == -1)
    return -1;

  strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
  ifr.ifr_name[IFNAMSIZ-1] = 0;
  if (ioctl(skfd, SIOCGIFADDR, &ifr) != 0)
  {
    close(skfd);
    return -1;
  }

  memcpy(&addr, &ifr.ifr_addr, sizeof(struct sockaddr_in));
  *ip = addr.sin_addr.s_addr;

  close(skfd);
  return 0;
}

/*********************************************************************************
  FUNCTION: hwu_get_ip_address

  DESCRIPTION:
*********************************************************************************/
void hwu_get_ip_address( unsigned long* ip)
{
    get_local_ip_address(NETWORK_INTERFACE, ip);
}

void net_get_ip_addr(UINT8* pAddr)    
{       
    unsigned long iptmp = 0;
    
   hwu_get_ip_address(&iptmp);
   memcpy(pAddr, &iptmp, 4);
} 


void main()
{
    UINT32 addr;

    net_get_ip_addr((UINT8*)&addr);
    printf("Address = %x\n",addr);
}
