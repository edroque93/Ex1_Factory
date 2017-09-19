#include "ingenialib.h"

// Assume all other code time is 0 us.

void delay(uint32_t us) {
  struct timeval tv;
  unsigned long start, end;
  gettimeofday(&tv, NULL);
  start = 1000000 * tv.tv_sec + tv.tv_usec;
  end = start;
  while ((end - start) < us) {
    gettimeofday(&tv, NULL);
    end = 1000000 * tv.tv_sec + tv.tv_usec;
  }
}

void RobotTask(uint8_t u8Command) {
#ifdef DEBUG
  printf("%d: Robot command start\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(100000); // 100 ms
#ifdef DEBUG
  if (!flagStop) { // RobotStop already called, no need to print this
    printf("%d: Robot command end\n", TimerGetus() / 1000);
    fflush(stdout);
  }
#endif
}

void RobotStop(void) {
#ifdef DEBUG
  printf("%d: Robot stop\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(15); // 15 us
}

void TimerInit(void) {
  struct sigaction action;

  memset(&action, 0, sizeof(action));
  action.sa_handler = &TimerISR;
  sigaction(SIGALRM, &action, NULL);

  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 1000;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 1000;
  setitimer(ITIMER_REAL, &timer, NULL);
  delay(5000); // 5 ms
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
  intCount++;
  pthread_mutex_unlock(&SPIBus); // SPI unlock
}

uint32_t TimerGetus(void) { return intCount * 1000 + timer.it_value.tv_usec; }

void SPIInit(void) {
  delay(7000); // 7 ms
}

void SPIEepromEnable(void) {
#ifdef DEBUG
  printf("%d: SPI enable EEPROM\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(1); // 1 us
}

void SPIEepromDisable(void) {
#ifdef DEBUG
  printf("%d: SPI disable EEPROM\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(1); // 1 us
}

void SPISensorEnable(void) {
#ifdef DEBUG
  printf("%d: SPI enable sensor\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(1); // 1 us
}

void SPISensorDisable(void) {
#ifdef DEBUG
  printf("%d: SPI disable sensor\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(1); // 1 us
}

uint8_t SPIRead(void) {
#ifdef DEBUG
  printf("%d: SPI data read\n", TimerGetus() / 1000);
  fflush(stdout);
#endif
  delay(5); // 5 us
  int value;
  FILE *file = fopen("SPI", "r"); // Mock up
  fscanf(file, "%d", &value);
  fclose(file);
  return (uint8_t)(value & 0xFF); // For the sake of the mock up
}
