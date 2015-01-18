#include "SampleListener.h"
#include "leapInterface.h"

leapInterface::leapInterface()
{
	tempLeap.posX = Left;
	tempLeap.posZ = Left;
	tempLeap.grip = Nuetral;
	//human =Player (VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
			  //'z','x','c','v','b', VK_RETURN);
}

void SampleListener::onInit(const Controller& controller) {
   cout << "Initialized" <<  endl;
}

void SampleListener::onConnect(const Controller& controller) {
   cout << "Connected" <<  endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
   cout << "Disconnected" <<  endl;
}

void SampleListener::onExit(const Controller& controller) {
   cout << "Exited" <<  endl;
}

void leapInterface::doGame(myleap leap)
{
#if 0
	human.up(30, 1);
	return;
#endif
	int d = 5;
	if ( leap.grip == Nuetral )
	{
		leap = tempLeap;
	}

	if( leap.posX == Left)
	{
		cout << "LEFT ";
		human.rightOff();
		human.left(d, 1);
	}
	else if( leap.posX == Right )
	{
		cout << "Right ";
		human.leftOff();
		human.right(d, 1);

	}else{
		human.leftOff();
		human.rightOff();
	}


	if( leap.grip == Closed )
	{
		//cout << "Closed \n";
		if( leap.posZ == Forward)
		{
			cout << "Forward \n";
			human.up(d, 1);
		
		}
		else if( leap.posZ == Backward)
		{
			cout << "Backward \n";
			human.upOff();
		}
		
	}
	else if( leap.grip == Open)
	{
		cout << "Stop \n";
		human.upOff();
	}
	else
	{
		human.upOff();
		cout << "Neutral \n";
	}


}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  
  static leapInterface leap;
  myleap leap1;

  HandList hands = frame.hands();
  float x=0.0f,y=0.0f,z=0.0f, handOpen=0.0f;
  int count = 0;
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;


     string handType = hand.isLeft() ? "Left hand" : "Right hand";
    // cout << "palm position (x): " << hand.palmPosition().x <<  endl;
    // cout << "palm position (z): " << hand.palmPosition().z <<  endl;

    //Leap::Vector handSpeed = hand.palmVelocity();
	Leap::Vector handPosition = hand.palmPosition();
	//Leap::Vector handPositionZ = hand.palmPosition().z;
    // cout << "palm velocity (x): " << handSpeed.x << "\n";
    // cout << "palm velocity (z): " << handSpeed.z <<  endl;
	x += handPosition.x;
	z +=handPosition.z;
	handOpen += hand.grabStrength();
	count++;
	
  }
  x /= count;
  z /= count;
  handOpen /= count;


	leap1.grip = Nuetral;
	leap1.posX = Right;
	leap1.posZ = Forward;
    if( x < -60)
	{
	   leap1.posX = Left;
    } 
	else if ( x > 60)
	{
	   leap1.posX = Right;
    }else{
		leap1.posX = Centered;
	}
    if ( z < -20)
	{
	   leap1.posZ = Forward;
    } 
	else if ( z > 20) 
	{
	   leap1.posZ = Backward;
    }

    if ( (handOpen <= .8) && (handOpen >= 0) )
	{
	   leap1.grip = Open;
    }
	else if( (handOpen <= 1) && (handOpen >= .8) )
	{
	   leap1.grip = Closed;
    }
	else
	{
		leap1.grip = Nuetral;
	}

		if( leap1.grip != Nuetral )
	{
		leap.tempLeap = leap1;
	}
	leap.doGame(leap1);
 
}

void SampleListener::onFocusGained(const Controller& controller) {
   cout << "Focus Gained" <<  endl;
   cout << "Center hand open!" << endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
   cout << "Focus Lost" <<  endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
   cout << "Device Changed" <<  endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
     cout << "id: " << devices[i].toString() <<  endl;
     cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") <<  endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
   cout << "Service Connected" <<  endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
   cout << "Service Disconnected" <<  endl;
}