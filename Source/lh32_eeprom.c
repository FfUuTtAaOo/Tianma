#include "lh32_eeprom.h"

/* Global Variable -----------------------------------------------------------*/
EEPROM_HandleTypeDef hEEPROM;

void eeprom_init(void)
{
    hEEPROM.Init.Device_ID = 0x01;
    hEEPROM.Init.PageA = FLASH_PAGE_28;
    hEEPROM.Init.PageB = FLASH_PAGE_29;
    if (LHL_EEPROM_Init(&hEEPROM) != LHL_OK)
    {
        while(1);                                               // FLASH????
    }
}
