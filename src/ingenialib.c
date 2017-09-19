#include "ingenialib.h"

void RobotTask(uint8_t u8Command) {
  usleep(100000); // 100 ms
}

void RobotStop(void) {
  usleep(15); // 15 us
}

void TimerInit(void) {
  struct sigaction action;
  struct itimerval timer;

  memset(&action, 0, sizeof(action));
  action.sa_handler = &TimerISR;
  sigaction(SIGALRM, &action, NULL);

  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 1000;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 1000;
  setitimer(ITIMER_REAL, &timer, NULL);
  usleep(5000); // 5 ms
}

void TimerISR(int dummy) {
  // We might want to move code out from the ISR
  pthread_mutex_unlock(&SPIBus); // SPI lock
  SPISensorEnable();
  if (SPIRead() > (uint8_t)128) {
    RobotStop();
    flagStop = 1;
  }
  SPISensorDisable();
  pthread_mutex_unlock(&SPIBus); // SPI unlock
}

uint32_t TimerGetus(void) { return 0; }

void SPIInit(void) {
  usleep(7000); // 7 ms
}

void SPIEepromEnable(void) {
  usleep(1); // 1 us
}

void SPIEepromDisable(void) {
  usleep(1); // 1 us
}

void SPISensorEnable(void) {
  usleep(1); // 1 us
}

void SPISensorDisable(void) {
  usleep(1); // 1 us
}

uint8_t SPIRead(void) {
  usleep(5); // 5 us
  int value;
  FILE *file = fopen("SPI", "r"); // Mock up
  fscanf(file, "%d", &value);
  fclose(file);
  return (uint8_t) (value & 0xFF); // For the sake of the mock up
}
