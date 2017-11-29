#ifndef SENSOR_H
#define SENSOR_H


class Sensor
{
public:
    int samplingPeriod;
    bool calTimeNeeded; // set true if sampling period will overflow clock_t

    Sensor(int smplPrd = 1);

    Sensor(int hubSN, int port, int samplingPeriod = 1);

    ~Sensor();

    double getVoltage();

    void getSample();
};

#endif // SENSOR_H
