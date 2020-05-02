#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include "DistanceSensor.h"

int triggerPin, echoPin;

void InitDistanceSensor(int trigger, int echo) {
	triggerPin = trigger;
	echoPin = echo;

	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
}

double MeasureDistance() {
	clock_t start, end, time;
	double distance;
	printf("Measuring Distance");
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	while(digitalRead(echoPin) == 1) {
		start = clock();
	}
	end = clock();

	time = start- end;

	distance = (time*340)/2.0;

	return distance*.01;
}

void avoidObstacle(int * action) {
    if(MeasureDistance() <= 20) {
        *action = 0;
        sleep(3);
        if(MeasureDistance() <= 20) {
            while(digitalRead(OBSTACLESENSOR) == 1) {
                *action = 3;
            }
            *action = 0;
        }
        while(digitalRead(OBSTACLESENSOR) == 0) {
            *action = 1;
        }
        *action = 0;
        while(digitalRead(OBSTACLESENSOR) == 1) {
            *action = 2;
        }
        *action = 0;
    }
}
