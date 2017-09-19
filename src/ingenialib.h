#ifndef INGENIALIB_H
#define INGENIALIB_H

#include <pthread.h> // Consider threads for C11 or any other sync utility
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

extern volatile int flagStop;
extern pthread_mutex_t SPIBus;
extern uint32_t intCount;

struct itimerval timer;

void delay(uint32_t us);

void RobotTask(uint8_t u8Command);
void RobotStop(void);
void TimerInit(void);
void TimerISR(int dummy);
uint32_t TimerGetus(void);
void SPIInit(void);
void SPIEepromEnable(void);
void SPIEepromDisable(void);
void SPISensorEnable(void);
void SPISensorDisable(void);
uint8_t SPIRead(void);

#endif
