// This file will read from the slider phidget and print it

#include <stdio.h>
#include <stdlib.h>
#include <phidget22.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif

/*int main(){
    PhidgetVoltageInputHandle ch;
    PhidgetReturnCode res;
    res = PhidgetVoltageInput_create(&ch);
    PhidgetVoltageInput_delete(&ch);
*/

// Define the attach handler function
  void CCONV
  onAttachedEventHandler(PhidgetHandle channel, void *userPtr) {
      printf("A channel has been attached\n");
      // Do things after attachment (i.e. read data, control the device)
  }

  int
  main(int argc, char **argv) {
    // .....Then, in the main code create the channel and set the attach handler:
    PhidgetVoltageInputHandle slider;
    PhidgetVoltageInput_create(&slider);
    Phidget_setIsHubPortDevice((PhidgetHandle) slider, 1);
    Phidget_setOnAttachHandler((PhidgetHandle)slider, onAttachedEventHandler, NULL);
 
    // other stuff in main
printf("Press Any Key to Continue\n");  
getchar(); 
  }

//}
