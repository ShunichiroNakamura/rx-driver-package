/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014(2015) Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.c
* Device       : RX231
* Tool-Chain   : Renesas RXC Toolchain v2.03.00
* OS           : not use
* H/W Platform : not use
* Description  : Functions for using DTC on RX231 devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 17.03.2014 1.00    Initial revision
*         : 17.07.2014 2.00    Second  revision
*         : 12.11.2014 2.01    Added RX113.
*         : 30.01.2015 2.02    Added RX71M.
*         : 13.04.2015 2.03    Added RX231.
*         : 31.07.2017 2.08    Fixed to correspond to Renesas coding rule.
*******************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Defines for DTC support */
#include "r_dtc_rx_if.h"
#include ".\src\r_dtc_rx_private.h"

/* Check MCU Group */
#if defined(BSP_MCU_RX231)

/*******************************************************************************
Exported global variables (to be accessed by other files)
*******************************************************************************/
/* The array of all interrupt source */
const dtc_activation_source_t g_source_array[DTC_NUM_INTERRUPT_SRC] =
{
DTCE_ICU_SWINT,DTCE_CMT0_CMI0,DTCE_CMT1_CMI1,DTCE_CMT2_CMI2,DTCE_CMT3_CMI3,
DTCE_USB0_D0FIFO0,DTCE_USB0_D1FIFO0,DTCE_SDHI_SBFAI,DTCE_RSPI0_SPRI0,DTCE_RSPI0_SPTI0,
DTCE_RSCAN_COMFRXINT,DTCE_CMPB_CMPB0,DTCE_CMPB_CMPB1,DTCE_CTSU_CTSUWR,DTCE_CTSU_CTSURD,
DTCE_ICU_IRQ0,DTCE_ICU_IRQ1,DTCE_ICU_IRQ2,DTCE_ICU_IRQ3,DTCE_ICU_IRQ4,
DTCE_ICU_IRQ5,DTCE_ICU_IRQ6,DTCE_ICU_IRQ7,DTCE_S12AD_S12ADI0,DTCE_S12AD_GBADI,
DTCE_CMPB1_CMPB2,DTCE_CMPB1_CMPB3,DTCE_ELC_ELSR18I,DTCE_ELC_ELSR19I,DTCE_SSI0_SSIRXI0,
DTCE_SSI0_SSITXI0,DTCE_SECURITY_RD,DTCE_SECURITY_WR,DTCE_MTU0_TGIA0,DTCE_MTU0_TGIB0,
DTCE_MTU0_TGIC0,DTCE_MTU0_TGID0,DTCE_MTU1_TGIA1,DTCE_MTU1_TGIB1,DTCE_MTU2_TGIA2,
DTCE_MTU2_TGIB2,DTCE_MTU3_TGIA3,DTCE_MTU3_TGIB3,DTCE_MTU3_TGIC3,DTCE_MTU3_TGID3,
DTCE_MTU4_TGIA4,DTCE_MTU4_TGIB4,DTCE_MTU4_TGIC4,DTCE_MTU4_TGID4,DTCE_MTU4_TCIV4,
DTCE_MTU5_TGIU5,DTCE_MTU5_TGIV5,DTCE_MTU5_TGIW5,DTCE_TPU0_TGI0A,DTCE_TPU0_TGI0B,
DTCE_TPU0_TGI0C,DTCE_TPU0_TGI0D,DTCE_TPU1_TGI1A,DTCE_TPU1_TGI1B,DTCE_TPU2_TGI2A,
DTCE_TPU2_TGI2B,DTCE_TPU3_TGI3A,DTCE_TPU3_TGI3B,DTCE_TPU3_TGI3C,DTCE_TPU3_TGI3D,
DTCE_TPU4_TGI4A,DTCE_TPU4_TGI4B,DTCE_TPU5_TGI5A,DTCE_TPU5_TGI5B,DTCE_TMR0_CMIA0,
DTCE_TMR0_CMIB0,DTCE_TMR1_CMIA1,DTCE_TMR1_CMIB1,DTCE_TMR2_CMIA2,DTCE_TMR2_CMIB2,
DTCE_TMR3_CMIA3,DTCE_TMR3_CMIB3,DTCE_DMAC_DMAC0I,DTCE_DMAC_DMAC1I,DTCE_DMAC_DMAC2I,
DTCE_DMAC_DMAC3I,DTCE_SCI0_RXI0,DTCE_SCI0_TXI0,DTCE_SCI1_RXI1,DTCE_SCI1_TXI1,
DTCE_SCI5_RXI5,DTCE_SCI5_TXI5,DTCE_SCI6_RXI6,DTCE_SCI6_TXI6,DTCE_SCI8_RXI8,
DTCE_SCI8_TXI8,DTCE_SCI9_RXI9,DTCE_SCI9_TXI9,DTCE_SCI12_RXI12,DTCE_SCI12_TXI12,
DTCE_RIIC0_RXI0,DTCE_RIIC0_TXI0
};


#if ((0 != BSP_CFG_USER_LOCKING_ENABLED) || (bsp_lock_t != BSP_CFG_USER_LOCKING_TYPE) \
      || (DTC_ENABLE != DTC_CFG_USE_DMAC_FIT_MODULE))
/*******************************************************************************
* Function Name: r_dtc_check_DMAC_locking_byUSER
* Description  : Checks all DMAC channel locking.
* Arguments    : none -
* Return Value : true -
*                    All DMAC channels are unlocked. 
*                false -
*                    One or some DMAC channels are locked.
*
*******************************************************************************/
bool r_dtc_check_DMAC_locking_byUSER(void)
{
    bool ret = true;

    /* User has to check the locking of DMAC by themselves. */
    /* do something */

    return ret;
}
#endif


/*******************************************************************************
* Function Name: r_dtc_module_enable
* Description  : Releases module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dtc_module_enable(void)
{
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
    /* Release from module stop state. */
    MSTP(DTC) = 0;
    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    return;
}

/*******************************************************************************
* Function Name: r_dtc_module_disable
* Description  : Sets to module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dtc_module_disable(void)
{
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
    /* Set to module stop state. */
    MSTP(DTC) = 1;
    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    return;
}


#endif /* defined(BSP_MCU_RX231) */

/* End of File */

