#ifndef SAMPLELISTENER_H
#define SAMPLELISTENER_H

#include <iostream>
#include <string.h>
#include "Leap.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
	  Leap::Vector handCenter;
	  bool centered;
	  bool left;
	  bool forward;
	  bool open;
};

#endif