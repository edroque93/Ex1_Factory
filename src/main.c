// Enrique Díaz Roque
// IngeniaMC Exercise 1

#include <stdio.h>
#include <stdlib.h>

#include "ingenialib.h"

volatile int flagStop;
pthread_mutex_t SPIBus;
uint32_t intCount;

int main(void) {
#ifdef DEBUG
  printf("System startup\n");
  fflush(stdout);
#endif
  intCount = 0;
  flagStop = 0;                      // We must remain in stop until reset
  pthread_mutex_init(&SPIBus, NULL); // C POSIX mutex
  SPIInit();
  TimerInit();

  while (1) {
    pthread_mutex_lock(&SPIBus);   // SPI lock
    SPIEepromEnable();             // 1 us
    uint8_t command = SPIRead();   // 5 us
    SPIEepromDisable();            // 1 us
    pthread_mutex_unlock(&SPIBus); // SPI unlock
    if (flagStop) {
      break;
    } else {
      RobotTask(command); // 100 ms
    }
  }

  pthread_mutex_destroy(&SPIBus); // Let's be clean :)

  return 0; // ...or idle loop
}
