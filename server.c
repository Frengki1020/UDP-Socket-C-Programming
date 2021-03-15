#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    	struct sockaddr_in server,client;
    	int serversock,n,fp,end;
    	char filename[20],buffer[1000];
    	serversock=socket(AF_INET,SOCK_DGRAM,0);
   	if(serversock==-1){
		printf("Error Socket");	
	}
	else{
		printf("Sukses Socket\n");
	}
	server.sin_family=AF_INET;
    	server.sin_port=5555;
    	server.sin_addr.s_addr=inet_addr("192.168.43.18");
    	int serverbind=bind(serversock,(struct sockaddr *)&server,sizeof(server));

	if(serverbind != 0){
		printf("Error Bind");
	}
	else{
		printf("Sukses Bind\n");
	}
	n=sizeof(client);
    	recvfrom(serversock,filename,sizeof(buffer), 0,(struct sockaddr *)&client,&n);
    	fp=open(filename,O_RDONLY);
    	while(1){
        	end=read(fp,buffer,sizeof(buffer));
        	if(end==0)
            		break;
        	sendto(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,n);
        	bzero(buffer,100);
    	}
    	strcpy(buffer,"end");
    	sendto(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,n);
}
