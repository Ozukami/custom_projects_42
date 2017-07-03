
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
	struct ifaddrs *myaddrs, *ifa;
	struct sockaddr_in *s4;
	int status;
	char *ip=(char *)malloc(64*sizeof(char));

	status = getifaddrs(&myaddrs);
	if (status != 0)
	{
		perror("Probleme de recuperation d'adresse IP");
		exit(1);
	}
	for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr == NULL) continue;
		if ((ifa->ifa_flags & IFF_UP) == 0) continue;
		if ((ifa->ifa_flags & IFF_LOOPBACK) != 0) continue;
		if (ifa->ifa_addr->sa_family == AF_INET)
		{
			s4 = (struct sockaddr_in *)(ifa->ifa_addr);
			if (inet_ntop(ifa->ifa_addr->sa_family,
						(void *)&(s4->sin_addr),ip, 64*sizeof(char)) != NULL)
			{
				printf("Adresse IP :%s\n",ip);
			}
		}
	}
	freeifaddrs(myaddrs);
}
