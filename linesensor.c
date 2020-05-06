#include "linesensor.h"
int LEFT = 0;
int MID = 0;
int RIGT = 0;

void setup_line_sensors(int lft, int mid, int rght)
{
    if (wiringPiSetup() < 0)
    {
        printf("wiringPiSetUp failed");
    }
    pinMode(lft, INPUT);
    pinMode(mid, INPUT);
    pinMode(rght, INPUT);
    LEFT = lft;
    MID = mid;
    RIGT = rght;
}

int line_sensor_loop(int *action)
{
    // while
    // {
        if (digitalRead(LEFT) == LOW && digitalRead(MID) == LOW && digitalRead(RIGT) == LOW)
        {
            *action = 0;
        }
        if (digitalRead(LEFT) == LOW && digitalRead(MID) == HIGH && digitalRead(RIGT) == LOW)
        {
            *action = 1;
        }

        if (digitalRead(LEFT) == LOW && digitalRead(MID) == LOW && digitalRead(RIGT) == HIGH)
        {
            *action = 3;
        }
        if (digitalRead(LEFT) == HIGH && digitalRead(MID) == LOW && digitalRead(RIGT) == LOW)
        {
            *action = 2;
        }
    // }

    return -1;
}