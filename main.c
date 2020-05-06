#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 

#include "motors.h"

#define STOP 0

int act = 0;
int *actPtr = &act;

void *motorThreadFunction(void *vargp){run(actPtr);}

int main() {
//    threadinf the motors function
   pthread_t thread_id;
   pthread_create(&thread_id,NULL,motorThreadFunction,(void *)&thread_id);
   
   pthread_join(thread_id,NULL);
   printf("Hello, World!");
   return 0;
}
