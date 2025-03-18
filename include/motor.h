/**
 * @file motor.h
 * @brief Header file for the Motor class, which provides motor control functionality with encoder feedback.
 *
 * This file contains the definition of the Motor class, which encapsulates an FEHMotor and DigitalEncoder pair.
 * The Motor class provides methods to control the motor, adjust its behavior, and retrieve encoder counts.
 */
#ifndef MOTOR_H
#define MOTOR_H

#include <FEHMotor.h>
#include <FEHIO.h>

/**
 * @class Motor
 * @brief A wrapper class that combines a motor with its encoder and provides motor control functionality.
 *
 * This class encapsulates an FEHMotor and DigitalEncoder pair, allowing for motor control
 * with encoder feedback. It provides features to adjust motor behavior, such as
 * reversing direction and applying power adjustments.
 */
class Motor
{
private:
    FEHMotor motor;                  /**< The FEHMotor instance for controlling the motor */
    DigitalEncoder encoder;          /**< The DigitalEncoder for tracking motor rotation */
    DigitalEncoder encoderSecondary; /**< The secondary encoder */
    bool reversed;                   /**< Flag indicating if motor direction is reversed */
    float adjustment;                /**< Adjustment factor for motor power calibration */

public:
    /**
     * @brief Constructs a Motor object with the specified parameters
     *
     * @param motorPort The port where the motor is connected
     * @param voltage The voltage level for the motor
     * @param encoderPort The pin where the encoder is connected
     * @param encoderPortSecondary The pin where the extra encoder is connected
     * @param reversed Whether the motor direction should be reversed (default: false)
     * @param adjustment Power adjustment factor for calibration (default: 1.0)
     */
    Motor(FEHMotor::FEHMotorPort motorPort, int voltage, FEHIO::FEHIOPin encoderPort, FEHIO::FEHIOPin encoderPortSecondary, bool reversed = false, float adjustment = 1.0);

    /**
     * @brief Stops the motor and resets the encoder counts
     */
    void stopAndReset();

    /**
     * @brief Sets motor power with adjustments for motor-specific correction and voltage
     *
     * @param power The power percentage to set (-100 to 100)
     */
    void SetPercent(int power);

    /**
     * @brief Gets the total encoder counts
     *
     * @return The number of encoder counts recorded
     */
    int Counts();

    /**
     * @brief Gets the secondary encoder counts
     *
     * @return The number of encoder counts recorded
     */
    int PrimaryCounts();

    /**
     * @brief Gets the secondary encoder counts
     *
     * @return The number of encoder counts recorded
     */
    int SecondaryCounts();
};

#endif // MOTOR_H
