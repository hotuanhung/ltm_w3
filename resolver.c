#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h> 
#include <arpa/inet.h>
int get_ip(char * hostname , char *ip)
{
    struct hostent *host;
    struct in_addr **addr_list;
    int i;
    if((host = gethostbyname(hostname))== NULL)
    {
        printf("Not found information\n");
        ip=NULL;
        return 1;
    }
    addr_list = (struct in_addr **) host->h_addr_list;
    for(i =0; addr_list[i]!=NULL ; i++)
    {
        strcpy(ip, inet_ntoa(*addr_list[i]));

    }
    return 0;
}
int get_hostname(char *hostname, char *ip)
{
    struct in_addr addr;
    struct hostent * host;
  
    inet_aton(ip, &addr);
    //printf("%s\n", addr);
    host= gethostbyaddr(((const char*)&addr),sizeof(addr), AF_INET);
    if(host == NULL)
    {
    	printf("Not found information\n");
    	hostname = NULL;
    	return 1;
    }
    strcpy(hostname, host->h_name);
    return 0;
}
int checkHostnameOrIp(char *info)
{
    if(info[0] > 47 && info[0] < 58)
		return 1; //is IP
	else
		return 0; // is Hostname
}
int main( int argc, char *argv[])
{
    if(argc <3)     
    {
    	printf("Please provide a hostname or ip");         
    	
    }   
    char a = *argv[1];
    char *temp = argv[2];
    if(a=='1')
    {
        if(checkHostnameOrIp(temp) == 0)
        {
            printf("Wrong parameter\n");
        }
        else
        {
            char *ip = argv[2];
        char hostname[100];
        if(!get_hostname(hostname, ip))
        {
            printf("Official name: %s\n", hostname);
        }
        }
    }
    else
    {
        if(checkHostnameOrIp(temp) == 1)
        {
            printf("Wrong parameter\n");
        }
        else
        {
            char *hostname = argv[2];
        char ip[100];
        if(!get_ip(hostname , ip))
        {
            printf("Official IP: %s\n", ip);
        }
        }

    }
   
}