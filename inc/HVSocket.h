/*
**	Filename : HVSocket.h
**	2021-09-06
**	username : rsehgal
*/
#ifndef HVSocket_h
#define HVSocket_h

class HVSocket{
	std::string fIpAddress;
	int fPort;
	int fSocket_Desc;

public:
	HVSocket();
	HVSocket(std::string ipaddress, int port);
	~HVSocket();
	
	int Connect();
	int DisConnect();
	int Send(std::string command);
	int Recv();
};

#endif
