[-P ]

// Constructor
Drive::Drive(Motor &m1, Motor &m2, Motor &m3, float correctionFactor)
    : motor1(m1), motor2(m2), motor3(m3), kP(correctionFactor) {}

void Drive::correctDriveStraight(Motor *mot1, Motor *mot2, int targetPower)
{
    int error = mot1->Counts() - mot2->Counts();

    int correction1 = kP * error;
    int correction2 = -kP * error;

    mot1->SetPercent(targetPower + correction1);
    mot2->SetPercent(targetPower + correction2);
}

void Drive::driveDirection(float distance, Direction direction, int power)
{
    resetAll();

    Motor *mot1;
    Motor *mot2;

    // Determines which motors will be turning based on direction
    switch (direction)
    {
    case Direction::FORWARD:
        mot1 = &motor1;
        mot2 = &motor2;
        break;

    case Direction::LEFT:
        mot1 = &motor2;
        mot2 = &motor3;
        break;

    case Direction::RIGHT:
        mot1 = &motor1;
        mot2 = &motor3;
        break;

    case Direction::TURN:
        mot1 = &motor1;
        mot2 = &motor1;
        break;
    }

    // accounts for the fact that wheels are at an angle
    int targetCounts = inchesToCounts(distance) / cos(120 * M_PI / 180);

    mot1->SetPercent(power);
    mot2->SetPercent(power);

    // TODO: also add a time limit
    while ((mot1->Counts() + mot2->Counts() / 2) <= targetCounts)
    {
        correctDriveStraight(mot1, mot2, power);
    }

    resetAll();
}
