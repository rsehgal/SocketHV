/*
**	Filename : HVSocket.h
**	2021-09-06
**	username : rsehgal
*/
#ifndef HVSocket_h
#define HVSocket_h

#include <string>
#include <vector>

class HVSocket {
  std::string fIpAddress;
  int fPort;
  int fSocket_Desc;
  int fNumOfChannels;
  bool fSystemOn;

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
  int ChannelsOnWithIndex(unsigned int channelIndex);
  int ChannelsOnWithCrateIndex(unsigned int crateIndex);
  int ChannelsOnWithCrateIndex(std::vector<unsigned int> vecOfCrateIndex);
  int ChannelsOnWithIndex(std::vector<unsigned int> vecOfChannelIndex);

  int SetVoltage(std::vector<unsigned int> channelNoVec);
  int SetVoltage(unsigned int channelNo,unsigned int voltage);
  int SetVoltage(unsigned int voltage);

  int SystemOff();
};

#endif
