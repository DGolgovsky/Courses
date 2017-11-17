//containers
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <cerrno> // errno
#include <stdio.h> // sprintf
#include <cstring> // strcat
//socket
#include "fcntl.h"
#include "sys/types.h"
#include <sys/ioctl.h>
#include "sys/socket.h"
#include "netinet/in.h"
#include "unistd.h"
#include <arpa/inet.h> //addr to ip - inet_ntoa
//epoll
#include "sys/epoll.h"

#define MaxReceivedEvents 50
#define MaxMessageLength 4096

int set_nonblock(int fd)
{
  int flags;
  #if defined(O_NONBLOCK)
    if(-1 == (flags = fcntl(fd, F_GETFL, 0)))
      flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  #else
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
  #endif
}

char* getIPFromAddr(struct sockaddr_in slaveAddr){
  char * addr = inet_ntoa(slaveAddr.sin_addr);
  char port[8];
  sprintf(port, "%d", slaveAddr.sin_port);

  char* ip = new char[30];
  strcpy(ip,addr);
  strcat(ip,":");
  strcat(ip,port);
  return ip;
}

int main(int argc, char** argv)
{
  // create master socket in core OS and return file descriptor
  int masterFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // socket settings
  struct sockaddr_in sAddr;
  sAddr.sin_family = AF_INET;
  sAddr.sin_port = htons(12345);
  sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(masterFD, (struct sockaddr *)(&sAddr), sizeof(sAddr));

  // nonblock socket - do not wait all data
  // read any and continue
  set_nonblock(masterFD);

  //listen as server ip and port from settings
  listen(masterFD, SOMAXCONN);

  std::cout << "master begin listen with FD = " << masterFD << std::endl;

  // create poll in OS core and return file descriptor
  // poll for correct work with slave socket`s
  int EPollFD = epoll_create1(0);

  struct epoll_event Event;
  Event.data.fd = masterFD;
  Event.events = EPOLLIN;// catch read event, all unread data generate new event

  // register Event listener in control
  epoll_ctl(EPollFD,EPOLL_CTL_ADD,masterFD,&Event);

  std::map<unsigned int,std::string> slaveSockets;

  while (true)
  {
    struct epoll_event Events[MaxReceivedEvents];

    // receive N events
    int N = -1;
    std::cout << "begin wait event..." << std::endl;
    // if N < 0 - core signal error - repeat wait
    while(true){
      N = epoll_wait(EPollFD,Events,MaxReceivedEvents,-1);
      if (N >= 0)
        break;
    }

    std::cout << "wait terminated..." << std::endl;


    for (int i = 0; i < N; ++i)
    {
      // new connection
      if (Events[i].data.fd == masterFD){
        //slave ip
        struct sockaddr_in slaveAddr; socklen_t slaveAddrSize = sizeof(slaveAddr);

        //register new connection
        int slaveFD = accept(masterFD, (sockaddr*)&slaveAddr, &slaveAddrSize);
        set_nonblock(slaveFD);

        struct epoll_event Event;
        Event.data.fd = slaveFD;
        Event.events = EPOLLIN;// catch read event, all unread data generate new event

        // register slave Event listener in control
        epoll_ctl(EPollFD,EPOLL_CTL_ADD,slaveFD,&Event);

        char * ip = getIPFromAddr(slaveAddr);

        //save to chat list
        slaveSockets.insert(std::pair<unsigned int,std::string> (slaveFD, ip));

        std::cout << "slave connected with FD = " << slaveFD
            << " AND slAddr = " << ip // << " || "
            //<< slaveAddr.sin_addr << " || "
            //<< slaveAddr.sin_port
            << std::endl;
      } else
      // read data
      {
        auto receiver = slaveSockets.find(Events[i].data.fd);
        if (receiver == slaveSockets.end()){
          continue;
        }

        static char Buffer[MaxMessageLength];

        int reciveResult = recv(Events[i].data.fd,Buffer,MaxMessageLength,MSG_NOSIGNAL);
        //connection closed
        if ((reciveResult == 0) && (errno != EAGAIN)){
          //close connection
          shutdown(Events[i].data.fd,SHUT_RDWR);
          close(Events[i].data.fd);
          //delete from listener
          slaveSockets.erase(Events[i].data.fd);

          std::cout << "slave disconnected with FD = " << Events[i].data.fd << std::endl;
        } else
        //read data from slave
        if (reciveResult > 0){
          int authorLength = receiver->second.length() + 4;
          char* ResBuffer = new char[reciveResult + authorLength];
          strcpy(ResBuffer,receiver->second.c_str());
          strcat(ResBuffer," || ");

          std::cout << "server receive message from slave with FD = " << Events[i].data.fd
              << " || message = " << Buffer
              << " || author = " << ResBuffer
              << std::endl;

          strcat(ResBuffer,Buffer);
          
          std::cout << "resultBuffer" << ResBuffer << std::endl;

          //translate message to all listener
          for (auto it = slaveSockets.begin(); it != slaveSockets.end();++it){
            if (it->first != (unsigned int)Events[i].data.fd){
              send(it->first,ResBuffer,reciveResult + authorLength,MSG_NOSIGNAL);
            }
          }
          delete [] ResBuffer;
        }
      }
    }
  }
  return 0;
}

