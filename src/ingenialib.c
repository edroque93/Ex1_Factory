#include "ingenialib.h"

void RobotTask(uint8_t u8Command) {
	usleep(100000);
}

void RobotStop(void) {
	usleep(15);
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
  usleep(5000); // we can do better
}

void TimerISR(int dummy) { // Interrupt
	printf("interrupt\n");
	fflush(stdout);
	return;
}

uint32_t TimerGetus(void) {
	return 0;
}

void SPIInit(void) {
	usleep(7);
}

void SPIEepromEnable(void) {
	usleep(1);
}

void SPIEepromDisable(void) {
	usleep(1);
}

void SPISensorEnable(void) {
	usleep(1);
}

void SPISensorDisable(void) {
	usleep(1);
}

uint8_t SPIRead(void) {
	usleep(5);
	return 0;
}
