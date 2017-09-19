#ifndef INGENIALIB_H
#define INGENIALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

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
