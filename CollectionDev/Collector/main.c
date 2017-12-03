#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif

#include <time.h>
#include <string.h>
#include <errno.h>

// includes for piping
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SAMPLEPIPE "/tmp/samplePipe"
#define SAMPLEPIPE_PORT 0666
#define SAMPLEPIPE_SETUP_MESSAGE "test"

#define SAMPLE_BACKUPFILE "sampleBackUp.txt"

static void CCONV ssleep(int);

static void CCONV
onAttachHandler(PhidgetHandle phid, void *ctx) {
    PhidgetReturnCode res;
    int hubPort;
    int channel;
    int serial;

    res = Phidget_getDeviceSerialNumber(phid, &serial);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get device serial number\n");
        return;
    }

    res = Phidget_getChannel(phid, &channel);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get channel number\n");
        return;
    }

    res = Phidget_getHubPort(phid, &hubPort);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get hub port\n");
        hubPort = -1;
    }

    if (hubPort == -1)
        printf("channel %d on device %d attached\n", channel, serial);
    else
        printf("channel %d on device %d hub port %d attached\n", channel, serial, hubPort);
}

static void CCONV
onDetachHandler(PhidgetHandle phid, void *ctx) {
    PhidgetReturnCode res;
    int hubPort;
    int channel;
    int serial;

    res = Phidget_getDeviceSerialNumber(phid, &serial);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get device serial number\n");
        return;
    }

    res = Phidget_getChannel(phid, &channel);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get channel number\n");
        return;
    }

    res = Phidget_getHubPort(phid, &hubPort);
    if (res != EPHIDGET_OK)
        hubPort = -1;

    if (hubPort != -1)
        printf("channel %d on device %d detached\n", channel, serial);
    else
        printf("channel %d on device %d hub port %d detached\n", channel, hubPort, serial);
}

static void CCONV
errorHandler(PhidgetHandle phid, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {

    fprintf(stderr, "Error: %s (%d)\n", errorString, errorCode);
}

static void CCONV
onVoltageChangeHandler(PhidgetVoltageInputHandle ch, void *ctx, double voltage) {
    clock_t start_t, end_t, total_t;
    start_t = clock();

    struct timeval tv;
    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch =
            (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_usec) / 1000;

    int hubSN = -1;
    int hubPort = -1;
    Phidget_getDeviceSerialNumber((PhidgetHandle) ch, &hubSN);
    Phidget_getHubPort((PhidgetHandle) ch, &hubPort);

    // write to samplePipe
    int samplePipeFile;
    char* samplePipe = SAMPLEPIPE;
    samplePipeFile = open(samplePipe, O_WRONLY);
    printf("Writing to pipe\n");
    char* msg = SAMPLEPIPE_SETUP_MESSAGE;
    int numBits = write(samplePipeFile, msg, sizeof(msg));
    printf("Wrote to pipe\n");
    printf("%i\n", numBits);
    // int n = close(samplePipeFile);
    // printf("%i\n", n);
    // printf("closed pipe file\n");

    FILE *fp;
    fp = fopen(SAMPLE_BACKUPFILE, "a");
    fprintf(fp,"%d %d %llu %f\n", hubSN, hubPort, millisecondsSinceEpoch, voltage);
    fclose(fp);

    // print to console/terminal
    printf("%d %d %llu %f\n", hubSN, hubPort, millisecondsSinceEpoch, voltage);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t);
}

/*
* Creates and initializes the channel.
*/
static PhidgetReturnCode CCONV
initChannel(PhidgetHandle ch) {
    PhidgetReturnCode res;

    res = Phidget_setOnAttachHandler(ch, onAttachHandler, NULL);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to assign on attach handler\n");
        return (res);
    }

    res = Phidget_setOnDetachHandler(ch, onDetachHandler, NULL);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to assign on detach handler\n");
        return (res);
    }

    res = Phidget_setOnErrorHandler(ch, errorHandler, NULL);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to assign on error handler\n");
        return (res);
    }

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
    Phidget_setDeviceSerialNumber(ch, 497194);

    /*
    * For VINT devices, this specifies the port the VINT device must be plugged into.
    *
    * The default is any port.
    */
    //Phidget_setHubPort(ch, 3);

    /*
    * Specifies that the channel should only match a VINT hub port.
    * The only valid channel id is 0.
    *
    * The default is 0 (false), meaning VINT hub ports will never match
    */
    Phidget_setIsHubPortDevice(ch, 1);

    return (EPHIDGET_OK);
}

int
main(int argc, char **argv) {
    //fprintf(fp, "This is testing for fprintf...\n");
    //fputs("This is testing for fputs...\n", fp);

    mkfifo(SAMPLEPIPE, SAMPLEPIPE_PORT);

    // write to samplePipe
    int samplePipeFile;
    char* samplePipe = SAMPLEPIPE;
    samplePipeFile = open(samplePipe, O_WRONLY);
    printf("Writing to pipe\n");
    char* msg = SAMPLEPIPE_SETUP_MESSAGE;
    int numBits = write(samplePipeFile, msg, sizeof(msg));
    printf("Wrote to pipe\n");
    printf("%i\n", numBits);
    // int n = close(samplePipeFile);
    // printf("%i\n", n);
    // printf("closed pipe file\n");

    PhidgetVoltageInputHandle ch1;
    PhidgetVoltageInputHandle ch2;
    PhidgetReturnCode res;
    const char *errs;

    /*
    * Enable logging to stdout
    */
    //PhidgetLog_enable(PHIDGET_LOG_INFO, NULL);

    res = PhidgetVoltageInput_create(&ch1);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to create voltage input channel\n");
        exit(1);
    }
    res = PhidgetVoltageInput_create(&ch2);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to create voltage input channel\n");
        exit(1);
    }

    res = initChannel((PhidgetHandle)ch1);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to initialize channel:%s\n", errs);
        exit(1);
    }
    res = initChannel((PhidgetHandle)ch2);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to initialize channel:%s\n", errs);
        exit(1);
    }

    res = PhidgetVoltageInput_setOnVoltageChangeHandler(ch1, onVoltageChangeHandler, NULL);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to set voltage change handler: %s\n", errs);
        goto done;
    }
    res = PhidgetVoltageInput_setOnVoltageChangeHandler(ch2, onVoltageChangeHandler, NULL);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to set voltage change handler: %s\n", errs);
        goto done;
    }

    Phidget_setHubPort((PhidgetHandle) ch1, 3);
    Phidget_setHubPort((PhidgetHandle) ch2, 5);

    /*
    * Open the channel synchronously: waiting a maximum of 5 seconds.
    */
    res = Phidget_openWaitForAttachment((PhidgetHandle)ch1, 5000);
    if (res != EPHIDGET_OK) {
        if (res == EPHIDGET_TIMEOUT) {
            printf("Channel did not attach after 5 seconds: please check that the device is attached\n");
        } else {
            Phidget_getErrorDescription(res, &errs);
            fprintf(stderr, "failed to open channel:%s\n", errs);
        }
        goto done;
    }
    res = Phidget_openWaitForAttachment((PhidgetHandle)ch2, 5000);
    if (res != EPHIDGET_OK) {
        if (res == EPHIDGET_TIMEOUT) {
            printf("Channel did not attach after 5 seconds: please check that the device is attached\n");
        } else {
            Phidget_getErrorDescription(res, &errs);
            fprintf(stderr, "failed to open channel:%s\n", errs);
        }
        goto done;
    }

    unsigned int* DI;
    DI = malloc(sizeof(unsigned int));
    *DI = 1000;
    res = PhidgetVoltageInput_setDataInterval(ch1, *DI);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to set DataInterval: %s\n", errs);
        goto done;
    }
    *DI = 1000;
    res = PhidgetVoltageInput_setDataInterval(ch2, *DI);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to set DataInterval: %s\n", errs);
        goto done;
    }


    printf("Gathering data for 20 seconds...\n");
    ssleep(20);

    printf("Gather data for 10 seconds with new dataInterval...\n");
    *DI = 3000;
    res = PhidgetVoltageInput_setDataInterval(ch1, *DI);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to set DataInterval: %s\n", errs);
        goto done;
    }
    *DI = 3000;
    res = PhidgetVoltageInput_setDataInterval(ch2, *DI);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to set DataInterval: %s\n", errs);
        goto done;
    }
    free(DI);
    ssleep(10);
done:
    //printf("%s", samples);

    unlink(SAMPLEPIPE);

    Phidget_close((PhidgetHandle)ch1);
    PhidgetVoltageInput_delete(&ch1);
    Phidget_close((PhidgetHandle)ch2);
    PhidgetVoltageInput_delete(&ch2);

    exit(res);
}

static void CCONV
ssleep(int tm) {
#ifdef _WIN32
    Sleep(tm * 1000);
#else
    sleep(tm);
#endif
}
