/**
 * \file
 * \brief     The definitions of the mq-5 sensor functionality of GAS-02.
 * \author    Wilco Louwerse
 * \author	  Bram van bergeijk
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "mq5.hh"

float Mq5::readSensor() {
    // 4096.0f is previous max value
    // 3.3f is new max value
    float analogValue = (((float)sensor.get()) / 4096.0f * 3.3f);
    return analogValue;
}

float Mq5::readSensorAverage(int quantityCounter) {
    float totalValue = 0;
    float sensorValue;
    for(int i = 0; i < quantityCounter; i++){
        do {
            sensorValue = readSensor();
        }
        while((1+meanFilter) > (sensorValue / (totalValue/quantityCounter)) && (sensorValue / (totalValue/quantityCounter)) > (1-meanFilter));
        totalValue += readSensor();
        hwlib::wait_ms(200);
    }
    return totalValue/quantityCounter;
}

int Mq5::getSensorPercentage() {
    return (int)(100 / calibrationValue * readSensorAverage(1));
}
float Mq5::getCalibrationValue(/*int quantity*/){
    int measurementQuantity = 200;
    return readSensorAverage(measurementQuantity);
}