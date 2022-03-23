/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_rtc_user.c
* Version      : Applilet3 for RL78/G14 V2.05.05.01 [25 Nov 2020]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for RTC module.
* Creation Date: 2022-03-23
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"
/* Start user code for include. Do not edit comment generated here */
#include "cspy-print.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern rtc_alarm_value_t myalarm;
extern unsigned int seconds_it;
extern unsigned int minutes_it;
extern unsigned int seconds_rtc;
extern unsigned int minutes_rtc;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_rtc_interrupt
* Description  : This function is INTRTC interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTRTC_vect
__interrupt static void r_rtc_interrupt(void)
{
    if (1U == WAFG)
    {
        RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;        /* clear WAFG */
        r_rtc_callback_alarm();
    }

    if (1U == RIFG)
    {
        RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;    /* clear RIFG */
        r_rtc_callback_constperiod();
    }
}

/***********************************************************************************************************************
* Function Name: r_rtc_callback_constperiod
* Description  : This function is real-time clock constant-period interrupt service handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rtc_callback_constperiod(void)
{
    /* Start user code. Do not edit comment generated here */
    if (++seconds_rtc % 60u == 0u) {
        minutes_rtc++;
        seconds_rtc = 0;
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rtc_callback_alarm
* Description  : This function is alarm interrupt service handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rtc_callback_alarm(void)
{
    /* Start user code. Do not edit comment generated here */
    //printf("RTC..%02u:%02u, IT..%02u:%02u\n", minutes_rtc, seconds_rtc, minutes_it, seconds_it);
    __no_operation();
    R_RTC_Get_AlarmValue(&myalarm);
    myalarm.alarmwm++;
    R_RTC_Set_AlarmValue(myalarm);
    cspyPrint("ALARM: %02d:%02d:00", myalarm.alarmwh, myalarm.alarmwm);
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
