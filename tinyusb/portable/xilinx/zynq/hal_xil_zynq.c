/**************************************************************************/
/*!
    @file     hal_xil_zynq.c
    @author   hathach

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2018, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "tusb_option.h"

#if CFG_TUSB_MCU == OPT_MCU_XIL_ZYNQPS

#include <stdbool.h>

#include "tusb_hal.h"

#include "xparameters.h"
#include "xtime_l.h"

#define COUNTS_PER_SECOND (XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)

#if CFG_TUSB_OS == OPT_OS_NONE
// Only required to implement if using No RTOS (osal_none)
uint32_t tusb_hal_millis(void)
{
    XTime t;
    XTime_GetTime(&t);
    return t / (COUNTS_PER_SECOND / 1000000);
}
#endif
/*------------------------------------------------------------------*/
/* MACRO TYPEDEF CONSTANT ENUM
 *------------------------------------------------------------------*/

//#define USB_NVIC_PRIO   7

/*------------------------------------------------------------------*/
/* FUNCTION DECLARATION
 *------------------------------------------------------------------*/
//void power_usb_event_handler(uint32_t event);

// check if SD is present and enabled
static bool is_sd_enabled(void)
{
  uint8_t sd_en = false;

  return sd_en;
}


bool tusb_hal_init(void)
{
    return true;
}

void tusb_hal_int_enable(uint8_t rhport)
{
  (void) rhport;
  //NVIC_EnableIRQ(USBD_IRQn);
}

void tusb_hal_int_disable(uint8_t rhport)
{
  (void) rhport;
  //NVIC_DisableIRQ(USBD_IRQn);
}

#endif