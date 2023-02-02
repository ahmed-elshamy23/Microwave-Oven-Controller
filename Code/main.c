#include "APP/app.h"

#define F_CPU 8000000UL

int main()
{
    appInit();
    while (1)
    {
        if (!flag)
        {
            printInitialMessage();
        }
        takeInput();
        TIMER0_voidDelay(0.1f);
        switch (key)
        {
        case '1':
            startPopcornMode();
            break;
        case '2':
            startChickenMode();
            break;
        case '3':
            startCustomMode();
            break;
        }
        if (done)
        {
            printDoneMessage();
        }
    }
}