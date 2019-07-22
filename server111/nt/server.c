#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<string.h>
#include <sys/types.h>
#include <windows.h>
#include<conio.h>
#include<pthread.h>
#include <process.h>
#pragma comment (lib,"ws2_32.lib")

void *functionthread(void *);
int main(int argc,char *argv[])
{
	WSADATA wsa;
	SOCKET s,new_socket;
	struct sockaddr_in server,client;
	int c;
	char buffer[1024];
	int rev_size;
	char msg[100];
	char server_reply[2000];
	pthread_t threadid;

	 FILE *fp;
     int ch = 0;
	 int words;
	//int *yenisoket=0;
	//struct ThreadArgs*threadArgs;
	printf("\n initialising winsock >>>>");
	if(WSAStartup(MAKEWORD(2,2),&wsa) !=0)
	{
		printf("FAILED .ERROR CODE : %d",WSAGetLastError());
		return 1;
	}
	printf("Initialised .\n");

	//creat a socket
	if((s=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
		printf("Could not creat socket : %d",WSAGetLastError());
	printf("Socket Created..\n");

	//prepare the sockaddr 

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8888);

	

	if(bind(s,(struct sockaddr *)&server ,sizeof(server))==SOCKET_ERROR)
		printf("Bind failed with error code : %d",WSAGetLastError());
	puts("Bind Done..");

	

	listen(s,3);
	
	//accept and incoming connection

	puts("waiting for incoming connections.....");
	
	c=sizeof(struct sockaddr_in);
	
	while(new_socket=accept(s,(struct sockaddr *)&client,&c))
	{
	
	if(new_socket ==INVALID_SOCKET)
		printf("accept failed with error code : %d",WSAGetLastError());

	puts("Connection Accepted");

	
           fp = fopen("clintreceived.txt","a");   
			 
            
		//read(new_socket, &words, sizeof(int));
            fread(&new_socket,sizeof(int),1,fp);
        //  while(ch != words)
       	//   {
       // read(new_socket , buffer , 512); 
			//fp = fopen("clnreceived.txt","a"); 
			   fread(&new_socket,sizeof(int),1,fp);
	   	 fprintf(fp , " %s" , buffer);   
		 
		 ch++;
	 //  }
     	printf("The file was received successfully\n");
	
	if(pthread_create(&threadid,NULL,functionthread,(void *)new_socket))
	{
	printf("error thread....");
	return 1;
	}
	printf("thread created...");
	
	printf("from %s %d SOCKETID = %d\n",inet_ntoa(client.sin_addr),client.sin_port,new_socket);
	
	
	}
	printf("thread  created...");
	printf("from %s %d SOCKETID = %d\n",inet_ntoa(client.sin_addr),client.sin_port,new_socket);
	
	while((rev_size=recv(new_socket,server_reply,2000,0))>0)
	{
	send(new_socket,server_reply,strlen(server_reply),0);
	}
	
	getchar();
	
	closesocket(s);
	
	WSACleanup();

	return 0;
}


void *functionthread(void *s)
{
	SOCKET sock=(SOCKET) s;
	int rev_size;
	char message[2000];
while(1)
{
rev_size = recv(sock , message , 2000 , 0);
message[rev_size]=NULL;
puts(message);
}
}

