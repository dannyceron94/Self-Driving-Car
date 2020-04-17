/**************************************************************             
* sources: https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c
*          https://github.com/sbcshop/MotorShield/blob/master/PiMotor.py
**************************************************************/
// resources:
// 
#include "motors.h"
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
// struct for each motor configurations
struct config
{
    int e;
    int f;
    int r;
};
// struct for storing the data of the each motor.
// name, modulation pin, and output pins for making the motors run.
struct motor
{
    char motor[6];
    struct config config1;
    struct config config2;
    
    int arrow;
};
//  arrowpins={1:33,2:35,3:37,4:36}

// motor variable initialization
                     // pins 11,15,13,11,13,15,4
struct motor motor1 = {"motor1",0,3,2,0,2,3,27};
struct motor *motor1Ptr = &motor1;

struct motor motor2 = {"motor2",6,4,5,6,5,4,0};
struct motor *motor2Ptr = &motor2;

struct motor motor3 = {"motor3",12,13,14,12,14,13,0};
struct motor *motor3Ptr = &motor3;

struct motor motor4 = {"motor4",26,10,11,26,11,10,3};
struct motor *motor4Ptr = &motor4;


// int init(char[6],char[7]);
// int initHelper(struct motor *, char[7]);
// int foward(struct motor *,int,char[7]);
// int reverse(struct motor *,int,char[7]);
// int stop(struct motor *, char[7]);



// params motor name, motor configuration
// it calls the initHelper function to set up the pins for the motor being initialized 
int init(char motor[6],char config[7]){
    int check =-1;
    if( motor == NULL ||  config == NULL ||(strcmp(motor,"")==0) || (strcmp(config,"")==0)){
        printf("invalid input, ");
        printf("%s motor: ",motor);
        printf("%s config: ",config);
    }
    else if(strcmp(motor,"motor1") == 0){
        check = initHelper(&motor1,config);
    }
    else if(strcmp(motor,"motor2") == 0){ 
        check = initHelper(&motor2,config);
    }
    else if(strcmp(motor,"motor3") == 0){
        check = initHelper(&motor3,config);
    }
    else if(strcmp(motor,"motor4") == 0){
        check = initHelper(&motor4,config);
    }
    return check;
    
    
}
// params: pointer to the motor being initialized, configuration of the motor
// it configures the pins the motor will use.
int initHelper(struct motor *mot, char config[7]){
    if(wiringPiSetup()<0){

        printf("WiringPiSetUp failed");
        return-1;
    }
    // configuration 1
    // using pointer type 1
    if(strcmp(config,"config1")==0){
        int e = (*mot).config1.e;
        int f = (*mot).config1.f;
        int r = (*mot).config1.r;
        // set the pins
        printf("e= %d,f= %d,r=%d",e,f,r);
        pinMode((*mot).config1.e,OUTPUT);
        pinMode((*mot).config1.f,OUTPUT);
        pinMode((*mot).config1.r,OUTPUT);
        softPwmCreate((*mot).config1.e,0,100);//set PWM channal with range
        softPwmWrite((*mot).config1.e,0);

        // PinMode((*mot).config1.e,PWM_OUTPUT);
        // pwmWrite((*mot).config.e,0)
        softPwmWrite((*mot).config1.e,0);
        digitalWrite((*mot).config1.f,LOW);
        digitalWrite((*mot).config1.r,LOW);
        return 0;
    }
    // configuration 2
    // using pointer type 2
    if(strcmp(config,"config2")==0){
        int e = mot->config2.e;
        int f = mot->config2.f;
        int r = mot->config2.r;
        // set the pins
        printf("e= %d,f= %d,r=%d",e,f,r);
        // setting pins
        pinMode(mot->config1.e,OUTPUT);
        pinMode(mot->config1.f,OUTPUT);
        pinMode(mot->config1.r,OUTPUT);
        softPwmCreate(mot->config1.e,0,100);//set PWM channal with range

        // PinMode(mot->config1.e,PWM_OUTPUT);
        // pwmWrite(mot->config.e,0)
        softPwmWrite(mot->config2.e,0);
        digitalWrite(mot->config2.f,LOW);
        digitalWrite(mot->config2.r,LOW);
        return 0;
    }
    else{printf("invalid config");}
    return -1;

}
// params: struc motor pointer, int speed value, string motor configuration.
// sets the configuration pins to high voltage and the pin module to the speed value.
int foward(struct motor *mot, int speed,char config[7]){
    // pwmWrite(mot->config.e,speed)
    if(strcmp(config,"config1")){
        softPwmWrite(mot->config1.e,speed);
        digitalWrite(mot->config1.f,HIGH);
        digitalWrite(mot->config1.r,LOW);
        return 0;
    }
    if(strcmp(config,"config2")){
        softPwmWrite(mot->config2.e,speed);
        digitalWrite(mot->config2.f,HIGH);
        digitalWrite(mot->config2.r,LOW);
        return 0;
    }
    return -1;
}
// params: struc motor pointer, int speed value, string motor configuration.
// sets the configuration pins to high voltage and the pin module to the speed value.
int reverse(struct motor *mot,int speed,char config[7]){
    if(strcmp(config,"config1")){
        softPwmWrite(mot->config1.e,speed);
        digitalWrite(mot->config1.f,LOW);
        digitalWrite(mot->config1.r,HIGH);
        return 0;
    }
    if(strcmp(config,"config2")){
        softPwmWrite(mot->config2.e,speed);
        digitalWrite(mot->config2.f,LOW);
        digitalWrite(mot->config2.r,HIGH);
        return 0;
    }
    return -1;
}
// params: struc motor pointer, int speed value, string motor configuration.
// sets the configuration pins to 0 voltage and the pin module to 0.
int stop(struct motor *mot,char config[7]){
    // pwmWrite(mot->config.e,speed)
    if(strcmp(config,"config1")){
        softPwmWrite(mot->config1.e,0);
        digitalWrite(mot->config1.f,LOW);
        digitalWrite(mot->config1.r,LOW);
        return 0;
    }
    if(strcmp(config,"config2")){
        softPwmWrite(mot->config2.e,0);
        digitalWrite(mot->config2.f,LOW);
        digitalWrite(mot->config2.r,LOW);
        return 0;
    }
    return -1;

}

int run(int val){
    // int temp = 4
    int m1 = init("motor1","config1");
    printf("check = %d\n",m1);
    int m2 = init("motor2","config2");
    printf("check = %d\n",m2);
    for(int i=0;i<=val;i++){
        
        if(i ==1){
            printf("↑\nforward\n");
            m1 = foward(&motor1,25*i,"config1");
            m2 = foward(&motor2,25*i,"config2");
            
            sleep(5);
            m1 = stop(&motor1,"config1");
            m2 = stop(&motor2,"config2");
            printf("\nstop\n");
            sleep(2);
            }
        if(i ==2){
            printf("↓\nreverse\n");
            m1 = reverse(&motor1,10*i,"config1");
            m2 = reverse(&motor2,10*i,"config2");
            
            sleep(5);
            printf("\nstop\n");
            m1 = stop(&motor1,"config1");
            m2 = stop(&motor2,"config2");
            sleep(2);
            }
        if(i ==3){
            //turn left
            printf("←\nleft\n");
            m1 = foward(&motor1,10*i,"config1");
            m2 = reverse(&motor2,10*i,"config2");
            
            sleep(5);
            printf("\nstop\n");
            m1 = stop(&motor1,"config1");
            m2 = stop(&motor2,"config2");
            sleep(2);
            }
            if(i ==4){
            //turn right
            printf("→\nright\n");
            m1 = reverse(&motor1,10*i,"config1");
            m2 = foward(&motor2,10*i,"config2");
            
            sleep(5);
            printf("\nstop\n");
            m1 = stop(&motor1,"config1");
            m2 = stop(&motor2,"config2");
            sleep(2);
            }
        }
    return 0;
}