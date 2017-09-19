// Enrique Díaz Roque
// IngeniaMC Exercise 1

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "ingenialib.h"

volatile int flagStop = 0; // We must remain in stop until reset

int main(void) {
	SPIInit();
	TimerInit();
	
	while (1) {
		SPIEepromEnable();
		uint8_t command = SPIRead();
		SPIEepromDisable();
		if (!flagStop) RobotTask(command);
		
		// if is time to check, note we need a lock or something
		if (!flagStop) {
			SPISensorEnable();
			if (SPIRead() > (uint8_t) 128) {
					RobotStop();
					flagStop = 1;
				}
			}
			SPISensorDisable();
		}
		//
		
		usleep(10000);
	}
	
	return 0;
}
