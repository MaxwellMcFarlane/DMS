#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif

#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

#define SAMPLE_BACKUPFILE "sampleBackUp.txt"

struct Sensor{
    int hub;
    int port;
    PhidgetVoltageInputHandle ch;
    uint32_t samplingPeriod;
};

static void CCONV ssleep(int);

static void CCONV
onAttachHandler(PhidgetHandle phid, void *ctx) {
    PhidgetReturnCode res;
    int hubPort;
    int channel;
    int serial;

    if(ctx){
        struct Sensor *sen;
        sen = (struct Sensor*) ctx;
        res = PhidgetVoltageInput_setDataInterval((PhidgetVoltageInputHandle) phid, sen->samplingPeriod);
        if (res != EPHIDGET_OK) {
            fprintf(stderr, "failed to set device data interval\n");
            return;
        }
        uint32_t check = 0;
        res = PhidgetVoltageInput_getDataInterval((PhidgetVoltageInputHandle) phid, &check);
        if (res != EPHIDGET_OK) {
            fprintf(stderr, "failed to set device data interval\n");
            return;
        }
        printf("SET DI %i %i %i\n",sen->hub, sen->port, check);

        res = PhidgetVoltageInput_setVoltageChangeTrigger((PhidgetVoltageInputHandle) phid, 0);
        if (res != EPHIDGET_OK) {
            fprintf(stderr, "failed to set device voltage change trigger\n");
            return;
        }
    }

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
    // send attach to SensorManger here
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
    struct timespec tv;
    //gettimeofday(&tv, NULL);
    // use CLOCK_MONOTONIC for systems that want a time that will not be adjusted
    clock_gettime(CLOCK_REALTIME, &tv);
    unsigned long long millisecondsSinceEpoch =
            (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_nsec) / 1000000;

    int hubSN = -1;
    int hubPort = -1;
    Phidget_getDeviceSerialNumber((PhidgetHandle) ch, &hubSN);
    Phidget_getHubPort((PhidgetHandle) ch, &hubPort);

    // print to string buffer
    char msg[32]; // 32 hardcode count for below (account for '\0')
    snprintf(msg, (100*sizeof(char)), "%d %d %llu %f\n", hubSN, hubPort, millisecondsSinceEpoch, voltage);
    strcat(msg, "\0");
    strcat(ctx, msg);

    // file backup
    FILE *fp;
    fp = fopen(SAMPLE_BACKUPFILE, "a");
    fprintf(fp,"%d %d %llu %f\n", hubSN, hubPort, millisecondsSinceEpoch, voltage);
    fclose(fp);

    // print to console/terminal
    printf("%d %d %llu %f\n", hubSN, hubPort, millisecondsSinceEpoch, voltage);
}

/*
* Creates and initializes the channel.
*/
static PhidgetReturnCode CCONV
initChannel(PhidgetHandle ch, void *ctx) {
    PhidgetReturnCode res;

    res = Phidget_setOnAttachHandler(ch, onAttachHandler, ctx);
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
    * Specifies that the channel should only match a VINT hub port.
    * The only valid channel id is 0.
    *
    * The default is 0 (false), meaning VINT hub ports will never match
    */
    Phidget_setIsHubPortDevice(ch, 1);

    return (EPHIDGET_OK);
}

int main(int argc, char **argv) {

    char samples[1000];

    // use readPipe to instantiate Map Sensor Architecture
    int numbSensors = 2;
    struct Sensor map[numbSensors];
    PhidgetReturnCode res;
    const char *errs;
    for(int i = 0; i < numbSensors; i++){
        printf("%i\n", i);
        // read HUB and Port
        map[i].hub = 497194;
        map[i].port = i;
        map[i].samplingPeriod = 2000 + i * 600; // in msec
        // make ch
        res = PhidgetVoltageInput_create(&map[i].ch);
        if (res != EPHIDGET_OK) {
            fprintf(stderr, "failed to create voltage input channel\n");
            exit(1);
        }
    }

    /*
    * Enable logging to stdout
    */
    //PhidgetLog_enable(PHIDGET_LOG_INFO, NULL);

    for(int i = 0; i < numbSensors; i++){
        res = PhidgetVoltageInput_create(&map[i].ch);
        if (res != EPHIDGET_OK) {
            fprintf(stderr, "failed to create voltage input channel\n");
            exit(1);
        }
    }

    for(int i = 0; i < numbSensors; i++){
        res = initChannel((PhidgetHandle) map[i].ch, &map[i]);
        if (res != EPHIDGET_OK) {
            Phidget_getErrorDescription(res, &errs);
            fprintf(stderr, "failed to initialize channel:%s\n", errs);
            exit(1);
        }
    }

    for(int i = 0; i < numbSensors; i++){
        Phidget_setDeviceSerialNumber((PhidgetHandle) map[i].ch, map[i].hub);
        Phidget_setHubPort((PhidgetHandle) map[i].ch, map[i].port);
    }

    for(int i = 0; i < numbSensors; i++){
        res = PhidgetVoltageInput_setOnVoltageChangeHandler(map[i].ch, onVoltageChangeHandler, &samples);
        if (res != EPHIDGET_OK) {
            Phidget_getErrorDescription(res, &errs);
            fprintf(stderr, "failed to set voltage change handler: %s\n", errs);
            goto done;
        }
    }

    /*
    * Open the channel asynchronously: no waiting
    */
    for(int i = 0; i < numbSensors; i++){
        res = Phidget_open((PhidgetHandle) map[i].ch);
        if (res != EPHIDGET_OK) {
            if (res == EPHIDGET_TIMEOUT) {
                printf("Channel did not open\n");
            } else {
                Phidget_getErrorDescription(res, &errs);
                fprintf(stderr, "failed to open channel:%s\n", errs);
            }
            goto done;
        }
    }
    // give some time for sensors to attach
    ssleep(5);


    // check if channel is attached and report status
    int attached = 0;
    for(int i = 0; i < numbSensors; i++){
        res = Phidget_getAttached((PhidgetHandle) map[i].ch, &attached);
        if (res != EPHIDGET_OK) {
            if (res == EPHIDGET_TIMEOUT) {
                printf("Channel failed and error at getAttached\n");
            } else {
                Phidget_getErrorDescription(res, &errs);
                fprintf(stderr, "failed to open channel:%s\n", errs);
            }
            goto done;
        }
        if(attached){
            // report attached
        } else {
            // report detached
        }
    }

    //printf("Gathering data for 20 seconds...\n");
    //ssleep(20);
    // enter main loop
    volatile unsigned sink;
    struct timespec before, after, diff;
    clock_gettime(CLOCK_MONOTONIC, &before);
    printf("***** MAIN LOOP ***** (%i %i)\n", (long) before.tv_sec, before.tv_nsec);
    while(1){

        clock_gettime(CLOCK_MONOTONIC, &after);
        diff.tv_sec = after.tv_sec - before.tv_sec;
        diff.tv_nsec = after.tv_nsec - before.tv_nsec;
        if(((int) diff.tv_sec) > 5){
            before = after;
            clock_gettime(CLOCK_MONOTONIC, &after);
            printf("***** PUSH TO DMS ***** (%i %i)\n", (long) before.tv_sec, before.tv_nsec);
            printf("%s", samples);
            printf("***** PUSH TO DMS *****\n");
            samples[0] = "\0";

        }
    }


done:
    for(int i = 0; i < numbSensors; i++){
        Phidget_close((PhidgetHandle) map[i].ch);
        PhidgetVoltageInput_delete(&map[i].ch);
    }

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
