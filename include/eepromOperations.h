#ifndef _EEPROM_OPERATIONS_H_
#define _EEPROM_OPERATIONS_H_

#include <EEPROM.h>
#include <string.h>
#include "softwareVersion.h"

#define COMPANY_NAME                            "MOONMACH"
#define SIZE_OF_COMPANY_NAME                    8
#define EEPROM_START_ADDRESS                    0
#define EEPROM_END_ADDRESS                      0x0FFF
#define EEPROM_HEADER_START_ADDRESS             EEPROM_START_ADDRESS
#define EEPROM_COMPANY_NAME_ADDRESS             EEPROM_HEADER_START_ADDRESS
#define EEPROM_MAJOR_VERSION_ADDRESS            EEPROM_HEADER_START_ADDRESS + SIZE_OF_COMPANY_NAME
#define EEPROM_MINOR_VERSION_ADDRESS            EEPROM_MAJOR_VERSION_ADDRESS + 1
#define EEPROM_PATCH_VERSION_ADDRESS            EEPROM_MINOR_VERSION_ADDRESS + 1
#define EEPROM_DAY_ADDRESS                      EEPROM_PATCH_VERSION_ADDRESS + 1
#define EEPROM_MONTH_ADDRESS                    EEPROM_DAY_ADDRESS + 1
#define EEPROM_YEAR_ADDRESS                     EEPROM_MONTH_ADDRESS + 1
#define EEPROM_ERROR_COUNT_ADDRESS              EEPROM_YEAR_ADDRESS + 1
#define EEPROM_CRC16_ADDRESS                    EEPROM_ERROR_COUNT_ADDRESS + 2

#define EEPROM_ERROR_SECTOR_START_ADDRESS       (sizeof(EepromHeader_t))

typedef struct 
{
    uint8_t errorID;
    uint8_t errorSource;
}Error_t;

typedef struct 
{
    uint8_t character[SIZE_OF_COMPANY_NAME];
}CompanyName_t;

typedef struct 
{
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
}Version_t;

typedef struct 
{
    uint8_t day;
    uint8_t month;
    uint8_t year;
}Date_t;

typedef struct
{
    CompanyName_t companyName;
    Version_t version;
    Date_t date;
    uint16_t errorCount;
    uint16_t CRC16;
}EepromHeader_t;

/**
 * @brief 
 * 
 */
void InitializeEEPROM(void);

/**
 * @brief 
 * 
 */
void ErrorHistoryClear(void);

/**
 * @brief 
 * 
 * @param error 
 */
void LogError(Error_t error);

/**
 * @brief Get the Company Name object
 * 
 * @return CompanyName_t 
 */
CompanyName_t GetCompanyName(void);
/**
 * @brief Get the Software Version object
 * 
 * @return Version_t 
 */
Version_t GetSoftwareVersion(void);

/**
 * @brief Get the Software Update Date object
 * 
 * @return Date_t 
 */
Date_t GetSoftwareUpdateDate(void);

/**
 * @brief Get the Error Count object
 * 
 * @return uint16_t 
 */
uint16_t GetErrorCount(void);

/**
 * @brief Get the Error object
 * 
 * @param errorNo 
 * @return Error_t 
 */
Error_t GetError(uint16_t errorNo);

#endif /* _EEPROM_OPERATIONS_H_ */