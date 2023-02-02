#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "GIE_interface.h"

void GIE_voidEnable()
{
    SET_BIT(SREG, GENERAL_INTERRUPT);
}

void GIE_voidDisable()
{
    CLR_BIT(SREG, GENERAL_INTERRUPT);
}