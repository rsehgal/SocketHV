/*
**	Filename : socketTest.cpp
**	2021-09-06
**	username : rsehgal
*/
#include<iostream>
#include "HVSocket.h"
int main(int argc, char *argv[]){
	std::string ip="10.12.80.240";
	int port=4003;
	HVSocket sock(ip,port);
	//HVSocket sock("127.0.0.1",80);
	//sock.Send("GET / HTTP/1.1\r\n\r\n");
	std::string command=argv[1];
	sock.Send((command+"\n\Esc").c_str());
	sock.Recv();
	
	return 0;
}


