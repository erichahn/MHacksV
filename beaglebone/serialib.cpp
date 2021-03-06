 #include "serialib.h"

// Class constructor
serialib::serialib() {}

// Class desctructor
serialib::~serialib() {
    Close();
}

//_________________________________________
// ::: Configuration and initialization :::
char serialib::Open(const char *Device,const unsigned int Bauds) {
    struct termios options;                                             // Structure with the device's options

    // Open device
    fd = open(Device, O_RDWR | O_NOCTTY | O_NDELAY);                    // Open port
    if (fd == -1) return -2;                                            // If the device is not open, return -1
    fcntl(fd, F_SETFL, FNDELAY);                                        // Open the device in nonblocking mode

    // Set parameters
    tcgetattr(fd, &options);                                            // Get the current options of the port
    bzero(&options, sizeof(options));                                   // Clear all the options
    speed_t         Speed;
    switch (Bauds) {                                                     // Set the speed (Bauds)
    case 110  :     Speed=B110; break;
    case 300  :     Speed=B300; break;
    case 600  :     Speed=B600; break;
    case 1200 :     Speed=B1200; break;
    case 2400 :     Speed=B2400; break;
    case 4800 :     Speed=B4800; break;
    case 9600 :     Speed=B9600; break;
    case 19200 :    Speed=B19200; break;
    case 38400 :    Speed=B38400; break;
    case 57600 :    Speed=B57600; break;
    case 115200 :   Speed=B115200; break;
    default : return -4;
    }

    cfsetispeed(&options, Speed);                                       // Set the baud rate at 115200 bauds
    cfsetospeed(&options, Speed);
    options.c_cflag |= ( CLOCAL | CREAD |  CS8);                        // Configure the device : 8 bits, no parity, no control
    options.c_iflag |= ( IGNPAR | IGNBRK );
    options.c_cc[VTIME] = 0;                                              // Timer unused
    options.c_cc[VMIN] = 0;                                               // At least on character before satisfy reading
    tcsetattr(fd, TCSANOW, &options);                                   // Activate the settings
    return 1;                                                         // Success
}

void serialib::Close() {
    close (fd);
}
//___________________________________________
// ::: Read/Write operation on characters :::

char serialib::WriteChar(const char Byte) {
    
    if (write(fd,&Byte,1)!=1)                                           // Write the char
        return -1;                                                      // Error while writting
    return 1;                                                           // Write operation successfull
}
//________________________________________
// ::: Read/Write operation on strings :::


char serialib::WriteString(const char *String) {
    int Lenght=strlen(String);                                          // Lenght of the string
    
    if (write(fd,String,Lenght)!=Lenght)                                // Write the string
        return -1;                                                      // error while writing
    return 1;                                                           // Write operation successfull
}

// _____________________________________
// ::: Read/Write operation on bytes :::



char serialib::Write(const void *Buffer, const unsigned int NbBytes) {

    if (write (fd,Buffer,NbBytes)!=(ssize_t)NbBytes)                              // Write data
        return -1;                                                      // Error while writing
    return 1;                                                           // Write operation successfull
}



char serialib::ReadChar(char *pByte,unsigned int TimeOut_ms) {
    TimeOut         Timer;                                              // Timer used for timeout
    Timer.InitTimer();                                                  // Initialise the timer
    
    while (Timer.ElapsedTime_ms()<TimeOut_ms || TimeOut_ms==0) {        // While Timeout is not reached
        switch (read(fd,pByte,1)) {                                     // Try to read a byte on the device
            case 1  : return 1;                                             // Read successfull
            case -1 : return -2;                                            // Error while reading
        }
    }
    return 0;
}



int serialib::ReadStringNoTimeOut(char *String,char FinalChar,unsigned int MaxNbBytes) {
    unsigned int    NbBytes=0;                                          // Number of bytes read
    char            ret;                                                // Returned value from Read
    
    while (NbBytes<MaxNbBytes) {                                         // While the buffer is not full                                                                  // Read a byte with the restant time
        ret=ReadChar(&String[NbBytes]);
        
        if (ret==1) {                                                    // If a byte has been read
            
            if (String[NbBytes]==FinalChar) {                            // Check if it is the final char
                String  [++NbBytes]=0;                                  // Yes : add the end character 0
                return NbBytes;                                         // Return the number of bytes read
            }
            NbBytes++;                                                  // If not, just increase the number of bytes read
        }
        
        if (ret<0)
            return ret;                                          // Error while reading : return the error number
    }

    return -3;                                                          // Buffer is full : return -3
}

int serialib::ReadString(char *String,char FinalChar,unsigned int MaxNbBytes,unsigned int TimeOut_ms) {
    
    if (TimeOut_ms==0)
        return ReadStringNoTimeOut(String,FinalChar,MaxNbBytes);

    unsigned int    NbBytes=0;                                          // Number of bytes read
    char            ret;                                                // Returned value from Read
    TimeOut         Timer;                                              // Timer used for timeout
    long int        TimeOutParam;
    Timer.InitTimer();                                                  // Initialize the timer

    while (NbBytes<MaxNbBytes) {                                         // While the buffer is not full
                                                                        // Read a byte with the restant time
        TimeOutParam=TimeOut_ms-Timer.ElapsedTime_ms();                 // Compute the TimeOut for the call of ReadChar
        if (TimeOutParam>0) {                                             // If the parameter is higher than zero
            ret=ReadChar(&String[NbBytes],TimeOutParam);                // Wait for a byte on the serial link            

            if (ret==1) {                                                // If a byte has been read

                if (String[NbBytes]==FinalChar) {                        // Check if it is the final char
                    String  [++NbBytes]=0;                              // Yes : add the end character 0
                    return NbBytes;                                     // Return the number of bytes read
                }
                NbBytes++;                                              // If not, just increase the number of bytes read
            }
            
            if (ret<0) return ret;                                      // Error while reading : return the error number
        }
        
        if (Timer.ElapsedTime_ms()>TimeOut_ms) {                        // Timeout is reached
            String[NbBytes]=0;                                          // Add the end caracter
            return 0;                                                   // Return 0
        }
    }

    return -3;                                                          // Buffer is full : return -3
}


int serialib::Read (void *Buffer,unsigned int MaxNbBytes,unsigned int TimeOut_ms) {
    TimeOut          Timer;                                             // Timer used for timeout
    Timer.InitTimer();                                                  // Initialise the timer
    unsigned int     NbByteRead=0;

    while (Timer.ElapsedTime_ms()<TimeOut_ms || TimeOut_ms==0) {         // While Timeout is not reached
        unsigned char* Ptr=(unsigned char*)Buffer+NbByteRead;           // Compute the position of the current byte
        int Ret=read(fd,(void*)Ptr,MaxNbBytes-NbByteRead);              // Try to read a byte on the device
        if (Ret==-1) return -2;                                         // Error while reading
        if (Ret>0) {                                                    // One or several byte(s) has been read on the device
            NbByteRead+=Ret;                                            // Increase the number of read bytes
            if (NbByteRead>=MaxNbBytes)                                 // Success : bytes has been read
                return 1;
        }
    }
    return 0;                                                           // Timeout reached, return 0
}
// _________________________
// ::: Special operation :::
void serialib::FlushReceiver() {
    tcflush(fd,TCIFLUSH);
}

int serialib::Peek() {
    int Nbytes=0;
    ioctl(fd, FIONREAD, &Nbytes);
    return Nbytes;
}

// ******************************************
//  Class TimeOut
// ******************************************
// Constructor
TimeOut::TimeOut() {}

//Initialize the timer
void TimeOut::InitTimer() {
    gettimeofday(&PreviousTime, NULL);
}

//Return the elapsed time since initialization
unsigned long int TimeOut::ElapsedTime_ms() {
    struct timeval CurrentTime;
    int sec,usec;
    gettimeofday(&CurrentTime, NULL);                                   // Get current time
    sec=CurrentTime.tv_sec-PreviousTime.tv_sec;                         // Compute the number of second elapsed since last call
    usec=CurrentTime.tv_usec-PreviousTime.tv_usec;                      // Compute
    if (usec<0) {                                                       // If the previous usec is higher than the current one
        usec=1000000-PreviousTime.tv_usec+CurrentTime.tv_usec;          // Recompute the microseonds
        sec--;                                                          // Substract one second
    }
    return sec*1000+usec/1000;
}
