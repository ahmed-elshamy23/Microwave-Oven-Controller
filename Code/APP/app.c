#include "../MCAL/DIO_interface.h"
#include "../MCAL/DIO_private.h"
#include "../HAL/LCD_interface.h"
#include "../HAL/LCD_private.h"
#include "../MCAL/TIMER0_interface.h"
#include "../HAL/KPD_interface.h"
#include "app.h"

u8 printDoneMessage()
{
    LCD_voidSendCommand(clearDisplay);
    LCD_voidSendString((u8 *)"        Done!");
    return 0;
}

void appInit()
{
    LCD_voidInit();
    LCD_voidSendCommand(cursorBlinkOff);
    TIMER0_voidInit();
    KPD_voidInit(KPD_PORT);
}

void printInitialMessage()
{
    LCD_voidSendString((u8 *)"Select mode: ");
    flag++;
}

void takeInput()
{
    do
    {
        key = KPD_u8GetPressedKey(KPD_PORT);
        if (key != NOT_PRESSED)
            LCD_voidSendChar(key);
    } while (key == NOT_PRESSED);
}

void calculateTime()
{
    weight = key - '0';
    if (weight & 1)
    {
        seconds = 30;
    }
    minutes = 0.5f * weight;
}

void printTime()
{
    LCD_voidSetCursorPosition(1, 0);
    LCD_voidSendNumber(minutes / 10);
    LCD_voidSendNumber(minutes % 10);
    LCD_voidSendChar(':');
    LCD_voidSendNumber(seconds / 10);
    LCD_voidSendNumber(seconds % 10);
}

void startPopcornMode()
{
    minutes = 1;
    LCD_voidSendCommand(cursorOff);
    LCD_voidSendCommand(clearDisplay);
    LCD_voidSendString((u8 *)"Popcorn mode:");
    LCD_voidSetCursorPosition(1, 0);
    printTime();
    startCooking();
}

void startChickenMode()
{
    LCD_voidSendCommand(clearDisplay);
    if (flag == 1)
    {
        LCD_voidSendString((u8 *)"Chicken weight: ");
        flag++;
    }
    key = NOT_PRESSED;
    takeInput();
    LCD_voidSendCommand(cursorOff);
    TIMER0_voidDelay(0.1f);
    calculateTime();
    LCD_voidSendCommand(clearDisplay);
    LCD_voidSendString((u8 *)"Cooking ");
    LCD_voidSendNumber(weight);
    LCD_voidSendString((u8 *)" kilo(s):");
    startCooking();
}

void startCustomMode()
{
    LCD_voidSendCommand(clearDisplay);
    if (flag == 1)
    {
        LCD_voidSendString((u8 *)"Cooking time: ");
        LCD_voidSetCursorPosition(1, 0);
        LCD_voidSendString((u8 *)"00:00");
        LCD_voidSetCursorPosition(1, 0);
        flag++;
    }
    key = NOT_PRESSED;
    do
    {
        key = KPD_u8GetPressedKey(KPD_PORT);
        if (key != NOT_PRESSED)
        {
            switch (flag)
            {
            case 2:
                minutes += 10 * (key - '0');
                break;
            case 3:
                minutes += key - '0';
                break;
            case 4:
                seconds += 10 * (key - '0');
                break;
            case 5:
                seconds += key - '0';
                break;
            }
            LCD_voidSendChar(key);
            flag++;
            if (flag == 4)
                LCD_voidSetCursorPosition(1, 3);
        }
    } while (flag < 6);
    LCD_voidSendCommand(cursorOff);
    LCD_voidSendCommand(clearDisplay);
    if (flag == 6)
    {
        LCD_voidSendString((u8 *)"Custom mode:");
        LCD_voidSetCursorPosition(0, 1);
        flag++;
    }
    TIMER0_voidDelay(0.1f);
    startCooking();
}

void startCooking()
{
    while (1)
    {
        TIMER0_voidDelay(1);
        if (!seconds)
        {
            if (minutes)
            {
                seconds = 59;
                minutes--;
            }
            else
                break;
        }
        else
            seconds--;
        printTime();
        done = 1;
    }
}