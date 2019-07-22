#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>
#include<process.h>
#pragma comment (lib,"ws2_32.lib")
#define BUFLEN 512
#define port 8888


int main(int argc ,char*argv[])
{

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	int recv_size;
	char msg[100];
	char mssg[100];
	char name[100];
	char message[100];
	char server_reply[2000];
	int choice=0;
	char buffer[1024];
	char ch ;
	FILE *f;
    int words = 0;
    char c;
	printf("initialising winsock >>>");
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
	{
		printf("Failed ..Error code %d",WSAGetLastError());
		return 1;

	}

	printf("INITIALISED...\n");

	//creat a socket

	if((s=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
		printf("Could not creat socket : %d",WSAGetLastError());
	printf("Socket Created..\n");


	//prepare the sockaddr in structure

	server.sin_addr.s_addr=inet_addr("192.168.43.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8888);


	//connect to remote server

	if(connect(s,(struct sockaddr *)&server ,sizeof(server))<0)
	{
		puts("connect error..");
		return 1;
	}
	puts("CONNECTED..");
	/* _beginthread(MyFunction,0,(void *)&s);*/
	//send some data

	//printf("enter your choice :1-chat  2-ssend file");
	//scanf("%d",&choice);

	//if(choice==1)
	//{
	puts("enter your name :");
	gets(name);
	while(1)
	{
	puts("enter your message :");
	gets(message);
	strcpy(msg,name);
	strcat(msg," : ");
	strcat(msg,message);
    send(s , msg , strlen(msg) , 0);
	strcpy(msg,"");
	strcpy(message,"");
	}
	//}
	//else if (choice==2)
	//{
	
     f=fopen("barol.txt","r");
    while((c=getc(f))!=EOF)	
	{	
		fscanf(f , "%s" , buffer);
		if(isspace(c)||c=='\t')
		words++;	
	}

	//ãÔÇä äßÊÈ ÏÇÎá ÇáãáÝ
	//write(s, &words, sizeof(int));
	fwrite(&s,sizeof(buffer),1,f);
     	rewind(f);
      
       
       
    
       while(ch != EOF)
      {
		
		fscanf(f , "%s" , buffer);
		//write(s,buffer,512);
		fwrite(&s,sizeof(buffer),1,f);
		ch = fgetc(f);
      }
	printf("The file was sent successfully");
	

	/*while(1)
	{
		printf("enter the message :");
		gets(msg);
	
	if(send(s,msg,sizeof(msg),0)<0)
	{
		puts("send failed..");
		return 1;
	}
	puts("Data Send \n");
	
	//receive a reply from the server*/

	if((recv_size=recv(s,server_reply,2000,0))<0)
	{
		puts("recv failed");
	
	}


	printf("replay ..");

	
	puts("REPLY RECEIVED...\n");
	
	server_reply[recv_size]='\0';
	puts(server_reply);
	gets(server_reply);
	
	//}
	
	
	getchar();
	return 0;
}