#ifndef APP_H
#define APP_H

#include "../MCAL/DIO_interface.h"
#include "../MCAL/DIO_private.h"
#include "../HAL/LCD_interface.h"
#include "../HAL/LCD_private.h"
#include "../MCAL/TIMER0_interface.h"
#include "../HAL/KPD_interface.h"

#define KPD_PORT PORTA

u8 seconds = 0, minutes = 0, flag = 0, key = NOT_PRESSED, done = 0, weight = 0, mode = 0;

u8 printDoneMessage();

void appInit();

void printInitialMessage();

void takeInput();

void calculateTime();

void printTime();

void startPopcornMode();

void startChickenMode();

void startCustomMode();

void startCooking();

#endif