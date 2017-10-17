/**************************************************************************//**
 * @file     sdh.h
 * @version  V1.00
 * @brief    M2351 SDH driver header file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#ifndef __SDH_H__
#define __SDH_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SDH_Driver SDH Driver
  @{
*/


/** @addtogroup SDH_EXPORTED_CONSTANTS SDH Exported Constants
  @{
*/

#define SDH_ERR_ID       0xFFFF0100UL

#define SDH_TIMEOUT      (SDH_ERR_ID|0x01UL)
#define SDH_NO_MEMORY    (SDH_ERR_ID|0x02UL)

//-- function return value
#define    Successful  0U
#define    Fail        1U

//--- define type of SD card or MMC
#define SDH_TYPE_UNKNOWN     0U
#define SDH_TYPE_SD_HIGH     1U
#define SDH_TYPE_SD_LOW      2U
#define SDH_TYPE_MMC         3U
#define SDH_TYPE_EMMC        4U

/* SD error */
#define SDH_NO_SD_CARD       (SDH_ERR_ID|0x10UL)
#define SDH_ERR_DEVICE       (SDH_ERR_ID|0x11UL)
#define SDH_INIT_TIMEOUT     (SDH_ERR_ID|0x12UL)
#define SDH_SELECT_ERROR     (SDH_ERR_ID|0x13UL)
#define SDH_WRITE_PROTECT    (SDH_ERR_ID|0x14UL)
#define SDH_INIT_ERROR       (SDH_ERR_ID|0x15UL)
#define SDH_CRC7_ERROR       (SDH_ERR_ID|0x16UL)
#define SDH_CRC16_ERROR      (SDH_ERR_ID|0x17UL)
#define SDH_CRC_ERROR        (SDH_ERR_ID|0x18UL)
#define SDH_CMD8_ERROR       (SDH_ERR_ID|0x19UL)

#define MMC_FREQ        20000   /*!< output 20MHz to MMC  \hideinitializer */
#define SD_FREQ         25000   /*!< output 25MHz to SD  \hideinitializer */
#define SDHC_FREQ       50000   /*!< output 50MHz to SDH \hideinitializer */

#define    CardDetect_From_GPIO  (1 << 8)   /*!< Card detection pin is GPIO \hideinitializer */
#define    CardDetect_From_DAT3  (1 << 9)   /*!< Card detection pin is DAT3 \hideinitializer */

/*@}*/ /* end of group SDH_EXPORTED_CONSTANTS */

/** @addtogroup SDH_EXPORTED_TYPEDEF SDH Exported Type Defines
  @{
*/
typedef struct SDH_info_t
{
    unsigned int    CardType;       /*!< SDHC, SD, or MMC */
    unsigned int    RCA;            /*!< relative card address */
    unsigned char   IsCardInsert;   /*!< card insert state */
    unsigned int    totalSectorN;   /*!< total sector number */
    unsigned int    diskSize;       /*!< disk size in Kbytes */
    int             sectorSize;     /*!< sector size in bytes */
} SDH_INFO_T;

/*@}*/ /* end of group SDH_EXPORTED_TYPEDEF */

/// @cond HIDDEN_SYMBOLS
extern SDH_INFO_T SD0;
/// @endcond HIDDEN_SYMBOLS

/** @addtogroup SDH_EXPORTED_FUNCTIONS SDH Exported Functions
  @{
*/

/**
 *  @brief    Enable specified interrupt.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTEN_BLKDIEN_Msk / \ref SDH_INTEN_CRCIEN_Msk / \ref SDH_INTEN_CDIEN0_Msk / \ref SDH_INTEN_CDIEN1_Msk /
 *                           \ref SDH_INTEN_CDSRC0_Msk / \ref SDH_INTEN_CDSRC1_Msk / \ref SDH_INTEN_RTOIEN_Msk / \ref SDH_INTEN_DITOIEN_Msk /
 *                           \ref SDH_INTEN_WKIEN_Msk
 *
 *  @return   None.
 * \hideinitializer
 */
#define SDH_ENABLE_INT(sdh, u32IntMask)    (sdh->INTEN |= (u32IntMask))

/**
 *  @brief    Disable specified interrupt.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTEN_BLKDIEN_Msk / \ref SDH_INTEN_CRCIEN_Msk / \ref SDH_INTEN_CDIEN0_Msk / \ref SDH_INTEN_CDIEN1_Msk /
 *                           \ref SDH_INTEN_RTOIEN_Msk / \ref SDH_INTEN_DITOIEN_Msk / \ref SDH_INTEN_WKIEN_Msk / \ref SDH_INTEN_CDSRC0_Msk /
 *                           \ref SDH_INTEN_CDSRC1_Msk
 *
 *  @return   None.
 * \hideinitializer
 */
#define SDH_DISABLE_INT(sdh, u32IntMask)    (sdh->INTEN &= ~(u32IntMask))

/**
 *  @brief    Get specified interrupt flag/status.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTSTS_BLKDIF_Msk / \ref SDH_INTSTS_CRCIF_Msk / \ref SDH_INTSTS_CRC7_Msk /
 *                           \ref SDH_INTSTS_CRC16_Msk / \ref SDH_INTSTS_CRCSTS_Msk / \ref SDH_INTSTS_DAT0STS_Msk /
 *                           \ref SDH_INTSTS_CDIF0_Msk / \ref SDH_INTSTS_CDIF1_Msk / \ref SDH_INTSTS_RTOIF_Msk /
 *                           \ref SDH_INTSTS_DITOIF_Msk / \ref SDH_INTSTS_CDSTS0_Msk / \ref SDH_INTSTS_CDSTS1_Msk /
 *                           \ref SDH_INTSTS_DAT1STS_Msk
 *
 *
 *  @return  0 = The specified interrupt is not happened.
 *           1 = The specified interrupt is happened.
 * \hideinitializer
 */
#define SDH_GET_INT_FLAG(sdh, u32IntMask) ((sdh->INTSTS & (u32IntMask))?1:0)


/**
 *  @brief    Clear specified interrupt flag/status.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTSTS_BLKDIF_Msk / \ref SDH_INTSTS_CRCIF_Msk / \ref SDH_INTSTS_CDIF0_Msk /
 *                           \ref SDH_INTSTS_CDIF1_Msk / \ref SDH_INTSTS_RTOIF_Msk / \ref SDH_INTSTS_DITOIF_Msk
 *
 *
 *  @return   None.
 * \hideinitializer
 */
#define SDH_CLR_INT_FLAG(sdh, u32IntMask) (sdh->INTSTS = u32IntMask)


/**
 *  @brief    Check SD Card inserted or removed.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *
 *  @return   1: Card inserted.
 *            0: Card removed.
 * \hideinitializer
 */
#define SDH_IS_CARD_PRESENT(sdh) ((sdh == SDH0)? SD0.IsCardInsert : 0)

/**
 *  @brief    Get SD Card capacity.
 *
 *  @param[in]    sdh    The pointer of the specified SDH module.
 *
 *  @return   SD Card capacity. (unit: KByte)
 * \hideinitializer
 */
#define SDH_GET_CARD_CAPACITY(sdh)  ((sdh == SDH0)? SD0.diskSize : 0)


void SDH_Open(SDH_T *sdh, uint32_t u32CardDetSrc);
uint32_t SDH_Probe(SDH_T *sdh);
uint32_t SDH_Read(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount);
uint32_t SDH_Write(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount);

unsigned int SDH_CardDetection(SDH_T *sdh);
void SDH_Open_Disk(SDH_T *sdh, unsigned int u32CardDetSrc);
void SDH_Close_Disk(SDH_T *sdh);

/*@}*/ /* end of group SDH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SDH_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  //end of __SDH_H__
/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/