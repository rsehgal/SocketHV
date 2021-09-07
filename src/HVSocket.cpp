/*
**	Filename : HVSocket.cpp
**	2021-09-06
**	username : rsehgal
*/
#include<iostream>
#include "HVSocket.h"
#include <sys/socket.h>
#include <arpa/inet.h>

HVSocket::HVSocket(){

}
HVSocket::~HVSocket(){


}

HVSocket::HVSocket(std::string ipaddress, int port) : fIpAddress(ipaddress), fPort(port){
	Connect();
}

int HVSocket::Connect(){
        struct sockaddr_in server;

        //Create socket
        fSocket_Desc = socket(AF_INET , SOCK_STREAM , 0);
        if (fSocket_Desc == -1)
        {
                printf("Could not create socket");
        }

        server.sin_addr.s_addr = inet_addr(fIpAddress.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(fPort);

        //Connect to remote server
        if (connect(fSocket_Desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                //puts("connect error");
		std::cerr << "Connect Error..." << std::endl;
                return 1;
        }

        std::cout << "Connected ...." << std::endl;
	return 0;
}



int HVSocket::DisConnect(){

}

int HVSocket::Send(std::string cmd){
	//Send some data
        //char *message = "GET / HTTP/1.1\r\n\r\n";
        if( send(fSocket_Desc , cmd.c_str() , cmd.length() , 0) < 0)
        {
                //puts("Send failed");
		std::cerr << "Send failed......." << std::endl;
                return 1;
        }
        std::cout << "Data Send...../" << std::endl;
	return 0;
}

int HVSocket::Recv(){
	char server_reply[2000];
         //Receive a reply from the server
        if( recvfrom(fSocket_Desc, server_reply , 2000 , 0) < 0)
        {
                std::cerr << "recv failed...." << std::endl;
		return 1;
        }

	std::cout << "Reply received........" << std::endl;
	std::cout << server_reply[0]<< std::endl;

	return 0;
}


