/*
**	Filename : HVSocket.cpp
**	2021-09-06
**	username : rsehgal
*/
#include "HVSocket.h"
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <string>
#include "colors.h"

HVSocket::HVSocket() {fSystemOn=false;}
HVSocket::~HVSocket() {}

HVSocket::HVSocket(std::string ipaddress, int port) : fIpAddress(ipaddress), fPort(port) {
  fSystemOn=false;
  fNumOfChannels = 16;
  Connect();
}

int HVSocket::Connect() {
  struct sockaddr_in server;

  // Create socket
  fSocket_Desc = socket(AF_INET, SOCK_STREAM, 0);
  if (fSocket_Desc == -1) {
    printf("Could not create socket");
  }

  server.sin_addr.s_addr = inet_addr(fIpAddress.c_str());
  server.sin_family = AF_INET;
  server.sin_port = htons(fPort);

  // Connect to remote server
  if (connect(fSocket_Desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    // puts("connect error");
    std::cerr << "Connect Error..." << std::endl;
    return 1;
  }

  std::cout << "Connected ...." << std::endl;
  return 0;
}

int HVSocket::DisConnect() {}

int HVSocket::Send(std::string cmd) {
  // Send some data
  // char *message = "GET / HTTP/1.1\r\n\r\n";
  cmd += "\n\Esc";
  if (send(fSocket_Desc, cmd.c_str(), cmd.length(), 0) < 0) {
    // puts("Send failed");
    std::cerr << "Send failed......." << std::endl;
    return 1;
  }
  std::cout << "Data Send...../" << std::endl;
  return 0;
}

int HVSocket::Recv() {
  char server_reply[2000];
  // Receive a reply from the server
  if (recv(fSocket_Desc, server_reply, 2000, 0) < 0) {
    std::cerr << "recv failed...." << std::endl;
    return 1;
  }

  std::cout << "Reply received........" << std::endl;
  std::cout << server_reply[2] << std::endl;

  return 0;
}

int HVSocket::SystemOnChannelsOff() { return Send("X 1"); }

int HVSocket::SystemOn() {

  int retVal = Send("X 1");
  if (!retVal) {
    fSystemOn = true;
  }
  return retVal;
}
int HVSocket::ChannelsOn() {
  // Send("X 1");
  if (fSystemOn) {
    for (unsigned int chNo = 0; chNo < fNumOfChannels; chNo++) {
      if (Send(("O " + std::to_string(chNo)).c_str()))
        std::cerr << RED << "Not able to switch on the Channel number : " << chNo << RESET << std::endl;
    }
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}

int HVSocket::ChannelsOnWithIndex(unsigned int channelIndex) {
  if (fSystemOn) {
    if (Send(("O " + std::to_string(channelIndex)).c_str()))
      std::cerr << RED << "Not able to switch on the Channel number : " << channelIndex <<  RESET
                << std::endl;
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}

int HVSocket::ChannelsOnWithCrateIndex(unsigned int crateIndex) {
  if (fSystemOn) {
    // Send("X 1");
    for (unsigned int chNo = crateIndex * fNumOfChannels; chNo < (crateIndex + 1) * fNumOfChannels; chNo++) {
      ChannelsOnWithIndex(chNo);;
    }
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}

int HVSocket::SystemOnChannelsOn() {
  unsigned int retVal = Send("X 1");
  if (retVal) {
    std::cerr << RED << "Power supply is not Switched ON, Please switch it ON first........" << RESET << std::endl;
    return 1;
  } else {
    fSystemOn = true;
    for (unsigned int chNo = 0; chNo < fNumOfChannels; chNo++) {
      if (Send(("O " + std::to_string(chNo)).c_str()))
        std::cerr << RED << "Not able to switch on channel Num : " << chNo << RESET << std::endl;
    }
    return 0;
  }
}

int HVSocket::SystemOnChannelsOn(unsigned int crateNo) {
  unsigned int retVal = Send("X 1");
  if (retVal) {
    std::cerr << RED << "Power supply is not Switched ON, Please switch it ON first........" << RESET << std::endl;
    return 1;
  } else {
    fSystemOn = true;
    ChannelsOnWithCrateIndex(crateNo);
  }
}

int HVSocket::SystemOff() {

  if (Send("X 0")) {
    std::cerr << RED << "ATTENTION !!!! : Not able to switch OFF the power supply... " << RESET << std::endl;
  } else {
    fSystemOn = false;
    std::cout << "Power Supply switched OFF... " << std::endl;
  }
}

int HVSocket::SetVoltage(unsigned int channelNum, unsigned int voltage) {
  if (fSystemOn) {
    if (Send(("S " + std::to_string(channelNum) + " " + std::to_string(voltage)).c_str())) {
      std::cerr << RED << "Not able to set voltage to Channel num : " << channelNum << RESET << std::endl;
    }
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}

int HVSocket::SetVoltage(unsigned int voltage) {
  if (fSystemOn) {
    if (Send(("A " + std::to_string(voltage)).c_str()))
      std::cerr << RED << "Not able to switch on all the channels." << RESET << std::endl;
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}

int HVSocket::ChannelsOnWithCrateIndex(std::vector<unsigned int> vecOfCrateIndex) {
  if (fSystemOn) {
    for (unsigned int crateIndex = 0; crateIndex < vecOfCrateIndex.size(); crateIndex++) {
      ChannelsOnWithCrateIndex(crateIndex);
    }
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}

int HVSocket::ChannelsOnWithIndex(std::vector<unsigned int> vecOfChannelIndex) {
  if (fSystemOn) {
    for (unsigned int channelIndex = 0; channelIndex < vecOfChannelIndex.size(); channelIndex++) {
      ChannelsOnWithIndex(channelIndex);
    }
  } else {
    std::cerr << RED << "It seems that Power supply is not switched ON, kindly switch it ON first..." << RESET
              << std::endl;
  }
}
