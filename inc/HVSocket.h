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
	int fNumOfChannels;

public:
	HVSocket();
	HVSocket(std::string ipaddress, int port);
	~HVSocket();
	
	int Connect();
	int DisConnect();
	int Send(std::string command);
	int Recv();

	/*Switch ON Power Supply*/
	int SystemOnChannelsOff();
	int SystemOn();
	int SystemOnChannelsOn();
	int SystemOnChannelsOn(unsigned int crateNo);
	int ChannelsOn();
	int ChannelsOn(unsigned int crateNo);

	int SystemOff();
};

#endif
