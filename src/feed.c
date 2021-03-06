#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"
#include "motorController.h"

#define RED_AMOUNT 1
#define GREEN_AMOUNT 2
#define BLUE_AMOUNT 3

U16 getColourFromRGB(S16 rgb[3], U8 intensityLowerBound, U8 deltaThreshold);
U8 getAmountFromSample(U16 colour);
U16 sampleColour(U32 sensorPort);

// Returns 0 if there's nothing to feed
U8 getFeedAmount() {
    U16 colour = sampleColour(PLANT_SENSOR_PORT);
    return getAmountFromSample(colour);
}

U16 sampleColour(U32 sensorPort) {
    S16 inputRGB[3];
    ecrobot_get_nxtcolorsensor_rgb(PLANT_SENSOR_PORT, inputRGB);
    return getColourFromRGB(inputRGB, 180, 100);
}

U8 getAmountFromSample(U16 colour) {
    switch (colour) {
    case NXT_COLOR_RED:
        return RED_AMOUNT;
    case NXT_COLOR_GREEN:
        return GREEN_AMOUNT;
    case NXT_COLOR_BLUE:
        return BLUE_AMOUNT;
    default:
        return 0;
    }
}

U16 getColourFromRGB(S16 rgb[3], U8 intensityLowerBound, U8 deltaThreshold) {
    if (rgb[0] > intensityLowerBound && (rgb[0] - rgb[1]) > deltaThreshold &&
        (rgb[0] - rgb[2]) > deltaThreshold) {
        return NXT_COLOR_RED;
    } else if (rgb[1] > intensityLowerBound &&
               (rgb[1] - rgb[0]) > deltaThreshold &&
               (rgb[1] - rgb[2]) > deltaThreshold) {
        return NXT_COLOR_GREEN;
    } else if (rgb[2] > intensityLowerBound &&
               (rgb[2] - rgb[0]) > deltaThreshold &&
               (rgb[2] - rgb[1]) > deltaThreshold) {
        return NXT_COLOR_BLUE;
    } else {
        return NXT_COLOR_UNKNOWN;
    }
}

void feedPills(U8 amount) {
    while (amount > 0) {
        rotateMotorByDegrees(100, 90, TRUE, ARM_MOTOR_PORT);
        amount--;
    }
}
