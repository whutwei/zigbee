#ifndef _HARDDRIVER_H
#define _HARDDRIVER_H

#include <stdint.h>
#include <time.h>

class HardDriver
{
  public:
  HardDriver() {}

  /*! @note How to use
   *  In order to provide platform crossable DJI onboardSDK library,
   *  we abstract this class as a hardware level.
   *
   *  @note function descriptions:
   *
   *  void init();
   *  @brief After calling this function, HardDriver should be able to
   *  read and send correctly, through a correct UART part
   *
   *  unsigned int getTimeStamp();
   *  @brief returns a TimeStamp data in unit msec.
   *  The difference between the return value of the function call two times
   *  is the excat time between them in msec.
   *
   *  size_t send(const uint8_t *buf, size_t len);
   *  @brief return sent data length.
   *
   *  size_t readall(uint8_t *buf, size_t maxlen) = 0;
   *  @brief return read data length.
   *
   *  void lockMemory();/ void freeMemory();
   *  @brief provide a mutex for multi-thread. when operating memory.
   *
   *  void lockMSG();/ void freeMSG();
   *  @brief provide a mutex for multi-thread. when operating messages.
   *
   *  void displayLog(char *buf);
   *  @brief Micro "API_LOG" invoked this function, to pass datalog.
   *  In order to pass data through different stream or channel.
   *  We abstract this virtual function for user.
   *  And different from others, this interface is not a pure virtual funcion.
   *  The default data-passing channel is stdout (printf).
   *  See also "DJI_HardDriver.cpp".
   *
   *  @attention
   *  when writting and reading data, there might have multi-thread problems.
   *  Abstract class HardDriver did not consider these issue.
   *  Please be careful when you are going to implement send and readall
   *  funtions.
   *
   *  @note
   *  we strongly suggest you to inherit this class in your own file, not just
   *  implement
   *  it in DJI_HardDriver.cpp or inside this class
   *
   * */
  public:
  virtual void init() = 0;
  virtual uint64_t getTimeStamp() = 0;
  virtual size_t send(const uint8_t *buf, size_t len) = 0;
  virtual size_t readall(uint8_t *buf, size_t maxlen) = 0;

  public:
  virtual void lockMemory() = 0;
  virtual void freeMemory() = 0;

  virtual void lockMSG() = 0;
  virtual void freeMSG() = 0;

  //public:
  //virtual void displayLog(const char *buf = 0);
};

#endif
