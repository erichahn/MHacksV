#ifndef SERIALIB_H
#define SERIALIB_H


// Used for TimeOut operations
#include <sys/time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <termios.h>
#include <string.h>
#include <iostream>
// File control definitions
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

class serialib {
public:
    serialib    ();
    ~serialib   ();

    // Open a device
    char Open(const char *Device,const unsigned int Bauds);
    // Close the current device
    void Close();
    //___________________________________________
    // ::: Read/Write operation on characters :::
    // Write a char
    char WriteChar(char);
    // Read a char (with timeout)
    char ReadChar(char *pByte,const unsigned int TimeOut_ms=0);
    //________________________________________
    // ::: Read/Write operation on strings :::
    // Write a string
    char WriteString(const char *String);
    // Read a string (with timeout)
    int ReadString(char *String, char FinalChar, unsigned int MaxNbBytes, const unsigned int TimeOut_ms = 0);
    // _____________________________________
    // ::: Read/Write operation on bytes :::
    // Write an array of bytes
    char Write(const void *Buffer, const unsigned int NbBytes);
    // Read an array of byte (with timeout)
    int Read(void *Buffer,unsigned int MaxNbBytes,const unsigned int TimeOut_ms=0);
    // _________________________
    // ::: Special operation :::
    // Empty the received buffer
    void FlushReceiver();
    // Return the number of bytes in the received buffer
    int Peek();
private:
    // Read a string (no timeout)
    int ReadStringNoTimeOut  (char *String,char FinalChar,unsigned int MaxNbBytes);

    int fd;
};
// Class TimeOut
class TimeOut {
public:
    // Constructor
    TimeOut();
    // Init the timer
    void InitTimer();
    // Return the elapsed time since initialization
    unsigned long int ElapsedTime_ms();

private:    
    struct timeval PreviousTime;
};

#endif // SERIALIB_H
