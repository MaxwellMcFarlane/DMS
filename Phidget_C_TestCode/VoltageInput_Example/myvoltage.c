#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif

int main(int argc, char **argv) {
	PhidgetVoltageInputHandle ch;
	PhidgetReturnCode res;
	const char *errs;

	/*
	* Enable logging to stdout
	*/
	//PhidgetLog_enable(PHIDGET_LOG_INFO, NULL);

	res = PhidgetVoltageInput_create(&ch);
	
	/*
	* Please review the Phidget22 channel matching documentation for details on the device
	* and class architecture of Phidget22, and how channels are matched to device features.
	*/

	/*
	* Specifies the serial number of the device to attach to.
	* For VINT devices, this is the hub serial number.
	*
	* The default is any device.
	*/
	Phidget_setDeviceSerialNumber((PhidgetHandle)ch, 497194); 

	/*
	* For VINT devices, this specifies the port the VINT device must be plugged into.
	*
	* The default is any port.
	*/
	Phidget_setHubPort((PhidgetHandle)ch, 3);

	/*
	* Specifies that the channel should only match a VINT hub port.
	* The only valid channel id is 0.
	*
	* The default is 0 (false), meaning VINT hub ports will never match
	*/
	Phidget_setIsHubPortDevice((PhidgetHandle)ch, 1);

	/*
	* Specifies which channel to attach to.  It is important that the channel of
	* the device is the same class as the channel that is being opened.
	*
	* The default is any channel.
	*/
	// Phidget_setChannel(ch, 0);
	
	/*
	* Open the channel synchronously: waiting a maximum of 5 seconds.
	*/
	res = Phidget_openWaitForAttachment((PhidgetHandle)ch, 5000);
	if (res != EPHIDGET_OK) {
		if (res == EPHIDGET_TIMEOUT) {
			printf("Channel did not attach after 5 seconds: please check that the device is attached\n");
		} exit(1);
	}
	double val = 1.0;
	printf("Value: %.2f \n", val);	
	for(int i = 0; i < 100; i++){
		res = PhidgetVoltageInput_getVoltage(ch,&val);
		printf("Value: %.2f \n", val);
		if (res != EPHIDGET_OK) {
			Phidget_getErrorDescription(res, &errs);
			fprintf(stderr, "read error: %s\n", errs);
		}
		sleep(1); // originall Sleep(500) for windows		
	}
	Phidget_close((PhidgetHandle)ch);
	PhidgetVoltageInput_delete(&ch);
}
